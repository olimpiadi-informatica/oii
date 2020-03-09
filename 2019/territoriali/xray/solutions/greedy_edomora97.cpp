#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 1000;

int compute(int N, int vec[MAXN + 2]) {
  int risp = 0;
  for (int i = 1; i <= N; i++) {
      while (vec[i]) {
          risp++;
          for (int j = i; j <= N; j++) {
              if (!vec[j]) break;
              vec[j]--;
          }
      }
  }

  return risp;
}

void solve(int t) {
  int N;
  cin >> N;
  int vec[MAXN + 2];

  vec[0] = vec[N + 1] = 0;
  for (int i = 1; i <= N; i++) {
    cin >> vec[i];
  }

  cout << "Case #" << t << ": " << compute(N, vec) << endl;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    solve(t);
  }
}
