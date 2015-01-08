unitsize(.7cm);

import trembling;
tremble tr = tremble(angle=10, frequency=.3, random=20);

void node(pair pos, pen bord = black, string content, pen inner = gray(.95), pen lbl = black) {
    path border = circle(pos, .5);
    fill(border, inner);
    draw(border, bord);

    label(content, pos, lbl);
}

pair W = (0,1);
pair L = (7,5);

pair A = (2.5,2.5);
pair B = (4.5,3.5);

draw(tr.deform(W{(1,0)} .. {(0,1)}B), dashed + gray(.3));
draw(tr.deform(A{(0,1)} .. {(1,0)}L), dashed + gray(.3));

draw(A -- B);

node(W, content = "$W$");
node(L, content = "$L$");
node(A, content = "$u$");
node(B, content = "$v$");
