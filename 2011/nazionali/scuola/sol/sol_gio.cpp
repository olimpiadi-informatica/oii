
/*
 * Soluzione di Giovanni per scuola
 *
 * In entrambi i casi ad ogni round devo mandare x in x+k, dove k varia sugli
 * elementi dell'insieme dei giocatori (eventualmente escludendo lo zero nel
 * secondo caso). L'unica parte diversa è che nel primo caso metto sul dominio
 * la struttura di gruppo ciclico $Z_n$, nel secondo ${Z_2}^{\log_2 n}$.
 *
 * Visto che la parte lunga è la scrittura dell'output, l'ho ottimizzata
 * pre-generando tutte le stringhe relative ai numeri che vengono utilizzati.
 * Non ho fatto prove precise, ma credo che aiuti parecchio.
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_NUMBER = 2100;

int used[MAX_NUMBER];
char *strings[MAX_NUMBER];

inline void print_pair(int a, int b) {

	fputs(strings[a], stdout);
	putc(' ', stdout);
	fputs(strings[b], stdout);
	putc(' ', stdout);

	// Molto più lento
	//printf("%d %d ", a+1, b+1);

}

int main() {

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, p;
	scanf("%d %d", &n, &p);

	for (int i = 0; i < n; i++) {
		asprintf(&strings[i], "%d", i+1);	
	}

	for (int i = 0; i < n; i++) {
		bzero(used, sizeof(used));
		for (int j = 0; j < n; j++) {
			if (p == 1) {
				print_pair(j, (i+j)%n);
			} else if (i != 0) {
				if (!used[j]) {
					used[j] = used[i^j] = 1;
					print_pair(j, i^j);
				}
			}
		}
		if ((p == 1) || (i != 0)) putc('\n', stdout);
	}

	return 0;

}

