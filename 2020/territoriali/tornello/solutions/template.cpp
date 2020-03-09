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
    // la lettura viene effettuata da tastiera
    // (puoi copiare e incollare i dati di input)
    // la scrittura viene effettuata a schermo
    // (puoi copiare i dati dalla finestra e incollarli in un file)
    
    // se preferisci leggere e scrivere da file
    // (input.txt e output.txt nella cartella dell'eseguibile)
    // ti basta decommentare le seguenti due righe:

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T, t;
    scanf("%d", &T);

    for (t = 1; t <= T; t++) {
        cout << "Case #" << t << ": " << solve() << endl;
    }
}
