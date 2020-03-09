
unitsize(0.5cm);
settings.tex = "pdflatex";

real TS = 1.4;
real LT = 3;
pair[] endpoints = {(-1.5, 2.5), (1.5, 2.5), (0, -2.5)};
pair[] txtpoints = {(-1.5, 3), (1.5, 3), (0, -3)};
path[] shapes = {
    (-2,1) -- (-1,1) -- (-1,2) -- (1,2) -- (1,1) -- (2,1) -- (2,-1) -- (1,-1) -- (1,-2) -- (-1,-2) -- (-1,-1) -- (-2,-1) -- cycle,
    (-2,1) -- (2,1) -- (2,-1) -- (-2,-1) -- cycle,
    (-2,1.5) -- (-0.5,1.5) -- (0,1) -- (0.5,1.5) -- (2,1.5) -- (0,-2) -- cycle
};

void connect(pair a, pair b) {
    draw(a{N} .. tension 1.5 .. {N}b, black+LT+squarecap);
    draw(a{N} .. tension 1.5 .. {N}b, mediumgray+LT/2+squarecap);
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


path rect(pair p, pair q) {
    return p -- (p.x,q.y) -- q -- (q.x,p.y) -- cycle;
}

fill(rect((0,-4), (48,-12)), palegreen);
fill(rect((0,-12), (48,-20)), paleblue);
fill(rect((0,-20), (48,-36)), palered);
label(scale(2)*("t=1"), (2, -8));
label(scale(2)*("t=2"), (2, -16));
label(scale(2)*("t=3"), (2, -28));

connect((8.0, -16)+endpoints[1], (16.0, -8)+endpoints[2]);
connect((16.0, -16)+endpoints[0], (16.0, -8)+endpoints[2]);
connect((16.0, -16)+endpoints[1], (24.0, -8)+endpoints[2]);
connect((32.0, -16)+endpoints[0], (32.0, -8)+endpoints[2]);
connect((40.0, -16)+endpoints[0], (32.0, -8)+endpoints[2]);
connect((40.0, -16)+endpoints[1], (40.0, -8)+endpoints[2]);
connect((8.0, -24)+endpoints[1], (16.0, -16)+endpoints[2]);
connect((16.0, -24)+endpoints[0], (16.0, -16)+endpoints[2]);
connect((16.0, -24)+endpoints[1], (32.0, -8)+endpoints[2]);
connect((28.0, -24)+endpoints[0], (16.0, -16)+endpoints[2]);
connect((28.0, -24)+endpoints[1], (32.0, -16)+endpoints[2]);
connect((30.0, -32)+endpoints[0], (16.0, -16)+endpoints[2]);
connect((30.0, -32)+endpoints[1], (40.0, -16)+endpoints[2]);
drawcomp((8.0, -8), "out[0]", "0", "+", "in[0]");
drawcomp((16.0, -8), "out[1]", "in[0]", "+", "in[1]");
drawcomp((24.0, -8), "t1[0]", "in[2]", "+", "in[3]");
drawcomp((32.0, -8), "t1[1]", "in[4]", "+", "in[5]");
drawcomp((40.0, -8), "t1[2]", "in[6]", "+", "in[7]");
drawcomp((8.0, -16), "out[2]", "in[2]", "+", "out[1]");
drawcomp((16.0, -16), "out[3]", "out[1]", "+", "t1[0]");
drawcomp((32.0, -16), "t2[0]", "t1[1]", "+", "in[7]");
drawcomp((40.0, -16), "t2[1]", "t1[1]", "+", "t1[2]");
drawcomp((8.0, -24), "out[4]", "in[4]", "+", "out[3]");
drawcomp((16.0, -24), "out[5]", "out[3]", "+", "t1[1]");
drawcomp((28.0, -24), "out[6]", "out[3]", "+", "t2[0]");
drawcomp((30.0, -32), "out[7]", "out[3]", "+", "t2[1]");
