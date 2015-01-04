#include <stdio.h>
#include <assert.h>
#define MAXN 10000000

static int N, i;
static int M[MAXN], P[MAXN];

long long solve(int N, int* M, int* P);

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(1 == fscanf(fin, "%d", &N));
    for(i=0; i<N; i++) assert(2 == fscanf(fin, "%d%d", M+i, P+i));
    fprintf(fout, "%lld\n", solve(N, M, P));
    fclose(fin);
    fclose(fout);
    return 0;
}
