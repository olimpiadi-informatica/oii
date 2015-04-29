unitsize(.9cm);
usepackage('inputenc', 'utf8');

void draw_node(pair c, string s) {
	real radius = .5;

	fill(circle(c, radius), white);
	draw(circle(c, radius));
	label(scale(1.2) * s, c);
}

void draw_edge(pair a, pair b, path p) {
	real radius = .5;

	real t_a = intersect(circle(a, radius), p)[1];
	real t_b = intersect(circle(b, radius), p)[1];

	p = subpath(p, t_a, t_b);
	draw(p, arrow = Arrow(TeXHead, size = 1.9));
}

currentpen = linewidth(1.0);

real spacing = 2.2;
pair A = spacing * (2, 0);
pair B = spacing * (3, 0);
pair C = spacing * (1, 0);
pair D = spacing * (4, 0);
pair E = spacing * (5, 0);
pair F = spacing * (0, 0);

draw_node(A, "$A$");
draw_node(B, "$B$");
draw_node(C, "$C$");
draw_node(D, "$D$");
draw_node(E, "$E$");
draw_node(F, "$F$");

draw_edge(A, B, A -- B);
draw_edge(C, B, C{(1,-1)} .. {(1,1)}B);
draw_edge(C, D, C{(1,1)} .. {(1,-1)}D);
draw_edge(D, E, D -- E);
draw_edge(F, E, F{(2,-1)} .. {(2,1)}E);