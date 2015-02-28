/*
  Soluzione ottima per triade.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>

using namespace std;

const int MaxN = 1000000;

typedef vector<vector<int> > graph_t;

int main()
{
  int M, N;
  cin >> M >> N;

  assert(1 <= N && N <= MaxN);
  assert(N-1 <= M && M <= 2*N-3);

  graph_t G(N);
  vector<int> degree(N);

  // legge l'input
  for (int i = 0; i < M; ++i ) {
    int u, v;
    cin >> u >> v;

    assert(1 <= u && u <= N);
    assert(1 <= v && v <= N);
    assert(u != v);
    
    --u; --v;

    assert(find(G[u].begin(), G[u].end(), v) == G[u].end());
    assert(find(G[v].begin(), G[v].end(), u) == G[v].end());

    G[u].push_back(v);
    G[v].push_back(u);
  }

  // queste sono le strutture che tengono conto dei nodi di grado 1
  // e 2. Durante le modifiche al grafo, portiamo i nodi in queste
  // liste. Una volta che un nodo appartiene alla queue2 puo' passare
  // alla queue1, per questo teniamo anche gli indici inversi.
  vector<int> queue1;
  vector<int> queue2;
  vector<int> invert_idx2(N);

  for (int i = 0; i < N; ++i) {
    degree[i] = G[i].size();
    if (degree[i] == 1) {
      queue1.push_back(i);
    } else if(degree[i] == 2) {
      queue2.push_back(i);
      invert_idx2[i] = queue2.size() - 1;
    }
  }
  
  // rimuove i nodi, uno alla volta, prendendo sempre quello
  // di grado minimo e modificando il grafo ottenuto di volta
  // in volta
  vector<int> erased;
  graph_t G_inc(N);
  for (int i = 0; i < N; ++i) {
    int u;
    
    if (!queue1.empty()) {
      u = queue1.back();
      queue1.pop_back();
    } else if (!queue2.empty()) {
      u = queue2.back();
      queue2.pop_back();
    } else {
      assert(false);
    }

    erased.push_back(u);
    for (vector<int>::iterator iter = G[u].begin(); iter != G[u].end(); ++iter) {
      int v = *iter;
      if (degree[v]) {
	assert(degree[u] > 0);
	// nota: teniamo conto dei vicini di questo nodo, per
	// mantenere il grafo incrementale
	G_inc[u].push_back(v);

	--degree[u];
	--degree[v];
	
	if (degree[v] == 1) {
	  // se portiamo un nodo a grado 1, vuol dire che prima
	  // aveva grado 2.. quindi lo eliminiamo dalla coda
	  int last_u = queue2.back();

	  invert_idx2[last_u] = invert_idx2[v];
	  queue2[invert_idx2[v]] = last_u;
	  queue2.pop_back();
	  queue1.push_back(v);
	} else if (degree[v] == 2) {
	  assert(v != u);
	  queue2.push_back(v);
	  invert_idx2[v] = queue2.size() - 1;
	}

	assert(degree[u] >= 0);
	assert(degree[v] >= 0);
      }
    }
    assert(degree[u] == 0);
  }

  assert(find_if(degree.begin(), degree.end(), bind2nd(greater<int>(), 0)) == degree.end());

  // reinseriamo cosi' uno alla volta i nodi del grafo, partendo
  // dall'ultimo eliminato
  int count = 0;
  for (vector<int>::reverse_iterator curr_node = erased.rbegin();
       curr_node != erased.rend(); ++curr_node) {
    int u = *curr_node;
    
    // se il nodo di questo grafo e' pari a due, allora dobbiamo
    // controllare se riesce a formare una cricca.
    if (G_inc[u].size() == 2) {
      int v = G_inc[u][0];
      int k = G_inc[u][1];

      // per vedere se i nodi sono connessi fra loro, non ho bisogno
      // di controllarlo nel grafo iniziale, mi basta quello indotto!
      // (qui c'e' il trucco :P)
      if (find(G_inc[v].begin(), G_inc[v].end(), k) != G_inc[v].end()
	  || find(G_inc[k].begin(), G_inc[k].end(), v) != G_inc[k].end()) {
	++count;
      }
    }
  }

  cout << count << endl;
}
