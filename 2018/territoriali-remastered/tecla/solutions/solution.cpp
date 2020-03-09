/* solutore oddcycle
   Romeo 2017-03-15
*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#define DEBUG 0

using namespace std;

const unsigned MAXN = 30;
int seen[MAXN];
int sex[MAXN];
int cycle[MAXN], posW = 0;

int N, M, L;
vector<int> adj[MAXN];

bool odd_cycle(int node, int mysex) {
  if (seen[node]) {
    if (sex[node] != mysex) {
      cycle[posW++] = node;
      L = posW;
      return true;
    } else
      return false;
  }
  seen[node] = 1;
  sex[node] = mysex;
  cycle[posW++] = node;
  for (int next : adj[node])
    if (odd_cycle(next, 1 - mysex))
      return true;
  posW--;
  return false;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    memset(seen, 0, sizeof seen);
    memset(sex, 0, sizeof sex);
    memset(cycle, 0, sizeof cycle);
    L = 0;
    posW = 0;

    cin >> N >> M;
    for (int i = 0; i < N; i++)
      adj[i].clear();

    for (int i = 0; i < M; i++) {
      int a, b;
      cin >> a >> b;
      assert(0 <= a && a < N);
      assert(0 <= b && b < N);
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    assert(odd_cycle(0, 0));

    int visitedTwice = cycle[L - 1];
    bool repeat = false;
    for (int i = L - 2; i >= 0; i--) {
      if (repeat)
        cycle[L++] = cycle[i];
      if (cycle[i] == visitedTwice)
        repeat = true;
    }

    cout << "Case #" << t << ":" << endl << L - 1 << endl;
    for (int i = 0; i < L; i++)
      cout << cycle[i] << " ";
    cout << endl;
  }

  return 0;
}
