#include <vector>
#include <cstdio>

using std::vector;

const int S_MAX = 100000, P_MAX = S_MAX;
const int A = 100;

vector<int> occ[A]; // occ[a] == [ i for i in range(S) if s[i] == a ] + [ S ]
int cur[S_MAX]; // s[occ[cur[j]]] == p[j]

const int debug = 0;

long long conta(int S, int s[], int P, int p[]) {
    long long ans = 0;

    for(int i = 0; i < S; i++) {
        occ[s[i]].push_back(i);
    }
    for(int a = 0; a < A; a++) {
        occ[a].push_back(S);
    }

    for(int i = 0; i < S; i++) {
        int left = i-1;
        for(int j = 0; j < P; j++) {
            int a = p[j];
            for(; occ[a][cur[j]] <= left; cur[j]++) {
                if(debug)
                    fprintf(stderr, "left: %2d i:%2d j:%2d a:%2d cur[j]:%2d occ[a][cur[j]]:%2d\n",
                            left, i, j, a, cur[j], occ[a][cur[j]]);
            }
            left = occ[a][cur[j]];
            if(left == S) break;
        }
        if(left == S) break;
        ans += S-occ[p[P-1]][cur[P-1]];
    }

    return ans;
}
