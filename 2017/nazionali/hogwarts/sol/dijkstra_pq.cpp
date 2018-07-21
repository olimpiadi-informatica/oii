/*
 * Soluzione O(M log N) (Alice Cortinovis)
 * 
 * Usa l'algoritmo di Dijkstra un po' modificato:
 * quando mi espando da un nodo devo verificare se posso percorrere l'arco, e in caso mettere un tempo opportuno (cioè controllo se devo aspettare).
 * 
 * Questo però è fatto male perché nella priority queue può esserci un sacco di spazzatura...
 * 
 */

#include <iostream>
#include <cassert>
#include <queue>
#include <utility>

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

priority_queue<ii> PQ; // first indica il tempo impiegato, con il segno cambiato; second indica l'ID del nodo
vector<arco> G[MAXN];
bool chiuso[MAXN];
int sol[MAXN];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
	// Costruzione del grafo
	for (int i=0; i<M; i++) {
		G[A[i]].pb(arco(B[i], inizio[i], fine[i]));
		G[B[i]].pb(arco(A[i], inizio[i], fine[i]));
	}
	
	// Inizializzazione della priority queue
	PQ.push(mp(0, 0));
	
	// Soluzione
	while (!PQ.empty()) {
		// Prendo l'elemento in cima alla pq
		ii current = PQ.top();
		PQ.pop();
		
		// Controllo di non aver già chiuso il nodo, altrimenti lo chiudo
		if (chiuso[current.second]) continue;
		chiuso[current.second] = true;
		sol[current.second] = -current.first;
		
		// Esamino gli archi uscenti dal nodo in questione
		for (int i=0; i<(int)G[current.second].size(); i++) {
			int v = G[current.second][i].arrivo;
			int t1 = G[current.second][i].inizio;
			int t2 = G[current.second][i].fine;
			int t = -current.first;
			
			if (chiuso[v]) continue;
			
			// Se è irraggiungibile:
			if ( (t+1) > t2 ) continue;
			
			// Altrimenti calcolo il tempo necessario e aggiungo alla coda
			int new_t = max(t, t1) + 1;
			PQ.push(mp(-new_t, v));
		}
	}
	
	// Guardo la risposta
	if (!chiuso[N-1]) return -1;
	else return sol[N-1];
}
