#include <iostream>
#include <vector>

std::vector<std::vector<int>> pyr;
int N;

int solve(int i, int j) {
    if (i == N-1) return pyr[i][j];
    int nextj = j;
    if (pyr[i+1][j] < pyr[i+1][j+1]) nextj = j+1;
    return pyr[i][j] + solve(i+1, nextj);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &N);
    pyr.resize(N);
    for (unsigned i=0; i<N; i++) {
        for (unsigned j=0; j<=i; j++) {
            int a;
            scanf("%d", &a);
            pyr[i].push_back(a);
        }
    }
    printf("%d\n", solve(0, 0));
}
