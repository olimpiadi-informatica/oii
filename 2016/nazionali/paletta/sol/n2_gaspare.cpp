/**
 *  Soluzione di paletta
 *
 *  Autore: Gaspare Ferraro
 *
 *  Descrizione: O(N^2)
 */
 
#include <vector>
using namespace std;


long long paletta_sort(int N, int v[]) {
    long long res = 0 ;    
    vector<int> V[2] ;

    for( int i = 0 ; i < N ; i++ ) 
    {
        int tmp = v[i];
        if( i%2 != tmp%2 ) return -1 ;  // Non ordinabile 
        V[i%2].push_back(tmp);
    }
    
    for( int p = 0 ; p < 2 ; p++ )
    {
        int i = 0 , flag = 1 ;
        while( i < V[p].size() && flag )
        {
            flag = 0 ;
            for( int j = i ; j < V[p].size()-1; j++ )
            {
                if( V[p][j] > V[p][j+1] )
                {
                    swap( V[p][j], V[p][j+1] );
                    flag = 1 ;
                    res++ ;
                }
            }        
        }
    }

    return res ; 
}

