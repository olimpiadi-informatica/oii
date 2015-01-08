#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXM = 1000000;
const int MAXN = 100000;
const int INF = 1000000001;

typedef pair<int, int> ii;

int minimo[MAXN+1];
int distanza[MAXN+1];
vector<ii> grafo[MAXN+1];

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int R, int C) {
	// Ricostruisco il grafo
	for (int i=0; i<M; i++) {
		grafo[arco_da[i]].push_back(make_pair(arco_a[i], capacita[i]));
		grafo[arco_a[i]].push_back(make_pair(arco_da[i], capacita[i]));
	}
	int best = INF;
	
	for (int tentativi = 0; tentativi < 5; tentativi++) {
		for (int i=0; i<N; i++) {
			random_shuffle(grafo[i].begin(), grafo[i].end());
		}
	
		// Trovo il minimo richiesto
		for (int i=1; i<=N; i++)
			distanza[i] = -1;
		
		queue<int> Q;
	
		distanza[W] = 0;
		minimo[W] = INF;
		Q.push(W);
	
		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
		
			for (int i=0; i<(int)grafo[v].size(); i++) {
				int x = grafo[v][i].first;
				int cap = grafo[v][i].second;
			
				if (distanza[x] == -1) {
					distanza[x] = distanza[v] + 1;
					minimo[x] = min(minimo[v], cap);
					Q.push(x);
				}
			}
		}
		best = min(best, minimo[L]);
	}
	
	return best;
}
