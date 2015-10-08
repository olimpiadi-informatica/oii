/**
 *  Soluzione ottima ma a partire dalla fine
 *
 *  Autore: Giorgio
 *
 *  Descrizione: Viene fatta una ricerca binaria sul K minimo ed una volta 
 *  trovato viene realizzato linearmente ma partendo dalla fine.
 *  La complessità è R*log(T).
 */

#define MAXT 1000000
#include <algorithm>

using namespace std;

bool greedy(int R, int A[], int B[], int T[], int t_try) {
    T[R-1] = B[R-1];
    for (int i=R-2; i>=0; i--) {
        T[i] = min(B[i], T[i+1]-t_try);
        if (T[i] < A[i]) return false;
    }
    return true;
}

void pianifica(int R, int A[], int B[], int T[]) {
    int dmin = 0, dmax = MAXT, dmed;
    while (dmax > dmin) {
        dmed = (dmin+dmax+1)/2;
        if (greedy(R, A, B, T, dmed)) dmin = dmed;
        else dmax = dmed-1;
    }
    greedy(R, A, B, T, dmin);
}
