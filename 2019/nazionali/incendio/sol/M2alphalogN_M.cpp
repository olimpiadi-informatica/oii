/**
 *  Soluzione di incendio.
 *
 *  Autore: edomora97
 *
 *  Descrizione: Fa una ricerca binaria sulla soluzione e controlla con una
 * union find se la destinazione è raggiungibile
 *
 *  Tempo: O(M² log N alpha)
 *  Spazio: O(M)
 */

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int alzati(int N, int M, int X[], int Y[]) {
    std::vector<int> uf(M + 2);
    std::vector<int> rank(M + 2);

    std::function<int(int)> find = [&](int i) -> int {
      return uf[i] == i ? i : uf[i] = find(uf[i]);
    };

    std::function<void(int,int)> union_ = [&](int i, int j) {
        i = find(i);
        j = find(j);
        if (rank[i] < rank[j]) uf[i] = j;
        else if (rank[i] > rank[j]) uf[j] = i;
        else {
            rank[i]++;
            uf[j] = i;
        }
    };

    std::function<bool(int)> possibile = [&](int t) {

        std::iota(uf.begin(), uf.end(), 0);
        rank.assign(M + 2, 0);

        for (int i = 0; i < M; i++) {
            if (t >= X[i] || t >= N - 1 - Y[i]) union_(i, M);
            if (t >= Y[i] || t >= N - 1 - X[i]) union_(i, M + 1);
            for (int j = i + 1; j < M; j++) {
                int d = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
                int q = (d - 1) / 2;
                if (X[i] == X[j] || Y[i] == Y[j]) q = d / 2;
                if (t >= q) union_(i, j);
            }
        }

        return find(M) != find(M + 1);
    };

    int lb = 0, ub = N+1;
    while (lb + 1 < ub)
    {
        auto t = (lb + ub) / 2;
        if (possibile(t)) lb = t;
        else ub = t;
    }

    for (int i = 0; i < M; i++)
    {
        lb = std::min(N - 1 - X[i] + N - 1 - Y[i] - 1, (int)lb);
        lb = std::min(X[i] + Y[i] - 1, (int)lb);
    }

    return lb;
}
