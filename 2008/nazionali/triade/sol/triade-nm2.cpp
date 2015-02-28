/*
  Soluzione N*M di triade furba.
  Come triade-nm, ma invece che scandire la lista degli archi,
  scandisce direttamente i nodi.
*/

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <cassert>
#include <algorithm>

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

  // Conta in modo semi-stupido il numero di triadi.
  // in pratica per ogni nodo si guardano le intersezioni con la lista
  // di adiacenza dei nodi adiacenti. Le intersezioni sono contate in
  // O(NlogN), i nodi sono N ed i loro adiacenti N. Dato che il grafo
  // pero' e' memorizzato mantenendo un ordine la complessita'
  // dovrebbe comunque essere di circa O(M) invece che O(M * logN).
  vector<int> dummy_count;
  dummy_count.reserve(N*3);
  
  for (int u = 0; u < N-2; ++u) {
    for (set<int>::iterator iter_v = G[u].begin(); iter_v != G[u].end(); ++iter_v) {
      int v = *iter_v;
      set_intersection(G[u].begin(), G[u].end(), G[v].begin(), G[v].end(), back_inserter(dummy_count));
    }
  }

  cout << dummy_count.size() << endl;
}
