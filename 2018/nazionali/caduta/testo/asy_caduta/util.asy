import patterns;
unitsize(1cm);

real SPESSORE = 0.3;
real MARGIN = 0.3;

pen random_color() {
	return hsv(unitrand()*360, 1, 1);
}

void tessera(int h, int pos, pen color) {
	real sx = pos-SPESSORE/2;
	real dx = pos+SPESSORE/2;
	real c = (sx+dx)/2;
	real top = h-MARGIN;

	filldraw(arc((c,0), top, 0, 90) -- (c,0) -- cycle, yellow+white);
	fill(arc((c,0), top, 0, 90) -- (c,0) -- cycle, pattern("hatch"));
	draw(arc((c,0), top, 0, 90), 1+color);

	for (int i = 0; i < h-1; ++i) {
		real dw = i;
		real up = i+1;
		fill((sx,dw) -- (dx,dw) -- (dx,up) -- (sx,up) -- cycle, color);
		draw((sx,dw) -- (sx,up), black);
		draw((dx,dw) -- (dx,up), black);
		draw((sx,up) -- (c,up), black);
	}
	fill((sx,h-1) -- (dx,h-1) -- arc((c,top-SPESSORE/2), SPESSORE/2, 0, 180) -- cycle, color);
	draw((sx,h-1) -- (sx,top-SPESSORE/2), black);
	draw((dx,h-1) -- (dx,top-SPESSORE/2), black);
	draw(arc((c,top-SPESSORE/2), SPESSORE/2, 0, 180), black);
	draw((sx,0) -- (dx,0), black);
}
void legenda(int len) {
	for (int i = 0; i <= len; ++i) {
		label(string(i), (i,-0.1), S, fontsize(8));
		draw((i,0) -- (i,-0.1));
	}
	draw((0,0) -- (len,0));
}

void main(int[] altezze, int[] colors, int D, int seed) {
	srand(seed);
	add("hatch",hatch(5, orange));
	pen[] fixed_colors = {random_color(), random_color(), random_color(), random_color(), random_color(), random_color(), random_color(), random_color(), random_color()};
	for (int i = 0; i < altezze.length; ++i) {
		pen color;
		if (colors[i] != 0)
			color = fixed_colors[colors[i]];
		else
			color = random_color();
		tessera(altezze[i], D*i, color);
	}
	legenda(D*(altezze.length-1));
}
