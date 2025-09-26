# Relatório – Lista 01 (SO2)

---

## Exercício 1 — Explicação e Como Rodar

**Explicação (resumo):** Simulação concorrente com threads representando participantes; largada sincronizada e controle de estado protegido por lock.

**Como rodar (extraído do topo do código):**
#como rodar? 
# Execução única
#     python ex01.py

---

## Exercício 2 — Explicação e Como Rodar

**Explicação (resumo):** Produtor–consumidor com buffer limitado; uso de semáforos/Conditions para cheios/vazios e medição de throughput.

**Como rodar (extraído do topo do código):**
#como rodar? 
#     python ex02.py -b 8 -P 2 -C 2 -d 10 --pmin 1 --pmax 5 --cmin 1 --cmax 5

---

## Exercício 3 — Explicação e Como Rodar

**Explicação (resumo):** Transferências entre contas com soma total preservada; mostra efeitos de races no modo sem lock e correção com travas por conta.

**Como rodar (extraído do topo do código):**
#como rodar? 
python ex03.py -m 32 -t 8 -n 200000 -i 1000
python ex03.py -m 32 -t 8 -n 200000 -i 1000 --no-lock

---

## Exercício 4 — Explicação e Como Rodar

**Explicação (resumo):** Pipeline em múltiplos estágios conectados por filas seguras (captura → processamento → gravação) com desligamento por poison pill.

**Como rodar (extraído do topo do código):**
#como rodar? 
python ex04.py -n 1000 -c1 8 -c2 8 --cap-ms 1,4 --proc-ms 2,5 --grav-ms 1,3

---

## Exercício 5 — Explicação e Como Rodar

**Explicação (resumo):** Pool de workers consumindo tarefas de uma fila concorrente; comandos `prime N` e `fib N` lidos de STDIN até EOF.

**Como rodar (extraído do topo do código):**
#como rodar? 
# 4 workers; imprime apenas resumo
# printf "prime 1000003\nfib 40\nprime 17\n" | python ex05.py -w 4 --quiet
#
# Mostra cada resultado
# printf "prime 97\nprime 221\nfib 45\nfib 10\n" | python ex05.py -w 2

---

## Exercício 6 — Explicação e Como Rodar

**Explicação (resumo):** Map/Reduce de arquivo grande (soma/histograma) com particionamento por blocos e redução final.

**Como rodar (extraído do topo do código):**
#como rodar? 
# Execução única
#     python ex06.py data.txt -p 4
#
# Sweep com speedup (1,2,4,8) + verificação de corretude
#     python ex06.py data.txt --sweep

---

## Exercício 7 — Explicação e Como Rodar

**Explicação (resumo):** Jantar dos Filósofos: prevenção de deadlock por ordem total ou por semáforo (garçom).

**Como rodar (extraído do topo do código):**
#como rodar? 
python ex07.py --n 5 --mode order --duration 10
python ex07.py --n 5 --mode sem --limit 4 --duration 10

---

## Exercício 8 — Explicação e Como Rodar

**Explicação (resumo):** Produtor–consumidor com rajadas (bursts) e backpressure; coleta ocupação/latências.

**Como rodar (extraído do topo do código):**
# Cenário: bursts rápidos e consumidores lentos (estressa backpressure)
python ex08.py -b 32 -P 3 -C 2 -d 20 --burst-len 250 --burst-gap 400

---

## Exercício 9 — Explicação e Como Rodar

**Explicação (resumo):** Corrida de revezamento com barreira; mede rodadas por minuto sob diferentes tamanhos de equipe.

**Como rodar (extraído do topo do código):**
#como rodar? 
python ex09.py --k 5 --duration 15 --run-ms 10,30 --impl barrier
python ex09.py --sweep 2,3,4,5,8 --duration 20

---

## Exercício 10 — Explicação e Como Rodar

**Explicação (resumo):** Cenário com deadlock intencional e watchdog; correção adotando ordem total de aquisição de locks.

**Como rodar (extraído do topo do código):**
#como rodar? 
python ex10.py --mode deadlock --resources 4 --threads 4 --iters 100 --hold-ms 10,30 --wd-timeout 2.0
python ex10.py --mode ordered  --resources 4 --threads 4 --iters 100 --hold-ms 10,30
