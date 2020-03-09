/**
 * Descrizione: dinamica che cerca gli intervalli ottimi degli irrigatori.
 * Lo stato è l'inizio dell'intervallo, per calcolarlo prova tutte le possibili
 * fini e ricorre. L'intervallo è mantenuto come il triangolo minimo che include
 * tutti i semi al suo interno.
 * Autore: Edoardo Morassutto
 * Complessità: O(N) in spazio, O(N²) in tempo
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using ll = long long;

void posiziona(int D, int T);

void budget(int B);

int N;
int C;

std::vector<std::pair<int, int>> seeds;
std::vector<ll> DP_cost;
std::vector<int> DP_next;

// begin triangle utils
using tri_t = std::pair<int, int>;
tri_t extend_triang(const tri_t& a, const tri_t& b)
{
    return tri_t(std::min(a.first, b.first), std::max(a.second, b.second));
}
tri_t tri_from_point(int x, int p) { return tri_t(x - p + 1, x + p - 1); }
int cost(const tri_t& tri) { return (tri.second - tri.first + 1) / 2 + 1; }
int tip(const tri_t& tri) { return (tri.second + tri.first) / 2; }
bool tri_intersect(const tri_t& a, const tri_t& b)
{
    return cost(a) + cost(b) >= cost(extend_triang(a, b));
}
// end triangle utils

ll f(int i)
{
    if (i >= N)
        return 0;
    if (DP_cost[i] >= 0)
        return DP_cost[i];
    ll best_cost = 1e18;
    int bestk = i;
    tri_t cur_triang = tri_from_point(seeds[i].first, seeds[i].second);
    for (int k = i; k < N; k++) {
        cur_triang = extend_triang(cur_triang,
            tri_from_point(seeds[k].first, seeds[k].second));
        ll new_cost = f(k + 1) + cost(cur_triang) + C;
        if (new_cost < best_cost) {
            best_cost = new_cost;
            bestk = k;
        }
    }
    DP_next[i] = bestk + 1;
    return DP_cost[i] = best_cost;
}

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P)
{
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
        tri_t cur_triag = tri_from_point(seeds[curr].first, seeds[curr].second);
        for (int i = curr + 1; i < next; i++) {
            cur_triag = extend_triang(
                cur_triag, tri_from_point(seeds[i].first, seeds[i].second));
        }
        W[k] = tip(cur_triag);
        T[k] = cost(cur_triag);
        curr = next;
        k++;
    }

    int out = 0;
    for (int i = 0; i < k; i++) {
        out += C + T[i];
        posiziona(W[i], T[i]);
    }
    budget(out);
}
