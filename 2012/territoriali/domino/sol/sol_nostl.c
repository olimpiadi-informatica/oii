/*
  Stefano Maggiolo (21/04/2011)
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 10


int N;
int tessere[MAXN][2];
int inserite[MAXN];
int ordine[MAXN];
int sol;

void
gen_seq_ric(int l, int ultima)
{
  int i;

  // Se sono arrivato qui, ho trovato una sequenza lunga l, quindi la
  // soluzione e` almeno l
  if (l > sol)
    {
      sol = l;
      if (l >= N)
        return;
    }

  // Scelgo una tessere non gia` inserita
  for (i = 0; i < N; i++)
    if (inserite[i] == 0)
      {
        ordine[l] = i;
        // Se c'e` un modo di continuare con quella tessera, continuo
        if (ultima == tessere[i][0])
          {
            inserite[i] = 1;
            gen_seq_ric(l+1, tessere[i][1]);
            inserite[i] = 0;
          }
        else if (ultima == tessere[i][1])
          {
            inserite[i] = 1;
            gen_seq_ric(l+1, tessere[i][0]);
            inserite[i] = 0;
          }
        // La soluzione non puo` essere piu` di N
        if (sol == N)
          return;
      }
}


int
main(void)
{
  int i, j;

#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d", &N);
  assert(2 <= N && N <= MAXN);
  for (i = 0; i < N; i++)
    {
      int a, b;
      scanf("%d%d", &a, &b);
      assert(0 <= a && a <= 6);
      assert(0 <= b && b <= 6);
      tessere[i][0] = a;
      tessere[i][1] = b;
    }

  // Provo a iniziare con una qualsiasi tessera, in entrambi i versi
  for (i = 0; i < N; i++)
    for (j = 0; j < 2; j++)
      {
        inserite[i] = 1;
        gen_seq_ric(1, tessere[i][j]);
        inserite[i] = 0;
      }

  printf("%d\n", sol);

  return 0;
}

