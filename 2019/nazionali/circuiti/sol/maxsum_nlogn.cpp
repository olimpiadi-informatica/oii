#include "util.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

void solveSum(int N) {}

void solvePrefixSum(int N) {}

void solveCountPrimes(int N, int maxV) {}

void maxSumRec(Array in, Array out, std::string mid) {
  if (in.size() == 1) {
    out[0] = Operation(in[0], "max", 0);
    return;
  }
  int sp = in.size() / 2;
  Array rec(mid + "_rec", 3);
  maxSumRec(in.slice(0, sp), rec.slice(0, 1), mid + "1");
  maxSumRec(in.slice(sp, in.size()), rec.slice(1, 2), mid + "2");
  Array imp(mid + "_imp", 2);
  Array pre(mid + "_pre", in.size() - sp);
  scan(in.slice(sp, in.size()), pre, mid + "p", "+", 0);
  reduce(pre, imp.slice(0, 1), mid + "pm", "max", 0);
  Array suf(mid + "_suf", sp);
  scan(in.slice(0, sp).reverse(), suf, mid + "s", "+", 0);
  reduce(suf, imp.slice(1, 2), mid + "sm", "max", 0);
  rec[2] = Operation(imp[0], "+", imp[1]);
  reduce(rec, out, mid + "m", "max", 0);
}

void solveMaxSubarray(int N) {
  Array in("in", N);
  Array out("out", 1);
  maxSumRec(in, out, "lay");
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
