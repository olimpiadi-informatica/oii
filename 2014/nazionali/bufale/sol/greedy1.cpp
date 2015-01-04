#include <algorithm>
#include <vector>
#define MAXN 10000000
using namespace std;

//long long solve(int N, int M[], int P[]){
//    long long tot = 0;
//    int j;
//    for(int i=0; i<N/2; i++){
//        j = max_element(M, M+N)-M;
//        tot += M[j];
//        M[j] = P[j] = -1;
//        j = max_element(P, P+N)-P;
//        tot += P[j];
//        M[j] = P[j] = -1;
//    }
//    return tot;
//}

int* M;
int* P;

inline bool less_than1(const int& a, const int& b)
{
    return M[a] > M[b] || (M[a] == M[b] && P[a] < P[b]);
}

inline bool less_than2(const int& a, const int& b)
{
    return P[a] > P[b] || (P[a] == P[b] && M[a] < M[b]);
}

long long solve(int N, int M_[], int P_[]){
    M = M_;
    P = P_;
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < N; i += 1)
    {
        a.push_back(i);
        b.push_back(i);
    }
    sort(a.begin(), a.end(), less_than1);
    sort(b.begin(), b.end(), less_than2);
    int idx_a = 0;
    int idx_b = 0;
    long long tot1 = 0;
    long long tot2 = 0;
    for (int i = 0; i < N/2; i += 1)
    {
        while (M[a[idx_a]] < 0) {
            idx_a += 1;
        }
        tot1 += M[a[idx_a]];
        M[a[idx_a]] *= -1;
        P[a[idx_a]] *= -1;
        while (P[b[idx_b]] < 0) {
            idx_b += 1;
        }
        tot1 += P[b[idx_b]];
        M[b[idx_b]] *= -1;
        P[b[idx_b]] *= -1;
    }
    for (int i = 0; i < N; i += 1)
    {
        P[i] *= -1;
        M[i] *= -1;
    }
    idx_a = 0;
    idx_b = 0;
    for (int i = 0; i < N/2; i += 1)
    {
        while (P[b[idx_b]] < 0) {
            idx_b += 1;
        }
        tot2 += P[b[idx_b]];
        M[b[idx_b]] *= -1;
        P[b[idx_b]] *= -1;
        while (M[a[idx_a]] < 0) {
            idx_a += 1;
        }
        tot2 += M[a[idx_a]];
        M[a[idx_a]] *= -1;
        P[a[idx_a]] *= -1;
    }
    return max(tot1, tot2);
}
