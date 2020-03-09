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

#define MAX_MAP_SIZE 10000007
int MAP_SIZE = 0;

struct map_entry {
  int key;
  int value;
  int link_entry;
};

map_entry hmap_mult[MAX_MAP_SIZE];

struct link_entry {
  int value;
  int prev;
  int next;
};

link_entry linked[MAX_MAP_SIZE];

int head = 0;
int tail = 0;
int next_alloc = 1;

int ll_add_entry(int value) {
  int alloc = next_alloc++;
  if (!head) head = alloc;
  if (!tail) tail = alloc;
  else linked[tail].next = alloc;
  linked[alloc] = { value, tail, 0 };
  tail = alloc;
  return alloc;
}

void ll_rem_entry(int pos) {

  link_entry &entry = linked[pos];
  if (!entry.prev) {
    head = entry.next;
    linked[head].prev = 0;
  }
  else linked[entry.prev].next = entry.next;

  if (!entry.next) {
    tail = entry.prev;
    linked[tail].next = 0;
  }
  else linked[entry.next].prev = entry.prev;

  entry = {0};
}

template<class F>
void ll_iterate(F func) {
  if (!head) return;
  int crt = head;
  while (crt) {
    func(hmap_mult[linked[crt].value]);
    crt = linked[crt].next;
  }
}


void hmap_add_one(int factor) {
  int pos = factor % MAP_SIZE;

  while (hmap_mult[pos].key && hmap_mult[pos].key != factor) pos = (pos + 1) % MAP_SIZE;

  hmap_mult[pos].key = factor;
  hmap_mult[pos].value++;
  if (!hmap_mult[pos].link_entry) {
    hmap_mult[pos].link_entry = ll_add_entry(pos);
  }
}

void hmap_rem_one(int factor) {
  int pos = factor % MAP_SIZE;

  while (hmap_mult[pos].key && hmap_mult[pos].key != factor) pos = (pos + 1) % MAP_SIZE;

  if (!--hmap_mult[pos].value) {
    ll_rem_entry(hmap_mult[pos].link_entry);
    hmap_mult[pos] = {0};
  }
}

int molt = 0;

#define OPTIM_RANGE 32

int S[OPTIM_RANGE];

void divide(ull num) {
  if (num == 1) return;
  if (num < OPTIM_RANGE) {
    S[num]--;
    return;
  }

  // cout << "Removing " << num << endl;
  hmap_rem_one(num);
}

void multiply(ull num) {
  if (num == 1) return;
  if (num < OPTIM_RANGE) {
    S[num]++;
    return;
  }
  // cout << "************************************** Pushing" << hmap_mult.size() << endl;
  hmap_add_one(num);
}

ull get() {
  ull res = 1;

  for (int i = 2; i < OPTIM_RANGE; i++) {
    res = (res * raise(i, S[i])) % MOD;
  }

  ll_iterate([&] (map_entry &a) {
    auto [factor, moltepl, _] = a;
    res = (res * raise(factor, moltepl)) % MOD;
  });
  return res;
}

int conta(int N, int K, std::vector<int>& V) {

  MAP_SIZE = min((int)V.size() * 10, MAX_MAP_SIZE);

  // cout << K << " " << val << endl;
  // // assert(K == val);
  // for (auto x : V) {
  //     cout << x << " ";
  // }
  // cout << endl;

  // return 0;

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
  // cout << MLEN << " " << K*2 - 9 << endl;
  // return 0;
  // cout << "Completed first pass" << endl;
  // cout << "Completed 1" << endl;


  ull result = 0;

  D0 = 0;
  memset(F, 0, sizeof(F));
  for (int i = 0; i < V.size(); i++) {
    // if (i % 10000 == 0) {
      // cout << "Pushed! " << i << " " << hmap_mult.size() << endl;
      // for (auto x : hmap_mult) {
      //   cout << x << " ";
      // }
      // cout << endl;
    // }
    if (F[V[i]] !=  0) {
      divide(F[V[i]]);
    }

    F[V[i]]++;
    if (F[V[i]] == 1) D0++;

    multiply(F[V[i]]);

    if (i >= MLEN-1) {

      if (D0 == K) {
        // ull rescmp = 1;
        // for (int k = 0; k < K; k++) {
        //   rescmp = (rescmp * (F[k] % MOD)) % MOD;
        // }
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
