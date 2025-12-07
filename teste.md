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
- Construir redes complexas de coautoria, vínculos institucionais e destinos de publicação, utilizando métricas como grau, centralidade, densidade e modularidade.  
- Analisar desigualdades de participação feminina e padrões estruturais da colaboração.  
- Desenvolver um painel de BI interativo para exploração estatística dos dados.  

---

## 📂 Estrutura do Repositório

A estrutura foi reorganizada para refletir com clareza todas as etapas do TCC:

### **`data/`** — Bases de dados  
- **`raw/`** → dados brutos extraídos da Plataforma Sucupira (2021–2023).  
- **`processed/`** → dados tratados, normalizados e prontos para análise.  

### **`sql/`** — Scripts SQL  
Contém as rotinas responsáveis por:
- extração e integração dos dados do período 2021–2023;  
- **inferência de gênero** (procedimentos aplicados no banco);  
- **limpeza e padronização das tabelas**;  
- geração dos arquivos finais de **nós e arestas** utilizados no Gephi.  

### **`notebooks/`** — Scripts e análises em Python  
Inclui notebooks dedicados a:
- criação/normalização de tabelas auxiliares;  
- classificação de gênero via algoritmos;  
- análises exploratórias e conferência de consistência dos dados.  

### **`gephi/`** — Arquivos de redes  
- Projetos **.gephi**  
- Arquivos **CSV** de nós e arestas  
Usados para análise e visualização das redes de coautoria, circulação institucional e destinos de publicação.

### **`reports/`** — Documentos finais  
- Versão final do TCC (PDF)  
- Resumo expandido e materiais complementares  

---

## ⚙️ Tecnologias utilizadas no TCC

- **Python** → integração de dados, rotinas de classificação de gênero e análises auxiliares.  
- **SQL Server** → armazenamento, limpeza e processamento dos dados.  
- **Gephi** → modelagem, métricas e visualização das redes.  
- **Power BI** → painel analítico interativo.  
- **GitHub** → versionamento e reprodutibilidade da pesquisa.  

---

## 📊 Redes analisadas no TCC

O estudo modela três redes principais:

### 1. **Rede de coautoria**
- **Nós**: autores  
- **Arestas**: relações de coautoria  
- Foco na **primeira autoria por gênero** em CET e Engenharias.  

### 2. **Rede de destinos de publicação**
- **Nós**: autoras e veículos (periódicos)  
- **Arestas**: artigos publicados  
- Análise incorporando **estrato Qualis**.

### 3. **Rede de circulação institucional**
- **Nós**: instituições brasileiras de ensino e pesquisa  
- **Arestas**: vínculos de publicação ao longo dos três anos  

Cada rede possui métricas como:
- grau médio e ponderado  
- densidade  
- modularidade  
- clustering  
- componentes  
- diâmetro  

Essas métricas permitem identificar **padrões de colaboração, posições estruturais e desigualdades de participação de gênero**.

---

## 📈 Painel de Business Intelligence (BI)

O TCC inclui o desenvolvimento de um **painel de BI interativo**, que permite a exploração visual e estatística da produção científica.

### **Funções principais:**
- Filtragem por **ano**, **área**, **região**, **instituição**, **gênero**, **estrato Qualis** e **tipo de vínculo**.  
- Visualização da distribuição da produção acadêmica no Brasil.  
- Identificação de padrões regionais e temáticos.  
- Complementação das análises estruturais feitas no Gephi.

🔗 **Link do painel de BI:**  
**[Acessar painel BI (Power BI)](COLOQUE_AQUI_O_LINK_DO_PAINEL_QUANDO_PUBLICAR)**

---

## 🔁 Reprodutibilidade

Este repositório garante reprodutibilidade total do estudo, reunindo:

- scripts SQL,  
- notebooks Python,  
- CSVs de nós e arestas,  
- arquivos .gephi para visualização.  

---

## 📝 Documento final

O TCC completo está disponível em:

🔗 **[Acessar TCC Final (PDF)](COLOQUE_AQUI_O_LINK_QUANDO_PUBLICAR)**

---
