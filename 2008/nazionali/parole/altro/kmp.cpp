using namespace std;
#include <iostream>

const int MAXM = 1000;
const int MAXN = 1000;
const int MODULO = 201100000;
int N, M, due_alla_M;
char bit[MAXM];
unsigned int phi[MAXM];
unsigned long int S;

int
main(void)
{
    FILE * fin, *fout;
    int i, j;
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    fscanf(fin, "%d %d", &M, &N);
    fscanf(fin, "%s", bit+1);

    phi[0] = -1;
    for (j = 1;  j <= M; j++)
      {
        i = phi[j-1];
        while (i >= 0 && bit[i + 1] != bit[j])
          i = phi[i];
        phi[j] = i + 1;
      }
    for (i = 1; i <= M; i++)
      printf("%d ", phi[i]);
    printf("\n");

    //    fprintf(fout, "\n");
  
    //    fflush(fout);
    
}
