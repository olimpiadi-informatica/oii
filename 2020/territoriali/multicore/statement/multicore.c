#include <stdio.h>

#define MAXN 300

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t, i;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        int N, B;
        int C[MAXN], P[MAXN];
        
        // scrivi in questa variabile la risposta
        int nc;

        scanf("%d %d", &N, &B);
        for (i = 0; i < N; i++)
            scanf("%d %d", &C[i], &P[i]);

        // RISOLVI QUI IL PROBLEMA!!

        printf("Case #%d: %d\n", t, nc);
    }
}
