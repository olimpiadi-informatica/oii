/*
 *  Dinamica quadratica O(N^2).
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: calcola il miglior percorso dalla spiaggia 0 alla spiaggia i,
 *  tramite la possibile penultima spiaggia j.
 */

#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> DD, PP;
vector<ll> Sol;


long long percorri(int N, long long L, long long D[], long long P[]) {
    DD.resize(N+2);
    PP.resize(N+2);
    Sol.resize(N+2);
    DD[0] = PP[0] = 0;
    for (int i=0; i<N; i++) {
        DD[i+1] = D[i];
        PP[i+1] = P[i];
    }
    DD[N+1] = L;
    PP[N+1] = 0;
    Sol[0] = 0;
    for (int i=1; i<N+2; i++) {
        Sol[i] = L;
        for (int j=0; j<i; j++)
            Sol[i] = min(Sol[i], max(Sol[j], PP[i]+PP[j]+DD[i]-DD[j]));
    }
    return Sol[N+1];
}
