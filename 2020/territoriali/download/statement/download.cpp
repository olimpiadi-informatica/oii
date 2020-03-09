#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    cin >> T;

    for (t = 1; t <= T; t++) {
        int N, F, C;
        
        // scrivi in queste variabili la risposta
        int nf, nc;

        cin >> N >> F >> C;

        // RISOLVI QUI IL PROBLEMA!!

        cout << "Case #" << t << ": " << nf << " " << nc << endl;
    }
}
