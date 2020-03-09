#include "util.hpp"
#include <cassert>

void solveSum(int N) {
    assert(false);
}

// logN / N²
void solvePrefixSum(int N) {
    Array in("in", N);
    Array out("out", N);
    for (int i = 0; i < N; i++) {
        reduce(in.slice(0, i+1), out.slice(i, i+1), "tmp" + std::to_string(i), "+", 0);
    }
}

// logN / N³
void solveMaxSubarray(int N) {
    Array in("in", N);
    Array out("out", 1);
    Array max_("max", N*(N+1)/2);
    int index = 0;
    int tempIndex = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            reduce(in.slice(i, j+1), max_.slice(index, index+1), "temp" + std::to_string(tempIndex++), "+", 0);
            index++;
        }
    }
    reduce(max_, out, "last", "max", 0);
}

int main() {
  int t;
  int N;
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
  case 3:
    std::cin >> N;
    solveMaxSubarray(N);
    break;
  default:
    return 1;
  };
}
