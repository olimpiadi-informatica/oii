#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cassert>
#include <utility>

using namespace std;

#define INF 100000000
#define MOD 46337

int F[10000000];
int D0 = 0;



constexpr int inverse_compute(int x) {
  int sol = 1;
  int mult = x;
  int y = MOD - 2;
  while (y) {
    if (y & 1) sol = (sol * mult) % MOD;
    y >>= 1;
    mult = (mult * mult) % MOD;
  }
  return sol;
}

template<class Function, std::size_t... Indices>
constexpr auto make_array_helper(Function f, std::index_sequence<Indices...>)
-> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)>
{
    return {{ f(Indices)... }};
}

template<int N, class Function>
constexpr auto make_array(Function f)
-> std::array<typename std::result_of<Function(std::size_t)>::type, N>
{
    return make_array_helper(f, std::make_index_sequence<N>{});
}


constexpr auto mem = make_array<MOD>(inverse_compute);



inline int inverse_get(int x) {
    return mem[x];
}

int value = 1;

inline void divide(int num) {
    value = (value * inverse_get(num)) % MOD;
}

inline void multiply(int num) {
    value = (value * num) % MOD;
}

inline int get() {
    return value;
}

int conta(int N, int K, std::vector<int>& V) {

  int result = 0;
  int MLEN = INF;

  int len = 0;
  for (int i = 0; i < V.size(); i++) {

    if (F[V[i]]) divide(F[V[i]]);

    if (++F[V[i]] == 1) D0++;
    else multiply(F[V[i]]);
    len++;

    while (D0 == K) {
      if (MLEN > len) {
        MLEN = len;
        result = 0;
      }
      if (MLEN == len) result = (result + get()) % MOD;
      len--;
      divide(F[V[i-len]]);
      if (!--F[V[i-len]]) D0--;
      else multiply(F[V[i-len]]);
    }
  }
  return result % MOD;
}

// a b c a
