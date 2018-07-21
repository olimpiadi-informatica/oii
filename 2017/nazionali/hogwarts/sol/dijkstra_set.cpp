/*
 * Soluzione O(M log M)  (Alice Cortinovis)
 * 
 * Usa l'algoritmo di Dijkstra un po' modificato:
 * quando mi espando da un nodo devo verificare se posso percorrere l'arco, e in caso mettere un tempo opportuno (cioè controllo se devo aspettare).
 * 
 */

#include <iostream>
#include <cassert>
#include <set>
#include <utility>
#include <climits>
#include <vector>

#define pb push_back
#define mp make_pair
#define MAXN 1000000

using namespace std;

typedef pair<int, int> ii;

class arco {	
	public:
		int arrivo;
		int inizio;
		int fine;
		arco() { arrivo = 0; inizio = 0; fine = 0;};
		arco(int a, int b, int c) {arrivo = a; inizio = b; fine = c;};
};

set<ii> S; // first indica il tempo impiegato, con il segno cambiato; second indica l'ID del nodo
vector<arco> G[MAXN];
bool chiuso[MAXN];
int sol[MAXN];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
	// Costruzione del grafo
	for (int i=0; i<M; i++) {
		G[A[i]].pb(arco(B[i], inizio[i], fine[i]));
		G[B[i]].pb(arco(A[i], inizio[i], fine[i]));
	}
	
	// Inizializzazione
	for (int i=0; i<N; i++)
		sol[i] = INT_MAX;
	S.insert(mp(0, 0));
	sol[0] = 0;
	
	// Soluzione
	while (!S.empty()) {
		// Prendo l'elemento in cima alla lista
		ii current = *(S.begin());
		S.erase(S.begin());
		
		// Controllo di non aver già chiuso il nodo, altrimenti lo chiudo
		if (chiuso[current.second]) continue;
		chiuso[current.second] = true;
		assert(sol[current.second] == current.first);
		
		// Esamino gli archi uscenti dal nodo in questione
		for (int i=0; i<(int)G[current.second].size(); i++) {
			int v = G[current.second][i].arrivo;
			int t1 = G[current.second][i].inizio;
			int t2 = G[current.second][i].fine;
			int t = current.first;
			
			if (chiuso[v]) continue;
			
			// Se è irraggiungibile:
			if ( (t+1) > t2 ) continue;
			
			// Altrimenti calcolo il tempo necessario e aggiungo alla coda
			int new_t = max(t, t1) + 1;
			if (new_t >= sol[v]) continue;
			
			S.erase(mp(sol[v], v));
			S.insert(mp(new_t, v));
			sol[v] = new_t;
		}
	}
	
	// Guardo la risposta
	if (!chiuso[N-1]) return -1;
	else return sol[N-1];
}
