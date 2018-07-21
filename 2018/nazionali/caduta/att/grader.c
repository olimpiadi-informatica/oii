#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

stato_t correggi(int N, int altezze[], coppia_t* scambio);


int main() {
	int N, *altezze;

	assert(1 == scanf("%d", &N));

	altezze = (int*) malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		assert(1 == scanf("%d", &altezze[i]));

	coppia_t scambio;
	stato_t stato = correggi(N, altezze, &scambio);

	if (stato == OK)
		printf("OK\n");
	else if (stato == IMPOSSIBILE)
		printf("IMPOSSIBILE\n");
	else
		printf("%d %d\n", scambio.domino1, scambio.domino2);

	free(altezze);
	return EXIT_SUCCESS;
}
