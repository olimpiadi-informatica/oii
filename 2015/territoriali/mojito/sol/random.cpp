/**
 *  Soluzione (sbagliata) di mojito.
 *
 *  Autore: William Di Luigi
 *
 *  Descrizione: mangiapunti(?) che stampa un valore random nel range [1, N].
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(8753);
    int N;
    scanf("%*d %*d\n%*d %*d\n%d\n", &N);
    printf("%d\n", rand() % N + 1);
    return 0;
}
