#include <stdio.h>
#include <assert.h>
#define MAXN 2000000

static FILE *fr, *fw;
static int altezza[MAXN];

void Pianifica(int N, int altezza[]);

void Abbatti(int indice, int direzione) {
    fprintf(fw, "%d %d\n", indice, direzione);
}

int main(){
    int N, i;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(1 == fscanf(fr, "%d", &N));
    for (i=0; i<N; i++)
        assert(1 == fscanf(fr, "%d", altezza + i));

    Pianifica(N, altezza);

    fclose(fr);
    fclose(fw);
    return 0;
}
