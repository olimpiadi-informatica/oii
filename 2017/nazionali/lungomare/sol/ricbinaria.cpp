/* Faccio ricerca binaria sulla soluzione
 * 
 * Tempo O(N log L)
 * 
 * */

#include <iostream>
#include <cassert>

#define MAXN 10000000

using namespace std;

int N;
long long S[MAXN];
long long d0;

bool celafa(long long x, long long P[]) {
    long long spazio = d0;
    if (spazio > x) return false;
    for (int i=0; i<N; i++) {
        // Vedo se posso fermarmi, e in caso se è conveniente, altrimenti vado avanti
        if (spazio + P[i] <= x)
            spazio = min(spazio, P[i]) + S[i];
        // Altrimenti vado avanti
        else 
            spazio += S[i];
        if (spazio > x) return false;
    }
    
    return true;
}

long long percorri(int N, long long L, long long D[], long long P[]) {
    ::N = N;
    d0 = D[0];
    for (int i=1; i<N; i++)
        S[i-1] = D[i] - D[i-1];
    S[N-1] = L - D[N-1];
    
    long long lb = 1;
    long long ub = L;
    long long medio;
    
    // Voglio trovare con una ricerca binaria il più piccolo valore che va bene
    while (lb <= ub) {
        medio = (lb + ub)/2;
        bool ans = celafa(medio, P);
        
        if (lb == ub) {
            if (ans) {
                assert(!celafa(medio-1, P));
                return medio;
            }
            else {
                assert(celafa(medio+1, P));
                return medio+1;
            }
        }        
        if (ans)
            ub = medio;

        else
            lb = medio+1;
    }
    
    assert(false);
    
	return medio;
}

