#include <bits/stdc++.h>

int main() {
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	unsigned N;
	std::string s;

	std::cin >> N >> s;

	std::vector<size_t> permutazione(N);
	std::iota(permutazione.begin(), permutazione.end(), 1);

	do {
		bool ok = true;
		for (size_t i = 0; i < N - 1 && ok; ++i) {
			ok &= (
				(s[i] == '<' && permutazione[i] < permutazione[i + 1]) ||
				(s[i] == '>' && permutazione[i] > permutazione[i + 1])
			);
		}

		if (ok) {
			for (const auto& elem: permutazione)
				std::cout << elem << " ";
			std::cout << std::endl;
			exit(0);
		}
	} while (std::next_permutation(permutazione.begin(), permutazione.end()));
}