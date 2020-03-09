import "grafi.asy" as grafi;
import roundedpath;

pen pa = palegray;
pen p1 = black+1;
pen p2 = red+1;

// posizioni dei vertici
pair[] P = {(3,4), (1,2), (3,2), (5,2), (0,0), (2,0), (4,0), (6,0)};

// colori dei vertici
pen[]  colV = {pa};

// archi del grafo
int[][] E = {{1,0}, {2,0}, {3,0}, {4,1}, {5,1}, {6,3}, {7,3}};

// orientamento degli archi
bool[] orE = {true};

{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"2", "3", "1", "5", "0", "6", "4", "7"};
    int[] A =      { 7,   5,   4,   0,   6,   2,   1,   3 };
    pen[]  colE = {p1, p1, p1, p2, p1, p1, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Promozione di 0 declassando 3.", (3, -1.5));
    add(p.fit(), (0,10), N);
}
{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"2", "0", "1", "5", "3", "6", "4", "7"};
    int[] A =      { 7,   6,   4,   0,   5,   2,   1,   3 };
    pen[]  colE = {p1, p1, p1, p1, p1, p1, p2};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Promozione di 7 declassando 5.", (3, -1.5));
    add(p.fit(), (0,5), N);
}
{
    picture p;
    p.unitsize(20, 20);
    string[] lbl = {"2", "0", "1", "7", "3", "6", "4", "5"};
    int[] A =      { 7,   6,   4,   3,   5,   2,   1,   0 };
    pen[]  colE = {p1, p1, p1, p1, p1, p1, p1};
    grafi.main(p, P, colV, E, colE, orE, A, lbl);
    label(p, "Situazione finale.", (3, -1.5));
    add(p.fit(), (0,0), N);
}
