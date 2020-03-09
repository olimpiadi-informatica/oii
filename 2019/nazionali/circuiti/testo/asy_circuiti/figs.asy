
unitsize(0.5cm);
settings.tex = "pdflatex";

real TS = 0.8;
real LT = 3;
pair[] endpoints = {(-1.5, 2.5), (1.5, 2.5), (0, -2.5)};
pair[] txtpoints = {(-1.5, 3), (1.5, 3), (0, -3)};
path[] shapes = {
    (-2,1) -- (-1,1) -- (-1,2) -- (1,2) -- (1,1) -- (2,1) -- (2,-1) -- (1,-1) -- (1,-2) -- (-1,-2) -- (-1,-1) -- (-2,-1) -- cycle,
    (-2,1) -- (2,1) -- (2,-1) -- (-2,-1) -- cycle,
    (-2,1.5) -- (-0.5,1.5) -- (0,1) -- (0.5,1.5) -- (2,1.5) -- (0,-2) -- cycle
};

void connect(pair a, pair b) {
    draw(a {N}..{N} b, black+LT+squarecap);
    draw(a {N}..{N} b, mediumgray+LT/2+squarecap);
}

void drawcomp(pair center, string var, string a, string op, string b) {
    bool out = substr(var,0,4) == "out[";
    int i;
    if (op == "+") i=0;
    if (op == "-") i=1;
    if (op == "max") i=2;
    filldraw(shift(center)*shapes[i], out ? heavygray : lightgray, black+LT);
    real x = op == "+" ? 1 : 1.5;
    real y = op == "max" ? 1.5 : 1;
    pen[] styles = {black+LT, mediumgray+LT/2};
    for (pen p : styles) {
        draw(center+(-x,y) {op == "+" ? NW : N}..{N} center+endpoints[0], p+squarecap);
        draw(center+( x,y) {op == "+" ? NE : N}..{N} center+endpoints[1], p+squarecap);
        draw(center+(0,op == "-" ? -1 : -2)    --    center+endpoints[2], p+squarecap);
    }
    label(scale(TS)*("\texttt{" + var + "}"), center, out ? white : black);
    if (substr(a,0,3) == "in[" || find(a, "[") == -1)
        label(scale(TS)*("\texttt{" + a + "}"), center+txtpoints[0], black);
    if (substr(b,0,3) == "in[" || find(b, "[") == -1)
        label(scale(TS)*("\texttt{" + b + "}"), center+txtpoints[1], black);
}



for (int i=1; i<=4; ++i) {
    real y = -i * 6;
    label(scale(TS)*("t=" + string(i)), (-1, y));
    draw((0,y) -- (24,y), black+dotted);
}

connect((8.0, -12)+endpoints[0], (6.0, -6)+endpoints[2]);
connect((8.0, -12)+endpoints[1], (12.0, -6)+endpoints[2]);
connect((16.0, -12)+endpoints[0], (12.0, -6)+endpoints[2]);
connect((16.0, -12)+endpoints[1], (18.0, -6)+endpoints[2]);
connect((12.0, -18)+endpoints[0], (8.0, -12)+endpoints[2]);
connect((12.0, -18)+endpoints[1], (16.0, -12)+endpoints[2]);
connect((12.0, -24)+endpoints[0], (12.0, -18)+endpoints[2]);
drawcomp((6.0, -6), "add[0]", "in[0]", "+", "in[1]");
drawcomp((12.0, -6), "add[1]", "5", "+", "in[3]");
drawcomp((18.0, -6), "add[2]", "in[3]", "+", "in[4]");
drawcomp((8.0, -12), "add[3]", "add[0]", "+", "add[1]");
drawcomp((16.0, -12), "add[4]", "add[1]", "-", "add[2]");
drawcomp((12.0, -18), "m[7]", "add[3]", "max", "add[4]");
drawcomp((12.0, -24), "out[0]", "m[7]", "+", "in[5]");
