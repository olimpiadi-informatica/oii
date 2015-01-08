#include <stdio.h>
#include <assert.h>
#define MAXN 1000000

static FILE *fr, *fw;

static int N;
static int acceso[MAXN + 1], pulsante[MAXN + 1];

void Accendi(int N, int acceso[], int pulsante[]);

int main() {
    int i;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(1 == fscanf(fr, "%d", &N));
    for (i=1; i<=N; i++)
        assert(1 == fscanf(fr, "%d", acceso + i));

    Accendi(N, acceso, pulsante);

    for (i=1; i<=N; i++) {
        if (i > 1) fprintf(fw, " ");
        fprintf(fw, "%d", pulsante[i]);
    }
    fprintf(fw, "\n");
    return 0;
}
