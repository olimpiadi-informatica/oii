/**
 *  Soluzione di nemesi
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione che in O(N) risolve il subtask 2.
 */
 

#define MAXN 100000
using namespace std;

void nuovo_gruppo();

void aggiungi(int bambino);


int gg[MAXN]; // 0 = gruppo non ancora assegnato, 1,2 = numero gruppo se assegnato

void smista(int N, int nemico[]) {
	
	for (int i = 0; i < N; i++) {
		if (gg[i] == 0) {
			gg[i] = 1;
			gg[nemico[i]] = 2;
		}
	}
	
	for (int k = 1; k <= 2; k++) {
		nuovo_gruppo();
		for (int i = 0; i < N; i++) {
			if (gg[i] == k) aggiungi(i);
		}
	}
}
