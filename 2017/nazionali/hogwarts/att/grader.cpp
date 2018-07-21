#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int M;
static int* A;
static int* B;
static int* inizio;
static int* fine;
static int tempo;

// Declaring functions
int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]);

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	fscanf(fr, " %d %d", &N, &M);
	A = (int*)malloc((M) * sizeof(int));
	B = (int*)malloc((M) * sizeof(int));
	inizio = (int*)malloc((M) * sizeof(int));
	fine = (int*)malloc((M) * sizeof(int));
	for (int i0 = 0; i0 < M; i0++) {
		fscanf(fr, " %d %d %d %d", &A[i0], &B[i0], &inizio[i0], &fine[i0]);
	}

	// Calling functions
	tempo = raggiungi(N, M, A, B, inizio, fine);

	// Writing output
	fprintf(fw, "%d\n", tempo);

	fclose(fr);
	fclose(fw);
	return 0;
}
