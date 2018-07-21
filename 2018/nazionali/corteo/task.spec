# Le righe che iniziano con # sono commenti.
# La stringa ***sezione*** indica l'inizio di una nuova sezione.
# Le sezioni devono essere sempre presenti tutte, l'ordine non conta ma è
# meglio se sono nell'ordine: variables, prototypes, calls, input, output


***variables***
int N
int M
int P1
int D1
int P2
int D2
int A[M]
int B[M]
int res


***prototypes***
int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[])

***calls***
res = pianifica(N, M, P1, D1, P2, D2, A, B)

***input***
N M
P1 D1
P2 D2
A[] B[]

***output***
res
