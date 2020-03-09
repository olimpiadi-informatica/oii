// Soluzione O(CP), C è il numero di occorrence di p[0] in s.

#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100010;
int nn[MAXS][101];  // next position with the given character in s.
long long conta(int S, int s[], int P, int p[]) {
    for (int c = 0; c < 101; c++) nn[S - 1][c] = S;
    for (int i = S - 2; i >= 0; i--) {
        for (int c = 0; c < 100; c++) {
            nn[i][c] = nn[i + 1][c];
        }
        nn[i][s[i + 1]] = i + 1;
    }
    long long res = 0;
    int curr = S;
    for (int i = S - 1; i >= 0; i--) {
        if (s[i] == p[0]) {
            int it = i;
            for (int j = 1; j < P and it != S; j++) it = nn[it][p[j]];
            curr = it;
        }
        res += S - curr;
    }
    return res;
}
