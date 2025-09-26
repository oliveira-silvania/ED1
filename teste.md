# Relatório – Lista 01 (SO2)

---

## Exercício 1

**Explicação:**  
Simula uma corrida de cavalos com threads, largada sincronizada e apuração de vencedor. Cada cavalo (thread) avança em passos aleatórios; o sistema registra posições, define o primeiro a cruzar e verifica a aposta do usuário com proteção contra condição de corrida.

**Decisões de sincronização:**  
- **Evento/Barreira** para largada simultânea.  
- **Mutex (Lock)** para atualizar vencedor/placar sem race.  
- Flag de “vencedor” lida/escrita sob **Lock**.

**Como rodar:**  
python ex01.py

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 2

**Explicação:**  
Problema Produtor–Consumidor com buffer circular. Produtores inserem e consumidores removem itens de um buffer limitado; mede throughput e ocupação do buffer. Evita espera ativa.

**Decisões de sincronização:**  
- **Mutex (Lock)** para seção crítica do buffer.  
- **Semáforos de vazios/cheios** ou **Conditions (not_full/not_empty)**.  
- Sem busy-wait (acordar por sinalização).

**Como rodar:**  
- Execução única:
python ex02.py -b 8 -P 4 -C 4 -d 15 --pmin 1 --pmax 5 --cmin 1 --cmax 5
  
- Experimento variando o buffer:
python ex02.py --sweep 1,2,4,8,16,32 -P 4 -C 4 -d 15 --pmin 1 --pmax 5 --cmin 1 --cmax 5
  
**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 3

**Explicação:**  
Transferências entre contas feitas por múltiplas threads mantendo a soma global. Há modo correto (com travas) e incorreto (sem travas) para evidenciar corrupção por race.

**Decisões de sincronização:**  
- **Lock por conta** (granularidade fina).  
- Aquisição em **ordem canônica** (id menor → id maior) para **evitar deadlock**.  
- Modo sem lock demonstra race/violação de invariante.

**Como rodar (modo correto):**  
python ex03.py -m 32 -t 8 -n 200000 -i 1000

**Como rodar (modo incorreto):**  
python ex03.py -m 32 -t 8 -n 200000 -i 1000 --no-lock

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 4

**Explicação:**  
Pipeline de três estágios (captura → processamento → gravação) conectados por filas com capacidade. Finalização limpa por poison pill.

**Decisões de sincronização:**  
- **queue.Queue(capacity)** (Lock + Conditions internos) para backpressure.  
- **Poison pill** para desligamento ordenado sem deadlock.  
- Sem seções críticas manuais além das filas.

**Como rodar:**  
python ex04.py -n 1000 -c1 8 -c2 8 --cap-ms 1,4 --proc-ms 2,5 --grav-ms 1,3

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 5

**Explicação:**  
Pool fixo de workers consumindo tarefas de uma fila concorrente. Lê da STDIN `prime N`/`fib N` até EOF; resumo final opcional.

**Decisões de sincronização:**  
- **queue.Queue()** para distribuição de tarefas (Lock + Conditions).  
- **Sentinelas** para sinalizar término aos workers.  
- Contadores/sumários sob **Lock** ou redução final a partir de parciais locais.

**Como rodar (resumido):**  
printf "prime 1000003\nfib 40\nprime 17\n" | python ex05.py -w 4 --quiet

**Como rodar (detalhado):**  
printf "prime 97\nprime 221\nfib 45\nfib 10\n" | python ex05.py -w 2

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 6

**Explicação:**  
Map/Reduce de arquivo grande (inteiros). Particiona por blocos alinhados em `\n`, processa soma/histograma por thread e reduz no final; mede speedup.

**Decisões de sincronização:**  
- **Sem compartilhamento fino** no map: acumuladores **locais** por thread.  
- **Reduce** serial na principal (sem Lock) ou fusão concorrente com **Lock** curto.  
- **Barrier** opcional para tempos consistentes.

**Como rodar (execução única):**  
python ex06.py data.txt -p 4

**Como rodar (sweep speedup):**  
python ex06.py data.txt --sweep

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 7

**Explicação:**  
Jantar dos Filósofos. Duas soluções: (A) ordem total de garfos; (B) semáforo “garçom” limitando filósofos simultâneos. Mede refeições/esperas.

**Decisões de sincronização:**  
- **Lock por garfo**.  
- **Ordem total** elimina ciclos (deadlock).  
- **Semaphore(n-1)** (“garçom”) previne deadlock e reduz contenção.

**Como rodar (ordem global):**  
python ex07.py --n 5 --mode order --duration 10

**Como rodar (semáforo/garçom):**  
python ex07.py --n 5 --mode sem --limit 4 --duration 10

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 8

**Explicação:**  
Produtor–Consumidor com rajadas. Backpressure controla ritmo produtor quando consumo não acompanha; coleta séries de ocupação/latência.

**Decisões de sincronização:**  
- **queue.Queue(capacity)** bloqueia produtor em **not_full** e consumidor em **not_empty**.  
- **Conditions** internas evitam busy-wait.  
- Métricas protegidas por **Lock** quando agregadas.

**Como rodar:**  
python ex08.py -b 32 -P 3 -C 2 -d 20 --burst-len 250 --burst-gap 400

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 9

**Explicação:**  
Corrida de revezamento: equipes com K threads; cada perna só inicia quando todas alcançam a barreira. Mede rodadas/min por K.

**Decisões de sincronização:**  
- **Barrier** nativa para sincronizar “pernas”.  
- Alternativa com **Condition + contador** (barreira manual) para comparação.  
- Atualizações de métricas sob **Lock**.

**Como rodar (execução normal):**  
python ex09.py --k 5 --duration 15 --run-ms 10,30 --impl barrier

**Como rodar (sweep K variando):**  
python ex09.py --sweep 2,3,4,5,8 --duration 20

**Evidências de execução (cole aqui seus prints/logs):**

---

## Exercício 10

**Explicação:**  
Cenário de deadlock intencional com múltiplos locks em ordens diferentes e **watchdog** que detecta ausência de progresso. Correção: impor ordem total de aquisição para remover ciclos.

**Decisões de sincronização:**  
- **Lock por recurso**; modo “deadlock” adquire em ordens distintas (ciclo).  
- **Watchdog** monitora heartbeats/timestamps e relata threads/locks suspeitos (leitura sob **Lock**).  
- **Ordem total** de aquisição (id crescente) ⇒ grafo de espera acíclico.

**Como rodar (modo com deadlock):**  
python ex10.py --mode deadlock --resources 4 --threads 4 --iters 100 --hold-ms 10,30 --wd-timeout 2.0

**Como rodar (modo ordenado, sem deadlock):**  
python ex10.py --mode ordered --resources 4 --threads 4 --iters 100 --hold-ms 10,30

**Evidências de execução (cole aqui seus prints/logs):**
