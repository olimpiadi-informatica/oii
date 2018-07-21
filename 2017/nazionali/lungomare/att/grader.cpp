#include <cstdio>
#include <cassert>
#include <cstdlib>

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
	fscanf(fr, " %d %lld", &N, &L);
	D = (long long int*)malloc((N) * sizeof(long long int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %lld", &D[i0]);
	}
	P = (long long int*)malloc((N) * sizeof(long long int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %lld", &P[i0]);
	}

	// Calling functions
	C = percorri(N, L, D, P);

	// Writing output
	fprintf(fw, "%lld\n", C);

	fclose(fr);
	fclose(fw);
	return 0;
}
