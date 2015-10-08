/**
 *  Soluzione di paletta
 *
 *  Autore: Federico
 *
 *  Descrizione: Soluzione ottima.
 *  Calcolo il numero di inversioni dei pari e dei dispari.
 *  Il calcolo del numero di inversioni è calcolato tramite un fenwick tree.
 *  La complessità è NlogN e lineare nel numero di mosse altrimenti.
 */

#include <iostream>
using namespace std;
#define MAXN 1500000

int N;
int A[MAXN];
int ord[MAXN];
int fen[MAXN];

int ask(int i) {
	int res = 0;
	for (; i >= 0; i = (i&(i+1))-1) res += fen[i];
	return res;
}

void add(int i, const int N) {
	for (; i < N; i = i|(i+1)) fen[i]++;
}

long long Solve(int N) {
	for (int i = 0; i < N; i++) fen[i] = 0;
	for (int i = 0; i < N; i++) ord[A[i]] = i;
	// for (int i = 0; i < N; i++) cout << A[i] << " ";
	// cout << "\n";
	//fenwick
	long long res = 0;
	for (int i = N-1; i >= 0; i--) {
		res += (long long)ask(ord[i]);
		add(ord[i], N);
	}
	return res;
}

long long paletta_sort(int N, int V[]) {	
		
	long long res = 0;
	for (int i = 0; i < N; i++) {
		if (V[i]%2 != i%2) return -1;
	}
	for (int i = 0; i < N; i+=2) A[i/2] = V[i]/2;
	res += Solve((N+1)/2);
	
	for (int i = 1; i < N; i+=2) A[(i-1)/2] = (V[i]-1)/2;
	res += Solve(N/2);
	
	return res;
}

