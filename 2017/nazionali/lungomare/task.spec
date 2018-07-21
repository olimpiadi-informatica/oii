# Le righe che iniziano con # sono commenti.
# La stringa ***sezione*** indica l'inizio di una nuova sezione.
# Le sezioni devono essere sempre presenti tutte, l'ordine non conta ma è
# meglio se sono nell'ordine: variables, prototypes, calls, input, output

***variables***
int N
longint L
longint D[N]
longint P[N]
longint C


***prototypes***
longint percorri(int N, longint L, longint &D[], longint &P[])

***calls***
C = percorri(N, L, D, P)

***input***
N L
D[]
P[]

***output***
C
