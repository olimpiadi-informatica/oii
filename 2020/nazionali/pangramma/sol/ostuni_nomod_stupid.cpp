/*
    Author: Dario Ostuni
    Complexity: θ(n) [with a log(MOD) constant factor]
*/

#include <bits/stdc++.h>

using namespace std;

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

const u32 MOD = 46'337;

int conta(int n, int k, std::vector<int>& w) {
    vector<i32>& v = w;
    vector<u32> coeff(k);
    size_t coeff_zero = k;
    u32 partial = 1;
    u64 min_window = numeric_limits<u64>::max();
    u32 sum = 0;
    size_t start = 0, end = 0;
    while(start < n) {
        if(end < n && coeff_zero > 0) {
            if(coeff[v[end]] > 0) {
                partial /= coeff[v[end]]++;
                partial *= coeff[v[end]];
            } else {
                coeff[v[end]]++;
                coeff_zero--;
            }
            end++;
        } else {
            partial /= coeff[v[start]]--;
            if(coeff[v[start]] == 0) {
                coeff_zero++;
            } else {
                partial *= coeff[v[start]];
            }
            start++;
        }
        if(coeff_zero == 0) {
            if(end - start < min_window) {
                min_window = end - start;
                sum = partial % MOD;
            } else if(end - start == min_window) {
                sum = (sum + partial) % MOD;
            }
        }
    }
    return sum % MOD;
}
