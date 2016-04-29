#include <iostream>
#include <vector>

std::vector<std::vector<int>> dyn;
std::vector<std::vector<int>> pyr;
int N;

int solve(int i, int j) {
    if (i == N-1) return pyr[i][j];
    if (dyn[i][j] != -1) return dyn[i][j];
    dyn[i][j] = pyr[i][j] + std::max(solve(i+1, j), solve(i+1, j+1));
    return dyn[i][j];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &N);
    dyn.resize(N);
    pyr.resize(N);
    for (unsigned i=0; i<N; i++) {
        for (unsigned j=0; j<=i; j++) {
            int a;
            scanf("%d", &a);
            pyr[i].push_back(a);
        }
        dyn[i].resize(i+1, -1);
    }
    printf("%d\n", solve(0, 0));
}
