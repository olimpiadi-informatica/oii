#include <vector>

const int INF = 1000000000;
const int MAXT = 5000000;
const int MAXN = 1000000;

std::vector<std::pair<int, int>> edges[MAXN+1];

std::vector <int> reached[MAXT+1];
bool visited[MAXN+1];
int dist[MAXN+1];

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    // Creation of the graph
    for (int i = 0; i < M; i++) {
        edges[A[i]].push_back(make_pair(i, B[i]));
        edges[B[i]].push_back(make_pair(i, A[i]));
    }
    // Initialization
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        dist[i] = INF;
    }
    
    // The vertex 0 is the unique reachable at time 0
    reached[0].push_back(0);
    dist[0] = 0;
    
    for (int t = 0; t <= MAXT; t++) {
        for (int v : reached[t]) {
            // We process the vertices in reached[t] which
            // have not been reached before t
            if (!visited[v]) {
                for (const auto& e : edges[v]) {
                    int stair = e.first;
                    int to = e.second;
                    int time = max(dist[v], inizio[stair])+1;
                    if (!visited[to] & dist[v] < fine[stair] & time < dist[to]){
                        dist[to] = time;
                        reached[time].push_back(to);
                    }
                }
                visited[v] = true;
            }
        }
    }
    return (dist[N-1] == INF)? -1 : dist[N-1];
}