/**
 *  Soluzione parziale di incendio.
 *
 *  Autore: edomora97
 *
 *  Descrizione: Fa una ricerca binaria sulla soluzione e controlla con una BFS
 *  N² se la destinazione è raggiungibile
 *
 *  Tempo: O(N² M log N)
 *  Spazio: O(N²)
 */

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

int alzati(int N, int M, int X[], int Y[]) {
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};
  std::vector<std::vector<bool>> used(N, std::vector<bool>(N, false));

  auto possibile = [&](uint32_t t) -> bool {
    for (int j = 0; j < M; j++)
      if (X[j] + Y[j] <= t)
        return false;
    for (auto &v : used)
      v.assign(N, false);
    std::queue<std::tuple<int, int>> q;
    q.emplace(0, 0);
    used[0][0] = true;
    while (!q.empty()) {
      int x, y;
      std::tie(x, y) = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int x0 = x + dx[i];
        int y0 = y + dy[i];
        if (x0 < 0 || x0 >= N || y0 < 0 || y0 >= N || used[x0][y0])
          continue;
        bool fuoco = false;
        for (int j = 0; j < M && !fuoco; j++)
          if (abs(x0 - X[j]) + abs(y0 - Y[j]) <= t)
            fuoco = true;
        if (fuoco)
          continue;
        if (x0 == N - 1 && y0 == N - 1)
          return true;
        used[x0][y0] = true;
        q.emplace(x0, y0);
      }
    }
    return used[N - 1][N - 1];
  };

  uint32_t lb = 0, ub = 2 * N;
  while (lb + 1 < ub) {
    auto t = (lb + ub) / 2;
    if (possibile(t)) {
      lb = t;
    } else {
      ub = t;
    }
  }
  return lb;
}
