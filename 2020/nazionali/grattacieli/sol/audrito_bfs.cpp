/**
 * Come dijkstra, ma dalla coda dei nodi da visitare si estraggono nodi secondo ordine bfs
 */

#include <deque>
#include <unordered_set>
#include <vector>

#define INF 1000000000000000000L

using namespace std;

template <typename T>
struct bfs_set {
    unordered_set<T> elems;
    deque<T> morelems;
    
    bool empty() {
        return elems.empty();
    }
    
    void insert(T x) {
        if (!elems.count(x)) {
            elems.insert(x);
            morelems.push_back(x);
        }
    }
    
    int pop() {
        int x = morelems.front();
        morelems.pop_front();
        elems.erase(x);
        return x;
    }
};

long long costruisci(int n, int m, vector<long long>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    vector<vector<int>> adj(n), wh(n);
    for (int i=0; i<m; ++i) {
        adj[a[i]].push_back(b[i]);
        wh[a[i]].push_back(c[i]);
    }
    vector<long long> D(n);
    for (int i=0; i<n; ++i) D[i] = h[i];
    bfs_set<int> tofix;
    for (int i=0; i<n; ++i) tofix.insert(i);
    while (!tofix.empty()) {
        int n = tofix.pop();
        for (int i=0; i<adj[n].size(); ++i)
            if (D[n]+wh[n][i] < D[adj[n][i]]) {
                D[adj[n][i]] = D[n]+wh[n][i];
                tofix.insert(adj[n][i]);
            }
    }
    for (int i=1; i<n; ++i) {
        D[0] += D[i];
    }
    return D[0];
}
