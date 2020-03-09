/**
 *  Soluzione di incendio.
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: Come M2_cairo ma riduce di un fattore log(M) rimuovendo la priority queue
 *
 *  Tempo: O(M²)
 *  Spazio: O(M²)
 */


#include <queue>
#include <utility>
#include <algorithm>

#include <cstdio>

const int M_MAX = 10000;

int dist[M_MAX + 2][M_MAX + 2]; // distance matrix

bool T[M_MAX + 2]; // node visited
int D[M_MAX + 2]; // distance from LB
bool V[M_MAX + 2]; // distance from LB

int alzati(int N, int M, int X[], int Y[])
{
  const int LB = M, RT = M+1;

  auto compute_dist = [&](int i, int j)
  {
    int dx = std::abs(X[i] - X[j]);
    int dy = std::abs(Y[i] - Y[j]);
    return (dx == 0 || dy == 0) ? (dx + dy) / 2 : (dx + dy - 1) / 2;
  };

  for(int i = 0; i < M; i++)
    for(int j = 0; j < M; j++)
      dist[i][j] = compute_dist(i, j);

  for(int i = 0; i < M+0; i++) dist[i][LB] = dist[LB][i] = std::min(X[i], N-1-Y[i]);
  for(int i = 0; i < M+0; i++) dist[i][RT] = dist[RT][i] = std::min(Y[i], N-1-X[i]);
  for(int i = 0; i < M+2; i++) D[i] = N;

  dist[LB][RT] = dist[RT][LB] = N;
  D[LB] = 0;

  while( true )
  {
    int i = -1;

    for(int j=0; j<M+2; j++)
      if( !T[j] && ( i == -1 || D[i] > D[j] ) )
        i = j;

    if(i == -1) break;
    if(T[i]) continue;

    T[i] = true;

    for(int j = 0; j < M+2; j++) {
      int d = std::max(D[i], dist[i][j]);
      D[j] = std::min(D[j], d);
    }
  }

  return D[RT] - 1;
}
