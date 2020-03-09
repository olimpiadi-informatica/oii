#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++) {
        i64 n;
        cin >> n;
        vector<i64> parent(n), value(n);
        vector<bool> ok(n);
        for(i64 i = 0; i < n; i++) {
            cin >> parent[i] >> value[i];
        }
        i64 cnt = 0;
        for(i64 i = 0; i < n; i++) {
            i64 index = -1;
            for(i64 j = 0; j < n; j++) {
                if(!ok[j] && (index < 0 || value[j] > value[index])) {
                    index = j;
                }
            }
            while(parent[index] >= 0 && value[parent[index]] < value[index]) {
                swap(value[index], value[parent[index]]);
                index = parent[index];
                cnt++;
            }
            ok[index] = true;
        }
        cout << "Case #" << caso << ": " << cnt << endl;
    }
    return 0;
}
