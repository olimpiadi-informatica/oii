#include <numeric>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

typedef pair<long long, long long> ii;

long long int costruisci(int N, int M, vector<long long>& H, vector<int>& A, vector<int>& B, vector<int>& C)
{
    vector<vector<ii>> nodes;
    nodes.assign(N, vector<ii>());
    vector<long long> dist(N, LLONG_MAX / 2);

    for (int i = 0; i < H.size(); i++) {
      dist[i] = H[i];
    }

    for(int i = 0; i < A.size(); i++)
        nodes[A[i]].push_back({B[i], C[i]});

    priority_queue<ii, vector<ii>, greater<ii>> pq;

    for (int i = 0; i < N; i++) {
      pq.push({H[i], i});
    }

    while(!pq.empty())
    {
        ii u = pq.top(); pq.pop();

        if(dist[u.second] < u.first) continue;

        for(ii &v : nodes[u.second])
        {
            int new_dist = dist[u.second] + v.second;//min(dist[u.second] + v.second, H[v.first]);
            if(dist[v.first] > new_dist)
            {
                dist[v.first] = new_dist;
                pq.push({dist[v.first], v.first});
            }
        }
    }

    bool ok = true;
    for(int i = 0; i < N; i++) if(dist[i] == LLONG_MAX / 2) ok = false;
    return ok ? accumulate(dist.begin(), dist.end(), 0LL) : -1LL;
}
