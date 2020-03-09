#include <iostream>
#include <vector>
using namespace std;

const int VERYBIG = 1000000001;  // just bigger than B is enough
                                 // using something too big is risky
                                 // (could overflow when adding to it...)

vector<int> costo, numero_core;
vector<vector<int>> memo;

int g(int c, int n) {
    if (c == 0) return 0;
    if (n == 0) return VERYBIG;

    if (memo[c][n] != -1) return memo[c][n];

    if (numero_core[n - 1] > c) {
        memo[c][n] = g(c, n - 1);
        return memo[c][n];
    } else {
        memo[c][n] = min(costo[n - 1] + g(c - numero_core[n - 1], n - 1), g(c, n - 1));
        return memo[c][n];
    }
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        costo.clear();
        numero_core.clear();
        memo.clear();

        int N, B;
        cin >> N >> B;

        costo.resize(N);
        numero_core.resize(N);

        int core_totali = 0;
        for (int i = 0; i < N; i++) {
            cin >> numero_core[i] >> costo[i];
            core_totali += numero_core[i];
        }

        memo.resize(core_totali + 1, vector<int>(N + 1, -1));  // matrice piena di -1

        for (int soluzione = core_totali; soluzione >= 0; soluzione--) {
            if (g(soluzione, N) <= B) {
                cout << "Case #" << t << ": " << soluzione << endl;
                break;
            }
        }
    }
}
