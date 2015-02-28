/* Pizzini - Input generator - Alessio Orlandi

Sintassi:

./pizzini_gen N minK maxK minR  seed >input.txt

N = numero di sequenze
minK, maxK = minima| massima lunghezza di una lunghezza, incluse
minR = minimo numero di anagrammi di una sequenza.

Prima si creano le sorgenti (ovvero le sequenze ordinate)
poi si genera la distribuzione del numero di perutazioni
poi le si crea e si permuta l'input.
Nell'ultima fase puo' esserci il problema che N venga diminuito
perche' rischia di aversi troppe permuazioni per l'ultimo
pizzini, per cui N , per quanto raramente su input grossi,
puo' essere cannato.


*/

#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

#define KLimit 80
#define NLimit 100

bool findstr(char **haystack, int startpos, int needle)
{
  for ( int i = startpos; i < needle; i++ )
    if ( !strcmp( haystack[i], haystack[needle] ) )
       return true;

  return false;
}

void
addperm ( char **where, int start, int *what, int itslen, int n)
{
   for(int i = 0; i < n; i++)
   {
      // Scrivi la stringa..
      where[start+i] = new char[1+itslen];
      int l = 0;
      for ( int j = 0; j < 10; j++ )
       for ( int k = 0; k < what[j]; k++)
         where[start+i][l++] = j+'0';

      // E poi permutala..
      do {
         char tmp;
         for ( int j = 0; j < itslen-1; j++)
         {
           int p = random() % (itslen-j) + j;
           if ( p != j )
           {
             tmp = where[start+i][j];
             where[start+i][j] = where[start+i][p];
             where[start+i][p] = tmp;
           }
         }
         where[start+i][itslen] = '\0';
      } while ( findstr(where, start, start+i) );
   }
}

int
main(int argc, char **argv)
{
    char *outfile[NLimit+1];
    int sources[NLimit+1][10];
    int explen[NLimit+1];

    if ( argc != 6 )
    {

     cerr << " Syntax: ./pizzini_gen N minK maxK minR  seed >input.txt " << endl;
     return 1;

    }

    int N, minK, maxK, minR, nSources, len;

    N = atoi(argv[1]);
    minK = atoi(argv[2]);
    maxK = atoi(argv[3]);
    minR = atoi(argv[4]);

    srandom(atol(argv[5]));


    if ( N > NLimit ) { cerr << " N troppo grande " << endl; return 1;}
    if ( minK > maxK ) { cerr << "minK e maxK sono invertiti?" << endl; return 1;}
    if ( maxK > KLimit || minK < 1 ) { cerr << "minK e maxK non in [1,80]" <<endl;return 1;}
    if ( minR > N ) { cerr << "minR maggiore di N"<<endl;return 1;}


    nSources = random() % (N / minR) + 1;
    cerr << "Numero sorgenti = " << nSources << endl;

    for ( int i = 0; i < nSources ; i ++ )
    {
      len = 0;
      explen[i] = random() % (maxK-minK+1) + minK;
      for (int j = 0; j < 10; j++ ) sources[i][j] = 0;
      while ( len < explen[i] )
      {
       sources[i][random() % 10] ++;
       len++;
      }
    }

    // Sto ignorando il fatto che possano capitarmi due counting sort uguali.. ma mi sembra talmente difficile
    // a meno di non mettere input cortissimi.


    // Scrivo le stringhe
    int extra = N  - nSources*minR;
#ifdef DEBUG
    cerr << "Extra = " << extra << endl;
#endif
    int j = 0;
    for(int i = 0; i < nSources-1; i++)
    {
      int cnt = 0;
      cnt = random() % (extra+1) + minR;
      if (cnt > explen[i]) cnt = explen[i];
#ifdef DEBUG
      cerr << cnt << " perms del pizzino " << i << endl;
#endif
      addperm ( outfile, j, sources[i], explen[i], cnt);
      extra -= cnt - minR;
      j += cnt;
    }

#ifdef DEBUG
    cerr << "L'ultimo e' candidato " << extra << "ed e' lungo " << explen[nSources-1] << endl;
#endif
    if ( minR+extra > explen[nSources-1] )
    {
       cerr << " ATTENZIONE! Meglio cambiare il seme, devo ridurre il numero di pizzini in output perche' l'ultimo e' corto."<<endl;
       extra = explen[nSources-1] - N;
       N = j + minR + extra;
    }
#ifdef DEBUG
    cerr << minR+extra << " perms del pizzino " << nSources-1 << endl;
#endif
    addperm ( outfile, j, sources[nSources-1], explen[nSources-1], minR+extra);

    // Permuto le stringhe in input
    char *tmp;
    cout << N << endl;
    for ( int i = 0; i < N-1; i++)
    {
        int p = random() % (N-i) + i ;
#ifdef DEBUG
        cerr << " swap " << i << " with " << p << endl;
#endif
        if ( p != i ) { tmp = outfile[i]; outfile[i] = outfile[p]; outfile[p] = tmp; }
        cout << outfile[i] << endl;
    }

    cout << outfile[N-1] << endl;
    return 0;
}
