# 📂 Pasta `data/raw`

Esta pasta armazena os **dados brutos (raw)** utilizados no projeto de Iniciação Científica:  
> **A INCLUSÃO DE MULHERES NA CIÊNCIA BRASILEIRA EM ÁREAS DE STEM: REPOSITÓRIO DE DADOS, ANÁLISES ESTATÍSTICAS E MODELAGENS QUE IDENTIFIQUEM PADRÕES OU TENDÊNCIAS**

Os arquivos aqui presentes são **metadados oficiais da CAPES (2021–2024)**, extraídos do **Banco de Metadados da Plataforma Sucupira**.  
Estes documentos descrevem a estrutura, variáveis e periodicidade de atualização dos dados homologados pelos **Programas de Pós-Graduação (PPGs)** no Brasil.

🔗 Catálogo oficial: [https://metadados.capes.gov.br/index.php](https://metadados.capes.gov.br/index.php)

---

## 📑 Arquivos disponíveis

### 1. Produção Intelectual
- **Arquivo:** `producao_intelectual.pdf`
- **Descrição:** Metadados das produções intelectuais dos PPGs (bibliográficas, técnicas e artísticas).
- **Variáveis principais:** programa, instituição, título da produção, tipo/subtipo, área de concentração, linha de pesquisa, projeto, ISSN (quando aplicável), vínculo com TCC.
- **Registros (2021–2023):** ~3,38 milhões  
  - Bibliográfica: 1,89M  
  - Técnica: 1,47M  
  - Artístico-cultural: 23k:contentReference[oaicite:0]{index=0}

---

### 2. Autores da Produção Intelectual
- **Arquivo:** `autor_producao_intelectual.pdf`
- **Descrição:** Identificação e vínculos dos autores das produções intelectuais.
- **Variáveis principais:** nome do autor, tipo de vínculo (docente, discente, egresso, pós-doc, externo), área de conhecimento, país, tempo de egresso.
- **Registros (2021–2023):** ~31,9 milhões:contentReference[oaicite:1]{index=1}

---

### 3. Financiadores de Projetos
- **Arquivo:** `financiadores.pdf`
- **Descrição:** Metadados sobre financiadores de projetos vinculados aos PPGs.
- **Variáveis principais:** nome e natureza do financiador, programa de fomento, país de origem, vínculo com programa/instituição.
- **Registros (2021–2023):**  
  - 2021 → 167.959 registros (109.808 projetos, 4.424 PPGs, 431 IES)  
  - 2022 → 170.027 registros (110.939 projetos, 4.362 PPGs, 432 IES)  
  - 2023 → 170.624 registros (110.743 projetos, 4.407 PPGs, 434 IES):contentReference[oaicite:2]{index=2}

---

### 4. Programas de Pós-Graduação
- **Arquivo:** `programas.pdf`
- **Descrição:** Informações sobre os Programas de Pós-Graduação stricto sensu no Brasil.
- **Variáveis principais:** área de conhecimento, área de avaliação, instituição, município, UF, conceito CAPES, modalidade (acadêmico/profissional), situação do programa.
- **Registros (2021–2023):**  
  - 2021 → 4.709 PPGs em 473 IES  
  - 2022 → 4.594 PPGs em 476 IES  
  - 2023 → 4.659 PPGs em 477 IES:contentReference[oaicite:3]{index=3}

---

## ⚠️ Observações
- Estes documentos são **metadados descritivos**, não os datasets em formato tabular.
- Os dados brutos devem ser tratados e transformados antes das análises → resultados ficam em [`data/processed`](../processed).
- Atualizações: os metadados são **anuais**, podendo ter revisões em função do calendário da CAPES.
- Em caso de múltiplas versões homologadas, considera-se sempre a **última versão** publicada pela CAPES.

---

## 📂 Estrutura da pasta

