#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <climits>

#define MAXN 1000000
#define pb push_back
#define mp make_pair

using namespace std;

class arco {	
	public:
		int arrivo;
		int inizio;
		int fine;
		arco() { arrivo = 0; inizio = 0; fine = 0;};
		arco(int a, int b, int c) {arrivo = a; inizio = b; fine = c;};
};

vector<arco> grafo[MAXN];
int distanza[MAXN];
bool visitati[MAXN];


int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i=0; i<M; i++) {
        grafo[A[i]].pb(arco(B[i], inizio[i], fine[i]));
        grafo[B[i]].pb(arco(A[i], inizio[i], fine[i]));
    }
    
    for (int i=1; i<N; i++)
        distanza[i] = INT_MAX;
        
    for (int i=0; i<N; i++) {
        int tempo = INT_MAX;
        int nodo;
        
        for (int j=0; j<N; j++)
            if (!visitati[j] && distanza[j] < tempo) {
                tempo = distanza[j];
                nodo = j;
            }
            
        if (tempo == INT_MAX) break;
        
        visitati[nodo] = true;
        for (int j=0; j<(int)grafo[nodo].size(); j++)
            if (tempo < grafo[nodo][j].fine)
                distanza[grafo[nodo][j].arrivo] = min(distanza[grafo[nodo][j].arrivo], max(tempo, grafo[nodo][j].inizio) + 1);
    }
    
	if (distanza[N-1] < INT_MAX) return distanza[N-1];
    else return -1;
}

