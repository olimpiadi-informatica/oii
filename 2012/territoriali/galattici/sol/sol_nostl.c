/*
  Stefano Maggiolo (21/04/2011)
*/

#include <stdio.h>
#include <assert.h>

#define MAXM 100
#define MAXN 100
#define MAXK 10

int M, N, K;
char s[MAXK];
int tr[MAXN][256];


int
main(void)
{
  int i, curr;
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  scanf("%d%d%d", &M, &N, &K);
  assert(2 <= M && M <= MAXM);
  assert(2 <= N && N <= MAXN);
  assert(2 <= K && K <= MAXK);

  for (i = 0; i < K; ++i)
    scanf("%s", s + i);

  for (i = 0; i < M; ++i)
    {
      int a, b;
      char c[5];
      scanf("%d%d%s", &a, &b, c);
      assert(1 <= a && a <= N);
      assert(1 <= b && b <= N);
      assert(tr[a][c[0]] == 0);
      tr[a][c[0]] = b;
    }

  curr = 1;
  for (i = 0; i < K; i++)
    {
      assert(tr[curr][s[i]] != 0);
      curr = tr[curr][s[i]];
    }
  printf("%d\n", curr);

  return 0;
}

