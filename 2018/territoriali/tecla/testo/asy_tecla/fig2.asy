import "grafi.asy" as grafi;
import roundedpath;


pen pa = palegray;
pen p1 = black+1;
pen p2 = heavyred+1;


// posizioni dei vertici
pair[] P = {(0,2), (2,2), (2,0), (0,0), (-1.5,-1), (-3,0), (-3,2), (-1.5,3)};

// colori dei vertici
pen[]  colV = {pa};

// archi del grafo
int[][] E = {{0,5}, {5,6}, {6,3}, {3,4}, {4,2}, {2,3}, {3,0}, {0,1}, {1,2}, {4,5}, {6,7}, {7,0}};

// orientamento degli archi
bool[] orE = {true, true, true, true, true, true, true, false};

// colori degli archi
pen[]  colE = {p2, p2, p2, p2, p2, p2, p2, p1};


grafi.main(P, colV, E, colE, orE);
