/*
  Giorgio Audrito

  Innanzittutto calcola il costo per spostare tutti nella riga R,
  poi aggiunge (greedy) il costo per spostare l'i-esima truppa
  dal basso in posizione i
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 512

int Count[MAXN];
int N, R;

int main()
{
    FILE *fin, *fout;
    int i, j, Row, Col, SOL;

#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    assert(fscanf(fin, "%d", &N) == 1);
    assert(2 <= N && N <= 500);
    assert(fscanf(fin, "%d", &R) == 1);
    assert(0 < R && R <= N);
    R--;

    SOL = 0;
    for (i = 0; i < N; i++)
      {
        assert(fscanf(fin, "%d %d", &Row, &Col) == 2);
        assert(Row > 0 || Row <= N);
        assert(Col > 0 || Col <= N);
	Row--, Col--;
	SOL += abs( Row - R );
	Count[Col]++;
      }
    for (i = j = 0; i < N && j < N; )
      {
	if (Count[i] == 0) i++;
	else
	  {
	    SOL += abs( i - j );
	    Count[i]--;
	    j++;
	  }
      }
    fprintf(fout, "%d\n", SOL);
    return 0;
}
