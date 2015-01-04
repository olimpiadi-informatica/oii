#include <stdio.h>
#include <assert.h>
#define MAXM 3000000

static int i, N, M, T;
static int S[MAXM], E[MAXM];

int solve(int N, int M, int T, int* S, int* E);

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(3 == fscanf(fin, "%d%d%d", &N, &M, &T));
    for(i=0; i<M; i++) assert(2 == fscanf(fin, "%d%d", S+i, E+i));
    fprintf(fout, "%d\n", solve(N, M, T, S, E));
    fclose(fin);
    fclose(fout);
    return 0;
}
