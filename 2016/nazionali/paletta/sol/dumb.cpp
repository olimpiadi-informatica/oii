/**
 *  Soluzione lenta di paletta: O(NR)
 *
 *  Autore: Giorgio
 *
 *  Descrizione: cerca uno scambio fattibile e poi lo fa.
 */

#include <utility>
using namespace std;

long long paletta_sort(int N, int V[]) {
    int i;
    long long count = 0;
	
	
	while(1) {
	    for (i=0; i<N-2; i++) {
	        if (V[i] > V[i+2]) {
	            swap(V[i], V[i+2]);
	            count++;
	            break;
	        }
	    }
		if (i == N-2) break;
	}
	
    for (int i=0; i<N-1; i++) if (V[i] > V[i+1]) return -1;
    return count;
}
