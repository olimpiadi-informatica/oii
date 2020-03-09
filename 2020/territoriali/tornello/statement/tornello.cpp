#include <iostream>
#include <cstdio>

using namespace std;

int solve() {
    int N;
    cin >> N;

    int risposta = 0;  // memorizza qui la risposta

    for (int i=0; i<N; i++) {
        int variazione;
        cin >> variazione;

        // aggiungi codice...
    }

    return risposta;
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        cout << "Case #" << t << ": " << solve() << endl;
    }
}
