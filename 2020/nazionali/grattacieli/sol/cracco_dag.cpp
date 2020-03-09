#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long ll;
typedef pair<long long, long long> ii;
vector<vector<ii>> nodes;

long long int costruisci(int N, int M, vector<long long>& H, vector<int>& A, vector<int>& B, vector<int>& C)
{
  vector<vector<ii>> nodes;
  nodes.assign(N, vector<ii>());

  for(int i = 0; i < A.size(); i++)
    nodes[A[i]].push_back({B[i], C[i]});

  for(int i = 0; i < N; i++)
  {
    for (auto [node, diff] : nodes[i]) {
      H[node] = min(H[node], H[i] + diff);
    }
  }

  return accumulate(H.begin(), H.end(), 0LL);
}
