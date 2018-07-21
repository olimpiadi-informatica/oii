/**
 *  Soluzione di classifica.
 *
 *  Autore: Federico
 *
 *  Descrizione: supera impiega O(1), squalifica e partecipante impiegano O(logN)
 * 				 La descrizione la devo copia-incollare dalla email.
 */

#include <utility>

const int MAXID = 1000010;
const int MAXN = 1<<20;

int N;
int id2globalrank[MAXID];
int globalrank2id[MAXN];
int NextOne[MAXN];
int PreviousOne[MAXN];


int rt[2*MAXN]; // range-tree
void PutZero(int rank) {
	int it = MAXN+rank;
	while (it != 0) {
		rt[it]--;
		it >>= 1;
	}
}

// [left, right]
int GetSum(int v, int left, int right, int x) {
	if (x >= right) return rt[v];
	if (x < left) return 0;
	int m = (left+right)/2;
	return GetSum(2*v, left, m, x) + GetSum(2*v+1, m+1, right, x); 
}

inline int rank2pos(int rank) {
	return GetSum(1, 0, MAXN-1, rank);
}

int pos2rank(int pos) {
	int rank_left = 0;
	int rank_right = N-1;
	while (rank_left < rank_right) {
		int m = (rank_left + rank_right) / 2;
		if (rank2pos(m) >= pos) rank_right = m;  
		else rank_left = m+1;
	}
	return rank_left;
}

// void debug() {
	// cout << "bitmask:       ";
	// for (int i = 0; i < N; i++) {
		// if (rt[i+MAXN]) cout << globalrank2id[i] << ' ';
		// else cout << 'x' << ' ';
	// }
	// cout << endl;
// }

void inizia(int N, int* ids) {
	::N = N;
	for (int i = 0; i < N; i++) {
		id2globalrank[ids[i]] = i;
		globalrank2id[i] = ids[i];
		NextOne[i] = i-1;
		PreviousOne[i] = i+1;
		rt[MAXN+i] = 1;
	}
	for (int i = MAXN-1; i >= 1; i--) rt[i] = rt[i<<1] + rt[(i<<1)|1];
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

