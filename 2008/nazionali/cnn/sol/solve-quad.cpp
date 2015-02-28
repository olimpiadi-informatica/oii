/* Soluzione O(N^2) -- Alessio Orlandi

Innanzitutto si inserisca l'evento "0"
che e' l'origine.

Sia Dx[i,j] il costo di assegnare i ad x con
la y ferma all'elemento j. Allora da
j+1 a i tutti gli elementi sono coperti da x,
quindi per calcolarlo ci basta Dx[j+1,j].
Idem per la y.

Per ogni evento calcoliamo 4 possibili costi:
assegnarlo alla troupe X dato che il precedente
e' X o Y e lo stesso per Y.
Nel caso i 2 parametri siano identici possiamo
estendere la soluzione dall'evento precedente,
per cui:

Cx[i, x] = (* costo di assegnare i ad x dove i-1 e' assegnato ad x *)
= min { Cx[i-1,x], Cx[i-1,y] } + dist_x(i-1,i)

Invece se il precedente e' dell'altra troupe
allora dobbiamo cercare qual'e' la miglior
posizione per la x subito antecedente che
mi minimizza il costo. Sfruttiamo il fatto
che se scelgo k come valore precedente, 
allora posso estendere la soluzione per cui
k+1 e' di y e il precedente e' su x.

Cx[i,y] = min(k=0..i-1) Cy[k+1,x] + copertura_y(k+1,i-1) + dist_x(k,x)

Dove "copertura" e' il costo di fare da i-1 a k+1 con la y,
che possiamo tenerci in un array di somme prefisse di costi.

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

int cost[2][1+MaxN][2]; // cost [assegno alla x][l'elemento i][con il precedente sulla x]
int psum[2][1+MaxN]; // calcolo delle copertura <0,i> per ogni i, su x o su y

int solution[1+MaxN];
int choice[2][1+MaxN][2];

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

   psum[USE_X] [0] = 0; 
   psum[USE_Y] [0] = 0;
   for(int i = 1; i <= N; i++)
   {
      psum[USE_X][i] = psum[USE_X][i-1] + dist(i-1,i,USE_X); 
      psum[USE_Y][i] = psum[USE_Y][i-1] + dist(i-1,i,USE_Y); 
  }
     
}

/* Calcola C_r[i,r] e C_r[i,!r] */
inline void calc(int i, int coord, bool build )
{
    int inv = coord  == USE_X ? USE_Y : USE_X;
    int r = INT_MAX;
    int argmin = -1;

    for(int k = 0; k < i-1; k++ )
    {
       int c =  cost[inv][k+1][coord] + dist(k,i,coord) +
			psum[inv][i-1] - psum[inv][k+1];
	if ( c < r ) { r = c; argmin = k; }
    }
    cost[coord][i][inv] = r;
    choice[coord][i][inv] = argmin;

    if ( cost[coord][i-1][coord] < cost[coord][i-1][inv]) 
    { argmin = coord;
      cost[coord][i][coord] = cost[coord][i-1][coord] + dist(i-1,i,coord);
    } else {
      argmin = inv;
      cost[coord][i][coord] = cost[coord][i-1][inv] + dist(i-1,i,coord);
    }

    choice[coord][i][coord] = argmin;
}

int solve(bool build)
{
    cost[USE_X][0][USE_X] = cost[USE_X][0][USE_Y] = 0;
    cost[USE_Y][0][USE_X] = cost[USE_Y][0][USE_Y] = 0;
    cost[USE_X][1][USE_X] = cost[USE_X][1][USE_Y] = x[0]-1; 
    cost[USE_Y][1][USE_Y] = cost[USE_Y][1][USE_X] = y[0]-1; 

    for ( int i = 2; i <= N; i++ ) 
    {
	calc( i, USE_X, build );
	calc( i, USE_Y, build );
    }

    int best = INT_MAX;
    int argbest = -1;
    for ( int i = 0; i < 4; i++ ) 
     if ( cost[i >> 1][N][i % 2] < best ) 
     {  best = cost[i>>1][N][i%2];
        argbest = i; }


    // Costruzione della soluzione
    int p = argbest >> 1, q = argbest % 2;
    int i = N;
    while ( build && i > 0 ) 
       if ( p == q )  
       {  
          // Cx[i,x] o Cy[i,y]. Ho informazioni su quello
          // locale ma "choice" mi dice qual'e' il precedente.
          q = choice[p][i][q];
	  solution[i--] = p;
       } else {
          // Coordinate invertite, choice contiene
          // l'elemento precedente che ho scelto
          // sulla mia coordinata. Assegno tutti quelli
          // in mezzo all'altra.
          int limit = choice[p][i][q];
          solution[i--] = p;
          while ( i > limit + 1)
	    solution[i--] = q;
          p = 1-p; q = 1-q;         
       }
    return best;
}

int main(int argc, char **argv)
{
   istream & inf = cin;
   ostream & outf = cout;

   bool print = !(argc >1 && !strcmp(argv[1], "-q"));

   input (inf);

   if ( N == 0 )
   {
      outf << endl;
      return 0;
   }
   if (print)
   {
     solve(print) ;
     for(int i = 1; i <= N; i++ )  
	cout << (solution[i] == USE_X ? 'R' : 'C'  ) << endl;
   } else cout << solve(print) << endl;

   return 0;
}
