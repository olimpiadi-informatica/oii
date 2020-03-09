#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, F, C;
        cin >> N >> C >> F;
        cout << "Case # " << t << ": " << N/F << " " << (N%F)/C << endl;
    }
}
