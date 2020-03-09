/*
 * Soluzione di incendio.
 *
 * Autore: Gaspare Ferraro
 *
 * Descrizione: Per ogni cella calcola tra quanto questa prenderà fuoco.
 * Poi dinamica sulla matrice delle distanze
 *
 *  Tempo: O(N²M)
 * Spazio: O(N²)
 */


#include <bits/stdc++.h>

int alzati(int N, int M, int X[], int Y[])
{
//  assert(N <= 10000); // Wow, so much memory

  std::vector<std::vector<int>> G(N+1, std::vector<int>(N+1, N));

  for(int i=0; i<=N; i++) G[i][0] = G[0][i] = 0;
  G[1][0] = G[0][1] = N;

  for(int i=1; i<=N; i++)
  for(int j=1; j<=N; j++)
  {
    for(int k=0; k<M; k++)
      G[i][j] = std::min(G[i][j], std::abs(i-1-X[k]) + std::abs(j-1-Y[k]));
    G[i][j] = std::min(G[i][j], std::max(G[i-1][j], G[i][j-1]));
  }

  return G[N][N]-1;
}
