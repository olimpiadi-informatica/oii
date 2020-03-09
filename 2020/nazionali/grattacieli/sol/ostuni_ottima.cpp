#include <numeric>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

using i64 = long long int;
using ii = pair<i64, i64>;
const i64 MAX_VALUE = numeric_limits<i64>::max();

i64 costruisci(int _n, int _m, vector<i64>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = h.size();
    size_t m = a.size();
    vector<vector<ii>> children(n);
    vector<i64> weight(n, MAX_VALUE);
    for(size_t i = 0; i < m; i++) {
        children[a[i]].push_back(make_pair(c[i], b[i]));
    }
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for(size_t i = 0; i < n; i++) {
        pq.push(make_pair(h[i], i));
    }
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        if(top.first >= weight[top.second]) {
            continue;
        }
        weight[top.second] = top.first;
        for(const auto& i : children[top.second]) {
            if(top.first + i.first < weight[i.second]) {
                pq.push(make_pair(top.first + i.first, i.second));
            }
        }
    }
    return accumulate(weight.begin(), weight.end(), 0LL);
}
