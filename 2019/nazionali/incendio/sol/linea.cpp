/*
 *  Soluzione di incendio: caso particolare con fuochi sulla stessa linea orizzontale.
 */

#include <bits/stdc++.h>

/*
 *  N = dim griglia
 *  M = num incendi
 *  X = coordinate x degli incendi
 *  Y = coordinate y degli incendi
*/
int alzati(int N, int M, int X[], int Y[])
{
  std::sort(Y, Y+M);
  int sol = std::max(N-Y[M-1]-1, Y[0]);

  for (int i = 1; i < M; i++)
  {
    int dist = (Y[i]-Y[i-1]-1);
    sol = std::max(sol, dist/2 + (dist%2));
  }
  return sol-1;
}
