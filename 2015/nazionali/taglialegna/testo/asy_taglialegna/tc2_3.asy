unitsize(.6cm);
import roundedpath;

// Variabili globali
real tr_angle = 68;
real outer_angle = 80;
real hgt_factor = .44;

int min_piani = 4, max_piani = 6;
real min_size = .2, max_size = 3.5;

// corner è il vertice in basso a sinistra
path rettangolo(pair corner, real w, real h) {
	return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

real trunk_hgt(real size) {
	return .2 + .45 * (size-min_size);
}

real valuta(int piani, real size) {
	real ans = trunk_hgt(size);

	real lato = size;
	for (int i=0; i<piani; ++i) {
		real altezza = lato * Tan(tr_angle) / 2;
		if (i < piani-1)
			ans += altezza * hgt_factor;
		else
			ans += altezza;

		lato = lato * (1 - hgt_factor * Tan(tr_angle) / Tan(outer_angle));
	}

	return ans;
}

pair ricerca_parametri(real desired_hgt, int minp, int maxp) {
	for (int num = minp; num <= maxp; ++num) {
		real lb = min_size, ub = max_size;
		for (int iteration = 0; iteration < 12; ++iteration) {
			real mid = (lb + ub)/2;
			if (valuta(num, mid) > desired_hgt)
				ub = mid;
			else
				lb = mid;
		}

		if (max_size-ub > 0.01)
			return (num, ub); 
	}

	return (7, 9);
}

path triangolo(pair centro, real lato, real angle = 60) {
	real altezza = lato * Tan(angle) / 2;
	return (centro.x - lato/2, centro.y) -- (centro.x, centro.y + altezza) -- (centro.x + lato/2, centro.y) -- cycle;
}

picture albero(int piani, real size, pen penna = black) {
	picture res; unitsize(res, .6cm);
	pair base = (0,0);

	real w_trunk = .2 * size, h_trunk = trunk_hgt(size), epsilon = .1;
	path trunk = rettangolo((base.x - w_trunk/2, base.y), w_trunk, (h_trunk+epsilon));
	fill(res, trunk, penna);

	pair centro = (base.x, base.y + h_trunk);
	real lato = size;
	for (int i=0; i<piani; ++i) {
		path tr = roundedpath(triangolo(centro, lato, tr_angle),.05);
		fill(res, tr, penna);
		centro = (centro.x, centro.y + lato * Tan(tr_angle) * hgt_factor / 2);
		lato = lato * (1 - hgt_factor * Tan(tr_angle) / Tan(outer_angle));
	}

	return res;
}

path clip_region = (-5, 0) -- (15,0) -- (15, 5) -- (-5, 5) -- cycle;

void make_tree(pair base, real altezza, int minp, int maxp, pen penna = black, int fall = 0) {
	picture tmp; unitsize(tmp, .6cm);
	pair conf = ricerca_parametri(altezza, minp, maxp);
	picture tree = shift(0, 0.1 * conf.y * Sin(abs(fall))) * (rotate(fall) * albero((int)conf.x, conf.y, penna));
	
	add(tmp, tree.fit(), base);
	clip(tmp, clip_region);
	add(tmp.fit(), (0,0));
}


// write(valuta(3, .5));
// write(valuta(5, 2.5));

for (int i=1; i<=4; ++i) {
	draw((-1+.2, i-.02) -- (5+1.3-.2, i-.02), dashed + gray(.8));
	label("\small$" + (string)i + "$", (-1.15, i-.02), gray(.6));
}

pen penna = gray(.2);
make_tree((0,0), 3, 4, 4, penna, -63);
make_tree((1,0), 1, 2, 6, penna, -75);
make_tree((2,0), 4, 5, 5, penna, -65);
make_tree((3,0), 1, 3, 3, penna, -85);
make_tree((4,0), 2, 3, 8, penna, -52);
make_tree((5,0), 1, 2, 8, penna, -28);

draw((-1+.2, -0.05) -- (5+1.3-.2,-0.05), linewidth(2.5));

void grid(pair o, int w, int h, pen p = gray(.8)) {
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			draw((o.x + x,o.y + y)--(o.x + x,o.y + y+1)--(o.x + x+1,o.y + y+1)--(o.x + x+1,o.y + y)--cycle, p);
		}
	}
}

int h[] = {3,1,4,1,2,1};
for (int i = 0; i < h.length; ++i) {
	real hh = -1.5;

	fill((i-.5,hh) -- (i+.5,hh) -- (i+.5, hh+1) -- (i-.5, hh+1) -- cycle, gray(1));	
	draw((i-.5, hh) -- (i+.5, hh+1));
	draw((i-.5, hh+1) -- (i+.5, hh));

	label("$" + (string)h[i] + "$", (i, -1));
}
grid((-.5, -1.5), h.length, 1, black + linewidth(.8));