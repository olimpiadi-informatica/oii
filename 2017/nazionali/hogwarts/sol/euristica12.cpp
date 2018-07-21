/** Euristiche 1 e 2 combinate **/

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

#define MAXN 1000000

using namespace std;

class arco {	
	public:
		int arrivo;
		int inizio;
		int fine;
		arco() { arrivo = 0; inizio = 0; fine = 0;};
		arco(int a, int b, int c) {arrivo = a; inizio = b; fine = c;};
        bool operator< (const arco &b) const {
            if (inizio != b.inizio) return (inizio < b.inizio);
            if (fine != b.fine) return (fine < b.fine);
            return (arrivo < b.arrivo);
        }
};

vector<arco> G[MAXN];
int prec[MAXN], ap[MAXN], ch[MAXN], succ[MAXN];
queue<int> Q;
int visti[MAXN];

int raggiungi1(int N, int M, int A[], int B[], int inizio[], int fine[]) {
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
    
	if (prec[N-1] == -2) return INT_MAX; // qui è sicuramente giusto, ma non è l'unico caso in cui deve ritornare -1
    
    int t = 0; // tempo impiegato
    int x = N-1;
    while (prec[x] != -1) {
        succ[prec[x]] = x;
        x = prec[x];
    }
    
    assert(x == 0);
    
    while (x != N-1) {
        t = max(t, ap[succ[x]]) + 1;
        if (t > ch[succ[x]]) return INT_MAX;
        x = succ[x];
    }
    
    return t;
}

int raggiungi2(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    /*for (int i=0; i<M; i++) {
        G[A[i]].push_back(arco(B[i], inizio[i], fine[i]));
        G[B[i]].push_back(arco(A[i], inizio[i], fine[i]));
    }*/
    
    for (int i=0; i<N; i++)
        sort(G[i].begin(), G[i].end());
    
    int t = 0; // tempo che è passato
    int x = 0; // nodo in cui mi trovo
    while (x != N-1) {
        visti[x] = true;
        bool ok = false;
        for (int i=0; i<(int)G[x].size(); i++) {
            if (!visti[G[x][i].arrivo] && (t < G[x][i].fine)) {
                t = 1 + max(t, G[x][i].inizio);
                x = G[x][i].arrivo;
                ok = true; // dice che sono riuscito ad andare avanti almeno un pezzettino
                break;
            }            
        }
        if (!ok) return INT_MAX;
    }
    
    return t;
}

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    int a = raggiungi1(N, M, A, B, inizio, fine);
    int b = raggiungi2(N, M, A, B, inizio, fine);
    
    if (min(a, b) == INT_MAX) return -1;
    else return min(a, b);
}




