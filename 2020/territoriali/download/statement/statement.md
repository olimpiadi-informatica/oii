> *Per aiutarti con questo task, abbiamo preparato delle **tracce di soluzione**, che includono solo le parti di lettura dell'input e scrittura dell'output (da tastiera e su schermo). Puoi decidere se leggere/scrivere su file decommentando le opportune righe di codice.*
>
> - *Scarica la traccia in C: [download.c](download.c)*
> - *Scarica la traccia in C++: [download.cpp](download.cpp)*
> - *Scarica la traccia in Pascal: [download.pas](download.pas)*

---

## Descrizione del problema

Monica ha regalato un nuovo hard disk a Mojito, il suo cagnolino. Si sa, Mojito
è un grande amante di filmati e canzoni, quindi ha intenzione di riempire tutto
lo spazio del suo hard disk scaricando quanti più filmati e canzoni possibili!

![Mojito che sceglie filmati e canzoni da scaricare](download.jpg "Mojito che sceglie filmati e canzoni da scaricare")

È importante menzionare che Mojito preferisce di gran lunga i filmati alle
canzoni, quindi comincerà subito a scaricare quanti più filmati possibile. Nel
caso in cui lo spazio rimanente sull'hard disk non gli desse altra scelta,
Mojito ripiegherà sulle canzoni e comincerà quindi a scaricarne fino a riempire
completamente l'hard disk.

I gusti di Mojito non sono molto vari, i filmati che gli interessano hanno tutti
la stessa dimensione, e lo stesso vale per le canzoni. Per l'esattezza, tutti i
filmati hanno una dimensione di $F$ byte e tutte le canzoni hanno una dimensione
di $C$ byte.

Sapendo che il nuovo hard disk ha una capacità di $N$ byte, scrivi un programma
che calcoli il **numero di filmati** ed il **numero di canzoni** che Mojito
scaricherà, sapendo che il cane darà preferenza ai filmati.

## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di casi di
test. Seguono $T$ casi di test, numerati da $1$ a $T$. Ogni caso di test è
preceduto da una riga vuota.

Ciascun caso di test è composto da una sola riga, contenente tre numeri interi
$N, F, C$ separati da uno spazio, rispettivamente: la capacità in byte dell'hard
disk, la dimensione in byte dei filmati e la dimensione in byte delle canzoni.

## Dati di output

Il file di output deve contenere la risposta ai casi di test che sei riuscito a
risolvere. Per ogni caso di test che hai risolto, il file di output deve
contenere una riga con la dicitura

```
Case #t: nf nc
```

dove `t` è il numero del caso di test (a partire da $1$) e i valori `nf`, `nc` sono il numero di filmati e canzoni che Mojito scaricherà.

## Assunzioni

- $T=6$, nei file di input che scaricherai saranno presenti esattamente $6$ casi di test.
- $1 \le N, F, C \le 10\,000$.
- Non è detto che i filmati occupino più spazio delle canzoni.

## Esempi di input/output

***

**Input:**
```
2

1000 300 10

1000 30  50
```

***

**Output:**
```
Case #1: 3 10
Case #2: 33 0
```

***

## Spiegazione

Nel **primo caso d'esempio**, Mojito può scaricare 3 filmati e 10 canzoni per un occupazione totale di $3 \cdot 300 + 10 \cdot 10 = 900 + 100 = 1000$ byte e riempire così l'hard disk completamente. Non può invece scaricare 4 filmati, perché il totale verrebbe di $4 \cdot 300 = 1200$ che eccede la capacità dell'hard disk.

Nel **secondo caso d'esempio**, Mojito può scaricare 33 filmati per un occupazione totale di $33 \cdot 30 = 990$ byte. Nello spazio rimanente non è possibile scaricare canzoni.
