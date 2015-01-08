import roundedpath;
unitsize(.7cm);

pair[] nodes;
real w_sp = 3, h_sp = 2.6;
int W = 4, H = 3;
for (int i = 0; i < H * W; ++i) {
	int h = floor(i / W), w = i % W;

	nodes.push((w * w_sp, -h * h_sp));
}

// corner è il vertice in basso a sinistra
path rect(pair corner, real w, real h) {
	return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void node(pair pos, pen bord = black, string content, pen inner = white, pen lbl = black) {
	path border = circle(pos, .5);
	fill(border, inner);
	draw(border, bord);

	label(content, pos, lbl);
}

void badge(pair pos, pen bk = white, pen lbl = black, string content, real badge_w = .4, real badge_h = .4) {
	path box = roundedpath(rect(pos - (badge_w, badge_h) / 2, badge_w, badge_h), 0.08);
	fill(box, bk);
	// draw(box);

	label(scale(.85) * content, pos, lbl);
}

void edge(pair a, pair b, int wgt, bool active = false) {
	if (active) {
		draw(a -- b, gray(.8) + linewidth(8));
		draw(a -- b, black + linewidth(1));

		if (a.y == b.y) { // orizzontale
			badge((a + b)/ 2, gray(.8), (string)wgt, .6, .4);
		} else { // verticale
			badge((a + b)/ 2, gray(.8), (string)wgt, .4, .6);
		}		
	} else {
		draw(a -- b, black);

		if (a.y == b.y) { // orizzontale
			badge((a + b)/ 2, (string)wgt, .6, .4);
		} else { // verticale
			badge((a + b)/ 2, (string)wgt, .4, .6);
		}		
	}
}

// Archi orizzontali

edge(nodes[0] , nodes[1] , 1);
edge(nodes[1] , nodes[2] , 8, true);
edge(nodes[2] , nodes[3] , 3, true);

edge(nodes[4] , nodes[5] , 4);
edge(nodes[5] , nodes[6] , 5);
edge(nodes[6] , nodes[7] , 6);

edge(nodes[8] , nodes[9] , 1);
edge(nodes[9] , nodes[10], 2);
edge(nodes[10], nodes[11], 5);

// Archi verticali
edge(nodes[0] , nodes[4] , 3);
edge(nodes[4] , nodes[8] , 6);

edge(nodes[1] , nodes[5] , 7);
edge(nodes[5] , nodes[9] , 8);

edge(nodes[2] , nodes[6] , 2); // <-- Quello minimo
edge(nodes[6] , nodes[10], 5);

edge(nodes[3] , nodes[7] , 9, true);
edge(nodes[7] , nodes[11], 2);

// Nodi
int William = 1, Luca = 7;
int active[] = {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0};
for (int i = 0; i < W * H; ++i) {
	pen bord = black;
	if (active[i] == 1)
		bord = black + linewidth(1);

	if (i == William)
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", inner = rgb(150/256, 150/256, 256/256), lbl = white);
	else if (i == Luca)
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", inner = rgb(256/256, 150/256, 150/256), lbl = white);
	else
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$");
}
