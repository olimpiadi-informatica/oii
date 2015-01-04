#include <vector>
#include <queue>
#include <limits>
#define MAXN 200000
using namespace std;

int N, M, T;

vector<int> graph[MAXN];
bool visited[MAXN];
int dist[MAXN];
int rdist[MAXN];

void bfs(int b, int* res){
    queue<pair<int, int> > q;
    q.push(make_pair(b, 0));
    for(int i=0; i<N; i++) visited[i] = false;
    while(!q.empty()){
        pair<int, int> c = q.front();
        q.pop();
        if(visited[c.first]) continue;
        visited[c.first] = true;
        res[c.first] = c.second;
        for(unsigned i=0; i<graph[c.first].size(); i++)
            q.push(make_pair(graph[c.first][i], c.second+1));
    }
}

void dfs(int nodo, int tempo) {
    if (tempo > T)
        return; // la marea e' cambiata, non dovresti essere qui
    visited[nodo] = true;
    for (int i=0; i<(int)graph[nodo].size(); i++) {
        int v = graph[nodo][i];
        if (!visited[v]) dfs(v, tempo + 1);
    }
}

int solve(int n, int m, int t, int S[], int E[]){
    N = n;
    M = m;
    T = t;
    for(int i=0; i<M; i++) graph[S[i]].push_back(E[i]);
    for(int i=0; i<N; i++) dist[i] = rdist[i] = numeric_limits<int>::max();
    dfs(0, 0);
    if (visited[N-1]) { // arrivo al traguardo prima della marea quindi...
        bfs(0, dist);
        return dist[N-1];
    }
    // arriva la marea prima che io arrivo al traguardo
    bfs(N-1, rdist);
    int best = numeric_limits<int>::max();
    for (int i=0; i<N; i++)
        if (visited[i]) // e' raggiungibile da 0
            best = min(best, T + dist[i]); // assumo che ci arrivo in fretta e poi devo aspettare fino a T
    if(best == numeric_limits<int>::max()) return -1;
    return best;
}

