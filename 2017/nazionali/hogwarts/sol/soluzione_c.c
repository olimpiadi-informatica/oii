#define MAXN 1003
#define INF 1000000

int grafo[MAXN][MAXN][2]; // indico inizio e fine
int distanza[MAXN];
int visitati[MAXN];

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int max(int a, int b) {
    return -min(-a, -b);
}


int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            grafo[i][j][0] = -1;
            
    for (int i=0; i<M; i++) {
        grafo[A[i]][B[i]][0] = inizio[i];
        grafo[A[i]][B[i]][1] = fine[i];
        grafo[B[i]][A[i]][0] = inizio[i];
        grafo[B[i]][A[i]][1] = fine[i];
    }
    
    for (int i=1; i<N; i++)
        distanza[i] = INF;
        
    for (int i=0; i<N; i++) {
        int tempo = INF;
        int nodo;
        
        for (int j=0; j<N; j++)
            if (visitati[j] == 0 && distanza[j] < tempo) {
                tempo = distanza[j];
                nodo = j;
            }
            
        if (tempo == INF) break;
        
        visitati[nodo] = 1;
        for (int j=0; j<N; j++)
            if (grafo[nodo][j][0] >= 0)
                if (tempo < grafo[nodo][j][1])
                    distanza[j] = min(distanza[j], max(tempo, grafo[nodo][j][0]) + 1);
    }
    
	if (distanza[N-1] < INF) return distanza[N-1];
    else return -1;
}
