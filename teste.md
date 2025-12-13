# Mini Sistema Operacional de Controle de Estacionamento

**Disciplina:** Sistemas Operacionais II

## Integrantes do Grupo
- **Khatlleen Hayssa Alves Pereira**
- **Isadora Rocha Costa**
- **Silvania Alves Oliveira**

---

## 1) Descrição do Projeto

Este projeto implementa um **mini sistema operacional em espaço de usuário**, desenvolvido em **C sobre Linux**, para controlar um **sistema de estacionamento simulado**.

O objetivo é aplicar, de forma integrada, conceitos de **Sistemas Operacionais II**, incluindo:
- **Threads** e execução concorrente
- **Sincronização** (mutex e variáveis de condição)
- **Escalonamento simples** (tarefa periódica)
- Comunicação entre tarefas via **memória compartilhada**
- Uso de **arquivos** (configuração e log)
- Interface de linha de comando (menu textual)

---

## 2) Estrutura do Projeto

Estrutura típica do projeto:


> Observação: ao rodar pela primeira vez, a pasta `logs/` pode ser criada automaticamente pelo `Makefile` ou pode ser criada manualmente (ver seção de compilação/execução).

---

## 3) Arquitetura e Módulos

| Módulo | Responsabilidade |
|-------|-------------------|
| `main` | Núcleo do sistema: inicialização, execução e encerramento |
| `core` | Estruturas globais (estado do sistema) e carregamento de configuração |
| `sensors` | Thread de sensores (simulação de eventos) |
| `actuators` | Atuadores: controle da cancela e contagem de vagas |
| `scheduler` | Thread de escalonamento simples (tarefa periódica) |
| `logger` | Thread de log (produtor–consumidor) |
| `interface` | Menu textual e comandos do usuário |

---

## 4) Funcionamento do Sistema (Regras)

### 4.1 Estado Inicial
- O estacionamento **sempre inicia vazio**
- `vagas_livres = max_vagas`
- A **cancela inicia fechada**
- Ao encerrar e iniciar novamente, o estacionamento **volta a ficar vazio**

### 4.2 Regras da Cancela
- 🔒 **Cancela fechada**
  - **Não entram carros**
  - **Só saem carros se houver carros no estacionamento**
- 🔓 **Cancela aberta**
  - Carros podem **entrar e sair** livremente

> A simulação de entrada/saída é feita por uma thread de sensores que gera eventos automaticamente.

---

## 5) Concorrência (Threads) e Tarefas

O sistema possui tarefas concorrentes:

- **Thread de sensores** (`sensors`)
  - Executa automaticamente a cada `sensor_interval_ms`
  - Simula eventos (entrada/saída/nada), respeitando o estado da cancela
- **Thread do scheduler** (`scheduler`)
  - Executa uma tarefa periódica de monitoramento (status do sistema)
- **Thread do logger** (`logger`)
  - Implementa fila de mensagens e grava eventos em arquivo (`logs/run.log`)
  - Usa mutex/condição no modelo produtor–consumidor para evitar perda de mensagens
- **Interface do usuário** (`interface`)
  - Menu reativo a comandos (entrada do teclado)

---

## 6) Comunicação e Sincronização

- Comunicação entre tarefas via **memória compartilhada** (estrutura global do sistema)
- **Mutex** para proteger variáveis compartilhadas (ex.: `vagas_livres`)
- **Variáveis de condição** no logger para sincronizar escrita/leitura da fila (evita perda quando fila lota)
- **Mutex de impressão** para evitar mensagens embaralhadas no terminal (quando aplicável)

---

## 7) Arquivo de Configuração

O sistema lê parâmetros do arquivo:

📄 `config/config.txt`

Exemplo:
```txt
sensor_interval_ms=500
max_vagas=50
hora_abertura=08:00
hora_fechamento=22:00
log_level=INFO
# Como Rodar o Projeto (Passo a Passo)

⚠️ **IMPORTANTE:**  
Todos os comandos devem ser executados **dentro da pasta `SO2/`** (pasta raiz do projeto).

---

## Passo 1 – Abrir o terminal
Abra um terminal no Linux.

---

## Passo 2 – Entrar na pasta do projeto
```bash
cd SO2

---

## Passo 3 – Limpar compilações antigas
make clean

---

## Passo 4 – Compilar o projeto
make

---

## Passo 5 – Executar o sistema
make run

---

## Passo 6 – Ver carros entrando e saindo (em tempo real)
cd SO2
tail -f logs/run.log
