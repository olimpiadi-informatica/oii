#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;

vector<int> spiedino;

int main(int argc, char** argv){
    assert(argc == 6);
    int N = atoi(argv[1]);    // Numero di spiedini
    int K = atoi(argv[2]);    // Massima quantita' di frutta cattiva sopportabile
    int D = atoi(argv[3]);    // Densita' di spiedini buoni (in percentuale)
    int T = atoi(argv[4]);    // Tipo di generatore
    int S = atoi(argv[5]);    // Seed

    srand(S);

    if ( T == 0 ) {
        // Caso di esempio
        printf("11 9\n1 0 2 8 0 5 1 6 0 0 3\n");
    }
    else if ( T == 3 ) {
        // Input degenere
        printf("4 4\n4 0 9 9\n");
    }
    else if ( T == 4 ) {
        printf("4 4\n9 9 0 4\n");
    }
    else {
        int sum = 0;

        for (int i=0; i<N; i++) {
            if ( rand() % 100 < D ) {
                spiedino.push_back(0);
            }
            else {
                int f = rand() % 9 + 1;
                spiedino.push_back( f );
                sum += f;
            }
        }

        if ( T == 2 ) {
            // Generatore che sceglie K a posteriori
            K = rand() % sum;
        }

        printf("%d %d\n", N, K);
        for(int i=0; i<N; i++){
            printf("%d ", spiedino[i]);
        }
        printf("\n");
    }
}
