using namespace std;
#include <iostream>

const int MAXM = 1000;
const int MAXN = 1000;
const int MODULO = 201100000;
int N, M, due_alla_M;
char bit[MAXM+1];
unsigned int phi[MAXM+1];
unsigned int P[MAXM+1];
unsigned long int S;

int
main(void)
{
    FILE * fin, *fout;
    int i, j, k;
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    fscanf(fin, "%d %d", &M, &N);
    fscanf(fin, "%s", bit+1);

    P[0] = 0;
    for (i = 1; i <= M-1; i++)
      {
        P[i] = 0;
        for (j = i; j >= 1; j--)
          {
            int found;
            if (bit[j] != bit[i+1])
              {
                found = 1;
                for (k = j-1; k >= 1; k--)
                  {
                    if (bit[k] != bit[i+1 - j + k])
                      {
                        found = 0;
                        break;
                      }
                  }
                if (found)
                  {
                    P[i] = j;
                    break;
                  }
              }
          }
      }
    
    
    for (i = 0; i <= M-1; i++)
      printf("%d ", P[i]);
    printf("\n");

    //    fprintf(fout, "\n");
  
    //    fflush(fout);
    
}
