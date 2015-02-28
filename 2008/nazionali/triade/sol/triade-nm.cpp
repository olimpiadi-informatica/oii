/*
  Soluzione N*M di triade.
  Scorre la lista degli archi, quindi prende un nodo esterno e vede se
  e' adiacente ad entrambi i nodi dell'arco.
*/

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;

const int MaxN = 1000000;

typedef vector<set<int> > graph_t;
typedef vector<pair<int, int> > adj_t;

int main()
{
  int M, N;
  cin >> M >> N;

  assert(1 <= N && N <= MaxN);
  assert(N-1 <= M && M <= 2*N-3);

  graph_t G(N);
  adj_t adj;
  
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    
    assert(1 <= u && u <= N);
    assert(1 <= v && v <= N);
    assert(u != v);

    --u; --v;
    if (u < v) {
      G[u].insert(v);
    } else {
      G[v].insert(u);
    }
    adj.push_back(make_pair(u, v));
  }

  vector<int> dummy_count;
  dummy_count.reserve(3*N);

  // scorre la lista degli archi e guarda le adiacenze fra i due nodi selezionati
  for (adj_t::iterator iter_arc = adj.begin(); iter_arc != adj.end(); ++iter_arc) {
    int u = iter_arc->first;
    int v = iter_arc->second;

    set_intersection(G[u].begin(), G[u].end(), G[v].begin(), G[v].end(), back_inserter(dummy_count));
  }

  cout << dummy_count.size() << endl;
}
