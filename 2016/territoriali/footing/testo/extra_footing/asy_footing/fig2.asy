unitsize(1cm);

void make_house(pair p, int id, bool act = false) {
	pen bg = gray;
	if (act)
		bg = black;

	real delta = .1;
	fill(shift(p - (.28,.28)) * scale(.56, .45) * unitsquare, white);
	path roof = (
		(p.x - .25 - delta, p.y + .1) --
		(p.x, p.y + .3 + delta) --
		(p.x + .25 + delta, p.y + .1) --
		cycle
	);
	fill(shift(p.x, p.y + .2) * scale(1.2, 1.2) * shift(-p.x, -p.y - .2) * roof, white);

	fill(shift(p - (.25,.25)) * scale(.5, .4) * unitsquare, bg);
	fill(roof, bg);
	label("$" + (string)id + "$", p, white);
}

void draw_edge(path p, int L, pair mod = N, bool act = false) {
	if (!act) {
		draw(p, gray + linewidth(1.2));
		label("$" + (string)L + "$", midpoint(p), mod, gray);
	} else {
		draw(p, gray(.9) + linewidth(5));
		draw(p, black + linewidth(1.2));
		label("$" + (string)L + "$", midpoint(p), mod);	
	}
}

real d = 2;
pair n1 = (d, 0);
pair n2 = (0, d);
pair n3 = -n1;
pair n4 = -n2;
pair n5 = (0, 0);
pair n6= (-d,d);

bool active = true;

draw_edge(n1 -- n2, 1, NE);
draw_edge(n2 -- n3, 2, SE);
draw_edge(n3 -- n4, 7, SW);
draw_edge(n4 -- n1, 2, SE, active);
draw_edge(n5 -- n1, 5, N, active);
draw_edge(n5 -- n2, 6, E);
draw_edge(n5 -- n3, 1, S);
draw_edge(n5 -- n4, 2, E, active);
draw_edge(n2 -- n6, 4, N);
draw_edge(n3 -- n6, 3, E);

make_house(n1, 1, active);
make_house(n2, 2);
make_house(n3, 3);
make_house(n4, 4, active);
make_house(n5, 5, active);
make_house(n6, 6);