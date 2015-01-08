import roundedpath;
unitsize(.7cm);

pair n0 = (1, -1.5);
pair n1 = (-2, -2.5);
pair n2 = (2, -4);
pair n3 = (3.5, .5);
pair n4 = (1, 2.5);
pair n5 = (6.5, 2);
pair n6 = (5.5, -2);
pair n7 = (8.5, 3.5);
pair n8 = (4.5, 3.5);
pair n9 = (7.5, -1);
pair n10= (9.5, .5);
pair n11= (9, -3);

picture man;
unitsize(man, .16cm);
fill(man, (0,0) -- (1,0) -- (.7, .8) -- (.3, .8) -- cycle);
fill(man, circle((.5, 1.1), .4));

// corner è il vertice in basso a sinistra
path rect(pair corner, real w, real h) {
	return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void node(pair pos, pen p = black, string str, string desc) {
	path border = circle(pos, .5);
	fill(border, white);
	draw(border, p);

	label(str, pos);

	//path desc_box = roundedpath(rect((pos.x + .7, pos.y - .3), 0.95, .6), 0.08);
	//fill(desc_box, gray(.75));
	//label(scale(.8) * desc, (pos.x + .95, pos.y));

	//add(man.fit(), (pos.x + 1.2, pos.y - .17));
}

pen active_link = black + linewidth(1);
pen active_bkg  = gray(.75) + linewidth(7);
pen inactive_link = black;
pen inactive_bkg  = white;

void make_link(pair a, pair b, bool active = false) {
	if (!active) {
		draw(a -- b, inactive_bkg);
		draw(a -- b, inactive_link);
	} else {
		draw(a -- b, active_bkg);
		draw(a -- b, active_link);	
	}
}

void depth_box(real y, real minx = -4.5, real maxx = 9.5, int d) {
	real h = 1.4;
	path rect = roundedpath(rect((minx, y - h/2), maxx - minx, h), .2);
	fill(rect, dashed + gray(.90));
	draw(rect, dashed + gray(.5));

	label("\small $\leftarrow$ profondit\`a: $" + (string)d + "$", (maxx + 2.3, y), gray(.2));
}

//depth_box(0, -1, 2.15, 0);
//depth_box(-2, -4, 5.65, 1);
//depth_box(-4, -4, 8.15, 2);
//depth_box(-6, -1, 8.15, 3);
//depth_box(-8, 3.5, 9.65, 4);

make_link(n0, n1);
make_link(n0, n2);
make_link(n0, n3);
make_link(n1, n4);
make_link(n3, n5);
make_link(n3, n6);
make_link(n5, n7);
make_link(n5, n8);
make_link(n6, n9);
make_link(n10, n9);
make_link(n11, n9);

node(n0,  black               , "$12$", "$3$");
node(n1,  black               , "$2$", "$7$");
node(n2,  black               , "$4$", "$9$");
node(n3,  black               , "$5$", "$8$");
node(n4,  black               , "$6$", "$1$");
node(n5,  black               , "$1$", "$3$");
node(n6,  black               , "$3$", "$4$");
node(n7,  black               , "$7$", "$1$");
node(n8,  black               , "$8$", "$8$");
node(n9,  black               , "$11$", "$5$");
node(n10, black               , "$9$", "$5$");
node(n11, black               , "$10$", "$7$");
