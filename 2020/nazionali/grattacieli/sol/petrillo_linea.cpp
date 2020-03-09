#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> ii;

long long int costruisci(int N, int M, vector<long long>& H, vector<int>& A, vector<int>& B, vector<int>& C)
{
    vector<int> weights;
    weights.assign(N, 0);

    for(int i = 0; i < A.size(); i++) {
      weights[A[i]] = C[i];
      // assert(A[i] + 1 == B[i]);
    }

    ll height = H[0];
    ll sol = height;
    for(int i = 0; i < N-1; i++)
    {
      height = min(height + weights[i], H[i + 1]);
      sol += height;
    }

    return sol;
}
