#include <bits/stdc++.h>

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
	std::vector<bool> coperto(N + 1, false);

	coperto[0] = true;
	for (int i=0; i<N; i++) {
		if (!coperto[i])
			return false;

		for (int j=1; j<altezze[i]; j++) {
			if (i + j <= N)
				coperto[i + j] = true;
		}
	}

	return true;
}

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
	::N = N;
	::altezze = altezze;

	if (check()) return OK;

	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			std::swap(altezze[i], altezze[j]);
			if (check()) {
				//std::cerr << i << " " << j << std::endl;
				scambio->domino1 = i;
				scambio->domino2 = j;
				return RISOLTO;
			}
			std::swap(altezze[i], altezze[j]);
		}
	}

	return IMPOSSIBILE;
}
