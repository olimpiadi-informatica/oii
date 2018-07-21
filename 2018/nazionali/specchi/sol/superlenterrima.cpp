#include <iostream>
#include <vector>

typedef int parete_t;
#define SOPRA 1
#define DESTRA 2
#define SOTTO 3
#define SINISTRA 4

typedef struct {
	parete_t lato;
	int posizione;
} foro_t;

std::vector<std::vector<char>> grid;
int N, M;

void inizia(int N, int M) {
	::N = N;
	::M = M;
	grid.resize(N+1, std::vector<char>(M+1));
}

void aggiungi(int r, int c, char diagonale) {
	r++;
	c++;
	grid[r][c] = diagonale;
}

int dc[] = {0, 0, 1, 0, -1};
int dr[] = {0, -1, 0, 1, 0};

foro_t calcola(foro_t ingresso) {
	ingresso.lato += 1;
	ingresso.posizione += 1;
	int r, c, d;
	if (ingresso.lato == SOPRA)
		r = 1, c = ingresso.posizione, d = SOTTO;
	if (ingresso.lato == DESTRA)
		r = ingresso.posizione, c = M, d = SINISTRA;
	if (ingresso.lato == SOTTO)
		r = N, c = ingresso.posizione, d = SOPRA;
	if (ingresso.lato == SINISTRA)
		r = ingresso.posizione, c = 1, d = DESTRA;
	int rimbalzi = 0;
	int lunghezza = 0;
	while (r > 0 && r <= N && c > 0 && c <= M) {
		char cell = grid[r][c];
		if (cell == '/') {
			if (d == SOPRA) d = DESTRA;
			else if (d == DESTRA) d = SOPRA;
			else if (d == SOTTO) d = SINISTRA;
			else if (d == SINISTRA) d = SOTTO;
			rimbalzi++;
		}
		if (cell == '\\') {
			if (d == SOPRA) d = SINISTRA;
			else if (d == DESTRA) d = SOTTO;
			else if (d == SOTTO) d = DESTRA;
			else if (d == SINISTRA) d = SOPRA;
			rimbalzi++;
		}
		r += dr[d];
		c += dc[d];
		lunghezza++;
	}
#ifdef DEBUG
	std::cerr << "ingresso: " << ingresso.posizione << " " << ingresso.lato << " rimbalzi: " << rimbalzi << " lunghezza: " << lunghezza << std::endl;
#endif
	if (r == 0) return {SOPRA-1, c-1};
	if (r == N+1) return {SOTTO-1, c-1};
	if (c == 0) return {SINISTRA-1, r-1};
	if (c == M+1) return {DESTRA-1, r-1};
}
