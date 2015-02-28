
using namespace std;
#include <iostream>
#include <map>
#include <cstdio>

struct cntsort_t {
   int data[10];
   int operator< ( const struct cntsort_t &other ) const {
       for (int i = 0; i < 10; i++)
           if ( data[i] < other.data[i] ) return true;
           else if ( data[i] > other.data[i] ) return false;
       return false;
   }

};



int
main()
{
    FILE * fin, *fout;
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif

    char input[150][150];
    cntsort_t sorted[150];
    // La soluzione migliore sarebbe una trie. Ma con 100 x 80 dubito migliori :)
    map < cntsort_t, int > numPerm;
    int N;

    fgets(input[0], sizeof(input[0]), fin);
    sscanf(input[0], "%d", &N);

     // Leggi stringa e countsorta.
    for(int i = 0; i < N; i++)
    {
       fgets(input[i], sizeof(input[i]), fin);

       for ( int j = 0;  j < 10; j++ ) sorted[i].data[j] = 0;
       for(int j = 0; input[i][j] >= '0' && input[i][j] <= '9'; j++)
          sorted[i].data[ input[i][j]-'0' ] ++;

       numPerm [ sorted[i] ] = numPerm[sorted[i]] + 1;
    }

    // E opla.. output!
    for ( int i = 0; i < N; i++ )
    {
#ifdef DEBUG
     fprintf(stderr, "numPerm[%d]   = %d ", i, numPerm[sorted[i]] );
     for(int j = 0; j < 10; j++) fprintf(stderr,"%d," , sorted[i].data[j]);
     fprintf(stderr,"\n");
#endif
     fputc ( input[i] [ numPerm [ sorted[i] ]  - 1] , fout);
    }
    fprintf(fout, "\n");

    fflush(fout);

}
