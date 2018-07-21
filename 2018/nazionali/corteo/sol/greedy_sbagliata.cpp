// Soluzione greedy sbagliata:
// Il primo corteo segue il percorso minimo fino a destinazione, il secondo cerca sempre di allontanarsi.
// Appena il primo arriva il secondo segue il percorso più corto.
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

void sposta(int chi, int dove);

const int MAXN = 10005;

vector<int> G[MAXN];
int N, M;
int dist[MAXN][MAXN];
bool vis2[MAXN];

// All Pair Shortest Path
void apsp() {
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
}

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {
	::N = N;
	::M = M;
	for (int i=0; i<M; i++) {
		G[A[i]].push_back(B[i]);
		G[B[i]].push_back(A[i]);
	}

	apsp();
	int sol = dist[P1][P2];
	// porta il primo corteo a destinazione
	while (P1 != D1) {
		bool spostato;
		// prova ad allontanare il più possibile il secondo
		do {
			spostato = false;
			for (int v : G[P2]) {
				if (dist[P1][v] > dist[P1][P2]) {
					sposta(2, v);
					P2 = v;
					spostato = true;
					sol = min(sol, dist[P1][P2]);
					break;
				}
			}
		} while (spostato);
		// sposta il primo verso la destinazione
		for (int v : G[P1]) {
			if (dist[v][D1] < dist[P1][D1]) {
				sposta(1, v);
				P1 = v;
				sol = min(sol, dist[P1][P2]);
				break;
			}
		}
	}
	// porta il secondo corteo a destinazione
	while (P2 != D2) {
		for (int v : G[P2]) {
			if (dist[v][D2] < dist[P2][D2]) {
				sposta(2, v);
				P2 = v;
				sol = min(sol, dist[P1][P2]);
				break;
			}
		}
	}
	return sol;
}
