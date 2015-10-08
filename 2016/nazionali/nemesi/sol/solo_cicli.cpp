/**
 *  Soluzione di nemesi
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione che in O(N) risolve il subtask in cui ci sono
 *  solo cicli
 */


#define MAXN 100000
using namespace std;

void nuovo_gruppo();

void aggiungi(int bambino);


int gruppo[MAXN]; // gruppo
int res = 2; // numero di gruppi (minimo 2)


void smista(int N, int nemico[]) {
	
	for (int i = 0; i < N; i++) {
		if (gruppo[i] == 0) {
			int gg = 1;
			gruppo[i] = 1;
			int at = nemico[i];
			int tt = 0;
			while (at != i and tt < N) {
				tt++;
				if (nemico[at] == i and gg == 2) {
					gruppo[at] = 3;
					res = 3;
					break;
				}
				gg = 3-gg;
				gruppo[at] = gg;
				at = nemico[at];
			}
		}
	}
	
	for (int k = 1; k <= res; k++) {
		nuovo_gruppo();
		for (int i = 0; i < N; i++) {
			if (gruppo[i] == k) aggiungi(i);
		}
	}
}
