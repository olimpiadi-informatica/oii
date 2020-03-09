/**
 * Come dijkstra, ma dalla coda dei nodi da visitare si estraggono nodi casualmente
 */

#include <chrono>
#include <random>
#include <unordered_set>
#include <vector>

#define INF 1000000000000000000L

using namespace std;

auto engine = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
auto distr  = uniform_real_distribution<double>(0.0, 1.0);

template <typename T>
struct random_set {
    unordered_set<T> elems;
    vector<T> morelems;
    
    bool empty() {
        return elems.empty();
    }
    
    void insert(T x) {
        if (!elems.count(x)) {
            elems.insert(x);
            morelems.push_back(x);
        }
    }
    
    void erase(T x) {
        elems.erase(x);
        if (morelems.size() > 2*elems.size())
            morelems = vector<T>(elems.begin(), elems.end());
    }
    
    int pop() {
        int x = morelems[(int)(distr(engine) * morelems.size())];
        if (elems.count(x)) {
            erase(x);
            return x;
        }
        return pop();
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
    random_set<int> tofix;
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
