#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string.h>
#include <string>

using namespace std;

#define INFTY 1000000000

const int MAXH = 100;
const int MAXW = 100;

int H, W;
int A[MAXH + 2][MAXW + 2];

int S;
bool V[MAXH + 2][MAXW + 2];

bool greedy_dfs(int i, int j, int val) {
  if (V[i][j])
    return false;
  V[i][j] = true;

  if (i == H && j == W) {
    S = val;
    return true;
  }

  int dirs[4][2] = {
      {0, +1},
      {0, -1},
      {+1, 0},
      {-1, 0},
  };

  int deltas[4];

  for (int dir = 0; dir < 4; dir++) {
    int ii, jj;
    ii = i + dirs[dir][0];
    jj = j + dirs[dir][1];
    deltas[dir] = std::abs(A[i][j] - A[ii][jj]);
  }

  int order[4] = {0, 1, 2, 3};
  std::sort(order, order + 4,
            [&](int d1, int d2) { return deltas[d1] < deltas[d2]; });

  for (int g = 0; g < 4; g++) {
    int dir = order[g];
    int ii, jj;
    ii = i + dirs[dir][0];
    jj = j + dirs[dir][1];

    if (greedy_dfs(ii, jj, std::max(val, deltas[dir]))) {
      return true;
    }
  }
  return false;
}

int compute() {
  for (int i = 1; i <= H; i++)
    V[i][0] = V[i][W + 1] = true;
  for (int j = 1; j <= W; j++)
    V[0][j] = V[H + 1][j] = true;
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      V[i][j] = 0;
    }
  }
  greedy_dfs(1, 1, 0);
  return S;
}

void solve(int t) {
  cin >> H >> W;

  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      cin >> A[i][j];
    }
  }

  cout << "Case #" << t << ": " << compute() << endl;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    solve(t);
  }
}
