#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20000000

int sufBuoni[MAXN], sufCattiveria[MAXN];

int cerca(int from, int to, int sopporta) {
    if (from > to)
        return 0;
    if (from == to)
        return (sufCattiveria[from] <= sopporta) ? sufBuoni[from] : 0;
    int mid = (from + to) / 2;
    if (sufCattiveria[mid] <= sopporta)
        return cerca(from, mid, sopporta);
    else
        return cerca(mid+1, to, sopporta);
}

int solve(int N, int K, int cattivo[]) {
    for (int i=N-1; i>=0; i--) {
        sufBuoni[i] = !cattivo[i];
        sufCattiveria[i] = cattivo[i];
        if (i+1 < N) {
            sufBuoni[i] += sufBuoni[i + 1];
            sufCattiveria[i] += sufCattiveria[i + 1];
        }
    }
    int ans = 0;
    int prefCattiveria = 0, prefBuoni = 0;
    for (int i=0; i<=N; i++) {
        if (prefCattiveria > K)
            break;
        ans = max(ans, prefBuoni + cerca(i+1, N-1, K - prefCattiveria));
        if (i==N) break;
        prefBuoni += !cattivo[i];
        prefCattiveria += cattivo[i];
    }
    return ans;
}
