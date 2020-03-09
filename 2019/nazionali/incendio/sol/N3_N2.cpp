/*
 *  Soluzione di incendio.
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: Simulazione l'evoluzione della griglia, ad ogni istante espande i fuochi
 *  e controlla con una bfs se è possibile raggiungere (N-1, N-1) partendo da (0,0)
 *
 *  Tempo: O(N³)
 *  Spazio: O(N²)
 */

#include <bits/stdc++.h>

int N, sol = 0;
std::vector<std::vector<bool>> G;
std::queue<std::pair<int,int>> F;

bool reach()
{
  if(G[0][0] || G[N-1][N-1]) return false;

  std::vector<std::vector<bool>> S(N, std::vector<bool>(N, false));
  std::queue<std::array<int, 2>> Q;

  Q.push({0,0});

  while(!Q.empty() && !S[N-1][N-1])
  {
    auto f = Q.front();
    int x = f[0], y = f[1];
    Q.pop();

    if(S[x][y]) continue;
    S[x][y] = true;

    if(x < N-1 && !G[x+1][y] && !S[x+1][y+0]) Q.push({x+1, y+0});
    if(y < N-1 && !G[x][y+1] && !S[x+0][y+1]) Q.push({x+0, y+1});

    if(x > 0 && !G[x-1][y] && !S[x-1][y+0]) Q.push({x-1, y+0});
    if(y > 0 && !G[x][y-1] && !S[x+0][y-1]) Q.push({x+0, y-1});
  }

  return S[N-1][N-1];
}

void step()
{
  auto size = F.size();
  sol++;

  while(size > 0)
  {
    auto f = F.front();
    int x = f.first;
    int y = f.second;

    F.pop();
    size--;

    if(x > 0 && !G[x-1][y])
    {
      F.emplace(x-1, y);
      G[x-1][y] = true;
    }

    if(y > 0 && !G[x][y-1])
    {
      F.emplace(x, y-1);
      G[x][y-1] = true;
    }

    if(x < N-1 && !G[x+1][y])
    {
      F.emplace(x+1, y);
      G[x+1][y] = true;
    }

    if(y < N-1 && !G[x][y+1])
    {
      F.emplace(x, y+1);
      G[x][y+1] = true;
    }
  }
}

int alzati(int N, int M, int X[], int Y[])
{
  ::N = N;
  G.resize(N, std::vector<bool>(N, false));

  for(int i=0; i<M; ++i) G[X[i]][Y[i]] = true;
  for(int i=0; i<M; ++i) F.emplace(X[i], Y[i]);

  while(reach()) step();

  return sol-1;
}
