/**
 *  Soluzione di paletta
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: O(NlogN) - Merge Sort
 */
 
#include <vector>
#include <stdio.h>
using namespace std;
#define MAXN 1500000

vector<int> V[2][2] ;
int N , bit = 0 ;
int left,right,fine, p = 0;
long long res = 0 ;

inline int min(int a, int b){ return a < b ? a : b ; } 

void merge()
{
	int l = left ;
    int r = right ;
	for( int i = left ; i < fine ; i++ )
    {
		if(  ( V[p][bit][l] <= V[p][bit][r] && l < right  ) || r >= fine  )
        {
            V[p][1-bit][i] = V[p][bit][l++] ;
        }
		else
        {
            res += (long long)(right - l);
            V[p][1-bit][i] = V[p][bit][r++] ;
        }
    }
}

long long paletta_sort(int N, int v[]) 
{
    for( int i = 0 ; i < N ; i++ ) 
    {
        int tmp = v[i];
        if( i%2 != tmp%2 ) return -1 ;  // Non ordinabile 
        V[i%2][0].push_back(tmp);
        V[i%2][1].push_back(tmp);
    }
    
    for( p = 0 ; p < 2 ; p++ )
    {
	    for( int w = 1 ; w < V[p][bit].size() ; w <<= 1, bit = 1-bit  )
        {	    
            for( int i = 0 ; i < V[p][bit].size() ; i += w<<1 )
            {
                left  = i ;
                right = min(i+w, V[p][bit].size());
                fine   = min(i+(w<<1), V[p][bit].size() );
                merge();
            }
        }
    }
    return res ; 
}

