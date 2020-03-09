#include <numeric>
#include <limits>
#include <vector>

using namespace std;

using i64 = long long int;
using ii = pair<i64, i64>;
const i64 MAX_VALUE = numeric_limits<i64>::max();

i64 costruisci(int _n, int _m, vector<i64>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = h.size();
    size_t m = a.size();
    vector<i64> weight = h;
    for(size_t j = 0; j < n; j++) {
        for(size_t i = 0; i < m; i++) {
            if(weight[a[i]] + i64(c[i]) < weight[b[i]]) {
                weight[b[i]] = weight[a[i]] + i64(c[i]);
            }
        }
    }
    return accumulate(weight.begin(), weight.end(), 0LL);
}
