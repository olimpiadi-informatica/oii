#include <iostream>
#include <cstdio>

const int MAXN = 1000;

using namespace std;

int solve() {
    int N;
    cin >> N;

    int risposta = 0;  // memorizza qui la risposta
    int R[MAXN], C[MAXN];

    for (int i=0; i<N; i++) {
        cin >> R[i] >> C[i];

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
