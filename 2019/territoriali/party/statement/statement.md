Mojito, il cane di Monica, vuole organizzare una festa con i suoi amici. Aiutalo a scegliere quali invitare e quali escludere in modo da rendere la festa più bella possibile.

![Foto dall'ultima festa in piscina organizzata da Mojito](party.jpg "Foto dall'ultima festa in piscina organizzata da Mojito")


## Dettagli

Mojito ha $N$ amici, ognuno dei quali ha un grado di amicizia $A_i$ che indica quanto Mojito apprezzi la sua presenza. Ovviamente nella lista c'è anche qualche antipatico che quindi ha un grado di amicizia negativo.

La bellezza della festa è definita come la somma del grado di amicizia degli invitati. Quanto può valere al massimo questa somma?

## Assunzioni

- $T=6$, sono presenti $6$ casi di input.
- $1 \le N \le 10.000$, il numero di amici di Mojito.
- $-100 \le A_i \le 100$, il grado di amicizia dell'$i$-esimo amico.
- È anche possibile che Mojito festeggi senza amici, in tal caso la festa ha valore $0$.

**Nota bene:** se utilizzi il linguaggio **Pascal**, fai attenzione al fatto che il valore massimo contenuto in una variabile `integer` è $32767$, troppo piccolo per risolvere questo task completamente. Superando quel numero, infatti, il programma comincerà a salvare numeri imprevedibili (senza mostrarti alcun errore!) per via dell'*overflow*. Per evitare questo fenomeno ti consigliamo di usare **sempre** il tipo `longint` al posto di `integer`.

## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di casi di test. Seguono $T$ casi di test, numerati da $1$ a $T$. Ogni caso di test è preceduto da una riga vuota.

In ciascun caso di test, la prima riga contiene l'unico intero $N$.

La seconda riga contiene gli $N$ interi separati da spazi, $A_i$.

## Dati di output

Il file di output deve contenere la risposta ai casi di test che sei riuscito a risolvere. Per ogni caso di test che hai risolto, il file di output deve contenere una riga con la dicitura:

```
Case #t: k
```

dove `t` è il numero del caso di test (a partire da $1$) e `k` è il massimo valore di bellezza ottenibile.

## Esempi di input/output

***

**Input:** [Download](party_input_example.txt)
```
2

8
1 -4 5 -2 -1 8 0 1

3
-1 -2 -4
```

***

**Output:**  [Download](party_output_example.txt)
```
Case #1: 15
Case #2: 0
```

***

## Spiegazione

Nel **primo caso d'esempio** la soluzione si ottiene invitando il primo, il terzo, il sesto, il settimo e l'ottavo amico, totalizzando una somma di $15$.

Nel **secondo caso d'esempio** la soluzione si ottiene non invitando alcun amico, totalizzando quindi $0$.

## Esempi di implementazione

Per aiutarti con questo task, abbiamo preparato degli esempi di implementazione di una soluzione. Includono solo le parti di lettura dell'input e scrittura dell'output:

- Versione C: [Download](party.c)
- Versione C++: [Download](party.cpp)
- Versione Pascal: [Download](party.pas)
