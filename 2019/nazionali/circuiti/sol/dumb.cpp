#include "util.hpp"
#include <cassert>

void solveSum(int N) {
    assert(false);
}

// profondità O(N)
// operazioni O(N²)
void solvePrefixSum(int N) {
    Array in("in", N);
    Array out("out", N);
    out[0] = Operation(in[0], "+", 0);
    for (int i = 1; i < N; i++) {
        Array tmp("tmp" + std::to_string(i), i);
        tmp[0] = Operation(in[0], "+", 0);
        for (int j = 1; j < i; j++)
            tmp[j] = Operation(tmp[j-1], "+", in[j]);
        out[i] = Operation(tmp[i-1], "+", in[i]);
    }
}

// profondità O(N)
// operazioni O(N³)
void solveMaxSubarray(int N) {
    Array in("in", N);
    Array out("out", 1);
    Array max_("max", N*(N+1)+1);
    int index = 0;
    int tempIndex = 0;
    for (int i = 0; i < N; i++) {
        max_[index++] = Operation(in[i], "max", 0);
        if (i < N-1)
            max_[index++] = Operation(in[i], "+", in[i+1]);
        for (int j = i+2; j < N; j++) {
            Array temp("temp" + std::to_string(tempIndex++), j-i+1);
            temp[0] = Operation(in[i], "+", in[i+1]);
            int l = 1;
            for (int k = i+2; k < j; k++, l++)
                temp[l] = Operation(temp[l-1], "+", in[k]);
            max_[index++] = Operation(temp[l-1], "+", in[j]);
        }
    }
    Array last("last", index);
    last[0] = Operation(max_[0], "max", max_[1]);
    for (int i = 1; i < index-2; i++)
        last[i] = Operation(last[i-1], "max", max_[i+1]);
    out[0] = Operation(last[index-3], "max", max_[index-1]);
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
