#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void mangia(int* cattivo, int& lx, int& rx, int& buoni, int& ans) {
    while (lx <= rx && !cattivo[lx]) {
        lx ++;
        ans ++;
        buoni --;
    }
    while (rx >= lx && !cattivo[rx]) {
        rx --;
        ans ++;
        buoni --;
    }
}

pair<int,int> ammucchiaCattiveria(int* cattivo, int start, int direzione) {
    int i, totale = 0;
    for (i=start; cattivo[i]; direzione ? i++ : i--)
        totale += cattivo[i];
    return pair<int,int>(totale, i);
}

int solve(int N, int K, int cattivo[]) {
    srand(8753);
    int buoni = 0;
    for (int i=0; i<N; i++) buoni += !cattivo[i];
    int lx = 0, rx = N - 1, sopportato = 0, ans = 0;
    while (buoni > 0 && sopportato <= K) {
        mangia(cattivo, lx, rx, buoni, ans);
        pair<int,int> al = ammucchiaCattiveria(cattivo, lx, 1);
        pair<int,int> ar = ammucchiaCattiveria(cattivo, rx, 0);
        if (al.first < ar.first || (al.first == ar.first && rand() % 2)) {
            sopportato += al.first;
            lx = al.second;
        } else {
            sopportato += ar.first;
            rx = ar.second;
        }
    }
    return ans;
}
