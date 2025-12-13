# 🚗 Mini Sistema Operacional de Controle de Estacionamento

**Disciplina:** Sistemas Operacionais II  
**Linguagem:** C (Linux)

---

## 👥 Integrantes do Grupo
- **Khatlleen Hayssa Alves Pereira**
- **Isadora Rocha Costa**
- **Silvania Alves Oliveira**

---

## 📌 1. Descrição do Projeto

Este projeto consiste na implementação de um **mini sistema operacional em espaço de usuário**, desenvolvido em **C sobre Linux**, para controlar um **sistema de estacionamento simulado**.

O objetivo principal é aplicar, de forma integrada, conceitos fundamentais da disciplina **Sistemas Operacionais II**, tais como:

- Execução concorrente com **threads**
- **Sincronização** com mutex e variáveis de condição
- **Escalonamento simples** por meio de tarefas periódicas
- Comunicação entre tarefas via **memória compartilhada**
- Uso de **arquivos** para configuração e registro de logs
- Interface de **linha de comando** (menu textual)

---

## 🗂️ 2. Estrutura do Projeto

```text
SO2/
├── build/
├── config/
│   └── config.txt
├── logs/
│   └── run.log
├── src/
├── Makefile
└── README.md
```

---

## 🏗️ 3. Arquitetura e Módulos

| Módulo | Responsabilidade |
|------|------------------|
| main | Inicialização, execução e encerramento |
| core | Estruturas globais e configuração |
| sensors | Simulação de eventos |
| actuators | Controle da cancela |
| scheduler | Tarefa periódica |
| logger | Registro em log |
| interface | Menu textual |

---

## ▶️ Como Rodar

```bash
cd SO2
make clean
make
make run
```

Para acompanhar os logs, em outro terminal

```bash
cd SO2
tail -f logs/run.log
```
