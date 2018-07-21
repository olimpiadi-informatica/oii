#include <vector>

const int INF = 1000000000;
const int MAXT = 5000000;
const int MAXN = 1000000;

std::vector < std::pair <int, int> > archi[MAXN+1];

std::vector <int> raggiunti[MAXT+1];
bool fatto[MAXN+1];
int dist[MAXN+1];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    // Creazione del grafo
    for (int i = 0; i < M; i++) {
        archi[A[i]].push_back(make_pair(i, B[i]));
        archi[B[i]].push_back(make_pair(i, A[i]));
    }
    // Inizializzazione
    for (int i = 0; i < N; i++) {
        fatto[i] = false;
        dist[i] = INF;
    }
    
    // Il nodo 0 è l'unico raggiungibile al tempo 0
    raggiunti[0].push_back(0);
    dist[0] = 0;
    
    for (int t = 0; t <= MAXT; t++) {
        for (int v : raggiunti[t]) {
            // Processo i vertici in raggiunti[t] che non sono
            // stati raggiunti prima di t
            if (!fatto[v]) {
                for (const auto& arco : archi[v]) {
                    int scala = arco.first;
                    int amico = arco.second;
                    int tempo = max(dist[v], inizio[scala])+1;
                    if (!fatto[amico] & dist[v] < fine[scala] & tempo < dist[amico]){
                        dist[amico] = tempo;
                        raggiunti[tempo].push_back(amico);
                    }
                }
                fatto[v] = true;
            }
        }
    }
    return (dist[N-1] == INF)? -1 : dist[N-1];
}
