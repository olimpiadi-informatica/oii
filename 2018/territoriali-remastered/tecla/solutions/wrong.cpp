#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for(int caso = 1; caso <= t; caso++)
    {
        uint64_t n, m, a, b;
        cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
	}
        cout << "Case #" << caso << ":" << endl;
	cout << n << endl << 0;
	for (int i = 1; i < n; i++) {
		cout << " " << i;
	}
	cout << " " << 0 << endl;
    }
    return 0;
}
