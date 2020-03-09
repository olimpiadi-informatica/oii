**Difficoltà: _2_**

Romeo è un grande appassionato di sport intellettuali, e adora ritrovarsi con
gli amici per seguire le competizioni internazionali più avvincenti di questo
tipo. Di recente, il gruppo di amici si è appassionato a uno sport molto
particolare. In questo gioco, un mazzo di carte numerate da $0$ a $N-1$ (dove
$N$ è dispari) viene prima mescolato, e poi le carte vengono affiancate in linea
retta sul tavolo. Ai telespettatori, per aumentare la suspence, vengono mostrati
i numeri delle carte $C_0$ , $C_1$ , ... , $C_i$ , ... , $C_{N-1}$ nell’ordine
così ottenuto. A questo punto i giocatori possono scoprire due carte disposte
consecutivamente sul tavolo, e prenderle nel solo caso in cui queste due carte
abbiano somma dispari. Se queste carte vengono prese, le altre vengono
aggiustate quanto basta per riempire il buco lasciato libero. Il gioco prosegue
quindi a questo modo finché nessun giocatore può più prendere carte.

Romeo e i suoi amici, per sentirsi più partecipi, hanno oggi deciso di fare un
"gioco nel gioco": all’inizio della partita, scommettono su quali carte pensano
rimarranno sul tavolo una volta finita la partita. Aiuta Romeo, determinando
quali carte potrebbero rimanere sul tavolo alla fine del gioco!

## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di testcase.
Seguono $T$ testcase, ognuno dei quali composto da due righe:

- Riga $1$: l'unico intero $N$.
- Riga $2$: gli $N$ interi $C_i$ separati da spazio, nell'ordine in cui sono
  disposti sul tavolo.

## Dati di output

Il file di output deve essere composto da tre righe per ciascun testcase:

- Riga $1$: la dicitura `Case #x:` dove $x$ è il numero del testcase (a partire
  da $1$).
- Riga $2$: il numero di diverse carte $K$ che potrebbero rimanere sul tavolo a
  fine partita.
- Riga $3$: i $K$ interi che identificano le carte che potrebbero rimanere sul
  tavolo a fine partita.

## Assunzioni

- $1 \le T \le 10$.
- $1 \le N \le 100$.
- $N$ è sempre un numero dispari.
- $0 \le C_i \le N-1$ per ogni $i = 0...N-1$.
- Ogni numero tra 0 e $N-1$ compare esattamente una volta nella sequenza dei $C_i$.

## Esempi di input/output

***

**Input:**
```
2
3
1 2 0
11
1 0 2 6 4 5 3 9 8 10 7
```

***

**Output:**
```
Case #1:
1
0
Case #2:
2
2 8
```

***

## Spiegazione

Nel **primo caso di esempio**, l’unica mossa possibile è eliminare le carte 1 e 2 per cui rimane sul tavolo necessariamente la carta 0.

Nel **secondo caso di esempio** sono invece possibili diverse sequenze di mosse. Una delle sequenze che lasciano la carta 2 è la seguente:

```
1 0 2 6 4-5 3 9 8 10 7
  1-0 2 6 3 9 8 10 7
    2 6-3 9 8 10 7
      2 9 8 10 7
        2 9-8
          2
```

Una delle sequenze di mosse che lasciano la carta 8 è la seguente:
```
1-0 2 6 4 5 3 9 8 10 7
  2 6 4-5 3 9 8 10 7
    2 6 3 9 8 10-7
      2 6-3 9 8
        2-9 8
          8
```
