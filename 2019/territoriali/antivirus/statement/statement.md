Il nuovo sistema di gara delle Selezioni Territoriali funziona alla grande, ma
Mojito non è così convinto... sembra infatti che la nota mascotte delle
Olimpiadi abbia fiutato un **virus** nascosto fra i file inviati da un
partecipante!

Conosciamo la lunghezza del virus e sappiamo che si ripete uguale nei quattro
file che abbiamo ricevuto, ma non sappiamo dove. Aiutaci ad
individuare il virus!

![Rappresentazione realistica dell'aspetto di un virus informatico](virus.jpg "Rappresentazione realistica dell'aspetto di un virus informatico")


## Dettagli

I quattro file $F_1, F_2, F_3, F_4$ sono dati in input, rappresentati come
quattro stringhe di caratteri di lunghezza rispettivamente $N_1,N_2,N_3,N_4$.

Il virus è una stringa di caratteri $V$ di lunghezza $M$. La lunghezza $M$ è
data in input, ma non si conosce il contenuto della stringa $V$ del virus.

Sappiamo con certezza che il virus $V$ appare all'interno di tutti e quattro i
file, come sottostringa di caratteri *consecutivi*. Sappiamo inoltre che *NON*
ci sono altre sottostringhe consecutive di lunghezza $M$ che si ripetono uguali
in tutti e quattro i file.

Le posizioni dei caratteri nelle stringhe sono numerati a partire da $0$. Per ciascuno dei
quattro file $F_i$, trova la posizione in cui è inserito il virus, ovvero la
posizione dove appare il primo carattere del virus $V$ all'interno della stringa
$F_i$.

## Assunzioni

- $T=12$, sono presenti $12$ casi di input.
- $2 \le N_1, N_2, N_3, N_4 \le 100$, i file non sono più lunghi di $100$
  caratteri.
- $2 \le M \le 20$, il virus non è più lungo di $20$ caratteri.
- $M \le \min(N_1, N_2, N_3, N_4)$, il virus non è più lungo del file più corto.
- Tutti i caratteri dei file sono lettere minuscole dell'alfabeto inglese (dalla
  `a` alla `z`), *NON* sono presenti spazi.
- È garantito che il virus esiste ed è unico.


## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di casi di
test. Seguono $T$ casi di test, numerati da $1$ a $T$. Ogni caso di test è
preceduto da una riga vuota.

In ciascun caso di test:

- La prima riga contiene quattro interi, $N_1$, $N_2$, $N_3$ e $N_4$, separati
  da uno spazio, che corrispondono alla lunghezza di ciascuno dei quattro file.
- La seconda riga contiene un solo intero $M$, che corrisponde alla lunghezza
  del virus.
- Le successive $4$ righe contengono rispettivamente le quattro stringhe $F_1$,
  $F_2$, $F_3$ e $F_4$.

## Dati di output

Il file di output deve contenere la risposta ai casi di test che sei riuscito a
risolvere. Per ogni caso di test che hai risolto, il file di output deve
contenere una riga con la dicitura

```
Case #t: p1 p2 p3 p4
```

dove `t` è il numero del caso di test (a partire da $1$) e i valori `p1`, `p2`,
`p3`, `p4` sono le posizioni in cui si trova il virus in ciascuno dei quattro
file. Con posizione si intende l'indice del primo carattere del virus, il primo
carattere del file ha indice zero.

## Esempi di input/output

***

**Input:** [Download](antivirus_input_example.txt)
```
2

8 12 10 7
4
ananasso
associazione
tassonomia
massone

6 9 11 10
3
simone
ponessimo
milionesimo
cassonetto
```

***

**Output:** [Download](antivirus_output_example.txt)
```
Case #1: 4 0 1 1
Case #2: 3 1 4 4
```

***

## Spiegazione

Nel **primo caso d'esempio** il virus è *asso*: anan**asso**, **asso**ciazione,
t**asso**nomia, m**asso**ne.

Nel **secondo caso d'esempio** il virus è *one*: sim**one**, p**one**ssimo,
mili**one**simo, cass**one**tto. Nota che *sim* è presente nei primi tre file ma
non nel quarto, quindi non è il virus cercato.

## Esempi di implementazione

Per aiutarti con questo task, abbiamo preparato degli esempi di implementazione
di una soluzione. Includono solo le parti di lettura dell'input e scrittura
dell'output:

- Versione C: [Download](antivirus.c)
- Versione C++: [Download](antivirus.cpp)
- Versione Pascal: [Download](antivirus.pas)
