#include <numeric>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

using i64 = long long int;
using ii = pair<i64, i64>;

long long costruisci(int _n, int _m, vector<long long>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = h.size();
    size_t m = a.size();
    vector<vector<ii>> children(n);
    vector<i64> weight(n, LLONG_MAX);
    for(size_t i = 0; i < m; i++) {
        children[a[i]].push_back(make_pair(c[i], b[i]));
    }
    queue<ii> q;
    for(size_t i = 0; i < n; i++) {
        q.push(make_pair(h[i], i));
    }
    while(!q.empty()) {
        auto top = q.front();
        q.pop();
        if(top.first >= weight[top.second]) {
            continue;
        }
        weight[top.second] = top.first;
        for(const auto& i : children[top.second]) {
            if(top.first + i.first < weight[i.second]) {
                q.push(make_pair(top.first + i.first, i.second));
            }
        }
    }
    return accumulate(weight.begin(), weight.end(), 0LL);
}
