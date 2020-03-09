/**
 *  Soluzione di incendio.
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: Per ogni coppia di fuochi i,j crea un evento (distanza(i,j), i, j)
 *  Per ogni fuoco crea due eventi (distanza(i, muro), i, muro) (più vicino tra UP/DX e DW/SX)
 *  Scorre gli eventi in ordine crescente di distanza unendo con una unionfind i fuochi/muri tra loro
 *  Si ferma quando due muri separati da scuola/hotel sono collegati
 *
 *  Tempo: O(M² * alpha)    (alpha = inversa di ackermann)
 *  Spazio: O(M²)
 */

#include <bits/stdc++.h>

std::vector<std::tuple<int,int,int>> E;
std::vector<int> uf, rank;

void makeSet(int n)
{
  uf = std::vector<int>(n);
  rank = std::vector<int>(n, 1);
  std::iota(uf.begin(), uf.end(), 0);
}

int find(int i){ return (uf[i] == i) ? i : (uf[i] = find(uf[i])); }

bool sameSet(int i, int j){ return find(i) == find(j); }

void unionSet(int x, int y)
{
    int xr = find(x);
    int yr = find(y);
    if(rank[xr] < rank[yr]) uf[xr] = yr;
    else if(rank[xr] > rank[yr]) uf[yr] = xr;
    else{ rank[xr]++; uf[yr] = xr;}
}

int alzati(int N, int M, int X[], int Y[]) {

  auto dist = [&](int i, int j){
    int dx = std::abs(X[i] - X[j]);
    int dy = std::abs(Y[i] - Y[j]);
    if (dx == 0 || dy == 0) return (dx + dy) / 2;
    return (dx + dy - 1) / 2;
  };

  for(int i=0; i<M; i++)
    for(int j=i+1; j<M; j++)
      E.emplace_back(dist(i, j), i, j);

  for(int i = 0; i < M; i++)
  {
    if( X[i] < N-1-Y[i] ) E.emplace_back(    X[i], i, M+0);
    else E.emplace_back(N-1-Y[i], i, M+0);

    if( Y[i] < N-1-X[i] ) E.emplace_back(    Y[i], i, M+1);
    else E.emplace_back(N-1-X[i], i, M+1);
  }

  std::sort(E.begin(), E.end());
  makeSet(M+2);

  int sol = 0;
  for(auto e : E)
  {
    unionSet(std::get<1>(e), std::get<2>(e));
    if(sameSet(M, M+1))
    {
      sol = std::get<0>(e)-1;
      break;
    }
  }

  for (int i = 0; i < M; i++)
  {
    sol = std::min(sol, N - 1 - X[i] + N - 1 - Y[i] - 1);
    sol = std::min(sol, X[i] + Y[i] - 1);
  }

  return sol;
}

