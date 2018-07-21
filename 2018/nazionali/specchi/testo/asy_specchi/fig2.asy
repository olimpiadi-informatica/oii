include util;

int N = 4;
int M = 5;
string[] grid = {
	'.....',
	'../.\\',
	'.....',
	'..../'
};
pair inizio = (4,3);
//int[] percorso = {dx, dx, dx, dx, dx, up, up, sx, sx, dw, dw, dw};
int[] percorso = {up, up, up, dx, dx, dw, dw, sx, sx, sx, sx, sx};


luce(N, M, inizio, percorso, penna_luce);
luce(N, M, inizio, percorso, penna_luce_2);
griglia(N, M);
numeri(N, M);
specchi(N, M, grid);
