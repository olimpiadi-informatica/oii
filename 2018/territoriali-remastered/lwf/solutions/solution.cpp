// Soluzione di lwf
// Autore: Edoardo Morassutto
// Complessità: O(N)
// Breve spiegazione:
//   Calcolo i numeri di Fibonacci fino ad N (incluso) e dal piu grande
//   li prendo gready se ci stanno in N e diminuisco.

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int fib[50];

void solve(int t) {
    int N;
    cin >> N;

    fib[0] = 1;
    fib[1] = 1;
    int i;
    for (i = 2; fib[i-1]+fib[i-2] <= N; i++) {
        fib[i] = fib[i-1]+fib[i-2];
    }
    i--;

    string s;
    while (i >= 0) {
        if (N >= fib[i]) {
            s += '1';
            N -= fib[i];
        } else {
            s += '0';
        }
        i--;
    }
    reverse(s.begin(), s.end());
    cout << "Case #" << t << ": " << s << endl;
}

int main() {
	int T; cin >> T;

	for (int t = 1; t <= T; t++)
		solve(t);
}
