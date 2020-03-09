#include <stdio.h>

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        int N, F, C;
        
        // scrivi in queste variabili la risposta
        int nf, nc;

        scanf("%d %d %d", &N, &F, &C);

        // RISOLVI QUI IL PROBLEMA!!

        printf("Case #%d: %d %d\n", t, nf, nc);
    }
}
