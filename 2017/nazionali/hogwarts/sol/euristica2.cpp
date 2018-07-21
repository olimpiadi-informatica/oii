/** Euristica per hogwarts: prendo il primo arco che compare e lo seguo, senza ritornare indietro mai **/
 
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
int visti[MAXN];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i=0; i<M; i++) {
        G[A[i]].push_back(arco(B[i], inizio[i], fine[i]));
        G[B[i]].push_back(arco(A[i], inizio[i], fine[i]));
    }
    
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
        if (!ok) return -1;
    }
    
    return t;
}

