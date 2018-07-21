/** Soluzione di hogwarts O(T*E)
 * Ad ogni tempo t so quali nodi ho raggiunto e guardo tutti gli archi che escono da essi. Mi fermo non appena raggiungo N-1
 **/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define MAXN 1000002

using namespace std;

class arco {	
	public:
		int arrivo;
		int inizio;
		int fine;
		arco() { arrivo = 0; inizio = 0; fine = 0;};
		arco(int a, int b, int c) {arrivo = a; inizio = b; fine = c;};
};

vector<arco> G[MAXN];
int N;
int t;
bool raggiunti[MAXN];
int Tmax;

int raggiungi(int N, int M, int* A, int* B, int* inizio, int* fine) {
	::N = N;
	for (int i=0; i<M; i++) {
		G[A[i]].push_back(arco(B[i], inizio[i], fine[i]));
		G[B[i]].push_back(arco(A[i], inizio[i], fine[i]));
		Tmax = max(Tmax, fine[i]);
	}
	
	queue<int> nuovi;
	nuovi.push(0);
	
	do {
		while (!nuovi.empty()) {
			raggiunti[nuovi.front()] = true;
			nuovi.pop();
		}
		
		if (raggiunti[N-1]) return t; // controllo se ho finito
		
		for (int i=0; i<N; i++)
			if (raggiunti[i])
				for (int j=0; j<(int)G[i].size(); j++)
					if (t >= G[i][j].inizio && t < G[i][j].fine && !raggiunti[G[i][j].arrivo])
						nuovi.push(G[i][j].arrivo);
						
		t++;
					
	} while (t < Tmax);
	
	return -1;
}
