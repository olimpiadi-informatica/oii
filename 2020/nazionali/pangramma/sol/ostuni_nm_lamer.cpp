#include <bits/stdc++.h>

using namespace std;

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

const u64 MOD = 46'337;

// Da donadoni_rangetree
pair<int, vector<size_t>> min_length(const vector<i32>& v, const int k) {
    vector<int> count(k);
    int taken = 0;
    int l = 0;
    int m = v.size();
    vector<size_t> spos;
    for(int i = 0; i < v.size(); i++) {
        // add element
        if(count[v[i]] == 0) {
            taken++;
        }
        count[v[i]]++;

        // remove useless
        while(count[v[l]] > 1) {
            count[v[l]]--;
            l++;
        }

        if(taken == k) {
            if(i - l + 1 < m) {
                m = i - l + 1;
                spos.push_back(l);
            } else if(i - l + 1 == m) {
                spos.push_back(l);
            }
        }
    }
    return make_pair(m, spos);
}

int conta(int n, int k, std::vector<int>& w) {
    vector<i32>& v = w;
    u64 sum = 0;
    pair<int, vector<size_t>> mret = min_length(v, k);
    int m = mret.first;
    for(size_t start : mret.second) {
        vector<u64> coeff(k);
        for(size_t i = 0; i < m; i++) {
            coeff[v[start + i]]++;
        }
        u64 acc = 1;
        for(size_t i = 0; i < k; i++) {
            acc = (acc * coeff[i]) % MOD;
        }
        sum = (sum + acc) % MOD;
    }
    return sum % MOD;
}
