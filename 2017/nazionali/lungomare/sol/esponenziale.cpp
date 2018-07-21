/*
 *  Esponenziale O(2^N).
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: provo ogni possibile scelta di spiagge.
 */

#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

typedef long long int ll;

vector<ll> DD, PP;

ll percorri(int N, ll L, ll D[], ll P[]) {
    DD.resize(N+2);
    PP.resize(N+2);
    DD[0] = PP[0] = 0;
    for (int i=0; i<N; i++) {
        DD[i+1] = D[i];
        PP[i+1] = P[i];
    }
    DD[N+1] = L;
    PP[N+1] = 0;
    
    ll scelta;
    ll sol = L;
    for (scelta=(1<<(N+1))+1; scelta<(1<<(N+2)); scelta+=2) {
        int last = 0;
        ll t = 0;
        for (int i=1; i<N+2; i++) if (scelta & (1<<i)) {
            //cout << i << " ";
            t = max(t, DD[i]-DD[last]+PP[i]+PP[last]);
            last = i;
        }
        //cout << ": " << t << endl;
        sol = min(sol, t);
    }
	return sol;
}

