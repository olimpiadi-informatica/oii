#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cassert>

using namespace std;

#define INF 100000000
#define MOD 46337ULL

int F[5000000];
int D0 = 0;
int MLEN = INF;

typedef long long ull;

ull raise(ull x, ull y) {
  ull sol = 1;
  ull mult = x;
  while (y) {
    if (y & 1) sol = (sol * mult) % MOD;
    y >>= 1;
    mult = (mult * mult) % MOD;
  }
  return sol;
}

unordered_map<int, int> hmap_mult;

int molt = 0;

void divide(ull num) {
  hmap_mult[num]--;
  if (hmap_mult[num] == 0) hmap_mult.erase(hmap_mult.find(num));
}

void multiply(ull num) {
  hmap_mult[num]++;
}

ull get() {
  ull res = 1;

  for (auto [factor, moltepl] : hmap_mult) {
    res = (res * raise(factor, moltepl)) % MOD;
  }
  return res;
}

int conta(int N, int K, std::vector<int>& V) {

  ull result = 0;

  int len = 0;
  for (int i = 0; i < V.size(); i++) {
    F[V[i]]++;
    if (F[V[i]] == 1) D0++;
    len++;

    while (D0 == K) {
      MLEN = min(MLEN, len);
      len--;
      F[V[i-len]]--;
      if (F[V[i-len]] == 0) D0--;
    }
  }

  D0 = 0;
  memset(F, 0, sizeof(F));
  for (int i = 0; i < V.size(); i++) {

    if (F[V[i]] !=  0) {
      divide(F[V[i]]);
    }

    F[V[i]]++;
    if (F[V[i]] == 1) D0++;

    multiply(F[V[i]]);

    if (i >= MLEN-1) {

      if (D0 == K) {
        result = (result + get()) % MOD;
      }
      divide(F[V[i-(MLEN-1)]]);
      F[V[i-(MLEN-1)]]--;
      if (F[V[i-(MLEN-1)]] == 0) D0--;
      else multiply(F[V[i-(MLEN-1)]]);
    }
  }

  return result % MOD;
}

// a b c a
