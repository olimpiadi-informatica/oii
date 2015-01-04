#include <stdio.h>
#include <assert.h>
#define MAXN 20000000

static int N, K, i;
static int s[MAXN];

int solve(int N, int K, int* S);

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(2 == fscanf(fin, "%d%d", &N, &K));
    for(i=0; i<N; i++) assert(1 == fscanf(fin, "%d", &s[i]));
    fprintf(fout, "%d\n", solve(N, K, s));
    fclose(fin);
    fclose(fout);
    return 0;
}
