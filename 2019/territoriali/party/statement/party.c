#include <stdio.h>

int main() {
    int T, t, N, i, sol, A;

    // le seguenti due righe possono essere utili per leggere e scrivere da file

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        // scrivi in questa variabile la soluzione
        sol = 0;

        scanf("%d", &N);

        for (i = 0; i < N; i++) {
            scanf("%d", &A);

            // il valore A rappresenta il valore di amicizia dell'i-esimo amico
        }

        printf("Case #%d: %d\n", t, sol);
    }

    return 0;
}
