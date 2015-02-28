/* Soluzione O(NM^2) di Roberto -- Alessio Orlandi
 *
 * Teniamo due matrici:
 * Cx[i,r] e Cy[i,c] 
 *
 * che rappresentano assegnare l'i-esimo (dei primi i) eventi
 * a x, avendo y sulla riga r.
 *
 * Cx[i,c] si calcola o partendo da Cx[i-1,c] (nel qual caso bisogna
 * solo spostare la x) oppure da Cy[i-1,r], minimizzando su r.
 * 
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

#define MaxN 10000
#define MaxM 1000
#define USE_X 0
#define USE_Y 1
#define MIN(a,b) ((a) < (b)) ? (a) : (b)

int x[MaxN], y[MaxN];
int cost[2][MaxN+1][MaxM+1];
int N, M;

inline int abs(int i)
{
  return i >= 0? i : -i;
}

inline int dist(int i, int j, int coord)
{
   return ( coord == USE_X ? 
      abs( ( i <= -1 ? 1 : x[i] ) - x[j] ) : 
      abs( ( i <= -1 ? 1 : y[i] ) - y[j] ));
}

void input(istream& inf)
{
   inf >> N >> M;

   for(int i = 0; i < N; i++) 
     inf >> x[i] >> y[i];
}

int solve()
{

    for ( int i = 0; i <= N; i++ ) 
      for ( int j = 0; j <= M; j++ ) 
       cost[USE_X][i][j] = cost[USE_Y][i][j] = INT_MAX;

    
    for ( int c = 1; c<= M; c++) 
    {
       cost[USE_X][0][c] = x[0]+c-2;
       cost[USE_Y][0][c] = y[0]+c-2;
    }

    for ( int i = 1; i < N; i++ )    
    { 
       for ( int c = 1; c <= M; c++ ) 
       {
	 cost[USE_X][i][c] = cost[USE_X][i-1][c] + dist(i-1,i,USE_X);
         for ( int r = 1; r <= M; r++ ) 
	    cost[USE_X][i][c] = MIN ( cost[USE_X][i][c],
                cost[USE_Y][i-1][ r ]+ abs(r -x[i])+abs(c-y[i-1]) );
       }
  
       for ( int r = 1; r <= M; r++ ) 
       {
	 cost[USE_Y][i][r] = cost[USE_Y][i-1][r] + dist(i-1,i,USE_Y);
         for( int c = 1; c <= M; c++ ) 
	   cost[USE_Y][i][r] = MIN ( cost[USE_Y][i][r], 
   	    cost[USE_X][i-1][ c ]+ abs(c-y[i]) + abs(r-x[i-1]) );
       }
      
    }

    int m = INT_MAX;
    for ( int i = 1; i <= M; i++ )
       m = MIN ( m, MIN ( cost[USE_X][N-1][i] , cost[USE_Y][N-1][i]) );

   return m;
}
   

int main(int argc, char **argv)
{
   istream & inf = cin;
   ostream & outf = cout;

   input (inf);

   if ( N == 0 )
   {
      outf << endl;
      return 0;
   }

   cout << solve() << endl;
      

   return 0;
}
