
/*
 * Soluzione di Giorgio per scuola
 *
 * Il problema 1 e' risolto analogamente a giovanni, soltanto riscritto.
 * Il problema 2 e' risolto con la soluzione "grafica" generale suggerita
 * da romeo, che funzionerebbe anche con N non potenza di due
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2560;

void p1( int N )
{
  int i,j;

  for (i=0; i<N; i++)
    {
      for (j=0; j<N; j++) printf( "%d %d ", j+1, (j+i)%N+1 );
      printf( "\n" );
    }
}

void p2( int N )
{
  int i,j;

  for (i=0; i<N-1; i++)
    {
      printf( "%d %d ", N, i+1 );
      for (j=1; j<N/2; j++) printf( "%d %d ", (i+j)%(N-1)+1, (i-j+N-1)%(N-1)+1 );
      printf( "\n" );
    }
}

int main() {

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, p;
	scanf("%d %d", &n, &p);

	if (p == 1) p1(n);
	if (p == 2) p2(n);

	return 0;
}

