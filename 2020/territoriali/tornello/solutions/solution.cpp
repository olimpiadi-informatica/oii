#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int min = 0, max = 0, sum = 0, N;

        cin >> N;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            sum += x;
            min = std::min(min, sum);
            max = std::max(max, sum);
        }

        cout << "Case #" << t << ": " << max - min << endl;
    }
}