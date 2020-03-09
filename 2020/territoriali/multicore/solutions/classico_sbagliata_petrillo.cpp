#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++) {
        i64 n, p;
        cin >> n >> p;
        // (value, weight)
        vector<pair<i64, i64>> ks(n);
        for(i64 i = 0; i < n; i++) {
            cin >> ks[i].first >> ks[i].second;
        }

        if(p <= 134217728 && p * n <= 2684354560) // Should take no more than 5s to run
        {
            vector<i64> tab[2];
            tab[0].assign(p + 1, 0);
            tab[1].assign(p + 1, 0);

            if(ks[0].second <= p)
                tab[0][ks[0].second] = ks[0].first;

            for(int i = 1; i < n; i++)
            {
                for(int w = 0; w <= p; w++)
                {
                    tab[i % 2][w] = tab[(i + 1) % 2][w];
                    if(w - ks[i].second >= 0)
                        tab[i % 2][w] = max(tab[i % 2][w], tab[(i + 1) % 2][w - ks[i].second] + ks[i].first);
                }
            }
            cout << "Case #" << caso << ": " << *max_element(tab[(n + 1) % 2].begin(), tab[(n + 1) % 2].end()) << endl;
        }

    }
    return 0;
}
