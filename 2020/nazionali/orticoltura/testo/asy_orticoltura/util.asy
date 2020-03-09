unitsize(1cm);
settings.tex = "pdflatex";

bool soldi = false;
real GRID_SIZE = 2;
pen penna_specchio = linewidth(3)+blue+white;
pen penna_luce = linewidth(5)+red+white;
pen penna_luce_2 = linewidth(2)+red;
Label grass = graphic("grass.jpg", "scale=0.46");
Label grass_wet = graphic("grass_wet.jpg", "scale=0.46");
Label dirt = graphic("dirt.jpg", "scale=0.46");
Label dirt_wet = graphic("dirt_wet.jpg", "scale=0.46");
// Label seed = graphic("seed.jpg", "scale=0.05");
Label seed = graphic("seed2.png", "scale=0.62");
Label irrigatore = graphic("irr.png", "scale=0.15");
Label cash = graphic("cash.png", "scale=0.15");

bool bagnato(pair p, pair[] irr) {
    for (int i = 0; i < irr.length; i+=1) {
        if (p.x - p.y >= irr[i].x-1 - irr[i].y+1 && p.x + p.y <= irr[i].x-1 + irr[i].y-1)
            return true;
    }
    return false;
}

void griglia(int larg, int alt, pair[] irr) {
	draw((0,0) -- (larg*GRID_SIZE,0));
	draw((larg*GRID_SIZE,0) -- (larg*GRID_SIZE,alt*GRID_SIZE));
	draw((larg*GRID_SIZE,alt*GRID_SIZE) -- (0,alt*GRID_SIZE));
	draw((0,alt*GRID_SIZE) -- (0,0));
    for (int r = 0; r < alt; r+=1) {
        for (int c = 0; c <= larg; c+=1) {
            bool bagn = bagnato((c, alt-r-1), irr);
            Label g;
            transform t = rotate(0);
            if (r == alt-1) {
                if (false) {
                    g = grass_wet;
                } else {
                    g = grass;
                }
            } else {
                if (false) {
                    g = dirt_wet;
                } else {
                    g = dirt;
                }
                t *= rotate((rand() % 4) * 90);
            }
            label(t * g, (c*GRID_SIZE+GRID_SIZE/2.0, r*GRID_SIZE+GRID_SIZE/2.0), NoAlign);
        }
    }
    layer();
	for (int i = 0; i < larg; i+=1) {
		draw( ((i+1)*GRID_SIZE, 0) -- ((i+1)*GRID_SIZE, alt*GRID_SIZE), heavygray+2+squarecap);
	}
	for (int i = 0; i < alt-1; i+=1) {
		draw( (0,(i+1)*GRID_SIZE) -- ((larg + 1) * GRID_SIZE,(i+1)*GRID_SIZE), heavygray+2+squarecap);
	}
}

void numeri(int larg, int alt) {
	for (int i = 0; i <= larg + 1; i+=1) {
		label(scale(1.4)*string(i * 10), (i * GRID_SIZE, -0.5));
//        draw( )
	}
	for (int i = 0; i <= alt; i+=1) {
		label(scale(1.4)*string((alt - i) * 10), (-0.5, i * GRID_SIZE));
	}
}

void seme(int alt, real x, real p) {
    transform t = rotate(0);// rotate((rand() * 1.0 / randMax - 0.5) * 60);
    label(t * seed, (x * GRID_SIZE, (alt - p) * GRID_SIZE + 0.35), NoAlign);
}

void irrigatore(int larg, int alt, real x, real p, int C) {
    label(irrigatore, (x * GRID_SIZE, alt * GRID_SIZE + 0.65), NoAlign);
    pair mid = (x * GRID_SIZE, (alt - p) * GRID_SIZE);
    path area;
    if (x + p > larg)
        area = ((x - p) * GRID_SIZE, alt * GRID_SIZE) -- mid -- ((larg + 1) * GRID_SIZE, (alt-p+larg+1-x) * GRID_SIZE) -- ((larg + 1) * GRID_SIZE, alt * GRID_SIZE);
    else
        area = ((x - p) * GRID_SIZE, alt * GRID_SIZE) -- mid -- ((x + p) * GRID_SIZE, alt * GRID_SIZE);
    fill(area -- cycle, lightblue + opacity(0.4));
    if (soldi) {
        for (int i = 0; i < C; i+=1) {
            real scale = 0.1;
            label(cash, (x * GRID_SIZE + GRID_SIZE / 3.0 + i * scale, alt*GRID_SIZE+GRID_SIZE/3.0+0.65+i*scale), NoAlign);
        }
        for (int i = 0; i < p; i+=1) {
            real scale = 0.1;
            label(cash, (x * GRID_SIZE + GRID_SIZE / 3.0, (alt - i - 1) * GRID_SIZE + GRID_SIZE / 3.0 + 0.65 + i * scale), NoAlign);
        }
    }
}

void main(int larg, int alt, int C, pair[] semi, pair[] irr) {
    griglia(larg, alt, irr);
    numeri(larg, alt);
    for (int i = 0; i < semi.length; i+=1)
        seme(alt, semi[i].x, semi[i].y);
    for (int i = 0; i < irr.length; i+=1)
        irrigatore(larg, alt, irr[i].x, irr[i].y, C);
}
