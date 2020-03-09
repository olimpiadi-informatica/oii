#include "util.hpp"
#include <cassert>
#include <vector>

void solveSum(int N) {
    assert(false);
}

void solvePrefixSum(int N) {
    assert(false);
}

// profondità O(logN)
// operazioni O(N²)
void solveMaxSubarray(int N) {
    Array in("in", N);
    Array out("out", 1);
    Array max("max", N*(N+1)/2);
    int index = 0;
    std::vector<std::vector<int>> cache(N+1);
    cache[1].resize(N);
    for (int i = 0; i < N; i++) {
        cache[1][i] = index;
        max[index++] = Operation(in[i], "+", 0);
    }

    for (int len = 2; len < N; len++) {
        cache[len].resize(N-len+1);
        int a = len/2;
        int b = len-a;
        for (int i = 0; i < N-len+1; i++) {
            int left = cache[a][i];
            int right = cache[b][i+a];
            cache[len][i] = index;
            max[index++] = Operation(max[left], "+", max[right]);
        }
    }
    max[index++] = Operation(max[cache[1][0]], "+", max[cache[N-1][1]]);
    reduce(max, out, "last", "max", 0);
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
