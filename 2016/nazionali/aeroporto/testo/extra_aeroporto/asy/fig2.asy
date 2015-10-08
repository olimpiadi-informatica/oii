unitsize(.8cm);
import plane_lib;

setup_grid(4, 13);

// 1 5
// 1 9
// 6 8
// 8 13

draw_plane(1, "$1$");
draw_interval(1, 1, 5);
select_tick(1, 2);

draw_plane(2, "$2$");
draw_interval(2, 1, 9);
select_tick(2, 5);

draw_plane(3, "$3$");
draw_interval(3, 6, 8);
select_tick(3, 8);

draw_plane(4, "$4$");
draw_interval(4, 8, 13);
select_tick(4, 13);