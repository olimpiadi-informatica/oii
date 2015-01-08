import roundedpath;
unitsize(.7cm);

pair[] nodes = {(0,0), (-2,1.4), (2.8, 0), (2.8,2.8), (0, 2.8)};

// corner è il vertice in basso a sinistra
path rect(pair corner, real w, real h) {
    return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void node(pair pos, pen bord = black, string content, pen inner = white, pen lbl = black) {
    path border = circle(pos, .4);
    fill(border, inner);
    draw(border, bord);

    label(content, pos, lbl);
}

void badge(pair pos, pen bk = gray(.95), pen lbl = black, string content, real badge_w = .4, real badge_h = .4, int active) {
    path box = roundedpath(rect(pos - (badge_w, badge_h) / 2, badge_w, badge_h), 0.08);
    fill(box, bk);
    // draw(box);

    if (active == 0)
        lbl = gray(.4);

    label(scale(.85) * content, pos, lbl);
}

void edge(pair a, pair b, int wgt, int active = 0) {
    if (active == 1) {
        draw(a -- b, gray(.8) + linewidth(8));
        draw(a -- b, black + linewidth(1));

        if (a.y == b.y) { // orizzontale
            badge((a + b)/ 2, gray(.8), (string)wgt, .6, .4, active);
        } else { // verticale
            badge((a + b)/ 2, gray(.8), (string)wgt, .4, .6, active);
        }
    } else {
        draw(a -- b, gray(.4));

        if (a.y == b.y) { // orizzontale
            badge((a + b)/ 2, (string)wgt, .6, .4, active);
        } else { // verticale
            badge((a + b)/ 2, (string)wgt, .4, .6, active);
        }
    }

    if (b.x != a.x && b.y != a.y) {
        real kx = (b.x - a.x) / length(a - b);
        real ky = (b.y - a.y) / length(a - b);
        draw(shift(.32 * (-kx,ky)) * (a -- b), gray(.95) + linewidth(4));
        draw(shift(.32 * (+kx,-ky)) * (a -- b), gray(.95) + linewidth(4));
    }
}

edge(nodes[0], nodes[1], 3);
edge(nodes[1], nodes[4], 5, 1);
edge(nodes[3], nodes[0], 2);
edge(nodes[0], nodes[2], 4);
edge(nodes[2], nodes[3], 1);
edge(nodes[4], nodes[3], 3);


string dist[] = {"$\infty$", "$0$", "$\infty$", "$\infty$", "$1$"};
string velo[] = {"$\infty$", "$\infty$", "$\infty$", "$\infty$", "$5$"};
pen pens[] = {gray(.4), black, gray(.4), gray(.4), red};

pair s = (-.3,-1.6);
for (int i = 0; i < nodes.length; ++i) {
    label(scale(.75) * dist[i], s + (i * .7,0) + (.35,.3), pens[i]);
    path r = rect(s + (i * .7,0), .7, .6);
    fill(r, gray(.95));
    draw(r, gray(.5));
}
draw(rect(s, nodes.length * .7, .6));
label(scale(.75) * "\texttt{distanza}", s + (0,.3), align=LeftSide);

s = (-.3,-2.4);
for (int i = 0; i < nodes.length; ++i) {
    label(scale(.5) * (string)(i+1), s + (i * .7,0) + (.35,1.6), gray(.3));
    label(scale(.75) * velo[i], s + (i * .7,0) + (.35,.3), pens[i]);
    path r = rect(s + (i * .7,0), .7, .6);
    fill(r, gray(.95));
    draw(r, gray(.5));
}
draw(rect(s, nodes.length * .7, .6));
label(scale(.75) * "\texttt{velocit\`a}", s + (0,.3), align=LeftSide);

draw(arc(nodes[1], length(nodes[4] - nodes[1]), -52, 52), gray(.3) + dashed);

// Nodi
int William = 1, Luca = 3;
int active[] = {0,1,0,0,2};
for (int i = 0; i < nodes.length; ++i) {

    if (i == William && (active[i] == 0 || active[i] == 3))
        node(nodes[i], bord = gray(.4), "$" + (string)(i+1) + "$", inner = rgb(200/256, 200/256, 256/256), lbl = gray(.4));
    else if (i == Luca && (active[i] == 0 || active[i] == 3))
        node(nodes[i], bord = gray(.4), "$" + (string)(i+1) + "$", inner = rgb(256/256, 200/256, 200/256), lbl = gray(.4));
    else if (active[i] == 1)
        node(nodes[i], bord = black + linewidth(.8), "$" + (string)(i+1) + "$", inner = gray(.4), lbl = white);
    else if (active[i] == 2)
        node(nodes[i], bord = black + linewidth(.8), "$" + (string)(i+1) + "$", inner = white, lbl = black);
    else if (active[i] == 3)
        node(nodes[i], bord = black, "$" + (string)(i+1) + "$", inner = gray(.95), lbl = gray(.4));
    else
        node(nodes[i], bord = gray(.4), "$" + (string)(i+1) + "$", inner = gray(.95), lbl = gray(.4));
}
