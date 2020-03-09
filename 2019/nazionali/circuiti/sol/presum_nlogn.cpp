#include "util.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

void solveSum(int N) {}

void costly_scan(Array in, Array out, std::string mid, std::string op,
                 long long neutral) {
  int N = in.size();
  Array last = in;
  for (int iter = 0; (1ULL << iter) < N; iter++) {
    Array cur(mid + "_" + std::to_string(iter), N);
    if ((2ULL << iter) >= N)
      cur = out;
    for (int i = 0; i < N; i++) {
      if (i < (1ULL << iter)) {
        cur[i] = Operation(last[i], op, neutral);
      } else {
        cur[i] = Operation(last[i], op, last[i - (1ULL << iter)]);
      }
    }
    last = cur;
  }
}

void costly_scan(int N, std::string in, std::string out, std::string mid,
                 std::string op, long long neutral) {
  Array input = Array(in, N);
  Array output = Array(out, N);
  costly_scan(input, output, mid, op, neutral);
}

void solvePrefixSum(int N) { costly_scan(N, "in", "out", "lay", "+", 0); }

void solveCountPrimes(int N, int maxV) {}

void solveMaxSubarray(int N) {}

int main() {
  int t;
  int N;
  int maxV;
  std::cin >> t;
  switch (t) {
  case 1:
    std::cin >> N;
    solveSum(N);
    break;
  case 2:
    std::cin >> N;
    solvePrefixSum(N);
    break;
  case 4:
    std::cin >> N >> maxV;
    solveCountPrimes(N, maxV);
    break;
  case 3:
    std::cin >> N;
    solveMaxSubarray(N);
    break;
  default:
    return 1;
  };
}
