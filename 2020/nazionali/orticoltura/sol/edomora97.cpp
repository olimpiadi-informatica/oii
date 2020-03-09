/**
 * Descrizione: Risolve il caso C=0 unendo i semi i cui triangoli si toccano,
 * poi unisce i triangoli che individualmente costano di più dell'unione.
 * Memorizza i triangoli con la coordinata della punta, *sbagliando* a causa
 * degli off-by-one nell'arrotondare.
 * Autore: Edoardo Morassutto
 * Complessità: O(N + sort)
 */
#include <algorithm>
#include <iostream>
#include <vector>

void posiziona(int D, int T);

void budget(int B);

using ii = std::pair<int, int>;
using ll = long long;

bool in_triang(const ii& triang, const ii& point)
{
    return abs(triang.first - point.first) + point.second <= triang.second;
}

ii extend_triang(const ii& a, const ii& b)
{
    if (in_triang(a, b))
        return a;
    if (in_triang(b, a))
        return b;
    int x1 = a.first - a.second + 1; // sposta `a` a P=1 verso sx
    int x2 = b.first + b.second - 1; // sposta `b` a P=1 verso dx
    return ii((x1 + x2) / 2, (x2 - x1 + 1) / 2 + 1);
}

bool tri_intersect(const ii& a, const ii& b)
{
    int xa = a.first + a.second - 1;
    int xb = b.first - b.second + 1;
    return xa >= xb - 1;
}

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P)
{
    std::vector<std::pair<int, int>> seeds;
    std::vector<int> W(N), T(N);

    for (int i = 0; i < N; i++) {
        seeds.emplace_back(X[i], P[i]);
    }
    std::sort(seeds.begin(), seeds.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first - a.second < b.first - b.second;
    });

    std::vector<ii> sets;
    ii prev_triag = ii(seeds[0].first, seeds[0].second);
    for (int i = 1; i < N; i++) {
        ii cur_triag = ii(seeds[i].first, seeds[i].second);
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
        ii current = sets[i];
        ii merged = extend_triang(prev_triag, current);
        if (merged.second + C <= prev_triag.second + C + current.second + C) {
            prev_triag = merged;
        } else {
            W[k] = prev_triag.first;
            T[k] = prev_triag.second;
            k++;
            prev_triag = current;
        }
    }
    W[k] = prev_triag.first;
    T[k] = prev_triag.second;
    k++;

    int out = 0;
    for (int i = 0; i < k; i++) {
        out += C + T[i];
        posiziona(W[i], T[i]);
    }
    budget(out);
}
