/*
 *  Soluzione quadratica subtask con passerelle uguali.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: come cubica, ma fa i minimi in modo furbo.
 */

#include <iostream>
#include <utility>

using namespace std;

typedef long long ll;

long long percorri(int N, long long L, long long D[], long long P[]) {
    ll sol = L;
    for (int i=0; i<N; i++) {
        ll t = D[i]+P[i];
        sol = min(sol, max(t, L-D[i]+P[i]));
        for (int j=i+1; j<N; j++) {
            t = max(t, D[j]-D[j-1]+P[j]+P[j-1]);
            sol = min(sol, max(t, L-D[j]+P[j]));
        }
    }
    return sol;
}
