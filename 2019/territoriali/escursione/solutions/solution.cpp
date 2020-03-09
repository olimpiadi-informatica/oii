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

int A[MAXH + 2][MAXW + 2];
int D[MAXH + 2][MAXW + 2];
int H, W;

int compute() {
  priority_queue<pair<int, pair<int, int>>> q;

  q.push(make_pair(0, make_pair(1, 1)));

  while (!q.empty()) {
    auto top = q.top();
    q.pop();

    if (D[top.second.first][top.second.second] != INFTY)
      continue;

    D[top.second.first][top.second.second] = -top.first;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i * j == 0) {
          q.push(make_pair(
              -max(-top.first,
                   abs(A[top.second.first][top.second.second] -
                       A[top.second.first + i][top.second.second + j])),
              make_pair(top.second.first + i, top.second.second + j)));
        }
      }
    }
  }
  return D[H][W];
}

void solve(int t) {
  cin >> H >> W;

  memset(D, 0, sizeof(D));

  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      cin >> A[i][j];
      D[i][j] = INFTY;
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
