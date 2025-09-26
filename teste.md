# Relatório – Lista 01 (SO2)

---

## Exercício 1

**Explicação:**  
Este exercício simula uma corrida de cavalos utilizando threads. Cada cavalo é representado por uma thread que percorre a pista de forma independente, mas a largada é sincronizada para que todos comecem juntos. O programa controla a posição de cada cavalo e determina o vencedor. Há proteção contra condições de corrida usando locks, especialmente no momento de registrar o primeiro colocado. O usuário pode apostar em um cavalo, e ao final o programa verifica se a aposta estava correta.

**Como rodar?**   
python ex01.py

---

## Exercício 2

**Explicação:**  
Implementa o clássico problema Produtor–Consumidor com buffer circular. Diversos produtores inserem itens no buffer enquanto consumidores os retiram. A coordenação é feita usando semáforos e locks, evitando race conditions e espera ativa. O programa mede métricas como throughput (itens/segundo) e ocupação média do buffer. A variação no tamanho do buffer impacta diretamente o desempenho.

**Como rodar?**   
python ex02.py -b 8 -P 2 -C 2 -d 10 --pmin 1 --pmax 5 --cmin 1 --cmax 5

---

## Exercício 3

**Explicação:**  
Simula transferências de valores entre contas bancárias, realizadas por múltiplas threads. Cada transferência envolve débito em uma conta e crédito em outra, sempre garantindo que o saldo global se mantenha constante. O programa pode ser executado em dois modos: correto (com locks por conta) e incorreto (sem locks). No modo incorreto, ocorre race condition que pode corromper o saldo global, evidenciando a importância da sincronização.

**Como rodar?**  
python ex03.py -m 32 -t 8 -n 200000 -i 1000  
python ex03.py -m 32 -t 8 -n 200000 -i 1000 --no-lock

---

## Exercício 4

**Explicação:**  
Este exercício modela um pipeline de três estágios: captura, processamento e gravação. Cada estágio é implementado como uma thread que se comunica com o próximo por meio de filas com capacidade limitada. Quando um estágio produz mais rápido do que o seguinte consome, ocorre backpressure, forçando a sincronização natural. A finalização ocorre de forma limpa através de mensagens especiais (poison pills).

**Como rodar?**  
python ex04.py -n 1000 -c1 8 -c2 8 --cap-ms 1,4 --proc-ms 2,5 --grav-ms 1,3

---

## Exercício 5

**Explicação:**  
Implementa um pool de threads fixo que consome tarefas de uma fila concorrente. As tarefas são lidas da entrada padrão (STDIN) até EOF e podem ser do tipo `prime N` (verificação de primalidade) ou `fib N` (cálculo de Fibonacci). Cada worker processa uma tarefa por vez e registra o resultado. O programa permite suprimir a saída detalhada, mostrando apenas o resumo final das execuções.

**Como rodar?**  
printf "prime 1000003\nfib 40\nprime 17\n" | python ex05.py -w 4 --quiet  
printf "prime 97\nprime 221\nfib 45\nfib 10\n" | python ex05.py -w 2

---

## Exercício 6

**Explicação:**  
Faz a leitura de um arquivo grande contendo números inteiros e aplica um modelo de processamento paralelo no estilo Map/Reduce. O arquivo é particionado em blocos, cada thread calcula localmente somas e histogramas, e o resultado é reduzido pela thread principal. O programa mede o speedup obtido com diferentes números de threads, comparando execução sequencial e paralela.

**Como rodar?**    
python ex06.py data.txt -p 4  
python ex06.py data.txt --sweep

---

## Exercício 7

**Explicação:**  
Resolve o problema do Jantar dos Filósofos, onde filósofos competem por garfos (recursos) para comer. São apresentadas duas soluções: (1) impor uma ordem global na aquisição de garfos, o que elimina deadlocks, e (2) usar um semáforo que limita o número de filósofos simultaneamente, atuando como um “garçom”. O programa mede estatísticas de refeições e tempos de espera, evidenciando o impacto da sincronização.

**Como rodar?**   
python ex07.py --n 5 --mode order --duration 10  
python ex07.py --n 5 --mode sem --limit 4 --duration 10

---

## Exercício 8

**Explicação:**  
É uma variação do Produtor–Consumidor, mas agora simulando rajadas (bursts) de produção seguidas de intervalos de ociosidade. O buffer limitado e o mecanismo de backpressure garantem que os produtores desacelerem quando o consumo não acompanha. O programa gera estatísticas sobre a ocupação do buffer ao longo do tempo, permitindo observar a estabilização e a latência.

**Como rodar?**  
python ex08.py -b 32 -P 3 -C 2 -d 20 --burst-len 250 --burst-gap 400

---

## Exercício 9

**Explicação:**  
Simula uma corrida de revezamento em que cada equipe é formada por K threads. As threads de uma equipe precisam sincronizar-se em uma barreira para liberar a próxima perna da corrida. O programa mede quantas rodadas completas são concluídas por minuto, variando o tamanho da equipe. Assim, observa-se como o custo de sincronização cresce com o aumento de K.

**Como rodar?**  
python ex09.py --k 5 --duration 15 --run-ms 10,30 --impl barrier  
python ex09.py --sweep 2,3,4,5,8 --duration 20

---

## Exercício 10

**Explicação:**  
Mostra um cenário proposital de deadlock entre threads que adquirem locks em ordens distintas. Uma thread “watchdog” monitora a execução e denuncia ausência de progresso após um tempo limite, listando os recursos e threads suspeitos. Em seguida, o problema é corrigido impondo uma ordem total de aquisição de locks, o que elimina a possibilidade de ciclos de espera e, consequentemente, o deadlock.

**Como rodar?**   
python ex10.py --mode deadlock --resources 4 --threads 4 --iters 100 --hold-ms 10,30 --wd-timeout 2.0  
python ex10.py --mode ordered  --resources 4 --threads 4 --iters 100 --hold-ms 10,30
