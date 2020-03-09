#include <stdio.h>

int solve() {
    int N, i;
    scanf("%d", &N);

    int risposta = 0;  // memorizza qui la risposta

    for (i = 0; i < N; i++) {
        int variazione;
        scanf("%d", &variazione);

        // aggiungi codice...
    }

    return risposta;
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        printf("Case #%d: %d\n", t, solve());
    }
}
