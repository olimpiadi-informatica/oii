#include "util.hpp"

void solveSum(int N) { reduce(N, "in", "out", "lay", "+", 0); }

void solvePrefixSum(int N) { scan(N, "in", "out", "lay", "+", 0); }

std::vector<int> primes(int N) {
  std::vector<bool> prime(N + 1, true);
  std::vector<int> ans;

  for (int p = 2; p * p <= N; p++) {
    if (prime[p] == true) {
      ans.push_back(p);
      for (int i = p * 2; i <= N; i += p)
        prime[i] = false;
    }
  }
  return ans;
}

void solveCountPrimes(int N, int maxV) {
  std::vector<int> p = primes(maxV);
  Array input = Array("in", N);
  Array islp = Array("is_large_prime", N);
  for (int i = 0; i < N; i++) {
    Array temp = Array("mod_" + std::to_string(i), p.size());
    for (size_t j = 0; j < p.size(); j++) {
      temp[j] = Operation(input[i], "%", p[j]);
    }
    Array min_mod = Array("min_mod_" + std::to_string(i), 1);
    reduce(temp, min_mod, "min_mod_tmp_" + std::to_string(i), "min",
           std::numeric_limits<long long>::max());
    islp[i] = Operation(min_mod[0], "min", 1);
  }
  Array num_large = Array("num_large", 1);
  reduce(islp, num_large, "sum_large", "+", 0);

  Array issp("is_small_prime", N * p.size());
  for (int i = 0; i < N; i++) {
    for (size_t j = 0; j < p.size(); j++) {
      issp[i * p.size() + j] = Operation(input[i], "==", p[j]);
    }
  }
  Array num_small = Array("num_small", 1);
  reduce(issp, num_small, "sum_small", "+", 0);
  Array output = Array("out", 1);
  output[0] = Operation(num_small[0], "+", num_large[0]);
}

void solveMaxSubarray(int N) {
  Array input = Array("in", N);
  Array prefsum = Array("prefix_sum", N);
  scan(input, prefsum, "ps", "+", 0);
  Array maxprefsum = Array("max_pref_sum", N);
  scan(prefsum.reverse(), maxprefsum.reverse(), "sm", "max",
       std::numeric_limits<long long>::min());
  Array localmax = Array("localmax", N + 1);
  for (int i = 0; i < N; i++) {
    Array tmp = Array("tmp_" + std::to_string(i), 1);
    tmp[0] = Operation(maxprefsum[i], "-", prefsum[i]);
    localmax[i] = Operation(tmp[0], "+", input[i]);
  }
  localmax[N] = Operation(input[0], "max", 0);
  Array output = Array("out", 1);
  reduce(localmax, output, "max", "max", 0);
}

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
