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

struct fontana {
    int x;
    int y;
    int cls; // la "classe" a cui appartiene la fontana, cioe', se la
             // fontana appartiene a quelle ordinate per x (i.e. x_f),
             // indica l'indice della colonna a cui appartiene, dove
             // una colonna e' una ascissa sulla quale c'e' una fontana
    int ord; // l'indice della fontana all'interno della classe
};

fontana x_f[MAXM]; // fontane ordinate per (x, y)
fontana y_f[MAXM]; // fontane ordinate per (y, x)

int x_rmq_s[MAXM]; // la dimensione delle classi delle x (colonne)
int y_rmq_s[MAXM]; // la dimensione delle classi delle y (righe)

int* x_rmq[MAXM]; // una struttura RMQ sulle classi delle x
int* y_rmq[MAXM]; // una struttura RMQ sulle classi delle y

// la struttura RMQ x_rmq[i] e' un array che rappresenta una matrice
// ceil(log2(x_rmq_s[i])) * x_rmq_s[i], in cui x_rmq[i][j][k] e' la
// massima distanza tra due fontane con indice in [k, k+2^j] nella
// classe i.

// Usiamo il tipo fontana perche' dopo dobbiamo comparare gli snodi
// con le fontane, ma non useremo mai i campi cls e ord.
fontana snodi[MAXN+1];

