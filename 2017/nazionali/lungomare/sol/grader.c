#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

static FILE *fr, *fw;

// Declaring variables
static int N;
static long long int L;
static long long int* D;
static long long int* P;
static long long int C;

// Declaring functions
long long int percorri(int N, long long int L, long long int D[], long long int P[]);

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	long long Nt;
	assert(read(STDIN_FILENO, &Nt, sizeof(long long))==sizeof(long long));
	N = Nt;
	assert(read(STDIN_FILENO, &L,  sizeof(long long))==sizeof(long long));
	D = (long long*)malloc((N) * sizeof(long long));
	assert(read(STDIN_FILENO, D, sizeof(long long)*N)==sizeof(long long)*N);
	P = (long long*)malloc((N) * sizeof(long long));
	assert(read(STDIN_FILENO, P, sizeof(long long)*N)==sizeof(long long)*N);

	// Calling functions
	C = percorri(N, L, D, P);

	// Writing output
	fprintf(fw, "%lld\n", C);

	fclose(fr);
	fclose(fw);
	return 0;
}
