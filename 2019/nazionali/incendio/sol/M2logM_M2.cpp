/**
 *  Soluzione di incendio.
 *
 *  Autore: Massimo Cairo
 *
 *  Descrizione: Calcola quando si crea una frontiera di fuoco che unisce i bordi left-bottom (LB) con right-top (RT).
 *  Il calcolo è una bottleneck shortest path, calcolato con una variante di Dijkstra.
 *
 *  Tempo: O(M² log M)
 *  Spazio: O(M²)
 */


#include <queue>
#include <utility>
#include <algorithm>

#include <cstdio>

const int M_MAX = 10000;

int N, M;
int *X, *Y;

int dist[M_MAX + 2][M_MAX + 2]; // distance matrix

bool T[M_MAX + 2]; // node visited
int D[M_MAX + 2]; // distance from LB

int compute_dist(int i, int j) {
  int dx = std::abs(X[i] - X[j]);
  int dy = std::abs(Y[i] - Y[j]);

  if (dx == 0 || dy == 0) return (dx + dy) / 2;
  return (dx + dy - 1) / 2;
}

int alzati(int N, int M, int X[], int Y[]) {
  ::N = N;
  ::M = M;
  ::X = X;
  ::Y = Y;

  const int LB = M, RT = M+1;

  for(int i = 0; i < M; i++) {
    for(int j = 0; j < M; j++) {
      dist[i][j] = compute_dist(i, j);
      // fprintf(stderr, "dist[%2d][%2d] = %2d\n", i, j, dist[i][j]);
    }
  }

  for(int i = 0; i < M; i++) {
    dist[i][LB] = dist[LB][i] = std::min(X[i], N-1-Y[i]);
    dist[i][RT] = dist[RT][i] = std::min(Y[i], N-1-X[i]);
  }

  dist[LB][RT] = dist[RT][LB] = N;

  std::priority_queue<std::pair<int, int>> Q;

  for(int i = 0; i < M+2; i++) {
    D[i] = N;
  }
  D[LB] = 0;

  Q.push(std::make_pair(-D[LB], LB));

  while(!Q.empty()) {
    auto p = Q.top();
    int i = p.second;

    Q.pop();
    
    if(T[i]) continue;
    T[i] = true;

    for(int j = 0; j < M+2; j++) {
      int d = std::max(D[i], dist[i][j]);

      // fprintf(stderr, "%2d -%2d: %2d (%2d)\n", i, j, dist[i][j], d);

      if(d >= D[j]) continue;
      D[j] = d;
      Q.push(std::make_pair(-D[j], j));
    }
  }

  return D[RT] - 1;
}
