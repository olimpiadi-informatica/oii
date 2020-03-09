#include <numeric>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long int;
using ii = pair<i64, i64>;
const i64 MAX_VALUE = numeric_limits<i64>::max();

i64 costruisci(int _n, int _m, vector<long long>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = _n;
    size_t m = a.size();
    vector<vector<i64>> weight;
    weight.assign(n+1, vector<i64>(n+1, MAX_VALUE / 2LL));
    for(size_t i = 0; i < n+1; i++)
        weight[i][i] = 0;

    for(size_t i = 0; i < h.size(); i++)
        weight[0][i+1] = h[i];

    for(size_t i = 0; i < a.size(); i++)
        weight[a[i]+1][b[i]+1] = c[i];

    for(size_t k = 0; k < n+1; k++)
        for(size_t i = 0; i < n+1; i++)
            for(size_t j = 0; j < n+1; j++)
                weight[i][j] = min(weight[i][j], weight[i][k] + weight[k][j]);

    return accumulate(weight[0].begin(), weight[0].end(), 0LL);
}
