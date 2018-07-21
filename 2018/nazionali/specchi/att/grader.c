#include <stdio.h>
#include <assert.h>

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
void aggiungi(int riga, int colonna, char orientamento);
foro_t calcola(foro_t ingresso);

int main() {
	int N, M, Q, riga, colonna, lato, posizione, i;
	char tipo;

	assert(3 == scanf("%d %d %d", &N, &M, &Q));
	inizia(N, M);

	for (i = 0; i < Q; i++) {
		assert(1 == scanf(" %c", &tipo));
		if (tipo == '?') {
			assert(2 == scanf("%d %d", &lato, &posizione));
			foro_t in = {(parete_t)lato, posizione};
			foro_t res = calcola(in);
			printf("%d %d\n", res.lato, res.posizione);
		} else if (tipo == '/' || tipo == '\\') {
			assert(2 == scanf("%d %d", &riga, &colonna));
			aggiungi(riga, colonna, tipo);
		} else {
			fprintf(stderr, "Tipo di comando errato (validi: / \\ ?): %c (ascii %d)\n", tipo, (int)tipo);
			assert(0);
		}
	}
}
