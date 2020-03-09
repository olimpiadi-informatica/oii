#include <cassert>
#include <numeric>
#include <vector>

using namespace std;

using i64 = long long int;
const i64 MAX_HEIGHT = 5;

i64 costruisci(int _n, int _m, vector<i64>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = h.size();
    size_t m = a.size();
    assert(n <= 5);
    i64 best_solution = 0;

    vector<long long> myh(5, 0LL);
    for(size_t i = 0; i < n; i++) {
        myh[i] = h[i];
    }

    for(i64 a0 = 0; a0 <= myh[0]; a0++) {
        for(i64 a1 = 0; a1 <= myh[1]; a1++) {
            for(i64 a2 = 0; a2 <= myh[2]; a2++) {
                for(i64 a3 = 0; a3 <= myh[3]; a3++) {
                    for(i64 a4 = 0; a4 <= myh[4]; a4++) {
                        vector<i64> height = {a0, a1, a2, a3, a4};
                        bool ok = true;
                        for(size_t i = 0; i < m && ok; i++) {
                            if(!(height[a[i]] >= height[b[i]] - i64(c[i]))) {
                                ok = false;
                            }
                        }
                        if(ok) {
                            best_solution =
                                max(best_solution,
                                    accumulate(height.begin(), height.end(), 0LL));
                        }
                    }
                }
            }
        }
    }
    return best_solution;
}
