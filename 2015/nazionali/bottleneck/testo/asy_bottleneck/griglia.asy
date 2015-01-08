import roundedpath;
unitsize(.7cm);

pair[] nodes;
real w_sp = 3, h_sp = 2.2;
int W = 6, H = 3;
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


edge(nodes[6] , nodes[7]);
edge(nodes[7] , nodes[8]);
edge(nodes[8] , nodes[9]);
edge(nodes[9] , nodes[10]);
edge(nodes[10], nodes[11]);


edge(nodes[12], nodes[13]);
edge(nodes[13], nodes[14]);
edge(nodes[14], nodes[15]);
edge(nodes[15], nodes[16]);
edge(nodes[16], nodes[17]);


// Archi verticali
edge(nodes[0] , nodes[6]);
edge(nodes[6] , nodes[12]);

edge(nodes[1] , nodes[7]);
edge(nodes[7] , nodes[13]);

edge(nodes[2] , nodes[8]);
edge(nodes[8] , nodes[14]);

edge(nodes[3] , nodes[9]);
edge(nodes[9] , nodes[15]);

edge(nodes[4] , nodes[10]);
edge(nodes[10], nodes[16]);

edge(nodes[5] , nodes[11]);
edge(nodes[11], nodes[17]);

// Nodi
for (int i = 0; i < W * H; ++i) {
	node(nodes[i], "$" + (string)(i+1) + "$");
}