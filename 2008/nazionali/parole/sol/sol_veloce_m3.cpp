/* Soluzione O(N x M)

  Simile a quella precedente, solo che si mantengono M+1 contatori (uno
  per prefisso di S, incluso il prefisso vuoto) utilizzando un'idea
  stile pattern preprocessing di KMP:

  C[i] = numero di stringhe di lunghezza k che hanno S[0..i]
  come suffisso (ma nessun S[0..j] come suffisso per j >i)
  e non contengono S, dove -1 <= i <= M-1
  (nota: S = S[0..M-1] e S[0..-1] e' la stringa vuota)

  *** Passo base k = 1

  C[-1] = 1  (prefisso vuoto per ~S[0])
  C[0] = 1   (prefisso S[0..0] per S[0])
  C[i] = 0 per 1 <= i <= M-1

  costrusci P t.c. P[i] = j sse S[0..j] e' il piu' lungo suffisso
  di S[0..i]~S[i+1] (S[0..i] seguito dal complemento di S[i+1])
  notare che j puo' essere -1 e, inoltre, -1 <= i <= M-2


  *** Passo k = 2, 3, ..., N

  C'[i] = 0 per -1 <= i <= M-1

  per -1 <= i <= M-2 fai i seguenti passi
  - C'[i+1] += C[i]   // il bit e' uguale al prossimo carattere
  - C'[P[i]] += C[i]  // il bit e' differente dal prossimo carattere

  C[i] = C'[i] per -1 <= i <= M-1


  *** Alla fine, restituisci sum_{-1 <= i <= M-2} C[i]

  Diverso da sol_veloce solo per il calcolo di P, nel modo triviale (M^3)
  */
 
using namespace std;
#include <cstdio>

const int MAXM = 1000;
const int MAXN = 1000;
const int MODULO = 2011;
int N, M;
char bit[MAXM];
int counters[MAXM+1], new_counters[MAXM+1];
int P[MAXM+1];
int conta = 0;

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
    fscanf(fin, "%s", bit+1); // qui l'array parte da 1, 0 = stringa vuota

    for (j = 0; j <= M; j++)
      counters[j] = 0;
    counters[1] = 1;
    counters[0] = 1;

    //calcolo di P
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
    //    for (i = 0; i <= M-1; i++)
    //      printf("%d ", P[i]);
    //    printf("\n");

    // principale
    for (i = 2; i <= N; i++)
      {
        for (j = 0; j <= M-1; j++)
          {
            new_counters[j+1] += counters[j];
            new_counters[P[j]] += counters[j];
          }
        for (j = 0; j <= M-1; j++)
          {
            counters[j] = new_counters[j] % MODULO;
            new_counters[j] = 0;
          }
        new_counters[M] = 0;
      }
    
    for (j = 0; j <= M-1; j++)
      conta = (conta + counters[j]) % MODULO;
    fprintf(fout, "%d\n", conta);
    
    fflush(fout);
    return 0;
}
