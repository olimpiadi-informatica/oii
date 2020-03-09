/**
 *  Soluzione di incendio.
 *
 *  Autore: Massimo Cairo
 *
 *  Descrizione: Calcola quando si crea una frontiera di fuoco che unisce i bordi left-bottom (LB) con right-top (RT).
 *  Il calcolo è una bottleneck shortest path, calcolato con una variante di Dijkstra.
 *
 *  Tempo: O(M² log M)
 *  Spazio: O(M)
 */


#include <queue>
#include <utility>
#include <algorithm>

#include <cstdio>

const int M_MAX = 20000;

int N, M, LB, RT;
int *X, *Y;

bool T[M_MAX + 2]; // node visited
int D[M_MAX + 2]; // distance from LB

auto compute_dist = [&](int i, int j)
{
  if( (i == LB || j == LB) && (i == RT || j == RT) ) return N;
  if( i == LB || j == LB ) return std::min(X[j+i-LB], N-1-Y[i+j-LB]);
  if( i == RT || j == RT ) return std::min(Y[i+j-RT], N-1-X[i+j-RT]);
  int dx = std::abs(X[i] - X[j]);
  int dy = std::abs(Y[i] - Y[j]);
  return (dx + dy - 1) / 2;
};


int alzati(int N, int M, int X[], int Y[]) {
  ::N = N;
  ::M = M;
  ::X = X;
  ::Y = Y;

  ::LB = M;
  ::RT = M+1;

  std::priority_queue<std::pair<int, int>> Q;

  for(int i = 0; i < M+2; i++) D[i] = N;
  D[LB] = 0;

  Q.push(std::make_pair(-D[LB], LB));

  while(!Q.empty()) {
    auto p = Q.top();
    int i = p.second;

    Q.pop();

    if(T[i]) continue;
    T[i] = true;

    for(int j = 0; j < M+2; j++) {
      int d = std::max(D[i], compute_dist(i, j));
      if(d >= D[j]) continue;
      D[j] = d;
      Q.push(std::make_pair(-D[j], j));
    }
  }

  return D[RT] - 1;
}
