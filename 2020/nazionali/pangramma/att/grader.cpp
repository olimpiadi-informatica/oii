#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int conta(int N, int K, vector<int>& V);

int main() {
    // Input da file:
    // freopen("input.txt", "r", stdin);

    // Output su file:
    // freopen("output.txt", "w", stdout);

    size_t n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(size_t i = 0; i < n; i++) {
        cin >> v[i];
    }
    cout << conta(n, k, v) << endl;
    return EXIT_SUCCESS;
}
