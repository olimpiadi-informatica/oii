# Le righe che iniziano con # sono commenti.
# La stringa ***sezione*** indica l'inizio di una nuova sezione.
# Le sezioni devono essere sempre presenti tutte, l'ordine non conta ma è
# meglio se sono nell'ordine: variables, prototypes, calls, input, output


***variables***
int N
int M
int A[M]
int B[M]
int inizio[M]
int fine[M]
int tempo


***prototypes***
int raggiungi(int N, int M, int[] A, int[] B, int[] inizio, int[] fine)

***calls***
tempo = raggiungi(N, M, A, B, inizio, fine)

***input***
N M
A[] B[] inizio fine

***output***
tempo
