unitsize(.8cm);

// Configuration variables (change as you like)

real INTERVAL_CIRCLE_OUTER_RADIUS = .15;
real INTERVAL_CIRCLE_INNER_RADIUS = .12;

// Actual code -- don't touch unless you know what you're doing :-)

void draw_plane(int plane, string num, string filename = "plane_cut.eps") {
	pair pos = (-1, -plane);
	label(rotate(-90) * scale(.07) * graphic(filename), pos);
	label(scale(.73) * num, pos + (.3, .3), black);
}

void draw_interval(int plane, int start, int end, pen p) {
	draw((start - .5, -plane) -- (end + .5, -plane), p + linewidth(2));
	for (int i = start; i <= end; ++i) {
		fill(circle((i, -plane), INTERVAL_CIRCLE_OUTER_RADIUS), p);
		fill(circle((i, -plane), INTERVAL_CIRCLE_INNER_RADIUS), white);
	}
}

void select_tick(int plane, int time, pen p) {
	fill(circle((time, -plane), INTERVAL_CIRCLE_INNER_RADIUS), p);
}

void setup_grid(int n_planes, int n_time_ticks) {
	//label("Tempo:", (-1, .4));

	draw((.3, 0) -- (n_time_ticks + .7, 0));
	for (int i = 1; i <= n_time_ticks; ++i) {
		draw((i, -.1) -- (i, +.1));
		label(scale(.8) * ("$" + (string)i + "$"), (i, .4), gray(.1));
		draw((i, -.2) -- (i, -n_planes - .5), gray + dotted);
	}
	//label((scale(.04 * n_planes) * graphic("tower.eps")), (n_time_ticks + 4, -n_planes/2));
}


setup_grid(3, 8);

// 3 5
// 1 7
// 4 8

pen ita_red = rgb("009246");
pen ita_green = rgb("CE2B37");

draw_plane(1, "$1$", "plane_cut_red.eps");
draw_interval(1, 3, 5, ita_red);
select_tick(1, 3, ita_red);

draw_plane(2, "$2$", "plane_cut_white.eps");
// Custom code:
//   draw_interval(2, 1, 7, white);
// does not work in this case.
draw((1 - .5, -2) -- (7 + .5, -2), black + linewidth(2.3));
draw((1 - .5, -2) -- (7 + .5, -2), white + linewidth(1.5));
for (int i = 1; i <= 7; ++i) {
	fill(circle((i, -2), .15), black);
	fill(circle((i, -2), .13), white);
}
	fill(circle((6, -2), .10), black);

draw_plane(3, "$3$", "plane_cut_green.eps");
draw_interval(3, 4, 8, ita_green);
select_tick(3, 8, ita_green);