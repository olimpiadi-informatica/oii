include util;

int N = 1;
int M = 1;
string[] grid = {
	'\\'
};
pair inizio = (1,1);
int[] percorso = {dx, dw};


luce(N, M, inizio, percorso, penna_luce);
luce(N, M, inizio, percorso, penna_luce_2);
griglia(N, M);
//numeri(N, M);
specchi(N, M, grid);
