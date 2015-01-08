import roundedpath;
unitsize(.7cm);

pair[] nodes = {(0,0), (-2,1.4), (2.8, 0), (2.8,2.8), (0, 2.8)};

// corner è il vertice in basso a sinistra
path rect(pair corner, real w, real h) {
    return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void node(pair pos, pen bord = black, string content, pen inner = gray(.95), pen lbl = black) {
    path border = circle(pos, .4);
    fill(border, inner);
    draw(border, bord);

    label(content, pos, lbl);
}

void badge(pair pos, pen bk = gray(.95), pen lbl = gray(.4), string content, real badge_w = .4, real badge_h = .4) {
    path box = roundedpath(rect(pos - (badge_w, badge_h) / 2, badge_w, badge_h), 0.08);
    fill(box, bk);
    // draw(box);

    label(scale(.85) * content, pos, lbl);
}

void edge(pair a, pair b, int wgt, bool active = false) {
    if (active) {
        draw(a -- b, gray(.8) + linewidth(8));
        draw(a -- b, black + linewidth(1));

        if (a.y == b.y) { // orizzontale
            badge((a + b)/ 2, gray(.8), (string)wgt, .6, .4);
        } else { // verticale
            badge((a + b)/ 2, gray(.8), (string)wgt, .4, .6);
        }
    } else {
        draw(a -- b, gray(.4));

        if (a.y == b.y) { // orizzontale
            badge((a + b)/ 2, (string)wgt, .6, .4);
        } else { // verticale
            badge((a + b)/ 2, (string)wgt, .4, .6);
        }
    }
}

edge(nodes[0], nodes[1], 3);
edge(nodes[1], nodes[4], 5);
edge(nodes[4], nodes[3], 3);
edge(nodes[3], nodes[0], 2);
edge(nodes[0], nodes[2], 4);
edge(nodes[2], nodes[3], 1);

string dist[] = {"$\infty$", "$0$", "$\infty$", "$\infty$", "$\infty$"};
string velo[] = {"$\infty$", "$\infty$", "$\infty$", "$\infty$", "$\infty$"};

pair s = (-.3,-1.6);
for (int i = 0; i < nodes.length; ++i) {
    label(scale(.75) * dist[i], s + (i * .7,0) + (.35,.3));
    path r = rect(s + (i * .7,0), .7, .6);
    fill(r, gray(.95));
    draw(r, gray(.5));
}
draw(rect(s, nodes.length * .7, .6));
label(scale(.75) * "\texttt{distanza}", s + (0,.3), align=LeftSide);

s = (-.3,-2.4);
for (int i = 0; i < nodes.length; ++i) {
    label(scale(.5) * (string)(i+1), s + (i * .7,0) + (.35,1.6), gray(.3));
    label(scale(.75) * velo[i], s + (i * .7,0) + (.35,.3));
    path r = rect(s + (i * .7,0), .7, .6);
    fill(r, gray(.95));
    draw(r, gray(.5));
}
draw(rect(s, nodes.length * .7, .6));
label(scale(.75) * "\texttt{velocit\`a}", s + (0,.3), align=LeftSide);

// Nodi
int William = 1, Luca = 3;
int active[] = {0,0,0,0,0,0,0,0};
for (int i = 0; i < nodes.length; ++i) {
    pen bord = gray(.4);
    if (active[i] == 1)
        bord = black + linewidth(1);

    if (i == William)
        node(nodes[i], bord = black, "$" + (string)(i+1) + "$", inner = rgb(200/256, 200/256, 256/256), lbl = black);
    else if (i == Luca)
        node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", inner = rgb(256/256, 200/256, 200/256), lbl = gray(.4));
    else
        node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", lbl = gray(.4));
}
