/**
 * Descrizione: Unisce due triangoli solo se nel farlo si risparmia rispetto al
 * non farlo. I semi sono ordinati per (X,P).
 *
 * Autore: Edoardo Morassutto
 * Complessità: O(N + sort)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

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

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P)
{
    std::vector<std::pair<int, int>> seeds;
    std::vector<int> W(N), T(N);

    for (int i = 0; i < N; i++) {
        seeds.emplace_back(X[i], P[i]);
    }
    std::sort(seeds.begin(), seeds.end());
    tri_t prev_triag = tri_from_point(seeds[0].first, seeds[0].second);
    int k = 0;
    for (int i = 1; i < N; i++) {
        tri_t cur_triag = tri_from_point(seeds[i].first, seeds[i].second);
        tri_t merged = extend_triang(prev_triag, cur_triag);
        if (cost(merged) + C <= cost(prev_triag) + C + cost(cur_triag) + C) {
            prev_triag = merged;
        } else {
            W[k] = tip(prev_triag);
            T[k] = cost(prev_triag);
            k++;
            prev_triag = cur_triag;
        }
    }
    W[k] = tip(prev_triag);
    T[k] = cost(prev_triag);
    k++;

    int out = 0;
    for (int i = 0; i < k; i++) {
        out += C + T[i];
        posiziona(W[i], T[i]);
    }
    budget(out);
}
