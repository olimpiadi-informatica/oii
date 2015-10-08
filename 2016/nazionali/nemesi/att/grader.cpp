#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int* nemico;

// Declaring functions
void smista(int N, int* nemico);

static int gruppi = 0;

void nuovo_gruppo() {
	if (gruppi != 0) fprintf(fw, "\n");
	gruppi++;
}

void aggiungi(int bambino) {
	fprintf(fw, "%d ", bambino);
}

int main() {
	#ifdef EVAL
		fr = fopen("input.txt", "r");
		fw = fopen("output.txt", "w");
	#else
		fr = stdin;
		fw = stdout;
	#endif

	// Reading input
	fscanf(fr, "%d ", &N);
	nemico = (int*)malloc(N * sizeof(int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, "%d ", &nemico[i0]);
	}

	// Calling functions
	smista(N, nemico);

	// Writing output
	
	fclose(fr);
	fclose(fw);
	return 0;
}
