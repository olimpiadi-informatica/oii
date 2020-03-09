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

const u64 MOD = 46337;

u64 fastexp(u64 b, u64 e) {
    if(e == 0) {
        return 1;
    } else if(e & 1) {
        return (b * fastexp(b, e - 1)) % MOD;
    } else {
        u64 tmp = fastexp(b, e >> 1);
        return (tmp * tmp) % MOD;
    }
}

u64 modinv(u64 n) { return fastexp(n, MOD - 2); }

int conta(int n, int k, std::vector<int>& w) {
    vector<i32>& v = w;
    vector<u64> coeff(k);
    size_t coeff_zero = k;
    u64 partial = 1;
    u64 min_window = numeric_limits<u64>::max();
    u64 sum = 0;
    size_t start = 0, end = 0;
    while(start < n) {
        if(end < n && coeff_zero > 0) {
            if(coeff[v[end]] > 0) {
                u64 d = modinv(coeff[v[end]]++);
                partial = (partial * d) % MOD;
                partial = (partial * coeff[v[end]]) % MOD;
            } else {
                coeff[v[end]]++;
                coeff_zero--;
            }
            end++;
        } else {
            u64 d = modinv(coeff[v[start]]--);
            partial = (partial * d) % MOD;
            if(coeff[v[start]] == 0) {
                coeff_zero++;
            } else {
                partial = (partial * coeff[v[start]]) % MOD;
            }
            start++;
        }
        if(coeff_zero == 0) {
            if(end - start < min_window) {
                min_window = end - start;
                sum = partial;
            } else if(end - start == min_window) {
                sum = (sum + partial) % MOD;
            }
        }
    }
    return sum;
}
