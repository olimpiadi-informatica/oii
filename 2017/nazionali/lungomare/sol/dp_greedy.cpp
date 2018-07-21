/*
 *  Dinamica quadratica con assunzioni greedy per andare in O(N).
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: come la dinamica quadratica, ma assume che la spiaggia j
 *  migliore da cui passare non si sposta mai all'indietro e che dopo un
 *  po' che non si migliora ha già trovato il meglio. Potrebbe sbagliare.
 */

#include <algorithm>
#include <vector>

#define TRY 10

using namespace std;

typedef long long ll;

vector<ll> DD, PP, Sol, Idx;

ll percorri(int N, ll L, ll D[], ll P[]) {
    DD.resize(N+2);
    PP.resize(N+2);
    Sol.resize(N+2);
    Idx.resize(N+2);
    DD[0] = PP[0] = 0;
    for (int i=0; i<N; i++) {
        DD[i+1] = D[i];
        PP[i+1] = P[i];
    }
    DD[N+1] = L;
    PP[N+1] = 0;
    Sol[0] = 0;
    Idx[0] = 0;
    for (int i=1; i<N+2; i++) {
        Sol[i] = L;
        Idx[i] = Idx[i-1];
        for (int j=Idx[i-1]; j<i and j<Idx[i]+TRY; j++) {
            ll t = max(Sol[j], PP[i]+PP[j]+DD[i]-DD[j]);
            if (Sol[i] > t) {
                Idx[i] = j;
                Sol[i] = t;
            }
        }
    }
    return Sol[N+1];
}
