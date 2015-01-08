import roundedpath;
unitsize(.7cm);

pair[] nodes = {(0,0), (-1.8,1.25), (2.5, 0), (2.5,2.5), (0, 2.5)};

// corner è il vertice in basso a sinistra
path rect(pair corner, real w, real h) {
	return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void node(pair pos, pen bord = black, string content, pen inner = gray(.95), pen lbl = black) {
	path border = circle(pos, .4);
	fill(border, inner);
	draw(border, bord);

	label(content, pos, lbl);
}

void badge(pair pos, pen bk = gray(.95), pen lbl = black, string content, real badge_w = .4, real badge_h = .4) {
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

edge(nodes[0], nodes[1], 3);
edge(nodes[1], nodes[4], 5);
edge(nodes[4], nodes[3], 3);
edge(nodes[3], nodes[0], 2);
edge(nodes[0], nodes[2], 4);
edge(nodes[2], nodes[3], 1);

// Nodi
int William = 1, Luca = 3;
int active[] = {0,0,0,0,0,0,0,0};
for (int i = 0; i < nodes.length; ++i) {
	pen bord = black;
	if (active[i] == 1)
		bord = black + linewidth(1);

	if (i == William)
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", inner = rgb(200/256, 200/256, 256/256), lbl = black);
	else if (i == Luca)
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$", inner = rgb(256/256, 200/256, 200/256), lbl = black);
	else
		node(nodes[i], bord = bord, "$" + (string)(i+1) + "$");
}

badge((-5.5,2.6), bk = rgb(150/256, 150/256, 256/256), "", 1, .6);
label("William", (-5, 2.6), align = RightSide);
badge((-5.5,1.6), bk = rgb(256/256, 150/256, 150/256), "", 1, .6);
label("Luca", (-5, 1.6), align = RightSide);
