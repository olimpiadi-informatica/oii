/** Soluzione ottima di "corteo"
 * 
 * Complessità: O(NM)
 * 
 * Costruisco un grafo i cui vertici sono coppie di vertici del grafo originale. Il peso della coppia (a, b)
 * è la distanza tra a e b nel grafo originale (precomputo tutte le coppie di distanze con N bfs sul grafo originale
 * partendo da ogni nodo). C'è un arco tra (a, b) e (c, d) se nel grafo originale c'è un arco tra a e c, oppure un arco
 * tra b e d, cioè se posso passare da una configurazione all'altra in due istanti di tempo successivi.
 * 
 * Ora faccio una visita (bfs) sul grafo nuovo, in cui raggiungo tutti i nodi con costo >= del costo della coppia
 * sorgente (P1, P2). Gli altri li metto in dei "bucket" a seconda del loro peso, e se non ho raggiunto la destinazione
 * (D1, D2) procedo con il bucket appena più leggero e uso lui come coda per la bfs. Continuo fino a quando non raggiungo la 
 * destinazione, stando attenta che non voglio riempire i bucket più costosi di quello in cui sono ora, ma piuttosto metto
 * il nodo nuovo nel bucket attuale.
 * 
 * Il nuovo grafo ha N^2 nodi e magicamente però ha solo MN archi...
 * 
 **/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAXN 1000

using namespace std;

typedef pair<int,int> ii;
vector<int> G[MAXN];
bool vis2[MAXN];
int N, M, P1, D1, P2, D2;
bool vis[MAXN][MAXN];
int dist[MAXN][MAXN];
bool inseriti[MAXN][MAXN];
queue<pair<int, int> > bucket[MAXN];
ii succ[MAXN][MAXN];

void sposta(int chi, int dove);

void ricostruisci(int m) {
	// Ricostruisce la soluzione che usa archi lunghi almeno m.
	// Fa una bfs dalla destinazione nel grafo prodotto fino alla sorgente
	// segnandosi gli archi usati, poi segue il percorso al contrario per
	// chiamare sposta.
	queue<ii> q;
	q.emplace(D1, D2);
	memset(succ, -1, sizeof(succ));
	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		q.pop();

		// prova a spostare a
		for (int v : G[a]) {
			if (dist[v][b] >= m && succ[v][b].first == -1) {
				succ[v][b] = {a,b};
				if (v == P1 && b == P2) break;
				q.emplace(v, b);
			}
		}
		// prova a spostare b
		for (int v : G[b]) {
			if (dist[a][v] >= m && succ[a][v].first == -1) {
				succ[a][v] = {a,b};
				if (a == P1 && v == P2) break;
				q.emplace(a, v);
			}
		}
	}
	int a = P1, b = P2;
	// sposta i due cortei finchè non arrivano a destinazione
	while (a != D1 || b != D2) {
		int na = succ[a][b].first;
		int nb = succ[a][b].second;
		// se a è fermo allora si è spostato b
		if (a == na)
			sposta(2, nb);
		else
			sposta(1, na);
		a = na;
		b = nb;
	}
}

bool espandi (int m) {
	// Quando vorrebbe esplorare un nuovo nodo, lo mette nel bucket corrispondente. In realta' se il bucket sarebbe uno di quelli già processati, lo mette nel bucket corrente
	// Ritorna true se ha raggiunto la destinazione, false altrimenti.

	while (!bucket[m].empty()) {
		int a = bucket[m].front().first;
		int b = bucket[m].front().second;
		bucket[m].pop();
		assert(!vis[a][b]);
		vis[a][b] = true;

		// visito i vicini di (a, b)
		for (int i=0; i<(int)G[a].size(); i++)
			if (!inseriti[G[a][i]][b]) {
				inseriti[G[a][i]][b] = true;
				if (dist[G[a][i]][b] >= m)
					bucket[m].push(make_pair(G[a][i], b));
				else
					bucket[dist[G[a][i]][b]].push(make_pair(G[a][i], b));
			}

		for (int i=0; i<(int)G[b].size(); i++)
			if (!inseriti[a][G[b][i]]) {
				inseriti[a][G[b][i]] = true;
				if (dist[a][G[b][i]] >= m)
					bucket[m].push(make_pair(a, G[b][i]));
				else
					bucket[dist[a][G[b][i]]].push(make_pair(a, G[b][i]));
			}                

	}

	if (vis[D1][D2]) return true;
	return false;
}

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {
	::N = N;
	::M = M;
	::P1 = P1;
	::P2 = P2;
	::D1 = D1;
	::D2 = D2;

	for (int i=0; i<M; i++) {
		G[A[i]].push_back(B[i]);
		G[B[i]].push_back(A[i]);
	}

	for (int j=0; j<N; j++) {
		for (int i=0; i<N; i++)
			vis2[i] = false;
		queue<int> Q;
		vis2[j] = true;
		Q.push(j);
		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
			for (int i=0; i<(int)G[v].size(); i++) {
				if (!vis2[G[v][i]]) {
					vis2[G[v][i]] = true;
					dist[j][G[v][i]] = 1 + dist[j][v];
					Q.push(G[v][i]);
				}
			}
		}
	}

	bucket[dist[P1][P2]].push(make_pair(P1, P2));
	inseriti[P1][P2] = true;

	for (int i=N-1; i>=0; i--)
		if (espandi(i)) {
			ricostruisci(i);
			return i;
		}

	assert(false);
}
