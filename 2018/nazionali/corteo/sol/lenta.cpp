// Costruisce il grafo prodotto. In ogni nodo c'è un costo dato dalla distanza tra i due tizi
// Voglio un cammino che arrivi da sorgente massimizzando il nodo di etichetta minima in cui passo.
// Posso farlo per ricerca binaria sulla soluzione. O(N M log N)

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAXN 1000

using namespace std;

void sposta(int chi, int dove);

typedef pair<int,int> ii;
vector<int> G[MAXN];
int N, M, P1, D1, P2, D2;
bool vis[MAXN][MAXN];
int dist[MAXN][MAXN];
bool vis2[MAXN];
ii succ[MAXN][MAXN];

bool celafaccio (int m) {
	// Dice se riesco ad andare dalla partenza all'arrivo stando solo su archi che hanno distanza >= m
	if (dist[P1][P2] < m || dist[D1][D2] < m)
		return false;

	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			vis[i][j] = false;

	queue<pair<int, int> > Q;
	Q.push(make_pair(P1, P2));
	vis[P1][P2] = true;
	if (P1 == D1 && P2 == D2) return true;
	while (!Q.empty()) {
		int a = Q.front().first;
		int b = Q.front().second;
		Q.pop();
		// visito i vicini di (a, b)
		for (int i=0; i<(int)G[a].size(); i++)
			if (!vis[G[a][i]][b] && dist[G[a][i]][b] >= m) {
				if (G[a][i] == D1 && b == D2) return true;

				vis[G[a][i]][b] = true;
				Q.push(make_pair(G[a][i], b));
			}
		for (int i=0; i<(int)G[b].size(); i++)
			if (!vis[a][G[b][i]] && dist[a][G[b][i]] >= m) {
				if (a == D1 && G[b][i] == D2) return true;

				vis[a][G[b][i]] = true;
				Q.push(make_pair(a, G[b][i]));
			}
	}

	return false;
}

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

	// Stampa le distanze
	/*for (int i=0; i<N; i++) {
	  for (int j=0; j<N; j++)
	  cout << dist[i][j] << " ";
	  cout << endl;
	  }*/


	// Ricerca binaria
	int lb = 0;
	int ub = N;
	int m;
	while (lb < ub) {
		if (lb == ub -1) {
			if (celafaccio(ub)) {
				ricostruisci(ub);
				return ub;
			} else {
				ricostruisci(lb);
				return lb;
			}
		}
		m = (lb + ub)/2;
		if (celafaccio(m))
			lb = m;
		else
			ub = m;
	}

	ricostruisci(m);
	return m;    
}
