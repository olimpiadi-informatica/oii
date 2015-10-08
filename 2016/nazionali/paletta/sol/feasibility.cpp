/**
 *  Soluzione parziale di paletta
 *
 *  Autore: Giorgio
 *
 *  Descrizione: controlla solo se e' fattibile ordinare.
 */


long long paletta_sort(int N, int V[]) {
    for (int i=0; i<N; i++) if ((V[i] + i)%2 > 0) return -1;
    return 42;
}
