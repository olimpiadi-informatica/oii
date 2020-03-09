import patterns;

add("hatch",hatch(1mm,gray));

path rect(pair p, real w, real h) {
	return p -- (p.x + w, p.y) -- (p.x + w, p.y + h) -- (p.x, p.y + h) -- cycle;
}

void skyscraper(picture pic, real x, real h, real shrink = 0, real antenna_h = 0, real antenna_r = 0) {
	path box = (x, 0) -- (x + 1, 0) -- (x + 1 - shrink, h) -- (x + shrink, h) -- cycle;
	filldraw(pic, box, palegray, black);

    if (antenna_h * antenna_r > 0.006) {
        draw(pic, (x + .5, h) -- (x + .5, h + antenna_h));
        fill(pic, circle((x+.5, h + antenna_h), antenna_r), black);
    }

	int n_win = (3 + rand() % 3) * (int)h;
	for (int i = 0; i < n_win; ++i) {
		real win_w = .1 + unitrand() * .1;
		real win_h = win_w * (unitrand() + 1);
		real win_y = h/n_win * i;
		if (win_h + win_y > h)
			win_y = h - win_h;
		real win_x = x + shrink * (i+1) / n_win + unitrand() * (1 - 2 * shrink * (i+1) / n_win - win_w);

		filldraw(pic, rect((win_x, win_y), win_w, win_h), white, gray(.4));
	}
}

void boxednum(picture pic, pair c, int n) {
    draw(pic, rect(c - (.65,0.4), 1.3, 0.8));
    label(pic, scale(1.1) * string(n), c);
}

picture main(int[] H, int[] S, int[] A, int[] B, int[] C) {
    picture pic;
    unitsize(pic, .7cm);
    real MAXY = 0;
    real MAXX = 1.5*H.length;
    for (int i=0; i<H.length; ++i) MAXY = max(MAXY, H[i]);
    for (int h = 1; h <= MAXY; ++h) {
        draw(pic, (-.5, h) -- (MAXX, h), gray + dashed);
        label(pic, (string)h, (-1, h), gray);
    }

    for (int i=0; i<S.length; ++i) {
        filldraw(pic, rect((i*1.5-0.1,0), 1.2, H[i]), pattern("hatch"), mediumgray);
        skyscraper(pic, i*1.5, S[i], shrink = .4*unitrand()-.1, antenna_h = .5*unitrand(), antenna_r = .03+.03*unitrand());
        label(pic, scale(.9) * string(i), (i * 1.5 + .5, -.4), black);

        boxednum(pic, (i * 1.5 + .5, -1.4), H[i]);
        boxednum(pic, (i * 1.5 + .5, -2.7), S[i]);
    }
    draw(pic, rect((-.25, -1.9), MAXX, 1));
    draw(pic, rect((-.25, -3.2), MAXX, 1));
    label(pic, scale(1.1) * "$H$", (-1, -1.4));
    label(pic, scale(1.1) * "$S$", (-1, -2.7));
    draw(pic, (-.5, 0) -- (MAXX, 0), black+1);
    int M = A.length;
    for (int i=0; i<M; ++i) {
        pen col = S[B[M-1-i]] <= S[A[M-1-i]] + C[M-1-i] ? deepgreen : heavyred;
        pair c = (MAXX+2.5,i+0.5);
        label(pic, scale(0.9) * ("$S[" + string(B[M-1-i]) + "] \leq S[" + string(A[M-1-i]) + "] + " + string(C[M-1-i]) + "$"), c, col);
        draw(pic, rect(c-(2,.4), 4, .8), col);
    }
    return pic;
}
