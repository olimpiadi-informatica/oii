#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static FILE *fr, *fw;

// Declaring variables
static int R;
static int* A;
static int* B;
static int* T;

// Declaring functions
void pianifica(int R, int* A, int* B, int* T);

int main() {
	#ifdef EVAL
		fr = fopen("input.txt", "r");
		fw = fopen("output.txt", "w");
	#else
		fr = stdin;
		fw = stdout;
	#endif

	// Iterators used in for loops
	int i0;

	// Reading input
	fscanf(fr, "%d ", &R);
	A = (int*)malloc(R * sizeof(int));
	B = (int*)malloc(R * sizeof(int));
	for (i0 = 0; i0 < R; i0++) {
		fscanf(fr, "%d %d ", &A[i0], &B[i0]);
	}

	// Calling functions
	T = (int*)malloc(R * sizeof(int));
	pianifica(R, A, B, T);

	// Writing output
	for (i0 = 0; i0 < R; i0++) {
		fprintf(fw, "%d ", T[i0]);
	}
	fprintf(fw, "\n");
	
	fclose(fr);
	fclose(fw);
	return 0;
}
