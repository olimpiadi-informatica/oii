#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

#define MAXN 300

using namespace std;

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t, i;
    cin >> T;

    for (t = 1; t <= T; t++) {
        int N, B;
        int C[MAXN], P[MAXN];
        
        // scrivi in questa variabile la risposta
        int nc;

        cin >> N >> B;
        for (i = 0; i < N; i++)
            cin >> C[i] >> P[i];
        
        // RISOLVI QUI IL PROBLEMA!!

        cout << "Case #" << t << ": " << nc << endl;
    }
}
