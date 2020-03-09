#include <bits/stdc++.h>

using namespace std;

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

const u64 MOD = 46'337;

int conta(int n, int k, std::vector<int>& w) {
    vector<i32>& v = w;
    u64 lsum = 0;
    for(size_t length = 1; length <= n; length++) {
        u64 sum = 0;
        for(size_t start = 0; start < n - length + 1; start++) {
            vector<u64> coeff(k);
            for(size_t i = 0; i < length; i++) {
                coeff[v[start + i]]++;
            }
            u64 acc = 1;
            for(size_t i = 0; i < k; i++) {
                acc = (acc * coeff[i]) % MOD;
            }
            sum = (sum + acc) % MOD;
        }
        if(sum > 0 && lsum == 0) {
            lsum = sum;
        }
    }
    return lsum;
}
