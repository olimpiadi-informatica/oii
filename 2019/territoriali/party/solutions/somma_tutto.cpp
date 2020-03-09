#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int N; cin >> N;
        int sum = 0;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            sum += x;
        }
        cout << "Case #" << t << ": " << sum << endl;
    }
}
