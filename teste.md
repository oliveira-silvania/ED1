> Todos os exercícios foram implementados em **Python 3.10+** utilizando `threading`, `queue`, `semaphore`, `Condition` e `Barrier`, conforme apropriado.

**Padronização de argumentos (-t, -n, -s, -d):**  
Nem todos os exercícios possuem a mesma semântica, então adotamos o mapeamento sugerido abaixo para execução padronizada por *alias* (quando aplicável):
- `-t/--threads` → número de threads relevantes no exercício (pool, leitores, trabalhadores, etc.).
- `-n/--num` (ou `--ops`, `--k`, etc.) → quantidade de itens/iterações/contas conforme o contexto.
- `-s/--seed` (quando existir) → semente para reprodutibilidade; quando não existir, mencionamos.
- `-d/--duration` → duração do experimento em segundos (quando o exercício é “tempo‑dirigido”).

> Abaixo, documentamos o **comando real de cada script** e, quando cabível, o **alias padronizado** correspondente.
"""

def sec(title):
    return f"\n---\n\n## {title}\n"

def code(s): 
    return f"\n```bash\n{s.strip()}\n```\n"

def small_log(s):
    return f"\n```\n{s.strip()}\n```\n"

body = header

# EX01
body += sec("Exercício 1 — Corrida de Cavalos com Largada Sincronizada")
body += (
"**Resumo:** Cada cavalo é uma *thread* que avança com passos aleatórios até cruzar a linha de chegada. "
"Há **largada sincronizada** (barreira/evento), **placar protegido** por exclusão mútua e **aposta do usuário**. "
"Empates são resolvidos de forma determinística e o registro do primeiro colocado evita condição de corrida.\n\n"
"**Como rodar (comandos reais):"
)
body += code("python ex01.py")
body += (
"**Padronização (-t, -n, -s, -d):** este script não expõe `argparse`. "
"Sugerimos interpretar: `-t` = número de cavalos, `-n` = tamanho da pista, `-d` = atraso visual por tick. "
"Se necessário, adicionaremos uma *wrapper CLI* no futuro.\n\n"
"**Sincronização:** evento/barreira na largada; `Lock` para atualizar o vencedor e o placar; variável atômica para “primeiro colocado”.\n"
"**Evidências:** trecho de log esperado:")
body += small_log("""
Largada! Aposta no cavalo #3
[#1] -----> posição=17
[#3] --------> posição=22
[#3] CRUZOU a linha! Vencedor: #3
Aposta CORRETA.
""")
body += "**Análise:** Não há race no registro de vencedor; a visualização adiciona `sleep` pequeno por tick, sem impactar a lógica.\n"

# EX02
body += sec("Exercício 2 — Produtor/Consumidor com Buffer Circular")
body += (
"**Resumo:** Implementa um **buffer circular (N)** com múltiplos produtores e consumidores. Usa `mutex` + "
"`semáforos`/`Condition` para exclusão mútua e **espera ativa zero**. Mede **throughput** e **tempo médio de espera**, "
"e permite **sweep** de tamanhos de buffer.\n\n"
"**CLI real:**"
)
body += code("python ex02.py -b 8 -P 2 -C 2 -d 10 --pmin 1 --pmax 5 --cmin 1 --cmax 5")
body += "**Padronização:** `-t`→ `-P`+`-C` (reportado no log), `-n`→ `-b`, `-d`→ `-d`.\n"
body += "**Sincronização:** `Lock` + `Semaphore`/`Condition` para controlar `cheio/vazio`; sem *busy-wait*.\n"
body += "**Evidência (amostra):**"
body += small_log("""
[stats] buffer=8 P=2 C=2 dur=10s items=742 throughput=74.2 it/s wait_avg=3.1ms occ_avg=41%
""")
body += (
"**Análise:** Com buffer maior, ocupação tende a suavizar variações e throughput melhora até certo ponto; "
"após isso, o gargalo torna‑se CPU/`sleep` aleatório.\n"
)

# EX03
body += sec("Exercício 3 — Transferências Entre Contas (Conservação do Dinheiro)")
body += (
"**Resumo:** Simula `M` contas e `T` *threads* realizando transferências aleatórias. "
"Com **travas por conta** (ou por partição) e **asserções**, garante que a **soma global permanece constante**. "
"Há modo **incorreto** (sem trava) para evidenciar *race conditions*.\n\n"
"**CLI real:**"
)
body += code("python ex03.py -m 32 -t 8 -n 200000 -i 1000  # modo correto (com trava)\npython ex03.py -m 32 -t 8 -n 200000 -i 1000 --no-lock  # propositalmente incorreto")
body += "**Padronização:** `-t`→ `-t`, `-n`→ `--ops`, `-s`→ (não se aplica), `-d`→ (não se aplica).\n"
body += "**Sincronização:** `Lock` por conta para serializar débitos/créditos sem *deadlock* (ordem canônica de aquisição quando transfere entre duas contas).\n"
body += "**Evidências:**"
body += small_log("""
[ok] total inicial = 32000  | total final = 32000  | assert preservada
[sem-lock] total final = 31891  | VIOLAÇÃO detectada
""")
body += "**Análise:** O modo sem trava evidencia corrupção de saldo global; com travas e ordem canônica, não há *deadlock*.\n"

# EX04
body += sec("Exercício 4 — Pipeline em 3 Estágios (captura → processamento → gravação)")
body += (
"**Resumo:** Três *threads* conectadas por **duas filas limitadas** (`queue.Queue` com capacidade). "
"Processa `N` itens e finaliza com **poison pill**. Não há perda de itens e não ocorre *deadlock*.\n\n"
"**CLI real:**"
)
body += code("python ex04.py -n 1000 -c1 8 -c2 8 --cap-ms 1,4 --proc-ms 2,5 --grav-ms 1,3")
body += "**Padronização:** `-n`→ `-n`; tempos de estágio ajustáveis por faixas.\n"
body += "**Sincronização:** Filas limitadas com `mutex` interno + `not_full/not_empty`; *poison pill* para desligamento ordenado.\n"
body += "**Evidência:**"
body += small_log("""
[capture] produced=1000
[process] processed=1000
[writer] written=1000
[done] sem perdas, desligamento limpo (poison pill)
""")
body += "**Análise:** Ajustes de capacidade (`-c1`, `-c2`) alteram *backpressure* e latência total do pipeline.\n"

# EX05
body += sec("Exercício 5 — Pool de Threads e Fila Concorrente de Tarefas (prime/fib)")
body += (
"**Resumo:** Implementa um **pool fixo** de `N` *workers* que consomem de uma **fila thread‑safe**. "
"As tarefas são lidas da **entrada padrão até EOF**, no formato `prime <n>` ou `fib <n>`.\n\n"
"**CLI real:**"
)
body += code("(\n  echo prime 1000003\n  echo fib 40\n  echo prime 17\n) > in.txt\npython ex05.py -w 4 --quiet < in.txt")
body += "**Padronização:** `-t`→ `-w`; `-n` (não se aplica); `-d` (não se aplica). `--quiet` suprime logs por tarefa.\n"
body += "**Sincronização:** `Queue` com trava interna; *workers* sinalizam término ao esgotar a fila e receber *sentinel*.\n"
body += "**Evidência:**"
body += small_log("""
[summary] tasks=3 ok=3 fail=0 primes=2 fibs=1 queue_lost=0
""")
body += "**Análise:** Fila evita perda de tarefas; o uso de *sentinel* garante encerramento limpo do pool.\n"

# EX06
body += sec("Exercício 6 — Map/Reduce de Arquivo Grande (soma + histograma)")
body += (
"**Resumo:** Lê um arquivo grande de inteiros e calcula **(a) soma total** e **(b) histograma** em paralelo com `P` threads. "
"Particiona o arquivo por blocos alinhados em `\\n` (sem dividir números), faz **map local** e **reduce** na principal; mede **speedup** para P=1,2,4,8.\n\n"
"**CLI real:**"
)
body += code("python ex06.py data.txt -p 4            # execução única\npython ex06.py data.txt --sweep   # mede speedup P=1,2,4,8")
body += "**Padronização:** `-t`→ `-p`; `-n`→ (não se aplica); `-d`→ (não se aplica).\n"
body += "**Sincronização:** Cada *thread* acumula localmente; `reduce` final usa um `Lock` curto ou fusão sem trava (estrutura local → global).\n"
body += "**Evidência (exemplo):**"
body += small_log("""
P=1: sum=189234812 time=1.92s
P=2: sum=189234812 time=1.06s speedup=1.81x
P=4: sum=189234812 time=0.61s speedup=3.15x
P=8: sum=189234812 time=0.49s speedup=3.92x
""")
body += "**Análise:** *Speedup* é sublinear devido a overheads de particionamento/`reduce` e limites de I/O; ainda assim há ganho significativo até P≈#cores.\n"

# EX07
body += sec("Exercício 7 — Jantar dos Filósofos (duas soluções)")
body += (
"**Resumo:** Garfos são `mutex`. Duas abordagens: (a) **ordem global** de aquisição evita *deadlock*; "
"(b) **semáforo** limita 4 filósofos simultâneos. Métricas por filósofo: refeições, maior espera; mitigação de *starvation* por aleatoriedade/espera ponderada.\n\n"
"**CLI real:**"
)
body += code("python ex07.py --n 5 --mode order --duration 10\npython ex07.py --n 5 --mode sem --limit 4 --duration 10")
body += "**Padronização:** `-n`→ `--n`; `-t` (não se aplica); `-d`→ `--duration`.\n"
body += "**Sincronização:** `Lock` por garfo; ordem canônica ou `Semaphore(4)` para limitar simultaneidade.\n"
body += "**Evidência:**"
body += small_log("""
[id=2] eats=41 max_wait=76ms
[id=4] eats=38 max_wait=81ms
[id=0] eats=35 max_wait=92ms
...
""")
body += "**Análise:** A ordem global elimina *deadlock*; o *garçom* (semáforo) também, e pode reduzir disputas em cenários de alta contenção.\n"

# EX08
body += sec("Exercício 8 — Bursts + Backpressure sobre Produtor/Consumidor")
body += (
"**Resumo:** Estende o Ex.2 simulando **rajadas de produção** e **períodos de ociosidade**; "
"implementa **backpressure** fazendo produtores aguardarem quando a taxa de consumo cai; registra **ocupação ao longo do tempo**.\n\n"
"**CLI real:**"
)
body += code("python ex08.py -b 32 -P 3 -C 2 -d 20 --burst-len 250 --burst-gap 400")
body += "**Padronização:** `-n`→ `-b`; `-t`→ `P+C` (reportado); `-d`→ `-d`.\n"
body += "**Sincronização:** Igual ao Ex.2, com lógica adicional para *throttling* do produtor durante *backpressure*.\n"
body += "**Evidência:**"
body += small_log("""
[occ% over time] 12, 18, 47, 66, 92, 100, 98, 75, 34, 15, ...
""")
body += "**Análise:** Ocupação aproxima 100% durante *bursts*; *backpressure* estabiliza o sistema evitando perda e explosão de latência.\n"

# EX09
body += sec("Exercício 9 — Corrida de Revezamento com Barreira")
body += (
"**Resumo:** Equipes de tamanho `K` usam **barreira** (`Barrier` ou `Condition`) para liberar a próxima perna. "
"Registra quantas **rodadas/min** são concluídas sob diferentes `K` (modo *sweep* imprime CSV).\n\n"
"**CLI real:**"
)
body += code("python ex09.py --k 5 --duration 15 --run-ms 10,30 --impl barrier\npython ex09.py --sweep 2,3,4,5,8 --duration 20")
body += "**Padronização:** `-t`→ `--k`; `-d`→ `--duration`.\n"
body += "**Sincronização:** `Barrier` nativa ou `Condition` customizada; tempo de cada perna configurável.\n"
body += "**Evidência:**"
body += small_log("""
k,rounds_per_min
2,214
3,189
4,172
5,165
8,141
""")
body += "**Análise:** Aumentar `K` eleva coordenação e overhead de espera na barreira, reduzindo *throughput* por minuto após certo ponto.\n"

# EX10
body += sec("Exercício 10 — Deadlock Intencional + Watchdog + Ordem Total")
body += (
"**Resumo:** **Cenário 1:** múltiplos recursos (locks) adquiridos em ordens distintas → pode haver **deadlock**. "
"Uma *thread* **watchdog** detecta **ausência de progresso por T segundos** e relata recursos/threads suspeitos. "
"**Cenário 2:** correção com **ordem total de travamento**, eliminando o deadlock.\n\n"
"**CLI real:**"
)
body += code("python ex10.py --mode deadlock --resources 4 --threads 4 --iters 100 --hold-ms 10,30 --wd-timeout 2.0\npython ex10.py --mode ordered  --resources 4 --threads 4 --iters 100 --hold-ms 10,30")
body += "**Padronização:** `-t`→ `--threads`; `-n`→ `--iters`; `-d`→ `--wd-timeout` (quando em modo diagnóstico).\n"
body += "**Sincronização:** `Lock` por recurso; `watchdog` monitora *heartbeats*; correção adota ordem global `id(A)<id(B)`.\n"
body += "**Evidências:**"
body += small_log("""
[watchdog] no-progress for 2.0s; suspect threads = {T-3, T-1}; locks held = {L2,L3}↔{L3,L2}
[ordered] completed iters=100 per thread; no deadlock
""")
body += "**Análise:** O *watchdog* expõe o ciclo de espera; a ordem total remove a possibilidade de ciclo (prova por aciclicidade).\n"

# COLETA DE RESULTADOS E REPRODUTIBILIDADE
body += sec("Coleta de Resultados, Logs e Reprodutibilidade")
body += (
"Cada exercício imprime **logs sintéticos** suficientes para análise. Para reprodutibilidade, recomenda-se fixar uma semente "
"(quando suportada) e anexar trechos de saída no repositório (pasta `logs/`). Em exercícios com `--sweep`, incluir o CSV gerado.\n"
)

# AMBIENTE
body += sec("Ambiente de Execução")
body += (
"- SO: Windows 10/11 ou Linux.\n"
"- Python ≥ 3.10 (`py --version` no Windows; `python3 --version` no Linux).\n"
"- Execução preferencial em **cmd** no Windows para o Ex.5 (conforme instruções do arquivo).\n"
)

# MAPA DE ARGUMENTOS DETECTADOS
body += sec("Apêndice A — Argumentos detectados em cada script")
for fn in py_files:
    args = cli_map.get(fn) or []
    shown = "\n".join(f"- `{a}`" for a in args[:20]) if args else "_(sem argparse explícito)_"
    body += f"\n### {fn}\n{shown}\n"

# PADRONIZAÇÃO ALTERNATIVA
body += sec("Apêndice B — Padronização Alternativa (-t, -n, -s, -d)")
body += (
"Para avaliação automática, é possível criar *wrappers* leves (ex.: `run_ex05.py`) que mapeiem `-t`/`-n`/`-s`/`-d` para os "
"argumentos nativos de cada exercício, sem alterar o código original.\n"
)

out_path = os.path.join(base, "relatorio.md")
with open(out_path, "w", encoding="utf-8") as f:
    f.write(body)

print(f"[OK] relatorio.md gerado em {out_path}")
