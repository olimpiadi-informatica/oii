/**
 *  Soluzione sbagliata di nemesi
 *
 *  Autore: Giorgio
 *
 *  Descrizione: Scandisco i bambini uno per volta e li metto nel primo
 *  gruppo in cui posso.
 */


#define MAXN 102400
#include <vector>

using namespace std;

void nuovo_gruppo();
void aggiungi(int bambino);


void smista(int N, int nemico[]) {
    vector<vector<int>> gruppi;
    vector<vector<int>> blacklist;

    int ng = 0;
    for (int i=0; i<N; i++) {
        int j=0;
        for (; j<ng; j++) {
            if (blacklist[j][i] == 0 and gruppi[j][nemico[i]] == 0) {
                gruppi[j][i] = 1;
                blacklist[j][nemico[i]] = 1;
                break;
            }
        }
        if (j == ng) {
            gruppi.push_back(vector<int>(N));
            blacklist.push_back(vector<int>(N));
            gruppi[ng][i] = 1;
            blacklist[ng][nemico[i]] = 1;
            ng++;
        }
    }
    for (auto &g : gruppi) {
        nuovo_gruppo();
        for (int i=0; i<N; i++)
            if (g[i])
                aggiungi(i);
    }
}
