# 📂 `scripts/` — Predição de Gênero + Atualização no SQL Server (rondon florest)

Documento técnico do pipeline **rondon florest** para **inferência de gênero** (CAPES/Sucupira) com **atualização direta** na tabela alvo do **SQL Server**.  
Foco em **reprodutibilidade**, **cobertura controlada por limiares**, **calibração probabilística** e **auditoria**.

> **Fluxo resumido**  
> 1) Treina **RF contextual** (features institucionais/produção)  
> 2) Treina **modelo por NOME** (TF-IDF de caracteres + **LR calibrada**)  
> 3) Monta estatísticas **Bayes (nome, UF)** e **Bayes (nome)**  
> 4) **Adapta limiares** até atingir a **meta de cobertura**  
> 5) Aplica **fallback** para garantir **100%** de cobertura  
> 6) **Escreve colunas de saída** em `STEM_Y` e registra em **LOG**  

---

## 🔧 Pré-requisitos e Esquema

**Entrada (SQL Server)**  
- Banco: `IC`  
- Tabela: `dbo.STEM_Y`  
- Chave primária: `ROW_ID`  
- Nome completo do autor: `NM_AUTOR`  
- Coluna alvo (rótulo humano): `GENERO` (`FEMININO`, `MASCULINO`, `INDETERMINADO`)

**Features mínimas para RF contextual**  
`NM_AREA_BASICA`, `NM_MODALIDADE_PROGRAMA`, `NM_GRAU_PROGRAMA`, `DS_SITUACAO_PROGRAMA`,  
`NM_REGIAO`, `SG_UF_PROGRAMA`, `DS_DEPENDENCIA_ADMINISTRATIVA`, `NM_ENTIDADE_ENSINO`,  
`NM_PROGRAMA_FOMENTO`, `NM_FINANCIADOR`, `NM_NATUREZA_FINANCIAMENTO`,  
`NM_TIPO_PRODUCAO`, `NM_SUBTIPO_PRODUCAO`, `TP_AUTOR`

**Saídas gravadas em `STEM_Y`**  
- `GENERO_PRED` (classe prevista)  
- `PROB_GENERO_PRED` (confiança associada)  
- `FOI_IMPUTADO` (0/1)  
- `MODO_IMPUTACAO` (`RF`, `NOME_ML`, `NOME_UF`, `NOME_BR`, `FALLBACK`)  
- `CONF_FONTE` (`RF`, `ML`, `BAYES_UF`, `BAYES_BR`, `FALLBACK`)  
- `IMPUTACAO_FORCADA` (0/1)

**Artefatos gerados (disco)**  
- `modelo_genero.joblib` (RF contextual)  
- `modelo_genero_nome.joblib` (TF-IDF char + LR **calibrada**)  
- `modelo_genero_metrics.json` (métricas RF)  
- `modelo_genero_nome_metrics.json` (métricas Nome)  
- `checkpoint_predicao.log` (log local texto)

**Tabela de auditoria (SQL)**  
- `dbo.LOG_IMPUTACAO_GENERO` (criada/alterada on-the-fly, com thresholds, cobertura, caminhos dos modelos, %fallback etc.)

---

## 🧠 Metodologia de Predição (detalhada)

### 1) **RF contextual**
- **Objetivo**: aprender padrões de gênero a partir do **contexto acadêmico** (programa, região, tipo de produção etc.).
- **Pré-processamento**: imputação da moda + One-Hot Encoding de todas as features categóricas.
- **Modelo**: `RandomForestClassifier(n_estimators=400, class_weight="balanced", n_jobs=-1)`.
- **Avaliação**: hold-out estratificado (`test_size=0.20`) com `classification_report` e `confusion_matrix` **normalizada**.
- **Uso na inferência**: para autores com `GENERO == INDETERMINADO`, a RF é aplicada **via agregação por primeiro nome**:  
  1) Extrai-se `FIRST_NAME_NORM` (normalizado, sem acentos, `A–Z`).  
  2) Para cada `FIRST_NAME_NORM`, calculam-se **features agregadas** (moda por nome) sobre o conjunto INDETERMINADO.  
  3) A RF prevê `P(y|features_agregadas)` → gera `GENERO_PRED_RF` + `PROB_GENERO_PRED_RF`.

> *Racional*: o primeiro nome “herda” um contexto típico aprendido na base rotulada (evita sparsidade por indivíduo).

---

### 2) **Modelo por NOME (TF-IDF + LR calibrada)**
- **Representação**: TF-IDF **de caracteres** em n-gramas `(2,4)` sobre `FIRST_NAME_NORM`.  
- **Classificador base**: `LogisticRegression(max_iter=2000, class_weight="balanced")`.  
- **Calibração**: `CalibratedClassifierCV(estimator=lr, method="isotonic", cv=3, n_jobs=-1)`.  
  - Corrige o **desalinhamento probabilístico** típico da LR/TF-IDF para que `P̂(y)` se aproxime de probabilidades **bem-calibradas**.  
- **Uso**: produz `GENERO_PRED_NM` + `PROB_GENERO_PRED_NM` para todos com primeiro nome disponível.

> *Por quê calibrar?* Coberturas dirigidas por **limiares** dependem de probabilidades confiáveis; a calibração melhora a relação “limiar ↔ precisão”.

---

### 3) **Bayes (nome, UF) e (nome) — com suavização**
A partir da base **rotulada** (não-INDETERMINADO), extraímos tabelas de frequências:

