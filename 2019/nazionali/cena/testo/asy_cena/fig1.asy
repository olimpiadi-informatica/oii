unitsize(1cm);
settings.tex = "pdflatex";
include cloud;

//string s = "0021010121";
//string p = "x0x1xx0x2x";

string s = "001201";
string p = "x0x20x";

pen[][] HAIR_COLORS = {
    {rgb("831D12"), rgb("932D22")},
    {rgb("533D32"), rgb("6A4E42")},
    {rgb("faf0be"), rgb("fbf3be")},
    {rgb("c65c2c"), rgb("ac5639")}
};
pen[] SKIN_COLORS = {
    rgb("ffe0bd"),
    rgb("6f4f1d"),
    rgb("ffceb4"),
    rgb("3f2f0d")
};

path rect(pair p, pair q) {
    return p -- (p.x, q.y) -- q -- (q.x, p.y) -- cycle;
}

// ---------------------------------------------------------------------------

int S = length(s);
int P = length(p);

real TAB_H = 10;
real TAB_DIAG = 5;
real TAB_Y = 30;
real TAB_PLATE = 12;
real PLATE_W = 10;
real PLATE_H = 6;
real FONT_SIZE = 8;
real HEAD_W = 12;
real HEAD_H = 14;
real EAR_W = 2;
real EAR_H = 3;

pair[] table = {(TAB_DIAG, TAB_Y + TAB_H), (TAB_DIAG + S * TAB_PLATE, TAB_Y + TAB_H),
     (TAB_DIAG + S * TAB_PLATE + TAB_DIAG, TAB_Y), (0, TAB_Y)};
for (pair p : table) {
    fill(shift(p) * rect((-.4,0), (.4,-15)), brown);
}
filldraw(table[0] -- table[1] -- table[2] -- table[3] -- cycle, palecyan, brown + 20);

pen getColor(string c) {
    if (c == "0")
        return palegreen;
    else if (c == "1")
        return palered;
    else if (c == "2")
        return paleblue;
    else
        return palegray;
}

void drawPlate(int i, string c) {
    real x = TAB_DIAG + i * TAB_PLATE + TAB_PLATE / 2;
    real y = TAB_Y + TAB_H / 2;
    pen color = getColor(c);
    filldraw(shift((x,y))*xscale(PLATE_W/2)*yscale(PLATE_H/2)*unitcircle, palegray*1.001);
    filldraw(shift((x,y))*xscale(PLATE_W/2*0.8)*yscale(PLATE_H/2*0.8)*unitcircle, color);
    label(scale(FONT_SIZE)*Label(c, (x,y)));
}

picture chairPic() {
    picture pic;
    draw(pic, (-5, -13) -- (-5, -3), (rgb("533D32")*0.8 + black*0.2) + 20);
    draw(pic, (5, -13) -- (5, -3), (rgb("533D32")*0.8 + black*0.2) + 20);
    filldraw(pic, (-5, -5) -- (-5, -10) -- (5, -10) -- (5, -5) .. (0, -4) .. cycle,
             rgb("6A4E42"), (rgb("533D32")*0.8 + black*0.2) + 20);
    return pic;
}
picture chair = chairPic();

void drawChair(int i) {
    real x = TAB_DIAG + i * TAB_PLATE + TAB_PLATE / 2;
    real y = 23;
    add(shift((x,y))*chair);
}

void drawHead(int i, string c, pen[] colors, pen skin_color, int k, bool standing) {
    real x = TAB_DIAG + i * TAB_PLATE + TAB_PLATE / 2;
    real y = 24;

    if (standing) {
        x = TAB_DIAG + (S + 2 + k) * TAB_PLATE;
    }

    // head
    filldraw(shift((x-HEAD_W/2,y))*xscale(EAR_W/2)*yscale(EAR_H/2)*unitcircle, skin_color);
    filldraw(shift((x+HEAD_W/2,y))*xscale(EAR_W/2)*yscale(EAR_H/2)*unitcircle, skin_color);
    filldraw(shift((x,y))*xscale(HEAD_W/2)*yscale(HEAD_H/2)*unitcircle, skin_color);
    // hairs
    real w = HEAD_W;
    real h = HEAD_H;
    real r = 9;
    real cy = 6;
    real h_y = 1;
    real h_x = 0.3;
    real color_error = 0.1;
    for (int k = 0; k < 5000; ++k) {
        real X = (unitrand()-0.5) * w;
        real Y = (unitrand() * 1.3 - 0.3) * h / 2;
        pen color = colors[k % colors.length];
        real R2 = X**2+(h/2+cy-Y)**2;
        if (R2 <= (w/2+r)**2 && X**2/(w/2)**2+Y**2/(h/2)**2 <= 1) {
            // skip hairs near the border
            if (unitrand() < 1-((w/2+r)**2 - R2)**0.5/5)
                continue;
            draw((x+X, y+Y) ..
                 (x+X+(unitrand()-0.5)*h_x*2, y+Y+h_y/2) ..
                 (x+X+(unitrand()-0.5)*h_x*2, y+Y+h_y),
                 linewidth(2)+(color*(1+(unitrand()*color_error*2-color_error))));
        }
    }
    if (standing) {
        // cloud
        filldraw(shift((x+2, y+HEAD_H/2))*scale(0.5)*unitcircle, getColor(c));
        filldraw(shift((x+3, y+HEAD_H/2+1))*scale(1)*unitcircle, getColor(c));
        filldraw(cloudpath(shift((x+6, y+HEAD_H/2+4))*scale(3)*unitcircle, 0.5, 3), getColor(c));
        label(scale(FONT_SIZE)*Label(c, (x+6,y+HEAD_H/2+4)));

        label(scale(FONT_SIZE) * ("\texttt{\#" + string(k) + "}"), (x, y - 10));
    }
}

for (int i = 0; i < S; ++i)
    drawPlate(i, substr(s, i, 1));

int k = 0;
for (int i = 0; i < P; ++i) {
    if (substr(p, i, 1) != "x") {
        drawHead(i, substr(p, i, 1), HAIR_COLORS[k], SKIN_COLORS[k], k, false);
        drawHead(i, substr(p, i, 1), HAIR_COLORS[k], SKIN_COLORS[k], k, true);
        ++k;
    }

    drawChair(i);
}

draw((TAB_DIAG + (S + 1.2) * TAB_PLATE, 24) -- (TAB_DIAG + (S - 0.2) * TAB_PLATE, 24), blue+50+squarecap+miterjoin, EndArrow(100));
