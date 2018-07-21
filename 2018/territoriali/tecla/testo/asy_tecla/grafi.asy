unitsize(1cm);
import math;
settings.tex = "pdflatex";



bool orientato = false; // se il grafo è orientato

real node_size = .5; // dimensione nodi
real text_size = 1.; // dimensione label
real max_bend  = .15; // massimo bending per un arco



// angolo dei self-loop e bending degli archi (automatico)
real[] deg, bend;

// disegno un nodo
void node(pair pos, string txt = "", pen color = black, pen background = white) {
	path c = circle(pos, node_size);
	fill(c, background);
	draw(c, black+1);
	label(scale(text_size)*txt, pos, color);
}

// disegno un arco
void edge(pair start, pair end, string txt = "", pen p = black, real deg = 0, real bending = 0, bool arrow = true) {
    path l;
    if (start != end) {
        pair d = unit(end-start) * node_size;
        pair mid = (start+end)/2;
        pair vec = (-d.y, d.x);
        l = (start+d) .. (mid+vec*bending) .. (end-d);
    } else {
        pair center = start+dir(deg)*node_size*sqrt(2);
        if (arrow) l = arc(center, node_size, deg-135, deg+90) -- start+dir(deg+45)*node_size;
        else l = arc(center, node_size, deg-135, deg+135);
    }
    if (arrow) draw(l, p, EndArrow(21*node_size));
    else draw(l, p);
    label(scale(text_size)*txt, l, p);
}

// interfaccia per disegnare un arco che usa parametri ottimali calcolati
void ed(pair[] P, int[][] E, int i, string txt = "", pen p = black, bool arrow = orientato) {
    edge(P[E[i][0]], P[E[i][1]], txt, p, deg[E[i][0]], bend[i], arrow);
}

// riscala angolo in 0..360
real clockify(real x) {
    while (x<0)   x+=360;
    while (x>360) x-=360;
    return x;
}

// calcolo angoli e bending ottimali
void calcdeg(pair[] P, int[][] E) {
    bool[] hasloop, isdouble;
    real[][] deglist;
    for (int i=0; i<P.length; ++i) {
        hasloop[i] = false;
        deglist[i] = new real[];
        deg[i] = 0;
    }
    for (int i=0; i<E.length; ++i) {
        bend[i] = 0;
        if (E[i][0] == E[i][1]) hasloop[E[i][0]] = true;
        else {
            deglist[E[i][0]].push(degrees(P[E[i][1]]-P[E[i][0]]));
            deglist[E[i][1]].push(degrees(P[E[i][0]]-P[E[i][1]]));
        }
        isdouble[i] = false;
        for (int j=0; j<i; ++j) if (E[i][0] == E[j][1] && E[j][0] == E[i][1])
            isdouble[i] = isdouble[j] = true;
    }
    for (int i=0; i<P.length; ++i) {
        if (deglist[i].length == 0) continue;
        if (hasloop[i]) {
            real[] l = sort(deglist[i]);
            l.push(l[0]+360);
            int imax = 0;
            for (int i=1; i<l.length-1; ++i)
                if (l[i+1]-l[i] > l[imax+1]-l[imax]) imax = i;
            deg[i] = (l[imax]+l[imax+1])/2;
            deglist[i].push(clockify(deg[i]-45));
            deglist[i].push(clockify(deg[i]+45));
        }
        deglist[i] = sort(deglist[i]);
        deglist[i].push(deglist[i][0]+360);
        deglist[i].insert(0, deglist[i][deglist[i].length-2]-360);
    }
    for (int i=0; i<E.length; ++i) if (E[i][0] != E[i][1]) {
        real cws, cwe, ccs, cce, dg;
        int k0, k1, start = E[i][0], end = E[i][1];
        dg = degrees(P[E[i][1]]-P[E[i][0]]);
        for (k0=1; deglist[start][k0] < dg; ++k0);
        if (abs(deglist[start][k0-1]-dg) < abs(deglist[start][k0]-dg)) --k0;
        k1 = k0;
        if (isdouble[i]) {
            if (abs(deglist[start][k0+1]-dg) < abs(deglist[start][k0-1]-dg)) ++k1;
            else --k0;
        }
        cws = deglist[start][k1+1]-dg;
        ccs = dg-deglist[start][k0-1];
        dg = degrees(P[E[i][0]]-P[E[i][1]]);
        for (k0=1; deglist[end][k0] < dg; ++k0);
        if (abs(deglist[end][k0-1]-dg) < abs(deglist[end][k0]-dg)) --k0;
        k1 = k0;
        if (isdouble[i]) {
            if (abs(deglist[end][k0+1]-dg) < abs(deglist[end][k0-1]-dg)) ++k1;
            else --k0;
        }
        cwe = dg-deglist[end][k0-1];
        cce = deglist[end][k1+1]-dg;
        real cw = min(cws, cwe);
        real cc = min(ccs, cce);
        if (isdouble[i]) cc = 0;
        bend[i] = (min(cw/90,1)-min(cc/90,1))*max_bend;
    }
}


void main(pair[] P, pen[] colV, int[][] E, pen[] colE, bool[] orE) {
    // calcolo parametri
    for (int i=colV.length; i<P.length; ++i) colV[i] = colV[i-1];
    for (int i=colE.length; i<E.length; ++i) colE[i] = colE[i-1];
    for (int i=orE.length;  i<E.length; ++i) orE[i]  = orE[i-1];
    calcdeg(P, E);
    real ymax = 0;
    for (int i=0; i<P.length; ++i) ymax = max(ymax, P[i].y);

    // disegno nodi e archi
    for (int i=0; i<P.length; ++i)
        node(P[i], string(i), black, colV[i]);
    for (int i=0; i<E.length; ++i)
        ed(P, E, i, colE[i], orE[i]);
}
