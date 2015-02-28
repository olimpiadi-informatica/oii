/* Soluzione O(2^N x N)

   Genera tutte le stringhe binarie di lunghezza N e aggiunge uno se
   contengono S.
   
*/

using namespace std;

#include <cstdio>
#include <cstring>


const int MAXM = 1000;
const int MAXN = 1000;
const int MODULO = 2011;
int N, M, conta = 0;
char bit[MAXM];

char attuale[MAXN];

int trova(char *cosa, char *dove)
{
  if (strstr(dove, cosa) == NULL)
    return 0;
  else
    return 1;
}

void genera(int index)
{
  if (index >= N)
    {
      if (!trova(bit, attuale))
        conta = (conta + 1) % MODULO;
    }
  else
    {
      attuale[index] = '0';
      genera(index+1);
      attuale[index] = '1';
      genera(index+1);
    }
}

int
main(void)
{
    FILE * fin, *fout;
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    fscanf(fin, "%d %d", &M, &N);
    fscanf(fin, "%s", bit);
    genera(0);

    fprintf(fout, "%d\n", conta);

    fflush(fout);

    return 0;
}
