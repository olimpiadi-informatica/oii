/* TODO: questa soluzione prende troppi punti. 
 * TODO: Nel caso in cui tutte le passerelle sono uguali non è detto che convenga o fermarsi in tutto o in nessuna.
 * 
 * Soluzione di lungomare.
 * 
 * Descrizione: Si ferma in tutte le spiagge (è un'euristica che vogliamo uccidere).
 * 
 */

#include <iostream>
#include <utility>

using namespace std;

long long percorri(int N, long long L, long long D[], long long P[]) {
    long long sol = max(D[0]+P[0], L-D[N-1]+P[N-1]);
    for (int i=1; i<N; i++)
        sol = max(sol, D[i]-D[i-1]+P[i]+P[i-1]);
    
    return min(L, sol);
}
