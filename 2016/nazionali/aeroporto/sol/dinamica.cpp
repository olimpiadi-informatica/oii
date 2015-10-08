/**
 *  Soluzione di aeroporto
 *
 *  Autore: Federico
 *
 *  Descrizione: O(NT²) Dinamica sui prefissi del tempo e degli aerei.
 */

#include <iostream>
#include <algorithm>
using namespace std;


#define MAXT 1200
#define MAXR 1200
int din[MAXT][MAXR];

void pianifica(int R, int A[], int B[], int T[]) {
	int maxt = 0;
	for (int i = 0; i < R; i++) maxt = max(maxt, B[i]);
	if (maxt+1 < R) {
		int pos = 0;
		for (int i = 0; i < R; i++) {
			T[i] = max(pos, A[i]);
			pos = T[i];
		} 
		return;
	}
	
	for (int t = A[0]; t <= maxt; t++) din[1][t] = maxt;
	for (int r = 2; r <= R; r++) {
		for (int t = A[r-1]; t <= maxt; t++) {
			if (t > B[r-1]) {
				din[r][t] = din[r][B[r-1]];
				continue;
			}
			for (int k = t; k >= 0; k--) {
				din[r][t] = max(min(t-k, din[r-1][k]), din[r][t]); 
				if (din[r-1][k] <= t-k) break;
			}
		}
	}
	
	int res = din[R][maxt];
	// cout << res << "\n";
	int lastpos = maxt;
	for (int i = R-1; i >= 0; i--) {
		T[i] = min(lastpos, B[i]);
		lastpos = T[i]-res;
	}
}

