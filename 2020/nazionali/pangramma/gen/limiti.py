MIN_N = 1
MAX_N = 9000000
MIN_K = 1
MAX_K = 9000000

MOD = 46337

subtasks = [
    dict(),

    # Casi d'esempio.
    dict(),
    # $K = 2$.
    dict(MAX_K=2,MAX_N=1000000),
    # $N \le 30$
    dict(MAX_N=30),
    # $N \le 300$
    dict(MAX_N=300),
    # $N \le 5000$
    dict(MAX_N=5000),
    # Nello striscione c'è almeno un pangramma \textit{eteroletterale}.
    dict(MAX_N=1000000),
    # Ogni pangramma è lungo al massimo 60
    dict(MAX_N=1000000),
    # Il numero di evidenziazioni minime è minore di $10^9$.
    dict(MAX_N=1000000),
    # $N \le 500000$
    dict(MAX_N=500000),
    # $N \le 1000000$
    dict(MAX_N=1000000),
    # Nessuna limitazione specifica.
    dict(MAX_N=5000000),
    dict()
]
