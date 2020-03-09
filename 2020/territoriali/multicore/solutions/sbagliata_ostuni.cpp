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
        vector<bool> mask(n);
        i64 lower_bound = 0;
        function<i64(i64)> solve = [&mask, &ks, &solve, &p,
                                    &lower_bound](i64 pos) -> i64 {
            auto value = [&ks, &mask]() {
                i64 val = 0;
                for(i64 i = 0; i < ks.size(); i++) {
                    if(mask[i]) {
                        val += ks[i].second.first;
                    }
                }
                return val;
            };
            auto weight = [&ks, &mask]() {
                i64 val = 0;
                for(i64 i = 0; i < ks.size(); i++) {
                    if(mask[i]) {
                        val += ks[i].second.second;
                    }
                }
                return val;
            };
            i64 current_weight = weight();
            i64 current_value = value();
            auto greedy = [&pos, &ks, &current_weight, &p]() {
                i64 cum_weight = 0;
                i64 cum_value = 0;
                for(i64 i = pos; i < ks.size(); i++) {
                    if(cum_weight + ks[i].second.second <= p - current_weight) {
                        cum_weight += ks[i].second.second;
                        cum_value += ks[i].second.first;
                    }
                }
                return cum_value;
            };
            if(current_weight > p) {
                return 0;
            }
            if(pos == ks.size()) {
                lower_bound = max(lower_bound, current_value);
                return current_value;
            }
            if(current_value + greedy() <= lower_bound) {
                return 0;
            }
            i64 max_value = 0;
            for(i64 bit = 1; bit >= 0; bit--) {
                mask[pos] = bit;
                max_value = max(solve(pos + 1), max_value);
            }
            return max_value;
        };
        cout << "Case #" << caso << ": " << solve(0) << endl;
    }
    return 0;
}
