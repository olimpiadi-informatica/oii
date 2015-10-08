/**
 *  Soluzione subottima O(TN^2)
 *
 *  Autore: Giorgio
 *
 *  Descrizione: Aggiungo un aereo per volta e fixo la soluzione precedentemente
 *  ottenuta spostando gli aerei nei punti piu' in mezzo possibili.
 */

#define MAXT 1000000
#define MAXR 102400
#include <algorithm>

using namespace std;

void pianifica(int R, int A[], int B[], int T[]) {
    int dist[MAXR], xt, j;
    bool done;

    for (int i=1; i<R; i++) A[i] = max(A[i], A[i-1]);
    for (int i=R-2; i>=0; i--) B[i] = min(B[i], B[i+1]);
    T[0] = A[0];
    dist[0] = MAXT;
    for (int i=1; i<R; i++) {
        T[i] = B[i];
        dist[i] = min(dist[i-1], T[i]-T[i-1]);
        if (dist[i] < dist[i-1]) {
            // fixo la soluzione ipotizzata
            done = false;
            while (not done) {
                done = true;
                for (j=i-1; j>0 and T[j] != A[j]; j--) {
                    xt = min(max((T[j-1]+T[j+1])/2,A[j]),B[j]);
                    if (xt != T[j]) {
                        T[j] = xt;
                        done = false;
                    }
                }
                for (int k=j+1; k<=i; k++)
                    dist[k] = min(dist[k-1], T[k]-T[k-1]);
            }
        }
    }
}

