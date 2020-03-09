#include <stdio.h>
#include <stdlib.h>
#include <cassert>

int alzati(int N, int M, int X[], int Y[]);

int main() {

  int N, M;

  assert(2==scanf("%d %d", &N, &M));

  int *X = (int*) malloc(M * sizeof(int));
  int *Y = (int*) malloc(M * sizeof(int));

  for(int i=0; i<M; i++)
    assert(2==scanf("%d %d", X+i, Y+i));

  printf("%d\n", alzati(N, M, X, Y));
  return 0;
}
