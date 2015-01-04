/**
 *  Soluzione di mojito.
 *
 *  Autore: Luca Versari
 *
 *  Descrizione: Simulazione O(n²)
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXX 100
#define MAXY 100
#define MAXN 100

int N, X, Y;
int MX, MY;
int RX[MAXN], RY[MAXN], PX[MAXN], PY[MAXN];
char visited[MAXN];

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1-x2) + abs(y1-y2);
}

int isless(int x1, int y1, int x2, int y2) {
    return (x1<x2) || (x1==x2 && y1 < y2);
}

int nearest(int x, int y) {
    int n = 0;
    int i;
    for(i=1; i<N; i++) {
        int di = dist(x, y, RX[i], RY[i]);
        int dn = dist(x, y, RX[n], RY[n]);
        if((di<dn) || (di==dn && isless(RX[i], RY[i], RX[n], RY[n])))
            n = i;
    }
    return n;
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i;
    scanf("%d%d%d%d%d\n", &X, &Y, &MX, &MY, &N);
    for(i=0; i<N; i++) scanf("%d%d%d%d", &RX[i], &RY[i], &PX[i], &PY[i]);
    int count = 0;
    while(1) {
        int nx = nearest(MX, MY);
        if(visited[nx]) break;
        visited[nx] = 1;
        count++;
        MX = PX[nx];
        MY = PY[nx];
    }
    printf("%d\n", count);
    return 0;
}
