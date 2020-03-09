#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int conta(int N, int K, int* V);

int main() {
    // Input da file:
    // freopen("input.txt", "r", stdin);

    // Output su file:
    // freopen("output.txt", "w", stdout);

    int r;
    size_t n;
    size_t k;
    r = scanf("%zu%zu", &n, &k);
    assert(r == 1);
    int* v = calloc(n, sizeof(int));
    assert(v);
    for(size_t i = 0; i < n; i++) {
        r = scanf("%d", &v[i]);
        assert(r == 1);
    }
    printf("%d\n", conta(n, k, v));
    free(v);
    return EXIT_SUCCESS;
}
