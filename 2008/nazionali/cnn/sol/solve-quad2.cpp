/* Soluzione O(N^2) -- Alessio Orlandi

(questa versione e' in realta' un'evoluzione
furba della cubica. La soluzione "quad" e'
sicuramente piu' furba.)

Ragioniamo sulla seguente questione, rispetto
alla cubica:

se i = j+1, allora Cx[i][j] = min (k=[0,j) )
	Cy(j,k) + delta_x ( k, i );

-- ovvero fissata una y cerco la miglior
   x precedente -- 

altrimenti, visto che quel che conta e' dove 
"atterro" subito dopo j sulla x ( che e' sempre
j + 1 ) e poi il resto lo copro pedestremente.

Per cui mi basta calcolare Cx[i,i-1] e
per ogni j = i-1, k > i devo solo completare sulla X.
Quindi, N^2 conti.


*/

#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>

using namespace std;

#define MaxN 1000
#define USE_X 0
#define PRED_X 0
#define USE_Y 1
#define PRED_Y 1
#define MIN(a,b) ((a) < (b)) ? (a) : (b)

int x[MaxN], y[MaxN];
int cost[2][1+MaxN][1+MaxN];
int pred[2][1+MaxN];
int pi[2][1+MaxN];

int N, M;

inline int abs(int i)
{
  return i >= 0? i : -i;
}

inline int dist(int i, int j, int coord)
{
   --i, --j;
   return ( coord == USE_X ? 
      abs( ( i <= -1 ? 1 : x[i] ) - x[j] ) : 
      abs( ( i <= -1 ? 1 : y[i] ) - y[j] ));
}

void input(istream& inf)
{
   inf >> N >> M;

   for(int i = 0; i < N; i++) 
     inf >> x[i] >> y[i];

   pi[USE_X] [0] = 0; pi[USE_X][1] = x[0]-1;
   pi[USE_Y] [0] = 0; pi[USE_Y][1] = y[0]-1;
   for(int i = 2; i <= N; i++)
   {
      pi[USE_X][i] = pi[USE_X][i-1] + dist(i-1,i,USE_X); 
      pi[USE_Y][i] = pi[USE_Y][i-1] + dist(i-1,i,USE_Y); 
  }
     
}


int solve()
{
     cost[USE_X][0][0] = cost[USE_Y][0][0] = 0;

     for ( int i = 1; i <= N; i++)
     {
	cost[USE_X][i][0] = pi[USE_X][i];
        cost[USE_Y][i][0] = pi[USE_Y][i];
     } 


     for ( int j = 1 ; j < N; j++)   
     {
        int r = INT_MAX;
	for(int k = 0; k < j; k++)
	   r = MIN ( r,cost[USE_Y][j][k] + dist(k,j+1,USE_X) );

        cost[USE_X][j+1][j] = r;
	
	for ( int i = j + 2 ; i <= N; i++)
		cost[USE_X][i][j] = cost[USE_X][i-1][j] + dist(i-1,i,USE_X);

        r = INT_MAX;
        for(int k = 0; k < j; k++)
           r = MIN ( r, cost[USE_X][j][k] + dist(k,j+1,USE_Y) );
        
        cost[USE_Y][j+1][j] = r;
     
        for ( int i = j + 2 ; i <= N; i++)
                cost[USE_Y][i][j] = cost[USE_Y][i-1][j] + dist(i-1,i,USE_Y);
     }
        
 
     int m = INT_MAX;
     for(int i = 0; i < N; i++)
	m = MIN ( m, MIN ( cost[USE_X][N][i] , cost[USE_Y][N][i]) );

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
