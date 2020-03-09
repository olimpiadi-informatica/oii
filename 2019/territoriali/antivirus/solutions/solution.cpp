#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void solve(int t) {
    int len[4];
    for (int i = 0; i < 4; i++)
        cin >> len[i];
    int M;
    cin >> M;
    string S[4];
    for (int i = 0; i < 4; i++)
        cin >> S[i];

    size_t res[4];
    for (int i = 0; i <= len[0]-M; i++) {
        bool valid = true;
        res[0] = i;
        for (int s = 1; s < 4 && valid; s++)
            if ((res[s] = S[s].find(&S[0][i], 0, M)) == string::npos)
                valid = false;

        if (valid) {
            cout << "Case #" << t << ":";
            for (int j = 0; j < 4; j++)
                cout << " " << res[j];
            cout << endl;
            return;
        }
    }
    assert(false);
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
        solve(t);
}
