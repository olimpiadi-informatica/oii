#include <algorithm>
#define MAXN 10000000
using namespace std;

int D[MAXN];
long long solve(int N, int M[], int P[]){
    long long tot = 0;
    for(int i=0; i<N; i++){
        D[i] = M[i] - P[i];
        tot += M[i] + P[i];
    }
    sort(D, D+N);
    for(int i=0; i<N/2; i++) tot -= D[i];
    for(int i=N/2; i<N; i++) tot += D[i];
    return tot/2;
}
