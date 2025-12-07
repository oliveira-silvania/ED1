# ANÁLISE DE REDES COMPLEXAS DAS PUBLICAÇÕES CIENTÍFICAS DE MULHERES EM PROGRAMAS DE PÓS-GRADUAÇÃO STRICTO SENSU NAS ÁREAS STEM (2021–2023), COM BASE NA PLATAFORMA SUCUPIRA

Repositório oficial do **Trabalho de Conclusão de Curso II (TCC)** apresentado ao curso de **Ciência da Computação da Pontifícia Universidade Católica de Goiás (PUC Goiás)**, sob orientação da **Profa. Maria José Pereira Dantas**, no período **2024/2–2025/1**.

O objetivo central deste TCC é investigar a **produção científica de mulheres** nas áreas de **Ciências Exatas e da Terra (CET)** e **Engenharias**, utilizando **modelagem de redes complexas** aplicada às informações disponibilizadas pela **Plataforma Sucupira/CAPES** referentes ao triênio **2021–2023**.

---

## 👤 Autoria  
- **Discente:** Silvania Alves Oliveira  
- **Orientadora:** Profa. Dra. Maria José Pereira Dantas  
- **Instituição:** Pontifícia Universidade Católica de Goiás (PUC Goiás)  
- **Curso:** Ciência da Computação  
- **Período:** 2024/2–2025/1  

---

## 🎯 Objetivos do TCC

### Objetivo geral
Analisar redes complexas da produção científica feminina em programas brasileiros de pós-graduação stricto sensu nas áreas STEM (com foco em CET e Engenharias), utilizando dados da Plataforma Sucupira (2021–2023).

### Objetivos específicos
- Construir um **banco de dados estruturado** a partir dos registros da Plataforma Sucupira.  
- Implementar rotinas de **classificação de gênero** baseadas em algoritmos, dicionários estatísticos e validação manual.  
- Modelar **redes de coautoria**, **redes de destinos de publicação** e **redes de circulação institucional**.  
- Calcular métricas estruturais de redes (grau, densidade, centralidades, clustering, modularidade).  
- Identificar **padrões, desigualdades ou tendências** de participação feminina na produção científica.  
- Elaborar visualizações em **Gephi** e análises descritivas complementares.  

---

## 📂 Estrutura do Repositório (somente elementos do TCC)

- **`data/`**  
  - **`raw/`** → dados brutos extraídos da Plataforma Sucupira (2021–2023).  
  - **`processed/`** → dados tratados, filtrados e integrados (CET + Engenharias).  

- **`sql/`**  
  Scripts utilizados para:
  - criação das tabelas normalizadas;  
  - integração dos anos 2021–2023;  
  - geração de arquivos de nós e arestas para o Gephi.  

- **`notebooks/`**  
  Notebooks Python usados para:
  - classificação de gênero;  
  - limpeza de dados;  
  - identificação de padrões.  

- **`gephi/`**  
  Arquivos de projeto (.gephi) e insumos (CSV de nós/arestas) das redes analisadas no TCC.  

- **`reports/`**  
  - Versão final do TCC em PDF.  
  - Resumo expandido e materiais complementares.  

---

## ⚙️ Tecnologias utilizadas no TCC

- **Python** → limpeza, integração de dados e classificação de gênero.  
- **SQL Server** → armazenamento e pré-processamento dos dados Sucupira.  
- **Gephi** → análise e visualização das redes.  
- **GitHub** → versionamento do TCC e reprodutibilidade.  

---

## 📊 Redes analisadas no TCC

O trabalho modela e analisa três tipos de redes:

1. **Redes de coautoria**  
   - Nós = autores  
   - Arestas = coautorias  
   - Filtragem pela **primeira autoria feminina** em CET e Engenharias.

2. **Redes de destinos de publicação**  
   - Nós = autoras e veículos (periódicos)  
   - Arestas = artigos publicados  
   - Estratos Qualis incorporados à análise.

3. **Redes de circulação institucional**  
   - Nós = instituições  
   - Arestas = vínculos de publicação dos autores ao longo dos anos.  

Cada rede possui cálculo de métricas como grau médio, densidade, modularidade, clustering, componentes e diâmetros, permitindo detectar padrões de concentração, centralidade e desigualdades de participação.

---

## 🔁 Reprodutibilidade

Todas as etapas — extração, limpeza, modelagem de redes e visualização — estão documentadas e podem ser replicadas usando:

- scripts SQL,  
- notebooks Python,  
- arquivos CSV de nós e arestas,  
- arquivos .gephi prontos para visualização.

---

## 📝 Documento final

O TCC completo está disponível em:

📄 **`reports/TCC_FINAL.pdf`**  

---

Se desejar, posso também:

✅ gerar a **versão em inglês** do README  
✅ criar um **README com visual mais profissional** (badges, ícones, seções expandidas)  
✅ gerar **figuras das redes** para colocar no GitHub  
✅ criar um **template automatizado** de organização do repositório  

É só pedir!
