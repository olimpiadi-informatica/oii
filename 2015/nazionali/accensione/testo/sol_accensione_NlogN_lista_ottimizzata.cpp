#include <cstddef>

const int MAXN = 1000000;
const int MAXL = 15000000;

// Per minimizzare l'overhead dovuto all'allocazione dinamica della memoria, allochiamo staticamente MAXL
// nodi di lista, e gestiamoli manualmente. Il numero MAXL è sufficientamente grande da garantire che
// non sarà necessario allocare ulteriori nodi 
struct node_t {
	int value;
	node_t* next = NULL;
};
// pool rappresenta la memoria allocata staticamente, ovvero i MAXL nodi di lista
node_t pool[MAXL];
// pool_ptr punta al primo nodo non ancora usato
node_t *pool_ptr;
// end[i] punta all'ultimo nodo della lista dei divisori del numero i
node_t *end[MAXN + 1];

void Accendi(int N, int acceso[], int pulsante[]) {
	// Inseriamo il divisore 1 nelle liste dei divisori dei numeri da 1 a N
	for (int i = 1; i <= N; i++) {
		pool[i].value = 1;
		end[i] = pool + i;
	}
	pool_ptr = pool + N + 1;

	// Inseriamo ora nelle varie liste tutti i divisori dal 2 in poi	
	for (int i = 2; i <= N; i++) {
		for (int j = i; j <= N; j += i) {
			pool_ptr->value = i;
			end[j]->next = pool_ptr;
			end[j] = pool_ptr++;
		}
	}

	// Dopo aver costruito le liste, procediamo come nella soluzione precedente, col vantaggio di conoscere
	// in anticipo quali computer vengono modificati dal pulsante i
	for (int i = N; i >= 1; i--) {
		if (!acceso[i]) {
			pulsante[i] = true;

			for (node_t* j = pool + i; j != end[i]; j = j->next)
				acceso[j->value] ^= 1;
		}
	}
}