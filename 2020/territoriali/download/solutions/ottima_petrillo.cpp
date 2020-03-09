#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int main() {
    i64 T;
    cin >> T;
    for(i64 caso = 1; caso <= T; caso++)
    {
        i64 C, G, B;
        cin >> B >> G >> C;
        i64 c = 0, g = 0;
        for(; B >= G; g++) B -= G;
        for(; B >= C; c++) B -= C;
        cout << "Case #" << caso << ": " << g << " " << c << endl;
    }
    return 0;
}
