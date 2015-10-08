// Configuration variables (change as you like)

real INTERVAL_CIRCLE_OUTER_RADIUS = .15;
real INTERVAL_CIRCLE_INNER_RADIUS = .12;

// Actual code -- don't touch unless you know what you're doing :-)

void draw_plane(int plane, string num) {
	pair pos = (-1, -plane);
	label(rotate(-90) * scale(.07) * graphic("plane_cut.eps"), pos);
	label(scale(.73) * num, pos + (.3, .3), black);
}

void draw_interval(int plane, int start, int end) {
	draw((start - .5, -plane) -- (end + .5, -plane), linewidth(2));
	for (int i = start; i <= end; ++i) {
		fill(circle((i, -plane), INTERVAL_CIRCLE_OUTER_RADIUS), black);
		fill(circle((i, -plane), INTERVAL_CIRCLE_INNER_RADIUS), white);
	}
}

void select_tick(int plane, int time) {
	fill(circle((time, -plane), INTERVAL_CIRCLE_INNER_RADIUS), black);
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
