#include <list>

const int MAXN = 1000000;
std::list<int> divisori[MAXN + 1];

void Accendi(int N, int acceso[], int pulsante[]) {
	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j += i)
			divisori[j].push_back(i);

	for (int i = N; i >= 1; i--) {
		if (!acceso[i]) {
			pulsante[i] = true;

			for (const auto& j: divisori[i])
				acceso[j] ^= 1;
		}
	}
}