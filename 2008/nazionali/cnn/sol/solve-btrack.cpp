/** Soluzione per  Branch&Bound classico -- Alessio Orlandi
 * Prima uso la greedy per darmi un bound, e poi vado di b&b.
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
int N, M;
int minCost = INT_MAX;
int minSolution[MaxN];

inline int abs(int i)
{
  return i >= 0? i : -i;
}

inline int dist(int i, int j, int coord)
{
   return ( coord == USE_X ? 
      abs( ( i == -1 ? 1 : x[i] ) - x[j] ) : 
      abs( ( i == -1 ? 1 : y[i] ) - y[j] ));
}

int greedy()
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
	     minSolution[i] = USE_X;
	} else { 
	     cost += diffY;
	     posY = y[i];
	     minSolution[i] = USE_Y;
	}
    }
    
    return cost;
}

void input(istream& inf)
{
   inf >> N >> M;

   for(int i = 0; i < N; i++) 
     inf >> x[i] >> y[i];
}


int solve(int currX, int currY, int i, int cost, int composition[])
{
   if ( cost > minCost ) return 0 ;

   if ( i == N ) { 
     if ( cost < minCost ) { 
 	 minCost = cost;
	 memcpy( minSolution, composition, sizeof(int)*N);
     }
     return 1;
   }

   composition[i] = USE_X;
   solve(x[i], currY, i+1, cost + abs(currX-x[i]), composition);
   composition[i] = USE_Y;
   solve(currX, y[i], i+1, cost + abs(currY-y[i]), composition);
   return 0;
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

   bool quiet =  ( argc > 1 &&  !strcasecmp(argv[1], "-q")  ) ;

   solve(1,1,0,0, new int[MaxN]);

   if ( quiet ) 	
	 cout << minCost << endl;
   else
   {
 	cerr << minCost << endl;
	for(int i = 0; i < N; i++) 
	   cout << (minSolution[i] == USE_X ? 'R' : 'C') << endl;
   }  

   return 0;
}
