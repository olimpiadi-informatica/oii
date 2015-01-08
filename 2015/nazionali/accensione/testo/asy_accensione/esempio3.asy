unitsize(.7cm);

int pc[] = {1, 1, 1, 1, 1, 1};
int bt[] = {0, 1, 0, 0, 1, 1};

int N = pc.length;

real w = 1, sp = 1.8;
real hgt_bt[] = {.8, .4};

path rect(pair corner, real w, real h) {
	return corner -- (corner.x + w, corner.y) -- (corner.x + w, corner.y + h) -- (corner.x, corner.y + h) -- cycle;
}

void button(int i) {
	real h = hgt_bt[bt[i]];
	path btn = rect((i, 0) * sp - (w/2,0), w, h);

	if (bt[i] == 1) {
		fill(btn, gray(.5));
	} else {
		fill(btn, gray(.9));
	}
	draw(btn);
	label(scale(.7) * ("$" + (string)(i+1) + "$"), (i * sp, -.3), gray(.4));
}

void computer(int i) {
	real h = w;
	path btn = rect((i * sp, 1.8) - (w*1.3/2,0), w*1.3, h);

	if (pc[i] == 1) {
		//fill(btn, rgb(100/256, 220/256, 100/256));
		fill(btn, white);
		label("\texttt{A}", (i * sp, 1.8 + h/2), black);
	}
	else {
		//fill(btn, rgb(230/256, 100/256, 100/256));
		fill(btn, gray(.5));
		label("\texttt{S}", (i * sp, 1.8 + h/2), white);
	}

	draw(btn, linewidth(1));

	path base = (i * sp - w*.5/2, 1.8) -- (i * sp - w * 1/2, 1.4) -- (i * sp + w * 1/2, 1.4) -- (i * sp + w*.5/2, 1.8) -- cycle;
	fill(base, gray(.2));
}

for (int i = 0; i < N; ++i)
	button(i);

for (int i = 0; i < N; ++i)
	computer(i);

draw((-1, 0) -- ((N - 1) * sp + 1, 0), black + linewidth(1));
draw((-1, 1.4) -- ((N - 1) * sp + 1, 1.4), black + linewidth(1));

label("Pulsanti", (-3, .3));
label("Computer", (-3, 2));

draw((N * sp - .3, hgt_bt[0]) -- (N * sp + .1, hgt_bt[0]));
draw((N * sp - .3, hgt_bt[1]) -- (N * sp + .1, hgt_bt[1]));
label(scale(.6) * "\texttt{OFF}", (N * sp + .1, hgt_bt[0]), align = RightSide);
label(scale(.6) * "\texttt{ON}", (N * sp + .1, hgt_bt[1]), align = RightSide);