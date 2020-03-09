#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 1000;

void solve(int t) {
  int N;
  cin >> N;

  int answer = 0;
  for (int i = 1; i <= N; i++) {
    int x;
    cin >> x;

    if (x > answer) answer = x;
  }

  cout << "Case #" << t << ": " << answer << endl;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    solve(t);
  }
}
