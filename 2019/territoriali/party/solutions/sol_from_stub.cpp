#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    // le seguenti due righe possono essere utili per leggere e scrivere da file

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        // scrivi in questa variabile la soluzione
        int sol = 0;

        for (int i = 0; i < N; i++) {
            int A;
            cin >> A;

            // il valore A rappresenta il valore di amicizia dell'i-esimo amico
            sol += A > 0 ? A : 0;
        }

        cout << "Case #" << t << ": " << sol << endl;
    }
}
