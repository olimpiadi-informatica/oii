#include <bits/stdc++.h>

#define MAXN (24)

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++) {
        i64 n, p;
        cin >> n >> p;
        vector<i64> value(n), weight(n);
        for(i64 i = 0; i < n; i++) {
            cin >> value[i] >> weight[i];
        }
        if(n > MAXN) {
            continue;
        }
        i64 max_value = 0;
        for(i64 s = 0; s < (1 << n); s++) {
            i64 sum_value = 0, sum_weight = 0;
            for(i64 i = 0; i < n; i++) {
                if((s >> i) & 1) {
                    sum_value += value[i];
                    sum_weight += weight[i];
                }
            }
            if(sum_weight <= p) {
                max_value = max(max_value, sum_value);
            }
        }
        cout << "Case #" << caso << ": " << max_value << endl;
    }
    return 0;
}
