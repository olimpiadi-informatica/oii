/*
  Stefano Maggiolo (21/04/2011)
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 1000
#define MAXDISL 100


int N;
int quote[MAXN+1];

int
main(void)
{
  int i, j;
  int sol = 1;
  int quota_sol = 5000;

#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d", &N);
  assert(2 <= N && N <= MAXN);
  quote[0] = 5000;
  for (i = 0; i < N; i++)
    {
      scanf("%d", quote + i + 1);
      assert(-MAXDISL <= quote[i+1] && quote[i+1] <= MAXDISL);
      quote[i+1] += quote[i];
    }



  for (i = 0; i <= N; i++)
    {
      int freq = 1;
      for (j = i+1; j <= N; j++)
        if (quote[j] == quote[i])
          freq++;
      if (freq >= sol)
        {
          sol = freq;
          quota_sol = quote[i];
        }
    }
  printf("%d\n", quota_sol);

  return 0;
}

