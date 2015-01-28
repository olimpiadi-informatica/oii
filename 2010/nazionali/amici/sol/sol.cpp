#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

const int MAXN = 1000000;
const int MAXK = MAXN-1;
const int MAXT = 100000000;

int N, K, T;
int perm[MAXN+1];
int amici[MAXK+1];

int permraised[MAXN+1];
int used[MAXN+1];
int revcicli[MAXN+1];
int indice[MAXN+1];
vector< vector< int > > cicli;

int
main(void)
{
  assert(scanf("%d%d%d", &N, &K, &T) == 3);
  for (int i = 0; i < N; ++i)
    {
      assert(scanf("%d", perm+i) == 1);
      --perm[i];
    }
  for (int i = 0; i < K; ++i)
    {
      assert(scanf("%d", amici+i) == 1);
      --amici[i];
    }
  assert(2 <= N && N <= MAXN);
  assert(2 <= K && K <= N-1);
  assert(0 <= T && T <= MAXT);

  
  for (int i = 0; i < N; ++i)
    if (used[i] == 0)
      {
        vector< int > nuovo;
        int tmp = 0;
        int x = i;
        int rev = cicli.size();
        do
          {
            nuovo.push_back(x);
            revcicli[x] = rev;
            used[x] = 1;
            indice[x] = tmp++;
            x = perm[x];
          } while(x != i);
        permraised[i] = nuovo[T % nuovo.size()];
        cicli.push_back(nuovo);
      }
    else
      {
        permraised[i] = cicli[revcicli[i]]
          [(indice[i] + T) % cicli[revcicli[i]].size()];
      }
  
  for (int i = 0; i < K; ++i)
    used[permraised[amici[i]]] = 2;

  if (used[0] == 2)
    if (used[N-1] == 2)
      {
        for (int i = 2; i < N; ++i)
          if (used[i-1] != 2 && used[i] == 2)
            {
              printf("%d\n", i+1);
              return 0;
            }
      }
    else
      printf("1\n");
  else
    for (int i = 1; i < N; ++i)
      if (used[i] == 2)
        {
          printf("%d\n", i+1);
          return 0;
        }
  return 1;
}
