#include <stdio.h>

#define MAXN 1000

int solve() {
    int N, i;
    scanf("%d", &N);

    int risposta = 0;  // memorizza qui la risposta
    int R[MAXN], C[MAXN];

    for (i=0; i<N; i++) {
        scanf("%d %d", &R[i], &C[i]);

        // aggiungi codice...
    }

    return risposta;
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        printf("Case #%d: %d\n", t, solve());
    }
}
