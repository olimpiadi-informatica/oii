#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

long long conta(int S, int s[], int P, int p[]);

int main() {
  int S, P;
  assert(2 == scanf("%d %d", &S, &P));

  int *s = (int*)malloc(S*sizeof(int));
  int *p = (int*)malloc(P*sizeof(int));

  for(int i=0; i<S; i++) assert(1 == scanf("%d", s+i));
  for(int i=0; i<P; i++) assert(1 == scanf("%d", p+i));

  printf("%lld\n", conta(S, s, P, p));
  return 0;
}

