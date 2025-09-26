# Relatório – Lista 01 (SO2)

---

## Exercício 1

**Explicação:**  
Simula uma corrida de cavalos com threads, largada sincronizada e apuração de vencedor. Cada cavalo (thread) avança em passos aleatórios; o sistema registra posições, define o primeiro a cruzar e verifica a aposta do usuário com proteção contra condição de corrida.

**Decisões de sincronização:**  
- **Evento/Barreira** para largada simultânea.  
- **Mutex (Lock)** para atualizar vencedor/placar sem race.  
- Variável/flag de “vencedor” lida/escrita sob proteção de **Lock**.

**Como rodar:**  
python ex01.py

---

## Exercício 2

**Explicação:**  
Problema Produtor–Consumidor com buffer circular. Produtores inserem e consumidores removem itens de um buffer limitado; mede throughput e ocupação do buffer. Evita espera ativa.

**Decisões de sincronização:**  
- **Mutex (Lock)** para seção crítica do buffer.  
- **Semáforo de vazios/cheios** (ou **Condition not_full/not_empty**) para bloquear produção/consumo.  
- Ausência de busy-wait; sinais acordam a contraparte.

**Como rodar:**  
python ex02.py -b 8 -P 2 -C 2 -d 10 --pmin 1 --pmax 5 --cmin 1 --cmax 5

---

## Exercício 3

**Explicação:**  
Transferências entre contas feitas por múltiplas threads mantendo a soma global. Há modo correto (com travas) e incorreto (sem travas) para evidenciar corrupção por race.

**Decisões de sincronização:**  
- **Lock por conta** (granularidade fina).  
- Transferência entre duas contas adquire locks em **ordem canônica** (ex.: menor id → maior id) para **evitar deadlock**.  
- Sem locks (opcional) demonstra race e corrupção do saldo global.

**Como rodar (modo correto):**  
python ex03.py -m 32 -t 8 -n 200000 -i 1000

**Como rodar (modo incorreto):**  
python ex03.py -m 32 -t 8 -n 200000 -i 1000 --no-lock

---

## Exercício 4

**Explicação:**  
Pipeline de três estágios (captura → processamento → gravação) conectados por filas com capacidade. Finalização limpa por poison pill.

**Decisões de sincronização:**  
- **queue.Queue(capacity)** (internamente com **Lock + Conditions**) para backpressure natural.  
- **Poison pill** para encerramento ordenado sem deadlock.  
- Sem seções críticas manuais além das filas (a fila já provê exclusão mútua).

**Como rodar:**  
python ex04.py -n 1000 -c1 8 -c2 8 --cap-ms 1,4 --proc-ms 2,5 --grav-ms 1,3

---

## Exercício 5

**Explicação:**  
Pool fixo de workers consumindo tarefas de uma fila concorrente. Lê da STDIN comandos `prime N` e `fib N`; opção de modo silencioso.

**Decisões de sincronização:**  
- **queue.Queue()** para distribuição de tarefas (Lock interno + Conditions).  
- **Sentinelas (None)** para sinalizar término a cada worker.  
- Somatórios/contadores protegidos por **Lock** ou feitos thread-local + redução final.

**Como rodar (resumido):**  
printf "prime 1000003\nfib 40\nprime 17\n" | python ex05.py -w 4 --quiet

**Como rodar (detalhado):**  
printf "prime 97\nprime 221\nfib 45\nfib 10\n" | python ex05.py -w 2

---

## Exercício 6

**Explicação:**  
Map/Reduce de arquivo grande (inteiros). Particiona o arquivo em blocos alinhados em `\n`, processa soma/histograma por thread e reduz no final; mede speedup.

**Decisões de sincronização:**  
- **Sem compartilhamento fino** durante o map: cada thread acumula **locais**.  
- **Reduce** na thread principal (sem Lock) ou fusão com **Lock** breve caso fusão seja concorrente.  
- Controle de início/fim via **Barrier** opcional para medir tempo consistente.

**Como rodar (execução única):**  
python ex06.py data.txt -p 4

**Como rodar (sweep speedup):**  
python ex06.py data.txt --sweep

---

## Exercício 7

**Explicação:**  
Jantar dos Filósofos. Duas soluções: (1) ordem total na aquisição dos garfos; (2) semáforo “garçom” limitando filósofos simultâneos. Mede refeições/esperas.

**Decisões de sincronização:**  
- **Lock por garfo**.  
- **Solução A (ordem):** adquirir sempre na **mesma ordem global** → elimina ciclos (deadlock).  
- **Solução B (garçom):** **Semaphore(n-1)** reduz contenção e previne deadlock.

**Como rodar (ordem global):**  
python ex07.py --n 5 --mode order --duration 10

**Como rodar (semáforo/garçom):**  
python ex07.py --n 5 --mode sem --limit 4 --duration 10

---

## Exercício 8

**Explicação:**  
Produtor–Consumidor com rajadas. Backpressure controla ritmo dos produtores quando consumidores não acompanham; coleta séries de ocupação/latências.

**Decisões de sincronização:**  
- **queue.Queue(capacity)** para bloquear produtores quando buffer cheio (**not_full**), e consumidores quando vazio (**not_empty**).  
- **Semáforos/Conditions** (internos da fila) evitam busy-wait.  
- Marcações temporais protegidas por **Lock** só quando necessário.

**Como rodar:**  
python ex08.py -b 32 -P 3 -C 2 -d 20 --burst-len 250 --burst-gap 400

---

## Exercício 9

**Explicação:**  
Corrida de revezamento: equipes com K threads; cada perna só inicia quando todas as threads da equipe alcançam a barreira. Mede rodadas/min por K.

**Decisões de sincronização:**  
- **Barrier** nativa para sincronizar “pernas” da equipe.  
- Alternativa com **Condition + contador** (barreira manual) para comparar overhead.  
- Métricas coletadas com proteção por **Lock** quando atualizadas concorrentemente.

**Como rodar (execução normal):**  
python ex09.py --k 5 --duration 15 --run-ms 10,30 --impl barrier

**Como rodar (sweep K variando):**  
python ex09.py --sweep 2,3,4,5,8 --duration 20

---

## Exercício 10

**Explicação:**  
Cenário de deadlock intencional com múltiplos locks em ordens diferentes e **watchdog** que detecta ausência de progresso. Correção: impor ordem total de aquisição para remover ciclos.

**Decisões de sincronização:**  
- **Lock por recurso**; versão “com deadlock” adquire em ordens distintas para induzir ciclo.  
- **Watchdog** monitora *heartbeats*/timestamps e reporta threads/locks suspeitos (leitura sob **Lock**).  
- **Correção:** **ordem total** de aquisição (id crescente) ⇒ grafo de espera acíclico (sem deadlock).

**Como rodar (modo com deadlock):**  
python ex10.py --mode deadlock --resources 4 --threads 4 --iters 100 --hold-ms 10,30 --wd-timeout 2.0

**Como rodar (modo ordenado, sem deadlock):**  
python ex10.py --mode ordered --resources 4 --threads 4 --iters 100 --hold-ms 10,30
