/*  Soluzione O(N x 2^M)

  2^M contatori:
  C[x] = numero di stringhe di lunghezza k che hanno x
  come suffisso e non contengono S, dove x in {0,1}^M


  *** Passo base k = M

  C[x] = 1 per x \neq S
  C[S] = 0

  *** Passo k = M+1, M+2, ..., N

  C'[y] = 0 per y \in {0,1}^M

  Per x \in {0,1}^M, x neq S, fai i seguenti passi
  - sia y = stringa degli ultimi M caratteri di x0
  - if (y \neq S) C'[y] += C[x]
  - sia y = stringa degli ultimi M caratteri di x1
  - if (y \neq S) C'[y] += C[x]

  C[x] = C'[x] per x \in {0,1}^M

  *** Alla fine, restituisci sum_{x \in {0,1}^M, x neq S} C[x]
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 1000
#define MAXN 1000
#define MODULO 2011
unsigned long long int N, M;
unsigned long long int due_alla_M;
char bit[MAXM];
unsigned long long int S;
unsigned long long int MASK;
int **counters;
int conta = 0;

int
main(void)
{
    FILE * fin, *fout;
    unsigned long long int i, j;
    int m, n;
    int indice = 1;
    int newindice = 0;
    
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    
    fscanf(fin, "%d %d", &m, &n);
    M = (unsigned long long) m;
    N = (unsigned long long) n;
    fscanf(fin, "%s", bit);
    due_alla_M = 1 << M;
    MASK = ~(1 << (M-1));
    S = 0;
    for (i = 0; i < M; i++)
      S = (S << 1) + bit[i] - '0';
    counters = (int**)calloc(sizeof(int*), 2);
    counters[0] = (int*)calloc(sizeof(int), due_alla_M);
    counters[1] = (int*)calloc(sizeof(int), due_alla_M);

    for (j = 0; j < due_alla_M; j++)
      counters[0][j] = 1;
    counters[0][S] = 0;
        
      
    for (i = M; i < N; i++)
      {
        indice = (i-M) % 2;
        newindice = 1-indice;
        memset(counters[newindice], 0, sizeof(int) * due_alla_M);

        for (j = 0; j < due_alla_M; j++)
          {
            unsigned long long int new_j = (j & MASK) << 1;
            if (new_j != S)
              counters[newindice][new_j] = (counters[newindice][new_j] + counters[indice][j]) % MODULO;
            if (new_j+1 != S)
              counters[newindice][new_j+1] = (counters[newindice][new_j+1] + counters[indice][j]) % MODULO;
          }
      }

    for (j = 0; j < due_alla_M; j++)
      conta = (conta + counters[newindice][j]) % MODULO;
    
    fprintf(fout, "%d\n", conta);
    return 0;
}
