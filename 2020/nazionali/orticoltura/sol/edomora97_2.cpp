/**
 * Descrizione: Dopo una scansione per togliere i semi inutili, unisce i semi i
 * cui triangoli si intersecano, poi unisce questi nuovi triangoli se il costo
 * individualmente è maggiore di quello combinato. Memorizza i triangoli usando
 * le coordiante dei vertici a P=1.
 *
 * Autore: Edoardo Morassutto
 * Complessità: O(N + sort)
 */
#include <algorithm>
#include <iostream>
#include <vector>

void posiziona(int D, int T);

void budget(int B);

using ll = long long;

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
bool inside(const tri_t& out, const tri_t& in)
{
    return out == extend_triang(out, in);
}
// end triangle utils

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P)
{
    std::vector<std::pair<int, int>> seeds;
    std::vector<int> W(N), T(N);

    for (int i = 0; i < N; i++) {
        seeds.emplace_back(X[i], P[i]);
    }
    std::sort(seeds.begin(), seeds.end(), [](auto a, auto b) {
        return a.first - a.second < b.first - b.second;
    });
    std::vector<int> pruned;
    for (int i = 0; i < N; i++) {
        tri_t tri = tri_from_point(seeds[i].first, seeds[i].second);
        while (!pruned.empty()) {
            tri_t last = tri_from_point(seeds[pruned.back()].first,
                seeds[pruned.back()].second);
            if (inside(tri, last)) {
                pruned.pop_back();
            } else {
                break;
            }
        }
        if (!pruned.empty()) {
            tri_t last = tri_from_point(seeds[pruned.back()].first,
                seeds[pruned.back()].second);
            if (!inside(last, tri)) {
                pruned.push_back(i);
            }
        } else {
            pruned.push_back(i);
        }
    }
    int j = 0;
    for (int i : pruned) {
        seeds[j] = seeds[i];
        j++;
    }
    N = pruned.size();
    seeds.resize(N);

    std::vector<tri_t> sets;
    tri_t prev_triag = tri_from_point(seeds[0].first, seeds[0].second);
    for (int i = 1; i < N; i++) {
        tri_t cur_triag = tri_from_point(seeds[i].first, seeds[i].second);
        if (tri_intersect(prev_triag, cur_triag)) {
            prev_triag = extend_triang(prev_triag, cur_triag);
        } else {
            sets.push_back(prev_triag);
            prev_triag = cur_triag;
        }
    }
    sets.push_back(prev_triag);

    int k = 0;
    prev_triag = sets[0];
    for (int i = 1; i < sets.size(); i++) {
        tri_t current = sets[i];
        tri_t merged = extend_triang(prev_triag, current);
        if (cost(merged) + C <= cost(prev_triag) + C + cost(current) + C) {
            prev_triag = merged;
        } else {
            W[k] = tip(prev_triag);
            T[k] = cost(prev_triag);
            k++;
            prev_triag = current;
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
