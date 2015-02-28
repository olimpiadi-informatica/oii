#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <cassert>

using namespace std;

const int MaxN = 1000000;

typedef vector<set<int> > graph_t;

int main()
{
  int M, N;
  cin >> M >> N;

  assert(1 <= N && N <= MaxN);
  assert(N-1 <= M && M <= 2*N-3);

  graph_t G(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    
    assert(1 <= u && u <= N);
    assert(1 <= v && v <= N);
    assert(u != v);

    --u; --v;
    if (v > u) {
      G[u].insert(v);
    } else {
      G[v].insert(u);
    }
  }

  // Conta in modo stupido il numero di triadi.
  int count = 0;
  for (int u = 0; u < N-2; ++u) {
    for (set<int>::iterator iter_v = G[u].begin(); iter_v != G[u].end(); ++iter_v) {
      int v = *iter_v;
      for (set<int>::iterator iter_k = G[u].begin(); iter_k != G[u].end(); ++iter_k) {
	if (*iter_k > v) {
	  count += G[v].count(*iter_k);
	}
      }
    }
  }

  cout << count << endl;
}

