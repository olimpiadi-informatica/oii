#include <bits/stdc++.h>

using namespace std;

#define MOD 46337ULL

int conta(int n, int k, std::vector<int>& v) {
    int s = 0;
    int last = v[0];
    for(size_t i = 1; i < v.size(); i++) {
        s += (last != v[i]);
        last = v[i];
    }
    return (s ? s : v.size()) % MOD;
}
