#!/usr/bin/env pypy3

from sys import stdin
from string import ascii_letters, digits

GRID = 6

header = """
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
    label(scale(TS)*("\\texttt{" + var + "}"), center, out ? white : black);
    if (substr(a,0,3) == "in[" || find(a, "[") == -1)
        label(scale(TS)*("\\texttt{" + a + "}"), center+txtpoints[0], black);
    if (substr(b,0,3) == "in[" || find(b, "[") == -1)
        label(scale(TS)*("\\texttt{" + b + "}"), center+txtpoints[1], black);
}

"""
print(header)

alpha  = set(ascii_letters + digits + '_')
arrset = set(["in", "out"])

comp   = []
level  = []
xpos   = []
cpos   = {}
clev   = [0 for _ in range(100)]
lmax   = 0

def parsearr(x):
    try:
        int(x)
        return None, None, x
    except:
        pass
    assert x[-1] == ']'
    name, idx = x[:-1].split('[')
    idx = int(idx)
    assert(set(name) <= alpha)
    arrset.add(name)
    return name, idx, x

def validarg(x):
    return x[0] in [None, "in"] or x[-1] in cpos

line = 1
err = 'label("syntactic error in line %s", (0,0), red);'
for row in stdin.readlines():
    try:
        assert row[-1] == '\n'
        var, val = row.split(' = ')
        a, op, b = val[:-1].split()
        assert op in ['+', '-', 'max', 'min']
        var = parsearr(var)
        a   = parsearr(a)
        b   = parsearr(b)
        assert var[0] is not None
        if var[-1] in cpos:
            err = 'label("duplicate component in line %s", (0,0), red);'
            exit(0)
        if var[0] == "in" or not validarg(a) or not validarg(b):
            err = 'label("invalid component in line %s", (0,0), red);'
            exit(0)
        cpos[var[-1]] = len(comp)
        comp.append((var, a, op, b))
        level.append(None)
        xpos.append(None)
    except:
        print(err % line)
        exit(0)
    line += 1

def levelize(c):
    global lmax
    if c[0] in [None, "in"]:
        return 0
    i = cpos[c[-1]]
    if level[i] is not None:
        return level[i]
    var, a, op, b = comp[i]
    level[i] = max(levelize(a), levelize(b)) + 1
    xpos[i] = clev[level[i]]
    clev[level[i]] += 1
    if level[i] >= 100:
        print('label("configuration exceeds depth limit", (0,0), red);')
        exit(0)
    lmax = max(lmax, level[i])
    return level[i]

for c in comp:
    levelize(c[0])

cmax = max(clev)
dlev   = [GRID*(cmax+1)/(clev[i]+1) for i in range(100)]

center = []
for i in range(len(comp)):
    center.append((dlev[level[i]]*(xpos[i]+1), -level[i]*GRID))

print("""
for (int i=1; i<=%d; ++i) {
    real y = -i * %d;
    label(scale(TS)*("t=" + string(i)), (-1, y));
    draw((0,y) -- (%d,y), black+dotted);
}
""" % (lmax, GRID, GRID*(cmax+1)))

for i in range(len(comp)):
    var, a, op, b = comp[i]
    if a[0] not in [None, "in"]:
        print('connect(%s+endpoints[0], %s+endpoints[2]);' % (center[i], center[cpos[a[-1]]]))
    if b[0] not in [None, "in"]:
        print('connect(%s+endpoints[1], %s+endpoints[2]);' % (center[i], center[cpos[b[-1]]]))
for i in range(len(comp)):
    var, a, op, b = comp[i]
    print(('drawcomp(%s, "%s", "%s", "%s", "%s");' % (center[i], var[-1], a[-1], op, b[-1])).replace('_', '\_'))
