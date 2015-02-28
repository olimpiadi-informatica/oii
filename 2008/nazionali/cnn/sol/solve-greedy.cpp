/* Soluzione greedy -- Alessio Orlandi

Giusto per vedere quanto funziona.
Assegna ogni elemento alla troupe che e' piu'
vicina.

*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

#define MaxN 10000
#define USE_X 0
#define USE_Y 1
#define MIN(a,b) ((a) < (b)) ? (a) : (b)

int x[MaxN], y[MaxN];
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
}

int solve(int write)
{
    int posX, posY;
    int cost = 0;
   
    posX = posY = 1;
    for(int i = 0; i< N; i++) 
    {
	const int diffX = abs(posX - x[i]);
	const int diffY = abs(posY - y[i]);

	if ( diffX < diffY ) { 
	     cost += diffX;
	     posX = x[i];
	     if ( write ) cout << "R" << endl;
	} else { 
	     cost += diffY;
	     posY = y[i];
	     if ( write ) cout << "C" << endl;
	}
    }
    
    return cost;
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

   if( argc > 1 && !strcmp(argv[1], "-q") )
      cout << solve(false) << endl;
   else
      cerr << solve(true) << endl;
      

   return 0;
}
