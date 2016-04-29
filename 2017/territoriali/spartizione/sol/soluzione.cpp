#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int G, P;
    scanf("%d%d", &G, &P);
    P--;
    int gemme_toto = 1;
    int tot_gemme_toto = 0;
    while (G > 0) {
        G -= gemme_toto;
        if (G < 0) tot_gemme_toto += G;
        tot_gemme_toto += gemme_toto;
        G -= P;
        gemme_toto++;
    }
    printf("%d\n", tot_gemme_toto);
}
