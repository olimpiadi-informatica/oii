#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

#ifdef EVAL
ifstream lettura("input.txt");
ofstream scrittura("output.txt");
#else
istream &lettura(cin);
ostream &scrittura(cout);
#endif

const int MAXN = 1000000; // percorso
const int MAXM = 1000000; // fontane

int N, M;

int fontane[MAXM+2];

int main () {
    lettura >> N >> M;

    int x1, x2, y1, y2;
    lettura >> x1 >> y1 >> x2 >> y2;

    const int H = 0;
    const int V = 1;

    int direction = H;
    int common = y1;
    fontane[0] = x1;
    fontane[1] = x2;
    if (x1 == x2) {
        direction = V;
        common = x1;
        fontane[0] = y1;
        fontane[1] = y2;
    }

    int j = 2;
    for (int i = 0; i < M; i += 1) {
        int x, y;
        lettura >> x >> y;
        if (direction == H) {
            if (y == common && min(x1, x2) <= x && x <= max(x1, x2)) {
                fontane[j++] = x;
            }
        } else {
            if (x == common && min(y1, y2) <= y && y <= max(y1, y2)) {
                fontane[j++] = y;
            }
        }
    }

    sort(fontane, fontane+j);
    
    int primo = fontane[0];
    int secondo = fontane[1];

    int massimo = fontane[1] - fontane[0];
    for (int i = 2; i < j; i += 1) {
        if (fontane[i] - fontane[i-1] > massimo) {
            massimo = fontane[i] - fontane[i-1];
            primo = fontane[i-1];
            secondo = fontane[i];
        }
    }

    scrittura << max(0, massimo - 100) << endl;
}
