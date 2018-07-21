/**
 *  Soluzione di classifica.
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: supera impiega O(1), squalifica e partecipante impiegano O(logN)
 *               La descrizione la devo copia-incollare dalla email.
 *               (Tradotta in c da soluzione.cpp di Federico)
 */

//~ #include <utility>
#include <stdio.h>

#define MAXID 1000010
#define MAXN (1<<20)

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
		it = it>>1;
	}
}
int pos2rank(int pos) {
	int it = 1;
	while (it < MAXN) {
		if (rt[it<<1] < pos) {
			pos -= rt[it<<1];
			it = (it<<1)|1;
		}
		else it = it<<1;
	}
	return it-MAXN;
}

void swap(int* a, int* b) {
    int x = *a;
    *a = *b;
    *b = x;
}

void inizia(int n, int* ids) {
	N = n;
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
	swap(id2globalrank+id1, id2globalrank+id2);
	swap(globalrank2id+rank1, globalrank2id+rank2);
}

int partecipante(int pos) {
	int rank = pos2rank(pos);
	return globalrank2id[rank];
}

