unitsize(1cm);
usepackage('inputenc', 'utf8');

string disug[] = {'<', '>', '<', '<', '>'};
string values[] = {'A','B','C','D','E','F'};
int N = values.length;

real sep = .75, sq_w = .7;
path r = (-.5, -sq_w/2 - .13) -- (2 * N * sep - 2 * sep + .5, -sq_w/2 - .13) -- (2 * N * sep - 2 * sep + .5, sq_w/2 + .13) -- (-.5, sq_w/2 + .13) -- cycle;
fill(r, gray(.8));

for (int i = 0; i < N; ++i) {
	path sq = shift((sep, 0) * (2 * i) + (-.5, -.5)*sq_w) * scale(sq_w) * unitsquare;
	fill(sq, white);
	draw(sq);
	label("$" + values[i] + "$", (sep, 0) * (2*i));
	if (i != N - 1) {
		label("$" + disug[i] + "$", (sep, 0) * (2*i+1));
	}
}