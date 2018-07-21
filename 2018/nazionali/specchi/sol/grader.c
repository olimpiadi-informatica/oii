// serve perchè altrimenti fputc_unlocked dà un warning
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

typedef enum {
	SOPRA = 0,
	DESTRA = 1,
	SOTTO = 2,
	SINISTRA = 3
} parete_t;
typedef struct {
	parete_t lato;
	int posizione;
} foro_t;

void inizia(int N, int M);
void aggiungi(int r, int c, char diagonale);
foro_t calcola(foro_t ingresso);

static void fast_write_int(int x) { // speed x2
	static short int digits[16];
	if (x == 0) {
		fputc_unlocked('0', stdout);
		return;
	}
	short int i = -1;
	while (x) {
		i++;
		digits[i] = x%10;
		x /= 10;
	}
	for (; i >= 0; i--) fputc_unlocked('0' + digits[i], stdout);
}

static void stampa(int a, int b) {
	fast_write_int(a);
	fputc_unlocked(' ', stdout);
	fast_write_int(b);
	fputc_unlocked('\n', stdout);
}

int main() {
	int N, M, Q, r, c, lato, posizione, i;
	char tipo;

	read(STDIN_FILENO, &N, 4);
	read(STDIN_FILENO, &M, 4);
	read(STDIN_FILENO, &Q, 4);
	inizia(N, M);
	char* buffer = (char*)malloc(Q * (1 + 4 + 4));
	assert(Q * (1 + 4 + 4) == read(STDIN_FILENO, buffer, Q * (1 + 4 + 4)));
	
	for (i = 0; i < Q; i++) {
		tipo = *(char*)buffer;
		if (tipo == '?') {
			lato = *(int*)(buffer + 1);
			posizione = *(int*)(buffer + 1 + 4);
			foro_t in = {(parete_t)lato, posizione};
			foro_t res = calcola(in);
			stampa(res.lato, res.posizione);
		} else if (tipo == '/' || tipo == '\\') {
			r = *(int*)(buffer + 1);
			c = *(int*)(buffer + 1 + 4);
			aggiungi(r, c, tipo);
		}
		buffer += 1 + 4 + 4;
	}
}
