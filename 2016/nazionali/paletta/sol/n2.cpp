/**
 *  Soluzione di paletta
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione O(n^2) che simula tutti gli scambi
 */


#include <vector>
#include <algorithm>
using namespace std;


long long paletta_sort(int N, int V[]) {
	
	for (int i = 0; i < N; i++) {
		if (V[i]%2 != i%2) return -1;
	}
	
	bool ordinato = false;
	long long res = 0;
	while (!ordinato) {
		ordinato = true;
		for (int i = 0; i < N-2; i++) {
			if (V[i] > V[i+2]) {
				swap(V[i], V[i+2]);
				ordinato = false;
				res++;
			}
		}
	}
	return res;
}
