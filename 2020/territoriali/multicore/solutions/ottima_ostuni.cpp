#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main(int argc, char** argv) {
    bool print_case = !(argc == 2 && argv[1][0] == '1');
    i64 T;
    cin >> T;
    for (i64 caso = 1; caso <= T; caso++) {
        i64 n, p;
        cin >> n >> p;
        vector<i64> value(n), weight(n);
        for (i64 i = 0; i < n; i++) {
            cin >> value[i] >> weight[i];
        }
        i64 max_value_sum = accumulate(value.begin(), value.end(), 0);
        i64 max_weight_sum = accumulate(weight.begin(), weight.end(), 0);
        vector<vector<i64>> memo(n + 1, vector<i64>(max_value_sum + 1, -1));
        memo[0][0] = 0;
        i64 max_valid_value = 0;
        for (i64 item = 0; item < n; item++) {
            for (i64 cum_val = 0; cum_val <= max_value_sum; cum_val++) {
                i64 r_val = cum_val - value[item];
                if (r_val >= 0 && memo[item][r_val] >= 0) {
                    memo[item + 1][cum_val] = memo[item][r_val] + weight[item];
                }
                if (memo[item][cum_val] >= 0 &&
                    (memo[item + 1][cum_val] < 0 ||
                     memo[item][cum_val] < memo[item + 1][cum_val])) {
                    memo[item + 1][cum_val] = memo[item][cum_val];
                }
                if (memo[item + 1][cum_val] >= 0 &&
                    memo[item + 1][cum_val] <= p && cum_val > max_valid_value) {
                    max_valid_value = cum_val;
                }
            }
        }
        if (print_case) cout << "Case #" << caso << ": ";
        cout << max_valid_value << endl;
    }
    return 0;
}
