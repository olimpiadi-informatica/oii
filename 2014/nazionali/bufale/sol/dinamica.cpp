#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
using namespace std;

#define MAXN 5010

int n, voto1[MAXN], voto2[MAXN], memo[MAXN][MAXN];

int f(int idx, int given1) {
    if (idx == n)
        return 0;
    if (memo[idx][given1] != -1)
        return memo[idx][given1];
    int given2 = idx - given1, ans = 0;
    if (2 * given1 < n)
        ans = max(ans, voto1[idx] + f(idx + 1, given1 + 1));
    if (2 * given2 < n)
        ans = max(ans, voto2[idx] + f(idx + 1, given1));
    return memo[idx][given1] = ans;
}


long long int solve(int N, int M[], int P[]){
    n = N;
    for (int i=0; i<n; i++){
        voto1[i] = M[i];
        voto2[i] = P[i];
    }
    memset(memo, -1, sizeof memo);
    return f(0, 0);
}
