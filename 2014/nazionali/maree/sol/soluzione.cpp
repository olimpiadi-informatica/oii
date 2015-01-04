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

int solve(int n, int m, int t, int S[], int E[]){
    N = n;
    M = m;
    T = t;
    for(int i=0; i<M; i++) graph[S[i]].push_back(E[i]);
    for(int i=0; i<N; i++) dist[i] = rdist[i] = numeric_limits<int>::max();
    bfs(0, dist);
    bfs(N-1, rdist);
    if(dist[N-1] <= T)
        return dist[N-1];
    int best = numeric_limits<int>::max();
    for(int i=0; i<N; i++)
        if(dist[i] <= T && rdist[i] < numeric_limits<int>::max()){
            int v = T + rdist[i];
            if(v<best) best = v;
        }
    if(best == numeric_limits<int>::max()) return -1;
    return best;
}

