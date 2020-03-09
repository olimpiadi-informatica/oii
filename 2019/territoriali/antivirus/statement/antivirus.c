#include <stdio.h>

#define MAXN 1000

void solve(int t) {
    int N1, N2, N3, N4;
    int M;
    char F1[MAXN+1], F2[MAXN+1], F3[MAXN+1], F4[MAXN+1];

    // scrivi in queste variabili la risposta
    int p1, p2, p3, p4;

    scanf("%d %d %d %d", &N1, &N2, &N3, &N4);
    scanf("%d", &M);
    scanf("%s %s %s %s", F1, F2, F3, F4);

    // RISOLVI QUI IL PROBLEMA!!

    printf("Case #%d: %d %d %d %d\n", t, p1, p2, p3, p4);
}

int main() {
    // le seguenti due righe possono essere utili per leggere e scrivere da file

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        solve(t);
    }
}
