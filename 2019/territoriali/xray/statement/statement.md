È stato appena ritrovato un fossile della rarissima specie *Canis mojitus
albus*, ritenuta antenata della più comune *Canis mojitus familiaris*. Per
analizzarlo, gli scienziati devono trattarlo con delle radiazioni: ogni
centimetro dell'osso deve riceverne una precisa quantità. La macchina che fa il
trattamento può applicare radiazioni in modo uniforme su un qualsiasi segmento
contiguo: calcola quante volte deve essere azionata la macchina per ottenere la
giusta quantità di radiazioni su ogni punto dell'osso.

![Raggi X ad un Canis mojitus familiaris](xray.png "Raggi X ad un Canis mojitus familiaris")


## Dettagli

L'osso da trattare è lungo $N$ centimetri, numerati da $1$ a $N$. Il centimetro
$i$ deve ricevere una quantità di radiazioni specificata da un numero naturale
$R_i$. Il numero $N$ ed i numeri $R_1, ..., R_N$ sono dati in input.

La macchina viene azionata specificando due numeri interi positivi $a$ e $b$,
che indicano gli estremi del segmento di osso su cui la macchina opera ($a \le b$).
Dopo tale azionamento, tutti i centimetri da $a$ a $b$ dell'osso accumulano
$1$ unità di radiazioni.

Dopo aver azionato la macchina un certo numero di volte, la quantità di
radiazioni ricevute sul centimetro $i$ si può conoscere contando quante volte
una radiazione ha operato su quella zona (ovvero, quante volte la macchina è
stata azionata con valori tali per cui $a \le i \le b$).

Calcola il numero minimo di volte in cui è necessario azionare la macchina
affinché ciascuna zona $i$ riceva *esattamente* la quantità di radiazioni
richiesta $R_i$.

## Assunzioni

- $T=19$, ci sono $19$ casi di prova.
- $1 \le N \le 1000$, ovvero, l'osso è lungo al massimo $1000$ centimetri.
- $0 \le R_i \le 1000$, ogni centimetro può dover ricevere una quantità
  di radiazione fino a $1000$ .

## Dati di input

La prima riga del file di input contiene un intero $T$, il numero di casi di
test. Seguono $T$ casi di test, numerati da $1$ a $T$. Ogni caso di test è
preceduto da una riga vuota.

In ciascun caso di test, la prima riga contiene l'intero $N$. La seconda riga
contiene gli $N$ valori $R_1, ..., R_N$, separati da spazio.

## Dati di output

Il file di output deve contenere la risposta ai casi di test che sei riuscito a
risolvere. Per ogni caso di test che hai risolto, il file di output deve
contenere una riga con la dicitura

```
Case #t: p
```

dove `t` è il numero del caso di test (a partire da $1$) e `p` è è il minimo
numero di volte in cui la macchina deve essere azionata.

## Esempi di input/output

***

**Input:** [Download](xray_input_example.txt)

```
2

4
1 2 3 1

4
100 0 1 1
```

***

**Output:** [Download](xray_output_example.txt)

```
Case #1: 3
Case #2: 101
```

***

## Spiegazione

Nel **primo caso d'esempio**, è possibile azionare la macchina ad esempio nel
seguente modo:

1. segmento da $a=2$ a $b=3$
1. segmento da $a=1$ a $b=4$
1. segmento da $a=3$ a $b=3$

Graficamente:

```
. x x .  <-- azionamento 1
x x x x  <-- azionamento 2
. . x .  <-- azionamento 3
-------
1 2 3 1  <-- totale radiazione accumulata
```

Non ci sono soluzioni con solo $2$ azionamenti o meno, quindi la risposta
corretta è $3$.

Nel **secondo caso d'esempio**, è possibile azionare la macchina ad esempio nel
seguente modo:

1. segmento da $a=1$ a $b=1$ (ripeti $100$ volte)
1. segmento da $a=3$ a $b=4$

Non ci sono soluzioni con solo $100$ azionamenti o meno, quindi la risposta
corretta è $101$.
