unitsize(.7cm);
import math;
import graph;

real f(real x) {
	real gamma = 0.57721566;
	return (log(x) + gamma) * 1.5;
}

draw(graph(f, .6, 14.2), dashed + black);

real s = 0;
for (int i = 1; i <= 14; ++i) {
	s += 1.0/i;

	draw((i,0) -- (i,s * 1.5), dotted + gray(.6));
	fill(circle((i, s * 1.5), .1), gray(0));

	draw((i,0) -- (i,-.1));
	label(scale(.5) * ("$" + (string)i + "$"), (i,-.3), gray(.3));
}

draw((.5,1 * 1.5) -- (.4,1 * 1.5));
draw((.5,2 * 1.5) -- (.4,2 * 1.5));
draw((.5,3 * 1.5) -- (.4,3 * 1.5));
label(scale(.5) * "$1$", (.2,1 * 1.5), gray(.3));
label(scale(.5) * "$2$", (.2,2 * 1.5), gray(.3));
label(scale(.5) * "$3$", (.2,3 * 1.5), gray(.3));

//draw((.5,1 * 1.5) -- (14.3, 1 * 1.5), dotted + gray(.6));
//draw((.5,2 * 1.5) -- (14.3, 2 * 1.5), dotted + gray(.6));
//draw((.5,3 * 1.5) -- (14.3, 3 * 1.5), dotted + gray(.6));

draw((.4,0) -- (14.5, 0), black + linewidth(.8), arrow=Arrow(TeXHead));
draw((.5,-.1) -- (.5, 5.5), black + linewidth(.8), arrow=Arrow(TeXHead));

draw((15.3,4.85) -- (16.0,4.85), dashed + black);
label(scale(.9) * "$\ln(n) + \gamma$", (16.1, 4.85), black, align=RightSide);

fill(circle((15.65, 3.85), .1));
label(scale(.9) * "$\sum (1/k)$", (16.1, 3.85), black, align=RightSide);

label(scale(.9) * "$n$",(14.8,0));