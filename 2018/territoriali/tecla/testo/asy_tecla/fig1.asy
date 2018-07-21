import "grafi.asy" as grafi;
import roundedpath;


pen pa = palegray;
pen p1 = black+1;
pen p2 = heavyred+1;


// posizioni dei vertici
pair[] P = {(2,2), (0,0), (4, 0)};

// colori dei vertici
pen[]  colV = {pa};

// archi del grafo
int[][] E = {{1, 0},{0, 2},{2, 1}};

// orientamento degli archi
bool[] orE = {true};

// colori degli archi
pen[]  colE = {p2};


grafi.main(P, colV, E, colE, orE);
