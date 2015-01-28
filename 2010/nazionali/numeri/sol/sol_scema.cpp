#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>

using namespace std;

#ifdef EVAL
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif

int main()
{
  int S, N;
  
  assert(scanf("%d %d", &S, &N) == 2);
  vector<int> numeri(N);
  for (int i = 0; i < N; ++i) {
    int x;
    assert(scanf("%d", &x) == 1);
    numeri[i] = x;
  }

  vector<int> partial(N+1);
  partial_sum(numeri.begin(), numeri.end(), partial.begin() + 1);
  partial[0] = 0;

  int count = 0;
  for (int i = 0; i < N; ++i) {
    //if (numeri[i] == S)
    //  ++count;
    for (int j = i+1; j <= N; ++j) {
      int s = (partial[j] - partial[i]);
      if (s == S) {
	++count;
      }
      //      if (s > S) break;
    }
  }

  printf("%d\n", count);
}
