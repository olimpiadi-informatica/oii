/**
 * Descrizione: Prova tutti i possibili intervalli degli irrigatori e sceglie la
 * soluzione migliore.
 * Autore: Edoardo Morassutto
 * Complessità: O(tanto)
 */
#include <algorithm>
#include <cstdlib>
#include <vector>

using ll = long long;

int N;
int C;
std::vector<std::pair<int, int>> seeds;

void posiziona(int D, int T);

void budget(int B);

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

std::pair<ll, std::vector<tri_t>> f(int i)
{
    if (i >= N)
        return std::make_pair(0, std::vector<tri_t>());
    ll best_cost = 1e18;
    std::vector<tri_t> best_tri;
    tri_t cur_triang = tri_from_point(seeds[i].first, seeds[i].second);
    for (int k = i; k < N; k++) {
        cur_triang = extend_triang(cur_triang,
            tri_from_point(seeds[k].first, seeds[k].second));
        auto res = f(k + 1);
        ll new_cost = res.first + cost(cur_triang) + C;
        if (new_cost < best_cost) {
            best_cost = new_cost;
            best_tri = res.second;
            best_tri.push_back(cur_triang);
        }
    }
    return std::make_pair(best_cost, best_tri);
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
    auto res = f(0).second;
    for (int k = 0; k < res.size(); k++) {
        W[k] = tip(res[k]);
        T[k] = cost(res[k]);
    }

    int out = 0;
    for (int i = 0; i < res.size(); i++) {
        out += C + T[i];
        posiziona(W[i], T[i]);
    }
    budget(out);
}
