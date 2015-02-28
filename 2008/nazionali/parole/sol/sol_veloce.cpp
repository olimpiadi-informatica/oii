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
  */
 
using namespace std;
#include <cstdio>

const int MAXM = 100000;
const int MAXN = 100000;
const int MODULO = 2011;
int N, M;
char bit[MAXM];
int counters[MAXM+1], new_counters[MAXM+1];
int P[MAXM+1];
int phi[MAXM+1];
int conta = 0;

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
    fscanf(fin, "%s", bit+1); // qui l'array parte da 1, 0 = stringa vuota

    for (j = 0; j <= M; j++)
      counters[j] = 0;
    counters[1] = 1;
    counters[0] = 1;

    // costruisco phi (bordo vero di KMP)
    phi[0] = -1;
    for (j = 1; j <= M; j++)
      {
        i = phi[j-1];
        while (i >= 0 && bit[i+1] != bit[j])
          i = phi[i];
        phi[j] = i+1;
      }
    
    // costruisco P a partire da phi
    P[0] = 0;
    for (j = 1; j <= M-1; j++)
      {
        i = phi[j];
        while (i >= 0 && bit[i+1] == bit[j+1])
          {
            i = phi[i];
          }
          P[j] = i+1;
      }
    //        for (i = 0; i <= M-1; i++)
    //          printf("%d ", P[i]);
    //        printf("\n");

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
