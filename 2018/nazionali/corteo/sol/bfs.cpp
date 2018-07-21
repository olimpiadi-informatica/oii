/** Risolve il subtask in cui i due cortei sono gia' a destinazione (quindi non ha senso che si muovano)
 * Complessità: O(M)
 **/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>

#define MAXN 1000

using namespace std;

vector<int> G[MAXN];
int N, M, P1, D1, P2, D2;
bool vis[MAXN];
int dist[MAXN];

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]) {    
	for (int i=0; i<M; i++) {
		G[A[i]].push_back(B[i]);
		G[B[i]].push_back(A[i]);
	}

	queue<int> Q;
	vis[P1] = true;
	Q.push(P1);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int i=0; i<(int)G[v].size(); i++) {
			if (!vis[G[v][i]]) {
				vis[G[v][i]] = true;
				dist[G[v][i]] = 1 + dist[v];
				Q.push(G[v][i]);
			}
		}
	}
	return dist[P2];
}

