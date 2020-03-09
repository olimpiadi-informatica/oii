#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++) {
        i64 n, p;
        cin >> n >> p;
        vector<pair<double, pair<i64, i64>>> ks(n);
        for(i64 i = 0; i < n; i++) {
            cin >> ks[i].second.first >> ks[i].second.second;
            ks[i].first =
                double(ks[i].second.second) / double(ks[i].second.first);
        }
        sort(ks.begin(), ks.end());
        i64 cum_weight = 0;
        i64 cum_value = 0;
        for(i64 i = 0; i < n; i++) {
            if(cum_weight + ks[i].second.second <= p) {
                cum_weight += ks[i].second.second;
                cum_value += ks[i].second.first;
            }
        }
        cout << "Case #" << caso << ": " << cum_value << endl;
    }
    return 0;
}
