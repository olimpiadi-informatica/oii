/*
 * Soluzione di incendio.
 *
 * Autore: Gaspare Ferraro
 *
 * Descrizione: Per ogni cella calcola tra quanto questa prenderà fuoco.
 * Poi dinamica sulla matrice delle distanze
 *
 *  Tempo: O(N²M)
 * Spazio: O(N)
 */


#include <bits/stdc++.h>

int alzati(int N, int M, int X[], int Y[])
{
  std::vector<int> oldR(N+1, 0), newR(N+1, 0);
  newR[0] = oldR[1] = N;

  for(int i=1; i<=N; i++)
  {
    for(int j=1; j<=N; j++)
    {
      newR[j] = N;
      for(int k=0; k<M; k++)
        newR[j] = std::min(newR[j], std::abs(i-1-X[k]) + std::abs(j-1-Y[k]));
      newR[j] = std::min(newR[j], std::max(oldR[j], newR[j-1]));
    }
    newR[0] = 0;
    std::swap(oldR, newR);
  }

  return oldR[N]-1;
}
