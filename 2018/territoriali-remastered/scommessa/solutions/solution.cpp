#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 150;

int solve(int tc) {
  int nums[MAX_N] = {};
  int parity[MAX_N] = {};
  int prefix[MAX_N] = {};
  int suffix[MAX_N] = {};

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> nums[i];
    parity[i] = (nums[i] % 2 == 0) ? 1 : -1;
  }

  for (int i = 0; i < N - 1; i++)
    prefix[i + 1] = prefix[i] + parity[i];
  for (int i = N - 1; i >= 1; i--)
    suffix[i - 1] = suffix[i] + parity[i];

  vector<int> sol;
  for (int i = 0; i < N; i++)
    if (prefix[i] == 0 && suffix[i] == 0)
      sol.push_back(nums[i]);

  cout << "Case #" << tc << ": ";
  cout << sol.size() << endl;
  for (int n : sol)
    cout << n << ' ';
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);
}
