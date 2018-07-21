/*
 *  Soluzione cubica subtask con passerelle uguali.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: prova ogni possibile sottointervallo di spiagge.
 */

#include <iostream>
#include <utility>

using namespace std;

typedef long long ll;

ll percorri(int N, ll L, ll D[], ll P[]) {
    ll sol=L;
    for (int i=0; i<N; i++) {
        for (int j=0; j<=i; j++) {
            ll t = max(D[j]+P[j],L-D[i]+P[i]);
            for (int k=j; k<i; k++)
                t = max(t, D[k+1]-D[k]+P[k+1]+P[k]);
            sol = min(sol, t);
        }
    }
    return sol;
}
