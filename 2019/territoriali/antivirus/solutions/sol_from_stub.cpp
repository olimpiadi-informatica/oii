#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

bool compare(const char* s1, const char* s2, int c) {
    while (c--) {
        if (*s1 != *s2) return false;
        s1++;
        s2++;
    }
    return true;
}

void solve(int t) {
    int N1, N2, N3, N4;
    cin >> N1 >> N2 >> N3 >> N4;

    int M;
    cin >> M;

    string F1, F2, F3, F4;
    cin >> F1 >> F2 >> F3 >> F4;

    // scrivi in queste variabili la risposta
    int p1, p2, p3, p4;

    for (int i = 0; i <= N1-M; i++) {
        p1 = i;
        p2 = p3 = p4 = -1;
        for (int j = 0; j <= N2-M && p2 < 0; j++)
            if (compare(F1.c_str()+i, F2.c_str()+j, M))
                p2 = j;
        for (int j = 0; j <= N3-M && p3 < 0; j++)
            if (compare(F1.c_str()+i, F3.c_str()+j, M))
                p3 = j;
        for (int j = 0; j <= N4-M && p4 < 0; j++)
            if (compare(F1.c_str()+i, F4.c_str()+j, M))
                p4 = j;
        if (p2 != -1 && p3 != -1 && p4 != -1)
            break;
    }

    cout << "Case #" << t << ": " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;
}

int main() {
    // le seguenti due righe possono essere utili per leggere e scrivere da file

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }
}
