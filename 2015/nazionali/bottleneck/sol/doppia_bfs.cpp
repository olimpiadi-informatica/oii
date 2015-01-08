#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAXM = 1000000;
const int MAXN = 100000;
const int INF = 1000000001;

int distanza[MAXN+1][2];
vector<int> grafo[MAXN+1];

void BFS(int inizio, int pos, int N) {
	for (int i=1; i<=N; i++)
		distanza[i][pos] = -1;
		
	queue<int> Q;
	
	distanza[inizio][pos] = 0;
	Q.push(inizio);
	
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		
		for (int i=0; i<(int)grafo[v].size(); i++) {
			int x = grafo[v][i];
			
			if (distanza[x][pos] == -1) {
				distanza[x][pos] = distanza[v][pos] + 1;
				Q.push(x);
			}
		}
	}
}

int Analizza(int N, int M, int W, int L, int arco_da[], int arco_a[], int capacita[], int R, int C) {
	// Ricostruisco il grafo
	for (int i=0; i<M; i++) {
		grafo[arco_da[i]].push_back(arco_a[i]);
		grafo[arco_a[i]].push_back(arco_da[i]);
	}
	
	// BFS da W e poi da L
	BFS(W, 0, N);
	BFS(L, 1, N);

	// Trovo il minimo degli archi che sono su percorsi di distanza minima
	int minimo = INF;
	int distWL = distanza[L][0];
	
	assert(distanza[L][0] == distanza[W][1]);
	
	for (int i=0; i<M; i++)
		if (distanza[arco_a[i]][0] + distanza[arco_da[i]][1] + 1 == distWL || distanza[arco_da[i]][0] + distanza[arco_a[i]][1] + 1 == distWL)
			minimo = min(minimo, capacita[i]);
	
	return minimo;
}
