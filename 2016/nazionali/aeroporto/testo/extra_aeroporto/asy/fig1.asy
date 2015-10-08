unitsize(.8cm);
import plane_lib;

setup_grid(3, 8);

// 3 5
// 1 7
// 4 8

draw_plane(1, "$1$");
draw_interval(1, 3, 5);
select_tick(1, 3);

draw_plane(2, "$2$");
draw_interval(2, 1, 7);
select_tick(2, 6);

draw_plane(3, "$3$");
draw_interval(3, 4, 8);
select_tick(3, 8);