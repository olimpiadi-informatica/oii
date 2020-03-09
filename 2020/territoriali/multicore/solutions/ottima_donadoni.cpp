#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T, t, i;
    cin >> T;

    for (t = 1; t <= T; t++) {
        int N, B;
        cin >> N >> B;
        vector<int> C(N), P(N);
        
        int sum_C = 0;
        for (i = 0; i < N; i++) {
            cin >> C[i] >> P[i];
            sum_C += C[i];
        }

        vector<int> DP(sum_C+1, B+1);
        DP[0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int k = DP.size()-1; k >= C[i]; k--) {
                if (DP[k-C[i]] + P[i] <= B) {
                    DP[k] = min(DP[k], DP[k-C[i]] + P[i]);
                }
            }
        }

        int sol = 0;
        for (int i = 0; i < DP.size(); ++i) {
            if (DP[i] <= B) {
                sol = i;
            }
        }
        cout << "Case #" << t << ": " << sol << endl;
    }
}
