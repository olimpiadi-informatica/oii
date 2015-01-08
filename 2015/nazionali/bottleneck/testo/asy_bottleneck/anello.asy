import roundedpath;
unitsize(.7cm);

pair[] nodes;
real w_sp = 3, h_sp = 2.6;
int W = 6, H = 1;
for (int i = 0; i < H * W; ++i) {
	int h = floor(i / W), w = i % W;

	nodes.push((w * w_sp, -h * h_sp));
}

void node(pair pos, pen bord = black, string content, pen inner = white, pen lbl = black) {
	path border = circle(pos, .5);
	fill(border, inner);
	draw(border, bord);

	label(content, pos, lbl);
}

void edge(pair a, pair b) {
	draw(a -- b, black);
}

// Archi orizzontali

edge(nodes[0] , nodes[1]);
edge(nodes[1] , nodes[2]);
edge(nodes[2] , nodes[3]);
edge(nodes[3] , nodes[4]);
edge(nodes[4] , nodes[5]);
edge(nodes[5] , nodes[5] + (1.5, 0));
edge(nodes[5] + (1.5, 0), nodes[5] + (1.5, -1.5));
edge(nodes[5] + (1.5, -1.5), nodes[0] + (-1.5, -1.5));
edge(nodes[0] + (-1.5, -1.5), nodes[0] + (-1.5, 0));
edge(nodes[0] + (-1.5, 0), nodes[0]);

// Nodi
for (int i = 0; i < W * H; ++i) {
	node(nodes[i], "$" + (string)(i+1) + "$");
}