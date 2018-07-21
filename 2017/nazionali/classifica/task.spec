# Le righe che iniziano con # sono commenti.
# La stringa ***sezione*** indica l'inizio di una nuova sezione.
# Le sezioni devono essere sempre presenti tutte, l'ordine non conta ma è
# meglio se sono nell'ordine: variables, prototypes, calls, input, output


***variables***
int N
int Q
int ids[N]
char types[Q]
int params[Q]
int answers[Q]


***prototypes***
inizia(int N, int[] ids)
supera(int id)
squalifica(int id)
int partecipante(int pos)

***calls***
inizia(N, ids)
make_calls(&Q, types, params, &answers)

***input***
N Q
ids[]
types[] params[]

***output***
answers[]
