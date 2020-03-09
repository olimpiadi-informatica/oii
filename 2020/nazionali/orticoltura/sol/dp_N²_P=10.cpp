/**
 * Descrizione: dinamica che cerca gli intervalli ottimi degli irrigatori.
 * Lo stato è l'inizio dell'intervallo, per calcolarlo prova tutte le possibili
 * fini e ricorre.
 * Autore: Edoardo Morassutto
 * Complessità: O(N) in spazio, O(N²) in tempo
 */
#include <algorithm>
#include <vector>

using ll = long long;

void posiziona(int D, int T);

void budget(int B);

int N;
int C;

std::vector<std::pair<int, int>> seeds;
std::vector<ll> DP_cost;
std::vector<int> DP_next;

ll f(int i) {
  if (i >= N) return 0;
  if (DP_cost[i] >= 0) return DP_cost[i];
  ll best_cost = 1e18;
  int bestk = i;
  for (int k = i; k < N; k++) {
    ll cost = f(k + 1) + (seeds[k].first - seeds[i].first + 10) / 2 + 5 + C;
    if (cost < best_cost) {
      best_cost = cost;
      bestk = k;
    }
  }
  DP_next[i] = bestk + 1;
  return DP_cost[i] = best_cost;
}

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P) {
  ::N = N;
  ::C = C;
  std::vector<int> W(N), T(N);

  for (int i = 0; i < N; i++) {
    seeds.emplace_back(X[i], P[i]);
  }
  std::sort(seeds.begin(), seeds.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
    return a.first - a.second < b.first - b.second;
  });
  DP_cost = std::vector<ll>(N, -1);
  DP_next = std::vector<int>(N, -1);
  f(0);
  int curr = 0;
  int k = 0;
  while (curr < N) {
    int next = DP_next[curr];
    W[k] = (seeds[next - 1].first + seeds[curr].first) / 2;
    T[k] = (seeds[next - 1].first - seeds[curr].first + 10) / 2 + 5;
    curr = next;
    k++;
  }

    int out = 0;
    for(int i=0; i<k; i++) {
      out += C + T[i];
      posiziona(W[i], T[i]);
    }
    budget(out);

}
