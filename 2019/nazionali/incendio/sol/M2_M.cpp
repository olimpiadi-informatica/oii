/**
 *  Soluzione di incendio.
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: Come M2_cairo ma riduce di un fattore log(M) rimuovendo la priority queue
 *
 *  Tempo: O(M²)
 *  Spazio: O(M)
 */

#include <queue>
#include <utility>
#include <algorithm>

#include <cstdio>

const int M_MAX = 20000;

bool V[M_MAX + 2]; // distance from LB
bool T[M_MAX + 2]; // node visited
int D[M_MAX + 2]; // distance from LB

int alzati(int N, int M, int X[], int Y[])
{
  const int LB = M, RT = M+1;

  auto compute_dist = [&](int i, int j)
  {
    if((i == LB || j == LB) && (i == RT || j == RT)) return N;
    if(i == LB || j == LB) return std::min(X[j+i-LB], N-1-Y[i+j-LB]);
    if(i == RT || j == RT) return std::min(Y[i+j-RT], N-1-X[i+j-RT]);

    int dx = std::abs(X[i] - X[j]);
    int dy = std::abs(Y[i] - Y[j]);
    return (dx == 0 || dy == 0) ? (dx + dy) / 2 : (dx + dy - 1) / 2;
  };

  for(int i = 0; i < M+2; i++) D[i] = N;
  D[LB] = 0;

  while( true )
  {
    int i = -1;

    for(int j=0; j<M+2; j++)
      if(!T[j] && (i == -1 || D[i] > D[j])) i = j;

    if(i == -1) break;
    if(T[i]) continue;

    T[i] = true;

    for(int j = 0; j < M+2; j++)
      D[j] = std::min(D[j], std::max(D[i], compute_dist(i,j)));

  }

  return D[RT] - 1;
}
