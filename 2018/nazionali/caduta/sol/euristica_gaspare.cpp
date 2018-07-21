#include <bits/stdc++.h>

using namespace std;

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;


int N;
int* altezze;

bool check() {
	int needed = 0;
	int covered = 0;

	for (int i=0; i<N; i++) {
		if (needed > covered)
			return false;

		covered = std::max(covered, needed + altezze[i]);
		needed++;
	}

	return true;
}

bool comp_altezza (int i, int j) { 
  return altezze[i] < altezze[j]; 
}

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
	::altezze = altezze;
	for (int i = 0; i < N; i++) {
        altezze[i]--;
    }

	if (check()) return OK;

	int h[N];
	for(int i=0; i<N; i++) h[i] = i;
	sort(h, h+N, comp_altezza);

	int i=0;
	int l=0;
	int r=N-1;

	// TODO Limite migliore

	while( i < N*(N-1)/2 )
        {
	
		swap(altezze[h[l]], altezze[h[r]]);
                if (check()) {
	                scambio->domino1 = h[l];
                        scambio->domino2 = h[r];
                        return RISOLTO;
                }
		swap(altezze[h[l]], altezze[h[r]]);

		r--;
		if( l >= r )
		{
			l++;
			r = N-1;
		}
                i++;
        }

	return IMPOSSIBILE;
}
