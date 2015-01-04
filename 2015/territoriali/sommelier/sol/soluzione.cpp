/**
 *  Soluzione di sommelier.
 *
 *  Autore: Luca Versari
 *
 *  Descrizione: Dinamica O(n²).
 */

#include <stdio.h>
#define MAXN 99

int N;
int din[MAXN];
int vals[MAXN];

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j;
    scanf("%d", &N);
    for(i=0; i<N; i++) scanf("%d", &vals[i]);
    for(i=N-1; i>=0; i--) {
        int max = 0;
        for(j=i+2; j<N; j++)
            if(vals[j] >= vals[i] && din[j] > max)
                max = din[j];
        din[i] = max + 1;
    }
    int max = din[0];
    for(i=1; i<N; i++)
        if(din[i] > max)
            max = din[i];
    printf("%d\n", max);
    return 0;
}
