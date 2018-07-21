/**
 *  Soluzione di classifica.
 *
 *  Autore: Federico
 *
 *  Descrizione: squalifica e supera sono O(1), mentre partecipante impiega O(N).
 * 				 L'idea è la stessa della soluzione federico.cpp, ma questa non
 * 				 usa un range-tree.
 */

#include <utility>

const int MAXID = 1000010;
const int MAXN = 1000000;

int N;
int id2globalrank[MAXID];
int globalrank2id[MAXN];
int NextOne[MAXN];
int PreviousOne[MAXN];


// Should be a range tree (easy range tree)
int bitmask[MAXN];
void PutZero(int rank) {
	bitmask[rank] = 0;
}
int pos2rank(int pos) {
	for (int rank = 0; rank < N; rank++) {
		pos -= bitmask[rank];
		if (pos == 0) return rank;
	}
	return -1;
}

void inizia(int N, int* ids) {
	::N = N;
	for (int i = 0; i < N; i++) {
		id2globalrank[ids[i]] = i;
		globalrank2id[i] = ids[i];
		bitmask[i] = 1;
		NextOne[i] = i-1;
		PreviousOne[i] = i+1;
	}
}

void squalifica(int id) {
	int rank = id2globalrank[id];
	int nextone = NextOne[rank];
	int previousone = PreviousOne[rank];
	if (nextone >= 0) PreviousOne[nextone] = previousone;
	if (previousone < N) NextOne[previousone] = nextone;
	
	PutZero(rank);
}

void supera(int id1) {
	int rank1 = id2globalrank[id1];
	int rank2 = NextOne[rank1];
	int id2 = globalrank2id[rank2];
	std::swap(id2globalrank[id1], id2globalrank[id2]);
	std::swap(globalrank2id[rank1], globalrank2id[rank2]);
}

int partecipante(int pos) {
	int rank = pos2rank(pos);
	return globalrank2id[rank];
}
