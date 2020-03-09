**Difficoltà: _1_**

Luca e William devono sovente scambiarsi delle segretissime informazioni
riguardo alle selezioni territoriali, sotto forma di numeri interi $N$. Per
evitare di essere scoperti, hanno quindi deciso di inventare un nuovo codice
crittografico, che hanno chiamato codice _Luca-William-Fibonacci_ (LWF).

In questo codice, ogni numero intero $N$ viene tradotto in una sequenza
$s_0 s_1 \ldots s_k$
di cifre binarie `'0'` e `'1'`, di cui l’ultima è un `'1'`, in
maniera tale che:

\\[ N = \sum_{i=0}^{k} s_i \cdot F_i \\]

dove $F_i$ è il numero di Fibonacci $i$-esimo. Più informalmente, una cifra $1$
in posizione $i$ nella sequenza indica che il numero di Fibonacci $i$-esimo fa
parte della somma che ricostruisce il numero $N$.

La sequenza dei numeri di Fibonacci è definita in maniera ricorsiva: i primi due
termini della sequenza sono $F_0 = 1$ e $F_1 = 1$, mentre ognuno dei successivi
viene calcolato sommando i due precedenti $F_i = F_{i-1} + F_{i-2}$.

Per esempio, consideriamo la sequenza `1011001` di lunghezza $k = 7$. Visto che
i primi $7$ numeri di Fibonacci sono:

\\[ 1 \quad 1 \quad 2 \quad 3 \quad 5 \quad 8 \quad 13 \\]

il numero $N$ corrispondente è pari a $1 + 2 + 3 + 13 = 19$.

Luca ha già implementato l’algoritmo di decodifica (descritto come sopra), che
da una sequenza di cifre binarie ricostruisce il numero $N$. Tuttavia William è
ancora in alto mare con l’algoritmo di codifica, che dato un numero $N$ dovrebbe
produrre una sequenza di cifre binarie corrispondente. Implementalo tu!.

## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di testcase.
Le successive $T$ righe contengono un intero ciascuna: il valore intero $N$ del
relativo testcase.

## Dati di output

Il file di output deve essere composto da $T$ righe, ciascuna delle quali
contenente la dicitura `Case #x: y` dove $x$ è il numero del testcase (a partire
da $1$) e $y$ è una sequenza di cifre binarie che termina con `'1'`
corrispondente al valore di $N$ del testcase.

## Assunzioni

- $1 \le T \le 20$.
- $1 \le N \le 1\,000\,000$.
- Potrebbero esserci più sequenze di cifre ugualmente valide.

## Esempi di input/output

***

**Input:**
```
2
19
9
```

***

**Output:**
```
Case #1: 1011001
Case #2: 11101
```

***

## Spiegazione

Il **primo caso di esempio** è quello discusso nel testo.

Nel **secondo caso di esempio**, $9$ può essere ottenuto sia come $1+1+2+5$
(come nell’output di esempio), oppure come $1 + 3 + 5$ (`10011`) e $1 + 8$
(`100001`).
