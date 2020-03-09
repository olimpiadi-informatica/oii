#include <stdio.h>
#include <stdbool.h>

#define MAXN 1000

bool compare(char* s1, char* s2, int c) {
    while (c--) {
        if (*s1 != *s2) return false;
        s1++;
        s2++;
    }
    return true;
}

void solve(int t) {
    int N1, N2, N3, N4;
    int M;
    char F1[MAXN+1], F2[MAXN+1], F3[MAXN+1], F4[MAXN+1];

    // scrivi in queste variabili la risposta
    int p1, p2, p3, p4;

    scanf("%d %d %d %d", &N1, &N2, &N3, &N4);
    scanf("%d", &M);
    scanf("%s %s %s %s", F1, F2, F3, F4);

    for (int i = 0; i <= N1-M; i++) {
        p1 = i;
        p2 = p3 = p4 = -1;
        for (int j = 0; j <= N2-M && p2 < 0; j++)
            if (compare(F1+i, F2+j, M))
                p2 = j;
        for (int j = 0; j <= N3-M && p3 < 0; j++)
            if (compare(F1+i, F3+j, M))
                p3 = j;
        for (int j = 0; j <= N4-M && p4 < 0; j++)
            if (compare(F1+i, F4+j, M))
                p4 = j;
        if (p2 != -1 && p3 != -1 && p4 != -1)
            break;
    }

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
