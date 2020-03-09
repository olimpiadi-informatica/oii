#include "util.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

void lin_reduce(Array last_layer, Array output, std::string mid, std::string op,
                long long neutral) {
  int N = last_layer.size();
  Array m(mid, N);
  m[0] = Operation(last_layer[0], op, neutral);
  for (int i = 1; i < N; i++) {
    m[i] = Operation(last_layer[i], op, m[i - 1]);
  }
  output[0] = Operation(m[N - 1], op, neutral);
}

void lin_reduce(int N, std::string in, std::string out, std::string mid,
                std::string op, long long neutral) {
  Array last_layer = Array(in, N);
  Array output = Array(out, 1);
  lin_reduce(last_layer, output, mid, op, neutral);
}

void solveSum(int N) { lin_reduce(N, "in", "out", "lay", "+", 0); }

void lin_scan(Array in, Array out, std::string mid, std::string op,
              long long neutral, int depth) {
  int N = in.size();
  out[0] = Operation(in[0], op, neutral);
  for (int i = 1; i < N; i++) {
    out[i] = Operation(in[i], op, out[i - 1]);
  }
}

void lin_scan(Array input, Array output, std::string mid, std::string op,
              long long neutral) {
  lin_scan(input, output, mid, op, neutral, 0);
}

void lin_scan(int N, std::string in, std::string out, std::string mid,
              std::string op, long long neutral) {
  Array input = Array(in, N);
  Array output = Array(out, N);
  lin_scan(input, output, mid, op, neutral);
}

void solvePrefixSum(int N) { lin_scan(N, "in", "out", "lay", "+", 0); }

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
    lin_reduce(temp, min_mod, "min_mod_tmp_" + std::to_string(i), "min",
               std::numeric_limits<long long>::max());
    islp[i] = Operation(min_mod[0], "min", 1);
  }
  Array num_large = Array("num_large", 1);
  lin_reduce(islp, num_large, "sum_large", "+", 0);

  Array issp("is_small_prime", N * p.size());
  for (int i = 0; i < N; i++) {
    for (size_t j = 0; j < p.size(); j++) {
      issp[i * p.size() + j] = Operation(input[i], "==", p[j]);
    }
  }
  Array num_small = Array("num_small", 1);
  lin_reduce(issp, num_small, "sum_small", "+", 0);
  Array output = Array("out", 1);
  output[0] = Operation(num_small[0], "+", num_large[0]);
}

void solveMaxSubarray(int N) {
  Array in = Array("in", N);
  Array sum = Array("sum", N);
  Array nnegsum = Array("nnegsum", N);
  sum[0] = Operation(in[0], "+", 0);
  nnegsum[0] = Operation(sum[0], "max", 0);
  for (int i = 1; i < N; i++) {
    sum[i] = Operation(nnegsum[i - 1], "+", in[i]);
    nnegsum[i] = Operation(sum[i], "max", 0);
  }
  Array output = Array("out", 1);
  lin_reduce(nnegsum, output, "max", "max", 0);
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
