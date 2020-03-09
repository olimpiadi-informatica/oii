#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++) {
        i64 cane, gatto, budget;
        cin >> budget >> gatto >> cane;
        i64 n_gatto = budget / gatto;
        i64 n_cane = (budget % gatto) / cane;
        cout << "Case #" << caso << ": " << n_gatto << " " << n_cane << endl;
    }
    return 0;
}
