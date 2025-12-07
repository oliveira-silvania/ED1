# ANÁLISE DE REDES COMPLEXAS DAS PUBLICAÇÕES CIENTÍFICAS DE MULHERES EM PROGRAMAS DE PÓS-GRADUAÇÃO STRICTO SENSU NAS ÁREAS STEM (2021–2023), COM BASE NA PLATAFORMA SUCUPIRA

Repositório oficial do **TCC (Trabalho de Conclusão de Curso)** apresentado ao curso de **Ciência da Computação da PUC Goiás (Pontifícia Universidade Católica de Goiás)**, sob orientação da **Profa. Maria José Pereira Dantas**, no ano **2025**.

O objetivo central deste TCC é investigar a **produção científica de mulheres** nas áreas de **Ciências Exatas e da Terra (CET)** e **Engenharias**, utilizando **modelagem de redes complexas** aplicada às informações disponibilizadas pela **Plataforma Sucupira/CAPES** referentes ao triênio **2021–2023**.

---

## 👤 Autoria  
- **Discente:** Silvania Alves Oliveira  
- **Orientadora:** Profa. Dra. Maria José Pereira Dantas  
- **Instituição:** Pontifícia Universidade Católica de Goiás (PUC Goiás)  
- **Curso:** Ciência da Computação  
- **Ano:** 2025  

---

## 🎯 Objetivos do TCC

### Objetivo geral
Analisar a participação de mulheres em programas de mestrado e doutorado nas áreas de STEM no Brasil, nos anos de 2021, 2022 e 2023, por meio de redes complexas aplicadas aos dados da Plataforma Sucupira.

### Objetivos específicos
- Extrair e organizar os dados dos programas de pós-graduação da Plataforma Sucupira, com foco nas áreas de Engenharias e CET (Ciências Exatas e da Terra).
- Construir redes complexas de coautoria, vínculos institucionais e qualidade de publicação, utilizando métricas como grau, centralidade, densidade e modularidade para identificar padrões estruturais da colaboração feminina.
- Analisar a presença, visibilidade e posição das mulheres nas redes acadêmicas, observando desigualdades de participação e influência entre instituições e áreas.
- Desenvolver um painel de BI interativo para visualização de dados estatísticos, permitindo a exploração dinâmica das informações por ano, área, instituição, tipo de vínculo e outras dimensões relevantes.

---

## 📂 Estrutura do Repositório 

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

- **Python** → integração de dados e classificação de gênero.  
- **SQL Server** → armazenamento e limpeza.  
- **Gephi** → análise e visualização das redes.  
- **GitHub** → versionamento do TCC e reprodutibilidade.  

---

## 📊 Redes analisadas no TCC

O trabalho modela e analisa três tipos de redes:

1. **Redes de coautoria**  
   - Nós = autores  
   - Arestas = coautorias  
   - Filtragem pela **primeira autoria por gênero** em CET e Engenharias.

2. **Redes de destinos de publicação**  
   - Nós = autoras e veículos (periódicos)  
   - Arestas = artigos publicados  
   - Estratos Qualis incorporados à análise.

3. **Redes de circulação institucional**  
   - Nós = instituições  
   - Arestas = vínculos de publicação (IES) dos autores ao longo dos anos.  

Cada rede possui cálculo de métricas como grau médio, densidade, modularidade, clustering, componentes e diâmetros, permitindo detectar padrões de concentração, centralidade e desigualdades de participação.

---

## 📈 Painel de Business Intelligence (BI)

O TCC também inclui o desenvolvimento de um **painel de BI interativo**, construído a partir da base consolidada em SQL Server e integrado ao Power BI. Esse painel cumpre um duplo papel:

- **Ferramenta analítica**: permite explorar de forma dinâmica os dados de produção científica, filtrando por:
  - ano (2021, 2022, 2023);  
  - área (CET, Engenharias);  
  - região e unidade da federação;  
  - instituição de ensino superior;  
  - gênero
  - estrato Qualis dos veículos de publicação;  
  - tipo de vínculo (docente, discente, egresso, colaborador externo).  

- **Validação visual das redes**: auxilia na identificação rápida da sobreposição entre **desigualdades regionais** e **desigualdades de gênero**, funcionando como um complemento visual às análises de redes complexas realizadas no Gephi.

🔗 **Link do painel de BI:**  
**[Acessar painel BI (Power BI)](COLOQUE_AQUI_O_LINK_DO_PAINEL_QUANDO_PUBLICAR)**

---

## 🔁 Reprodutibilidade

Todas as etapas — extração, limpeza, modelagem de redes e visualização — estão documentadas e podem ser replicadas usando:

- scripts SQL,  
- notebooks Python,  
- arquivos CSV de nós e arestas,  
- arquivos .gephi prontos para visualização.

---

## 📝 Documento final

O TCC completo disponibilizado em:

🔗 **[Acessar TCC Final (PDF)](COLOQUE_AQUI_O_LINK_QUANDO_PUBLICAR)**

---
