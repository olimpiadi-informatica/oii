/* Soluzione O(N^3) -- Alessio Orlandi

Si costruisce Cx[i][j] e Cy[i][j]

dove Cx[i][j] rappresenta il costo ottimo
di avere l'evento i assegnato a x e
avendo la troupe y ferma, tra tutti i precedenti,
sull'evento j.

Per calcolare tale valore, si provano tutte
le locazioni (piu' a destra) di x avendo j assegnato
a y, ovvero, Cy[j][k]; ai valori biosnga aggiungere
il mancante per coprire i rimanenti.

*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

#define MaxN 1000
#define USE_X 0
#define USE_Y 1
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
   cost[USE_X][1][0] = x[0]-1;
   cost[USE_Y][1][0] = y[0]-1;

   for(int i = 2; i <= N;  i++)
    for(int j = 0; j < i; j++)
    {
         int r = (j == 0 ? pi[USE_X][i] : INT_MAX );
	
	 for(int k = 0; k < j; k++)
	   r = MIN(r, cost[USE_Y][j][k] + dist(k,j+1,USE_X)+
	       pi[USE_X][i] - pi[USE_X][j+1]);

	 cost[USE_X][i][j] = r;

         r = (j == 0 ? pi[USE_Y][i] : INT_MAX );
	
	 for(int k = 0; k < j; k++)
	   r = MIN(r, cost[USE_X][j][k] + dist(k,j+1,USE_Y)+
	       pi[USE_Y][i] - pi[USE_Y][j+1]);

	 cost[USE_Y][i][j] = r;
    }

  int m = INT_MAX;
  for(int i = 0; i < N; i++)
    m = MIN(m, MIN(cost[USE_X][N][i], cost[USE_Y][N][i]));

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
