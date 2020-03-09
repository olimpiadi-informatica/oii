#include <iostream>
#include <string>

using namespace std;

void solve(int t) {
    int N1, N2, N3, N4;
    cin >> N1 >> N2 >> N3 >> N4;

    int M;
    cin >> M;

    string F1, F2, F3, F4;
    cin >> F1 >> F2 >> F3 >> F4;

    for (int i = 0; i + M <= N1; i++)
    for (int j = 0; j + M <= N2; j++)
    for (int k = 0; k + M <= N3; k++)
    for (int l = 0; l + M <= N4; l++) {
	bool match = true;

        for (int m = 0; m < M; m++)
            if (F1[i + m] != F2[j + m] || F2[j + m] != F3[k + m] || F3[k + m] != F4[l + m])
                match = false;

	if (match) {
            cout << "Case #" << t << ": " << i << " " << j << " " << k << " " << l << endl;
	    return;
	}
    }
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }
}
