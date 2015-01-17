/*
  Giorgio Audrito

  Per ogni divisore primo p di N dal piu` piccolo, effettua una
  ricerca binaria per capire con quale esponente minimo si ha una
  periodicita`.
  Complessita` O(n^(1/2)) per la scomposizione, poi per la ricerca
  O(sum_i log(e_i)) = O(log( prod_i (e_i) )) = O(log(d)) con d numero
  di divisori, moltiplicato per il singolo check O(n).
*/

#include <stdio.h>
#include <assert.h>

#define MAXN 102400
#define MAXP 8

int s[MAXN];
int primes[MAXP][2];
int nprimes;
int N, Per;

int esp( int a, int b )
{
  int r;

  if ( b == 0 ) return 1;
  r = esp( a, b/2 );
  r *= r;
  if ( b % 2 == 1 ) r *= a;
  return r;
}

void scomponi()
{
  int p, m;

  nprimes=0;
  m=N;
  for ( p=2; p*p<m; p++ )
    if ( m % p == 0 )
      {
	primes[nprimes][0] = p;
	primes[nprimes][1] = 0;
	for ( ; m % p == 0; primes[nprimes][1]++ ) m = m/p;
	nprimes++;
      }
  if ( m != 1 )
    {
      primes[nprimes][0] = m;
      primes[nprimes][1] = 1;
      nprimes++;
    }
}

int check(int k)
{
  int i;

  for (i = k; i < N; ++i)
    if (s[i-k] != s[i])
      return 0;
  return 1;
}

int bsearch( int pi, int e1, int e2 )
{
  int nper;

  if ( e1 == e2 ) return e1;
  nper = Per / esp(primes[pi][0], primes[pi][1] - (e1 + e2)/2);
  if ( check( nper ) )
    {
      primes[pi][1] = (e1+e2)/2;
      Per = nper;
      return bsearch( pi, e1, (e1+e2)/2 );
    }
  else
    {
      return bsearch( pi, (e1+e2)/2+1, e2 );
    }
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
    assert(fscanf(fin, "%d", &N) == 1);
    assert(2 <= N && N <= 100000);

    for (i = 0; i < N; ++i)
      {
        assert(fscanf(fin, "%d", s+i) == 1);
        assert(s[i] == 0 || s[i] == 1);
      }

    scomponi();
    Per = N;
    for (i = 0; i < nprimes; i++ )
      {
	bsearch(i, 0, primes[i][1]);
      }
    if ( Per == N ) fprintf(fout, "2\n");
    else
      {
	for ( i=0; i<Per; i++ )
	  fprintf(fout, "%d ", s[i]);
	fprintf(fout, "\n");
      }
    return 0;
}
