import "grafi.asy" as grafi;
import roundedpath;

pen pa = palegray;
pen p1 = black+1;
pen p2 = red+1;

// posizioni dei vertici
pair[] P = {(4,0), (4,6), (0,2), (6,4), (2,4), (2,2), (4,2)};

// colori dei vertici
pen[]  colV = {pa};

// archi del grafo
int[][] E = {{2, 4}, {5, 4}, {6, 4}, {0, 6}, {4, 1}, {3, 1}};

// orientamento degli archi
bool[] orE = {true};

{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"0", "1", "2", "3", "4", "5", "6"};
    int[] A =      { 6,   0,   4,   2,   1,   3,   5 };
    pen[]  colE = {p1, p1, p2, p2, p2, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Tripla promozione di 0 declassando 6, 4 e 1.", (3, -1.5));
    add(p.fit(), (0,21), N);
}
{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"6", "0", "2", "3", "1", "5", "4"};
    int[] A =      { 5,   6,   4,   2,   0,   3,   1 };
    pen[]  colE = {p1, p1, p2, p2, p1, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Doppia promozione di 6 declassando 4 e 1.", (3, -1.5));
    add(p.fit(), (0,14), N);
}
{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"4", "0", "2", "3", "6", "5", "1"};
    int[] A =      { 1,   6,   4,   2,   5,   3,   0 };
    pen[]  colE = {p1, p1, p1, p2, p1, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Promozione di 4 declassando 1.", (3, -1.5));
    add(p.fit(), (0,7), N);
}
{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"1", "0", "2", "3", "6", "5", "4"};
    int[] A =      { 0,   6,   4,   2,   5,   3,   1 };
    pen[]  colE = {p1, p1, p1, p1, p1, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Situazione finale.", (3, -1.5));
    add(p.fit(), (0,0), N);
}
