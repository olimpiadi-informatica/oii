#include <stdio.h>
#include <assert.h>
#define MAXN 100000
#define MAXM 1000000

static FILE *fr, *fw;

static int N, M, W, L;
static int R, C;
static int arco_da[MAXM], arco_a[MAXM], capacita[MAXM];

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int R, int C);

int main(){
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int i;
    assert(4 == fscanf(fr, "%d%d%d%d", &N, &M, &W, &L));
    assert(2 == fscanf(fr, "%d%d", &R, &C));
    for (i=0; i<M; i++)
        assert(3 == fscanf(fr, "%d%d%d", arco_da+i, arco_a+i, capacita+i));

    fprintf(fw, "%d\n", Analizza(N, M, W, L, arco_da, arco_a, capacita, R, C));

    fclose(fr);
    fclose(fw);
    return 0;
}
