unitsize(1cm);
settings.tex = "pdflatex";

int up = 0;
int dx = 1;
int dw = 2;
int sx = 3;
real GRID_SIZE = 2;
real MIRR_SPACE = 0.3;
real RADIUS = 0.3;
pen penna_specchio = linewidth(3)+blue+white;
pen penna_luce = linewidth(5)+red+white;
pen penna_luce_2 = linewidth(2)+red;
pair[] delta = {
	(0,1),
	(1,0),
	(0,-1),
	(-1,0)
};

void griglia(int N) {
	draw((0,0) -- (N*GRID_SIZE,0));
	draw((N*GRID_SIZE,0) -- (N*GRID_SIZE,N*GRID_SIZE));
	draw((N*GRID_SIZE,N*GRID_SIZE) -- (0,N*GRID_SIZE));
	draw((0,N*GRID_SIZE) -- (0,0));
	for (int i = 0; i < N-1; i+=1) {
		draw( ((i+1)*GRID_SIZE, 0) -- ((i+1)*GRID_SIZE, N*GRID_SIZE), dotted);
	}
	for (int i = 0; i < N-1; i+=1) {
		draw( (0,(i+1)*GRID_SIZE) -- (N*GRID_SIZE,(i+1)*GRID_SIZE), dotted);
	}
}
void numeri(int N) {
	for (int i = 0; i < N; i+=1) {
		label(scale(2)*string(N-i-1), (-0.5,i*GRID_SIZE+GRID_SIZE/2));
	}
	for (int i = 0; i < N; i+=1) {
		label(scale(2)*string(i), (i*GRID_SIZE+GRID_SIZE/2,N*GRID_SIZE+0.5));
	}
}
void specchi(int N, int M, string[] grid) {
	for (int i = 0; i < N; i+=1) {
		for (int j = 0; j < M; j+=1) {
			string c = substr(grid[i],j,1);
			real x1 = j * GRID_SIZE + MIRR_SPACE;
			real x2 = (j+1) * GRID_SIZE - MIRR_SPACE;
			real y1 = (N-i) * GRID_SIZE - MIRR_SPACE;
			real y2 = (N-i-1) * GRID_SIZE + MIRR_SPACE;
			if (c == '/')
				draw((x1,y2) -- (x2,y1), penna_specchio);
			if (c == '\\')
				draw((x1,y1) -- (x2,y2), penna_specchio);
		}
	}
}
arrowhead head = DefaultHead;
head.head=new path(path g, position position=EndPoint, pen p=currentpen, real size=5cm, real angle=arrowangle) {
	size = 10.9522;
	if(size == 0) size=DefaultHead.size(p);
	bool relative=position.relative;
	real position=position.position.x;
	if(relative) position=reltime(g,position);
	path r=subpath(g,position,0);
	pair x=point(r,0);
	real t=arctime(r,size);
	pair y=point(r,t);
	path base=arrowbase(r,y,t,size);
	path left=rotate(-angle,x)*r;
	path right=rotate(angle,x)*r;
	real[] T=arrowbasepoints(base,left,right);
	pair denom=point(right,T[1])-y;
	real factor=denom != 0 ? length((point(left,T[0])-y)/denom) : 1;
	path left=rotate(-angle*factor,x)*r;
	path right=rotate(angle*factor,x)*r;
	real[] T=arrowbasepoints(base,left,right);
	return subpath(left,0,T[0])--subpath(right,T[1],0)&cycle;
};
pair dir_to_deg(int a, int b) {
	if (a == up && b == dx) return (90, 180);
	if (a == up && b == sx) return (0, 90);
	if (a == dx && b == dw) return (0, 90);
	if (a == dx && b == up) return (-90, 0);
	if (a == dw && b == sx) return (-90, 0);
	if (a == dw && b == dx) return (180, 270);
	if (a == sx && b == dw) return (90, 180);
	if (a == sx && b == up) return (180, 270);
	return (0,0);
}
void luce(int N, int M, pair inizio, int[] percorso, pen penna) {
	pen arrowpen = red+orange;
	pair pos = ((inizio.y-1) * GRID_SIZE + GRID_SIZE/2, (N-inizio.x+1)*GRID_SIZE-GRID_SIZE/2);
	pair inizio = pos - delta[percorso[0]]*GRID_SIZE*0.45;
	pair inizio2 = pos - delta[percorso[0]]*GRID_SIZE*0.5;
	real usedDelta = GRID_SIZE;
	if (percorso[0] != percorso[1]) {
		pos -= delta[percorso[0]]*RADIUS;
		usedDelta = GRID_SIZE-RADIUS;
	}
	draw(inizio -- pos, penna);
	draw(inizio2 -- inizio2 + delta[percorso[0]]*GRID_SIZE/5, arrowpen, Arrow(head));
	for (int i = 0; i < percorso.length - 1; i+=1) {
		// destinazione del raggio
		pair new_pos = pos + delta[percorso[i]]*(GRID_SIZE-usedDelta);
		if (percorso[i] != percorso[i+1])
			new_pos -= delta[percorso[i]]*RADIUS;

		// disegna il raggio
		draw(pos -- new_pos, penna);
		// se deve curvare
		if (percorso[i] != percorso[i+1]) {
			pair angoli = dir_to_deg(percorso[i], percorso[i+1]);
			draw(arc(
				new_pos + delta[percorso[i+1]]*RADIUS,
				RADIUS,
				angoli.x, angoli.y
			), penna);
			new_pos += delta[percorso[i]]*RADIUS + delta[percorso[i+1]]*RADIUS;
			usedDelta = RADIUS;
		} else
			usedDelta = 0;
		pos = new_pos;
	}
	pair new_pos = pos + delta[percorso[percorso.length-1]]*(GRID_SIZE*0.3-usedDelta);
	pair new_pos2 = pos + delta[percorso[percorso.length-1]]*(GRID_SIZE*0.5-usedDelta);
	draw(pos -- new_pos, penna);
	draw(new_pos2 - delta[percorso[percorso.length-1]]*GRID_SIZE/5 -- new_pos2, arrowpen, Arrow(head));
}

void corsa(int N, int[] percorso, pen penna)
{
	real x = GRID_SIZE * 0.5;
	real y = (N-1)*GRID_SIZE + GRID_SIZE * 0.5;

	for(int i=0; i<percorso.length; ++i)
	{
	    real x2 = x;
	    real y2 = y;

	    if( percorso[i] == dx )
		x2 += GRID_SIZE;
	    else if( percorso[i] == dw )
		y2 -= GRID_SIZE;
	    else if( percorso[i] == sx )
		x2 -= GRID_SIZE;
	    else if( percorso[i] == up )
		y2 += GRID_SIZE;

	  	draw((x, y) -- (x2, y2), penna);
	    x = x2;
	    y = y2;
	}
}
