// https://codeforces.com/contest/245/submission/2592448

#include <iostream>
#include <cstdio>

using namespace std;

int solve() {
    int N;
    cin >> N;

    int a[N];
    int i;
    for (i=0; i<N; i++) cin >> a[i];

    int sc=0, risposta = 0;  // memorizza qui la risposta
	
    for(i = 0; a[i] == -1; ++i);

    for(; i!=N; ++i) {
        if(a[i] == '+')
            sc++;
        else
            sc--;

        risposta = max(risposta, sc);
    }

    sc = 0;

    for(i = 0; a[i] == 1; ++i);

    for(; i!=N; ++i) {
        if(a[i] == 1)
            sc++;
        else
            sc--;

        risposta = max(risposta, -sc);
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
