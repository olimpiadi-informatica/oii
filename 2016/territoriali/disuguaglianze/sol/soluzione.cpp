#include <bits/stdc++.h>

int main() {
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	unsigned N;
	std::string s;

	std::cin >> N >> s;

	unsigned min = 1, max = N;
	for (size_t i = 0; i < N-1; ++i) {
		if (s[i] == '<')
			std::cout << min++ << " ";
		else
			std::cout << max-- << " ";
	}

	assert(min == max);
	std::cout << min << std::endl;
}