- **Nível UF (condicionado)**  
  Para cada par `(FIRST_NAME_NORM, SG_UF_PROGRAMA)`:
  \[
  P(F) = \frac{n_F + \alpha}{n_F + n_M + 2\alpha},\;\;
  P(M) = \frac{n_M + \alpha}{n_F + n_M + 2\alpha}
  \]
  com \(\alpha = 1.0\) (**Laplace**) e suporte mínimo `MIN_SUP_UF = 30`.  
  Classe = \(\arg\max\{P(F),P(M)\}\), **confiança** = \(\max\{P(F),P(M)\}\).

- **Nível BR (marginal)**  
  Idêntico ao anterior, mas agregando apenas por `FIRST_NAME_NORM` (suporte `MIN_SUP_BR = 10`).

> *Racional*: quando o modelo de NOME ou RF está **abaixo do limiar**, Bayes oferece sinal “frequencial” estável — primeiro específico à UF (se houver suporte), depois nacional.

---

### 4) **Adaptação de Limiares por Cobertura (target-seeking)**
Alvos e limites:
- `TARGET_COVERAGE = 0.80` (80% dos INDETERMINADO **devem** ser imputados por fontes **não-fallback**),  
- **piso** de confiança: `MIN_CONF_FLOOR = 0.65`,  
- passo: `ADAPT_STEP = 0.02`.

Ordem de aplicação (em cada iteração):
1. **RF** se `PROB_GENERO_PRED_RF ≥ THRESH_RF`,  
2. **NOME_ML** se `PROB_GENERO_PRED_NM ≥ THRESH_NOME_ML`,  
3. **NOME_UF (Bayes)** se `CONF_UF ≥ THRESH_BAYES_UF` e suporte ≥ `MIN_SUP_UF`,  
4. **NOME_BR (Bayes)** se `CONF_BR ≥ THRESH_BAYES_BR` e suporte ≥ `MIN_SUP_BR`.

Se a **cobertura corrente** < `TARGET_COVERAGE`, reduz-se limiares nesta ordem **BR → UF → ML → RF**, respeitando o **piso**.  
Cada ciclo **limpa** as marcações e **reaplica** a cascata com os limiares atualizados, até:  
- alcançar a meta, **ou**  
- atingir o limite de 20 iterações, **ou**  
- tocar o piso de todos os limiares.

> *Métrica de cobertura*: sobre o conjunto INDETERMINADO, \(\text{cov}=\frac{\#\{\text{FOI\_IMPUTADO=True}\}}{\#\{\text{INDETERMINADO}\}}\).

---

### 5) **Fallback para 100%**
Para qualquer remanescente (ainda não imputado):
- Define-se a **classe majoritária** do treino contextual (F/M).  
- Se houver probabilidade do modelo de NOME, **herda-se** essa confidence; senão, usa-se **0.51**.  
- Marcações: `MODO_IMPUTACAO="FALLBACK"`, `CONF_FONTE="FALLBACK"`, `IMPUTACAO_FORCADA=1`.

> *Interpretação*: garante completude; entradas de fallback ficam **auditáveis** e **separáveis** para re-rotulação humana posterior.

---

## 🗂️ Arquitetura de Dados e Escrita no SQL

1) **Leitura total** de `dbo.STEM_Y` → `df_all`.  
2) **Deduplicação/coalescência** de colunas para evitar o erro  
   *“Selected columns are not unique”* (função `coalesce_duplicate_columns`).  
3) **Criação de staging** aleatória (`STEM_YSTAGING<uuid>`) via `to_sql(if_exists="replace")` com `fast_executemany=True`.  
4) **UPDATE…JOIN** de staging → `STEM_Y`.  
5) **DROP** de staging e **INSERT** de um registro em `dbo.LOG_IMPUTACAO_GENERO` com:
   - thresholds finais, meta e cobertura alcançada,  
   - totais de nulos, imputados, **forçados** e **%forçados**,  
   - caminhos dos artefatos (`.joblib`/`.json`).

> **Permissões exigidas**: `ALTER TABLE`, `CREATE TABLE`, `INSERT`, `UPDATE`, `DROP` no schema de destino.

---

## 📈 Métricas Exportadas

- **RF**: classes, relatório (precision/recall/F1 por classe, macro/weighted), matriz de confusão **normalizada**, meta-dados do treino.  
- **NOME (LR calibrada)**: classes, `ngram_range`, relatório e matriz de confusão.  
- **Cobertura operacional**: cobertura final sobre INDETERMINADO, quantidade e percentual de **fallback**.

---

## 🔒 Ética, Privacidade e Uso Responsável

- A inferência é **probabilística** e pode conter vieses (nome, UF, contexto institucional).  
- **Nunca substituir** rótulos humanos já validados sem justificativa/documentação.  
- **Separar** análises com `IMPUTACAO_FORCADA=1` e/ou `CONF_FONTE='FALLBACK'`.  
- **Documentar** thresholds e versões de modelo (registradas no LOG) para reprodutibilidade e auditoria.

---

## ▶️ Como Executar

1. **Configurar ODBC** para SQL Server (Driver *ODBC Driver 17 for SQL Server*) e garantir **Trusted_Connection**.  
2. **Instalar dependências** (exemplo):
   ```bash
   pip install numpy pandas scikit-learn sqlalchemy pyodbc joblib
