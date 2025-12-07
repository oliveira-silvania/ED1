# ANÁLISE DE REDES COMPLEXAS DAS PUBLICAÇÕES CIENTÍFICAS DE MULHERES EM PROGRAMAS DE PÓS-GRADUAÇÃO STRICTO SENSU NAS ÁREAS STEM (2021–2023), COM BASE NA PLATAFORMA SUCUPIRA

Repositório oficial do **TCC (Trabalho de Conclusão de Curso)** apresentado ao curso de **Ciência da Computação da PUC Goiás (Pontifícia Universidade Católica de Goiás)**, sob orientação da **Profa. Maria José Pereira Dantas**, no ano **2025**.

O objetivo central deste TCC é investigar a **produção científica de mulheres** nas áreas de **Ciências Exatas e da Terra (CET)** e **Engenharias**, utilizando **modelagem de redes complexas** aplicada às informações disponibilizadas pela **Plataforma Sucupira/CAPES** referentes ao triênio **2021–2023**.

---

## 👤 Autoria  
- **Discente:** Silvania Alves Oliveira  
- **Orientadora:** Profa. Dra. Maria José Pereira Dantas  
- **Instituição:** PUC Goiás  
- **Curso:** Ciência da Computação  
- **Ano:** 2025  

---

## 🎯 Objetivos do TCC

### Objetivo geral
Analisar a participação de mulheres em programas de mestrado e doutorado nas áreas de STEM no Brasil, nos anos de 2021, 2022 e 2023, por meio de redes complexas aplicadas aos dados da Plataforma Sucupira.

### Objetivos específicos
- Extrair e organizar os dados da Plataforma Sucupira, com foco nas áreas de Engenharias e CET.  
- Construir redes complexas de coautoria, vínculos institucionais e destinos de publicação.  
- Utilizar métricas como grau, centralidade, densidade, componentes, clustering e modularidade.  
- Identificar padrões estruturais da colaboração feminina e desigualdades de participação.  
- Desenvolver um painel de BI interativo para exploração dos dados.  

---

## 📂 Estrutura do Repositório

A seguir está a estrutura real do repositório, conforme representada na imagem:

### **`data/`** — Bases de dados  
- **`raw/`** → dados brutos extraídos da Plataforma Sucupira (2021–2023).  
- **`processed/`** → dados tratados e prontos para análises e geração das redes.  

### **`gephi/`** — Redes complexas  
Contém três conjuntos de redes modeladas no TCC:  
- **`circulação_institucional/`**  
- **`coautoria/`**  
- **`destinos_de_publicação/`**  

Cada pasta inclui arquivos **CSV de nós e arestas** e projetos **.gephi**.

### **`notebooks/`** — Processamento e análise em Python  
Inclui:  
- **`classificação_de_genero/`** → scripts e notebooks dedicados à inferência e validação de gênero.  
- **`converter_csv_para_banco.py`** → script para importar arquivos CSV diretamente no SQL Server.

### **`sql/`** — Scripts SQL  
- **`gephi/`** → consultas auxiliares para geração de listas finais de nós e arestas.  
- **`integracao_dos_dados.sql`** → integração das bases 2021–2023, padronização e limpeza dos dados.  

### **`README.md`**  
Documento principal de descrição do projeto.

---

## ⚙️ Tecnologias utilizadas no TCC

- **Python** → integração de dados, classificação de gênero e automações.  
- **SQL Server** → armazenamento, padronização e preparação da base.  
- **Gephi** → cálculo de métricas e visualização das redes.  
- **Power BI** → criação do painel analítico interativo.  
- **GitHub** → rastreamento de versões e reprodutibilidade do pipeline.  

---

## 📊 Redes analisadas no TCC

O estudo desenvolve e analisa três redes centrais:

### **1. Rede de coautoria**
- Nós = autores  
- Arestas = relações de coautoria  
- Foco em **primeiras autorias por gênero**  

### **2. Rede de destinos de publicação**
- Nós = autoras e veículos (periódicos)  
- Arestas = relações de publicação  
- Considera o **estrato Qualis** dos periódicos  

### **3. Rede de circulação institucional**
- Nós = instituições de ensino e pesquisa  
- Arestas = vínculos entre instituições ao longo do tempo  

Cada rede contém métricas estruturais importantes como:

- Grau e grau médio  
- Densidade  
- Clustering  
- Componentes  
- Diâmetro  
- Modularidade  

Essas métricas revelam padrões de colaboração, centralidade, conectividade e desigualdades regionais e de gênero.

---

## 📈 Painel de Business Intelligence (BI)

Foi desenvolvido um **painel interativo em Power BI**, utilizando toda a base integrada e filtrável por:

- área (CET, Engenharias)  
- gênero da primeira autoria  
- estrato Qualis  
- tipo de vínculo (docente, discente, egresso, externo)  
- ano  
- instituição  
- região/estado  

### Finalidade do painel:
- Permitir uma exploração rápida e dinâmica dos dados  
- Validar visualmente padrões encontrados nas redes  
- Relacionar desigualdades regionais às desigualdades de gênero  

🔗 **Link do painel de BI:**  
**[Acessar painel BI (Power BI)](COLOQUE_AQUI_O_LINK_DO_PAINEL_QUANDO_PUBLICAR)**

---

## 🔁 Reprodutibilidade

O repositório oferece reprodutibilidade completa por meio de:

- scripts SQL,  
- notebooks Python,  
- arquivos CSV de nós e arestas,  
- arquivos `.gephi` prontos para visualização.

---

## 📝 Documento final

O TCC completo está disponível em:

🔗 **[Acessar TCC Final (PDF)](COLOQUE_AQUI_O_LINK_QUANDO_PUBLICAR)**

---
