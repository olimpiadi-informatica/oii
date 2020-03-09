/*
    Author: Dario Ostuni
    Complexity: θ(n) [with a log(MOD) constant factor]
*/

#include <bits/stdc++.h>

using namespace std;

using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

const u16 MOD = 46337;

u16 modcache[MOD];
u16 genpow[MOD];

void populate() {
    genpow[0] = 1;
    for(int i = 1; i < MOD; i++) {
        genpow[i] = (u64(genpow[i-1]) * 3ULL) % u64(MOD);
    }

    for(int i = 0; i < MOD; i++) {
        modcache[genpow[i]] = genpow[MOD-1-i];
    }
}

int conta(int n, int k, std::vector<int>& w) {
    populate();
    vector<i32>& v = w;
    vector<u16> coeff(k);
    size_t coeff_zero = k;
    u64 partial = 1;
    u64 min_window = numeric_limits<u64>::max();
    u64 sum = 0;
    size_t start = 0, end = 0;
    while(start < n) {
        if(end < n && coeff_zero > 0) {
            if(coeff[v[end]] > 0) {
                u64 d = modcache[coeff[v[end]]++];
                partial = (partial * d) % MOD;
                partial = (partial * coeff[v[end]]) % MOD;
            } else {
                coeff[v[end]]++;
                coeff_zero--;
            }
            end++;
        } else {
            u64 d = modcache[coeff[v[start]]--];
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
