#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector< pair<int,int> > voti;

int main(int argc, char** argv){
	assert(argc == 5);
	int N = atoi(argv[1]);	// Numero di mozzarelle
	int M = atoi(argv[2]);	// Voto massimo (0-M)
	int T = atoi(argv[3]);	// Tipo di generatore
	int S = atoi(argv[4]);	// Seed

	srand(S);

	switch(T) {
		case 1:
			for(int i=0; i<N; i++){
				voti.push_back( pair<int,int>( rand()%(M+1), rand()%(M+1) ) );
			}
			break;

		case 2:
			// Caso ad-hoc

			for (int i=0; i<(N/2); ++i) {
				voti.push_back( pair<int,int>( M, M-1 ) );
			}
			voti.push_back( pair<int,int>(M-1,M-3) );
			for (int i=1; i<(N/2); ++i) {
				voti.push_back( pair<int,int>( rand()%M, rand()%M ) );
			}

			random_shuffle( voti.begin(), voti.end() );

			break;
	}

	printf("%d\n", N);
	for (int i=0; i<N; ++i) {
		printf("%d %d\n", voti[i].first, voti[i].second);
	}
}
