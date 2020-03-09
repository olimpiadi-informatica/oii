#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long costruisci(int N, int M, long long* H, int* A, int* B, int* C);

int main() {
    // Input da file:
    // freopen("input.txt", "r", stdin);

    // Output su file:
    // freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);
    long long* h = malloc(sizeof(long long) * n);
    for(size_t i = 0; i < n; i++) {
        scanf("%lld", &h[i]);
    }
    int* a = malloc(sizeof(int) * m);
    int* b = malloc(sizeof(int) * m);
    int* c = malloc(sizeof(int) * m);
    assert(a && b && c);
    for(size_t j = 0; j < m; j++) {
        scanf("%d%d%d", &a[j], &b[j], &c[j]);
    }
    printf("%lld\n", costruisci(n, m, h, a, b, c));
    free(c);
    free(b);
    free(a);
    free(h);
    return 0;
}
