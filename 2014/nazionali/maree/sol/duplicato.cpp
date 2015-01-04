#include <vector>
#include <queue>
#include <limits>
#define MAXN 200000
using namespace std;

vector< pair<int,int> > graph[2*MAXN];
bool visited[2*MAXN];
int dist[2*MAXN];

int solve(int N, int M, int T, int S[], int E[]){
    for (int i = 0; i < N; i += 1) {
        graph[i].push_back(make_pair(2000000000, N+i));
    }
    for (int i = 0; i < M; i += 1) {
        graph[S[i]].push_back(make_pair(1, E[i]));
        graph[N+E[i]].push_back(make_pair(1, N+S[i]));
    }

    for (int i = 0; i < 2*N; i += 1) {
        dist[i] = numeric_limits<int>::max();
    }
    priority_queue< pair<int,int> > coda;
    coda.push(make_pair(0, 0));
    dist[0] = 0;
    while (!coda.empty()) {
        pair<int,int> top = coda.top();
        coda.pop();
        int u = top.second;
        if (!visited[u]) {
            visited[u] = true;
            if (u < N && dist[u] <= T) {
                graph[u][0].first = T - dist[u];
            }
            for (int i = 0; i < graph[u].size(); i += 1) {
                int d = graph[u][i].first;
                int v = graph[u][i].second;
                if (dist[v] > d + dist[u]) {
                    if (v >= N || d + dist[u] <= T) {
                        dist[v] = d + dist[u];
                        coda.push(make_pair(-dist[v], v));
                    }
                }
            }
        }
    }
    if (min(dist[2*N-1], dist[N-1]) >= 2000000000) {
        return -1;
    } else {
        return min(dist[2*N-1], dist[N-1]);
    }
}

