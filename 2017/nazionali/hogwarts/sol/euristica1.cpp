/** Euristica per hogwarts: prendo il grafo con tutti gli archi, cerco il cammino minimo (se esiste) tra 0 e N-1;
 * poi guardo qudno posso percorrerlo e do quella come risposta **/
 
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 1000000

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
int prec[MAXN], ap[MAXN], ch[MAXN], succ[MAXN];
queue<int> Q;

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i=0; i<M; i++) {
        G[A[i]].push_back(arco(B[i], inizio[i], fine[i]));
        G[B[i]].push_back(arco(A[i], inizio[i], fine[i]));
    }
    
    prec[0] = -1;
    for (int i=1; i<N; i++) prec[i] = -2;
    Q.push(0);
    
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i=0; i<(int)G[x].size(); i++) {
            int y = G[x][i].arrivo;
            if (prec[y] != -2) continue;
            
            prec[y] = x;
            ap[y] = G[x][i].inizio;
            ch[y] = G[x][i].fine;
            Q.push(y);
        }
    }
    
	if (prec[N-1] == -2) return -1; // qui è sicuramente giusto, ma non è l'unico caso in cui deve ritornare -1
    
    int t = 0; // tempo impiegato
    int x = N-1;
    while (prec[x] != -1) {
        succ[prec[x]] = x;
        x = prec[x];
    }
    
    assert(x == 0);
    
    while (x != N-1) {
        t = max(t, ap[succ[x]]) + 1;
        if (t > ch[succ[x]]) return -1;
        x = succ[x];
    }
    
    return t;
}

