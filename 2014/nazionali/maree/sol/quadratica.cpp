#include <vector>
#include <queue>
#include <limits>
#define MAXN 200000
using namespace std;

int N, M, T;

vector<int> graph[MAXN], rgraph[MAXN];
bool visited[MAXN];
bool visited2[MAXN];
int res = numeric_limits<int>::max();

void bfs2(int b, int d){
    queue<pair<int, int> > q;
    q.push(make_pair(b, d));
    for(int i=0; i<N; i++) visited2[i] = false;
    while(!q.empty()){
        pair<int, int> c = q.front();
        q.pop();
        if(visited2[c.first]) continue;
        visited2[c.first] = true;
        if(c.first == N-1) res = min(res, c.second);
        for(unsigned i=0; i<rgraph[c.first].size(); i++)
            q.push(make_pair(rgraph[c.first][i], c.second+1));
    }
}

void bfs(int b){
    queue<pair<int, int> > q;
    q.push(make_pair(b, 0));
    for(int i=0; i<N; i++) visited[i] = false;
    while(!q.empty()){
        pair<int, int> c = q.front();
        q.pop();
        if(visited[c.first]) continue;
        visited[c.first] = true;
        if(c.second > T) continue;
        bfs2(c.first, T);
        if(c.first == N-1) res = min(res, c.second);
        for(unsigned i=0; i<graph[c.first].size(); i++)
            q.push(make_pair(graph[c.first][i], c.second+1));
    }
}

int solve(int n, int m, int t, int S[], int E[]){
    N = n;
    M = m;
    T = t;
    for(int i=0; i<M; i++) graph[S[i]].push_back(E[i]);
    for(int i=0; i<M; i++) rgraph[E[i]].push_back(S[i]);
    bfs(0);
    if(res==numeric_limits<int>::max()) return -1;
    return res;
}

