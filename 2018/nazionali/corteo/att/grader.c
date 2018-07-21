#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int pianifica(int N, int M, int P1, int D1, int P2, int D2, int A[], int B[]);

void sposta(int chi, int dove) {
	assert(chi == 1 || chi == 2);
	printf("%d %d\n", chi, dove);
}

int main() {
	int N, M, P1, D1, P2, D2, *A, *B, i;
	
	assert(2 == scanf("%d %d", &N, &M));
	assert(2 == scanf("%d %d", &P1, &D1));
	assert(2 == scanf("%d %d", &P2, &D2));
	
	A = (int*)malloc(M * sizeof(int));
	B = (int*)malloc(M * sizeof(int));

	for (i = 0; i < M; i++)
		assert(2 == scanf("%d %d", &A[i], &B[i]));
	
	printf("%d\n", pianifica(N, M, P1, D1, P2, D2, A, B));
}
