include util;

int N = 4;
int M = 5;
string[] grid = {
	'.....',
	'../.\\',
	'.....',
	'.....'
};
pair inizio = (2,5);
int[] percorso = {sx, up, up};


luce(N, M, inizio, percorso, penna_luce);
luce(N, M, inizio, percorso, penna_luce_2);
griglia(N, M);
numeri(N, M);
specchi(N, M, grid);