bool lt_x (const fontana& a, const fontana& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool lt_y (const fontana& a, const fontana& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

void leggi () {
    lettura >> N >> M;

    for (int i = 0; i <= N; i += 1) {
        lettura >> snodi[i].x >> snodi[i].y;
    }

    for (int i = 0; i < M; i += 1) {
        int x, y;
        lettura >> x >> y;
        x_f[i].x = y_f[i].x = x;
        x_f[i].y = y_f[i].y = y;
    }

    sort(x_f, x_f + M, lt_x);
    sort(y_f, y_f + M, lt_y);
}

void prepara () {
    // Assegna classi e indici
//    cout << "Ordini X" << endl;
    int prev_x = -2000000000;
    int cls_x = -1;
    int ord_x = 0;
    for (int i = 0; i < M; i += 1) {
        if (x_f[i].x != prev_x) {
            if (cls_x >= 0) {
                x_rmq_s[cls_x] = ord_x;
            }
            cls_x += 1;
            ord_x = 0;
        }
        x_f[i].cls = cls_x;
        x_f[i].ord = ord_x;
//        cout << "fontana " << x_f[i].x << ", " << x_f[i].y << " e' classe " << cls_x << " ordine " << ord_x << endl;
        ord_x += 1;
        prev_x = x_f[i].x;
    }
    x_rmq_s[cls_x] = ord_x;

//    cout << "Ordini Y" << endl;
    int prev_y = -2000000000;
    int cls_y = -1;
    int ord_y = 0;
    for (int i = 0; i < M; i += 1) {
        if (y_f[i].y != prev_y) {
            if (cls_y >= 0) {
                y_rmq_s[cls_y] = ord_y;
            }
            cls_y += 1;
            ord_y = 0;
        }
        y_f[i].cls = cls_y;
        y_f[i].ord = ord_y;
//        cout << "fontana " << y_f[i].x << ", " << y_f[i].y << " e' classe " << cls_y << " ordine " << ord_y << endl;
        ord_y += 1;
        prev_y = y_f[i].y;
    }
    y_rmq_s[cls_y] = ord_y;

    // Create the RMQ structure
    for (int i = 0; i < M;) {
        int cls = x_f[i].cls;
        int len = x_rmq_s[cls];
        int hei = (int) ceil(log2(len)) + 1;
        x_rmq[cls] = new int[len*hei];

//        cout << "La classe " << cls << " ha len " << len << " hei " << hei << endl;

        // Inizializza a zero la prima riga
        for (int j = 0; j < len; j += 1) {
            x_rmq[cls][j] = 0;
        }

        for (int k = 1; k < hei; k += 1) {
            int step = 1 << k;
            for (int j = 0; j < len; j += 1) {
                int max_sides = max(x_rmq[cls][(k-1)*len + j],
                                    x_rmq[cls][(k-1)*len + j + step/2]);
                int max_between = x_f[i+j+step/2].y - x_f[i+j+step/2-1].y;
                x_rmq[cls][k*len + j] = max(max_sides, max_between);
            }
        }

        i += len;
    }

    for (int i = 0; i < M;) {
        int cls = y_f[i].cls;
        int len = y_rmq_s[cls];
        int hei = (int) ceil(log2(len)) + 1;
        y_rmq[cls] = new int[len*hei];

//        cout << "La classe " << cls << " ha len " << len << " hei " << hei << endl;

        // Inizializza a zero la prima riga
        for (int j = 0; j < len; j += 1) {
            y_rmq[cls][j] = 0;
        }

        for (int k = 1; k < hei; k += 1) {
            int step = 1 << k;
            for (int j = 0; j < len; j += 1) {
                int max_sides = max(y_rmq[cls][(k-1)*len + j],
                                    y_rmq[cls][(k-1)*len + j + step/2]);
                int max_between = y_f[i+j+step/2].x - y_f[i+j+step/2-1].x;
                y_rmq[cls][k*len + j] = max(max_sides, max_between);
            }
        }

        i += len;
    }
//    cout << "DONE" << endl;
}

void elabora () {
    int prev_len = 0;

    int massimo = 0;

    for (int i = 1; i <= N; i += 1) {
//        cout << snodi[i-1].x << "," << snodi[i-1].y << " -> " << snodi[i].x << "," << snodi[i].y << endl;
        if (snodi[i-1].x == snodi[i].x) { // sulla stessa colonna
            // Trova la prima fontana nel percorso e quella dopo l'ultima.
            fontana *prima, *ultima;
            if (snodi[i-1].y < snodi[i].y) { // il percorso va verso y crescente
                prima = lower_bound(x_f, x_f + M, snodi[i-1], lt_x);
                ultima = upper_bound(x_f, x_f + M, snodi[i], lt_x);
            } else { // il percorso va verso y decrescente
                prima = lower_bound(x_f, x_f + M, snodi[i], lt_x);
                ultima = upper_bound(x_f, x_f + M, snodi[i-1], lt_x);
            }

            // Ci sono fontane su questo segmento?
            if (prima == ultima) {
                // No
//                cout << "Nessuna" << endl;
                prev_len += abs(snodi[i-1].y - snodi[i].y);
            } else {
                // Si'
//                cout << "Qualcuna: " << (ultima - prima) << endl;
//                cout << prima->x << " " << prima->y << endl;
//                cout << (ultima-1)->x << " " << (ultima-1)->y << endl;
//                for (fontana* f = prima; f < ultima; f += 1) {
//                    cout << f->x << " " << f->y << endl;
//                }
                ultima -= 1;

                assert(prima->cls == ultima->cls);
                assert(prima->ord <= ultima->ord);

                // l'esponente della piu' grande potenza di due minore
                // o uguale della differenza di indice tra ultimo e primo
                int k = (int) floor(log2(ultima->ord - prima->ord + 1));
                int step = 1 << k;

                // Range Minimum Query
                int cls = prima->cls;
                int ord1 = prima->ord;
                int ord2 = ultima->ord - step + 1;
                int len = x_rmq_s[cls];
//                cout << "classe " << cls << " da " << ord1 << " a " << ord2 << endl;
//                cout << "len " << len << " k " << k << " (step " << step << ")" << endl;
//                cout << "left " << x_rmq[cls][k*len + ord1] << endl;
//                cout << "right " << x_rmq[cls][k*len + ord2] << endl;
                massimo = max(massimo, max(x_rmq[cls][k*len + ord1], x_rmq[cls][k*len + ord2]));

                if (snodi[i-1].y > snodi[i].y) {
                    swap(prima, ultima);
                }

//                cout << "inizio " << prev_len + abs(snodi[i-1].y - prima->y) << endl;
//                cout << "fine " << abs(snodi[i].y - ultima->y) << endl;
                massimo = max(massimo, prev_len + abs(snodi[i-1].y - prima->y));
                prev_len = abs(snodi[i].y - ultima->y);
            }
        } else { // snodi[i-1].y == snodi[i].y - sulla stessa riga
            // Trova la prima fontana nel percorso e quella dopo l'ultima.
            fontana *prima, *ultima;
            if (snodi[i-1].x < snodi[i].x) { // il percorso va verso y crescente
                prima = lower_bound(y_f, y_f + M, snodi[i-1], lt_y);
                ultima = upper_bound(y_f, y_f + M, snodi[i], lt_y);
            } else { // il percorso va verso y decrescente
                prima = lower_bound(y_f, y_f + M, snodi[i], lt_y);
                ultima = upper_bound(y_f, y_f + M, snodi[i-1], lt_y);
            }

            // Ci sono fontane su questo segmento?
            if (prima == ultima) {
                // No
//                cout << "Nessuna" << endl;
                prev_len += abs(snodi[i-1].x - snodi[i].x);
            } else {
                // Si'
//                cout << "Qualcuna: " << (ultima - prima) << endl;
//                cout << prima->x << " " << prima->y << endl;
//                cout << (ultima-1)->x << " " << (ultima-1)->y << endl;
//                for (fontana* f = prima; f < ultima; f += 1) {
//                    cout << f->x << " " << f->y << endl;
//                }
                ultima -= 1;

                assert(prima->cls == ultima->cls);
                assert(prima->ord <= ultima->ord);

                // l'esponente della piu' grande potenza di due minore
                // o uguale alla differenza di indice tra ultimo e primo
                int k = (int) floor(log2(ultima->ord - prima->ord + 1));
                int step = 1 << k;

                // Range Minimum Query
                int cls = prima->cls;
                int ord1 = prima->ord;
                int ord2 = ultima->ord - step + 1;
                int len = y_rmq_s[cls];
//                cout << "classe " << cls << " da " << ord1 << " a " << ord2 << endl;
//                cout << "len " << len << " k " << k << " (step " << step << ")" << endl;
                massimo = max(massimo, max(y_rmq[cls][k*len + ord1], y_rmq[cls][k*len + ord2]));

                if (snodi[i-1].x > snodi[i].x) {
                    swap(prima, ultima);
                }

                massimo = max(massimo, prev_len + abs(snodi[i-1].x - prima->x));
                prev_len = abs(snodi[i].x - ultima->x);
            }
        }
//        cout << i-1 << " " << massimo << endl;
//        cout << endl;
    }
//    cout << prev_len << endl;
    massimo = max(massimo, prev_len);
    scrittura << max(0, massimo - 100) << endl;
}

int main () {
    leggi();
    prepara();
    elabora();
}
