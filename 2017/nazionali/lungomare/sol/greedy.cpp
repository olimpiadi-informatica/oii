/*
 *  Greedy scorretto.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: prende le spiaggie se localmente conviene, in ordine per P minore.
 *  Penso non dovrebbe funzionare.
 */

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

typedef long long int ll;


vector<ll> DD, PP, Idx;
set<ll> Sol;

bool sort_by_p(const int& i, const int& j) {
    return PP[i] < PP[j];
}

ll cost(int i, int j) {
    return PP[j]+PP[i]+DD[j]-DD[i];
}

ll percorri(int N, ll L, ll D[], ll P[]) {
    DD.resize(N+2);
    PP.resize(N+2);
    Idx.resize(N);
    DD[0] = PP[0] = Idx[0] = 0;
    for (int i=0; i<N; i++) {
        DD[i+1] = D[i];
        PP[i+1] = P[i];
        Idx[i] = i+1;
    }
    DD[N+1] = L;
    PP[N+1] = 0;
    sort(Idx.begin(), Idx.end(), sort_by_p);
    Sol.insert(0);
    Sol.insert(N+1);
    for (int i=0; i<N; i++) {
        int a = *Sol.lower_bound(Idx[i]);
        int b = *Sol.upper_bound(Idx[i]);
        if (cost(a,b) >= max(cost(a,i),cost(i,b)))
            Sol.insert(Idx[i]);
    }
    ll R = L;
    int last = 0;
    for (const auto& i : Sol) {
        R = max(R, cost(last, i));
        last = i;
    }
    return R;
}
