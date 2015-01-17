/*
  Giorgio Audrito

  Prova tutte le permutazioni e verifica se formano un rettangolo quasi palindromo.
  Per provare tutte le permutazioni usa un pessimo algoritmo:
  genera tutte le sequenze e verifica se sono permutazioni.
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 16

char Words[MAXN][MAXN];
int Perm[MAXN];
int Count[MAXN];
int N, M;

int diff( char a, char b )
{
  if ( a == '0' || b == '0' ) return 0;
  return a == b ? 0 : 1;
}

int Verify()
{
  int i, j;

  for (i=0; i<N; i++)
    for (j=0; j<M-1-j; j++)
      if (diff( Words[Perm[j]][i], Words[Perm[M-1-j]][i] )) return 0;
  return 1;
}

void NextInt()
{
  int i;

  Perm[M-1]++;
  for (i=M-1; i>=0 && Perm[i]==M; Perm[--i]++) Perm[i] = 0;
}

int IsPermutation()
{
  int i;

  for (i=0; i<M; i++) Count[i] = 0;
  for (i=0; i<M; i++)
    {
      Count[Perm[i]]++;
      if ( Count[Perm[i]] > 1 ) return 0;
    }
  return 1;
}

void NextPermutation()
{
  NextInt();
  while ( IsPermutation() == 0 ) NextInt();
}

int main()
{
    FILE *fin, *fout;
    int i;

#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    assert(fscanf(fin, "%d %d", &N, &M ) == 2);
    assert(2 <= N && N <= 8);
    assert(2 <= M && M <= 8);
    for (i = 0; i < M; i++)
      {
        assert(fscanf(fin, "%s", Words[i] ) == 1);
        assert(Words[i][N] == 0);
      }

    for (i=0; i < M; i++) Perm[i] = i;
    while( 1 )
      {
	if ( Verify() )
	  {
	    for ( i=0; i<M; i++ )
	      fprintf(fout, "%s\n", Words[Perm[i]]);
	    return 0;
	  }
	NextPermutation();
      }
    return 0;
}
