#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int conta(int n, int k, int* v);

int main() {
    size_t r;
    int n, k;
    r = fread_unlocked(&n, sizeof(int), 1, stdin);
    assert(r == 1);
    r = fread_unlocked(&k, sizeof(int), 1, stdin);
    assert(r == 1);
    int* v = calloc(n, sizeof(int));
    assert(v);
    int already_read = 0;
    while(already_read < n) {
        already_read += fread_unlocked(v + already_read, sizeof(int), n - already_read, stdin);
    }
    printf("%d\n", conta(n, k, v));
    free(v);
    return EXIT_SUCCESS;
}
