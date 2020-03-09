// Soluzione O(SA), dove A è la massima frequenza di un carattere.
// È molto simile alla dinamica naive, che per ogni coppia di suffissi calcola
// il primo punto in cui trovo il suffisso di P come sottosequenza. La
// differenza cruciale è che calcola solo le coppie di suffissi che iniziano con
// lo stesso carattere.
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100010;
const int MAXA = 1001;
int din[MAXS][MAXA]; // din[i][j] is the minimum x such that s[i:x] allows p[y:] to eat
                     // (where y is the j-th occurrence of s[i] in p)
int nn[MAXS][101];   // next position with the given character in s.

long long conta(int S, int s[], int P, int p[]) {
    // char_counter[c] := All the occurrences of c in p.
    vector<vector<int>> char_counter(100, vector<int>(0));
    // char_num[i]: Number of occurrences of p[i] in p before i.
    vector<int> char_num(P);
    for (int i = 0; i < P; i++) {
        int c = p[i];
        char_num[i] = char_counter[c].size();
        char_counter[c].push_back(i);
    }
    for (int c = 0; c < 100; c++) nn[S - 1][c] = S;
    for (int i = S - 2; i >= 0; i--) {
        for (int c = 0; c < 100; c++) {
            nn[i][c] = nn[i + 1][c];
        }
        nn[i][s[i + 1]] = i + 1;
    }
    for (int j = 0; j < MAXA; j++) din[S][j] = S; // nobody can eat with no dishes
    long long res = 0;
    int curr = S;
    for (int i = S - 1; i >= 0; i--) {
        int c = s[i];
        int len = char_counter[c].size();
        for (int j = 0; j < len; j++) {
            int pos = char_counter[c][j] + 1; // next preference to match
            // for din[i][j] we search for the next occurrence of p[pos] and match the rest
            din[i][j] = (pos == P) ? i : din[nn[i][p[pos]]][char_num[pos]];
        }
        if (s[i] == p[0]) curr = din[i][0];
        res += S - curr;
    }
    return res;
}
