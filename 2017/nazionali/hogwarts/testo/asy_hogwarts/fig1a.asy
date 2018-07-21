unitsize(1cm);
import math;
settings.tex = "pdflatex";

pen p0 = white;
pen p1 = palered;

// posizioni dei vertici
pair[] P = {(2,4), (0,2), (4, 2), (2,0)};
// colori dei vertici
pen[]  col = {p1, p0, p0, p0};
// archi del grafo
int[][] E = {{0, 1},{0, 2},{0, 3},{1, 3},{2, 3}};
// angolo dei self-loop
real[] deg;
// archi evidenziati
int[] X = {-1,0,-1,0,-1};

real node_size = .5;
real text_size = 1;

void node(pair pos, string txt = "", pen color = black, pen background = white) {
	path c = circle(pos, node_size);
	fill(c, background);
	draw(c, black+1);
	label(scale(text_size)*txt, pos, color);
}

void edge(pair start, pair end, string txt = "", pen p = black, real deg = 0, bool arrow = true) {
    path l;
    if (start != end) {
        pair d = unit(end-start) * node_size;
        l = (start+d) -- (end-d);
    } else {
        pair center = start+dir(deg)*node_size*sqrt(2);
        if (arrow) l = arc(center, node_size, deg-135, deg+90) -- start+dir(deg+45)*node_size;
        else l = arc(center, node_size, deg-135, deg+135);
    }
    if (arrow) draw(l, p, EndArrow(21*node_size));
    else draw(l, p);
    label(scale(text_size)*txt, l, p);
}

void calcdeg() {
    bool[] hasloop;
    real[][] deglist;
    for (int i=0; i<P.length; ++i) {
        hasloop[i] = false;
        deglist[i] = new real[];
        deg[i] = 0;
    }
    for (int i=0; i<E.length; ++i) {
        if (E[i][0] == E[i][1]) hasloop[E[i][0]] = true;
        else {
            deglist[E[i][0]].push(degrees(P[E[i][1]]-P[E[i][0]]));
            deglist[E[i][1]].push(degrees(P[E[i][0]]-P[E[i][1]]));
        }
    }
    for (int i=0; i<P.length; ++i) if (hasloop[i]) {
        if (deglist[i].length == 0) continue;
        real[] l = sort(deglist[i]);
        l.push(l[0]+360);
        int imax = 0;
        for (int i=1; i<l.length-1; ++i)
            if (l[i+1]-l[i] > l[imax+1]-l[imax]) imax = i;
        deg[i] = (l[imax]+l[imax+1])/2;
    }
}

void ed(int i, string txt = "", pen p = black, bool arrow = true) {
    edge(P[E[i][0]], P[E[i][1]], txt, p, deg[E[i][0]], arrow);
}

for (int i=0; i<P.length; ++i)
    node(P[i], string(i), black, col[i]);
calcdeg();
for (int i=0; i<E.length; ++i) if (X[i]>=0) {
    if (X[i]>0) ed(i, deepred+1);
    else ed(i, false);
}
draw(scale(1.5)*"$t=0$", box, (0,4), black+1);
for (int i=0; i<P.length; ++i) if (col[i] == p1) label(scale(0.1)*graphic("harry.png"), P[i]+(0,1));
