#include <cassert>
#include <vector>

using namespace std;

const int MOD = 46337;

int conta(int N, int K, vector<int>& V) {
    vector<int> C(K); // counts of letters
    int M = K; // missing letters
    int P = 1; // product of non-zero factors in C
    int L = N; // minimum length of a pangram
    int sol = 0;
    
    int a = 0, b =0; // [a,b) candidate pangram
    while (b <= N) {
        if (M > 0) {
            if (++C[V[b]] == 1) --M;
            else P = P/(C[V[b]]-1)*C[V[b]];
            ++b;
        } else {
            assert(C[V[b-1]] == 1);
            if (--C[V[a]] == 0) { // pangram found
                if (b-a == L) sol+=P;
                if (b-a <  L) sol=P, L=b-a;
                ++M;
                sol %= MOD;
            }
            else P = P/(C[V[a]]+1)*C[V[a]];
            ++a;
        }
        assert(P <= 1000000000);
    }
    return sol;
}
