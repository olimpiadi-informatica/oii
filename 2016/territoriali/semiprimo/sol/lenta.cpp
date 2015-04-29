#include <iostream>

// Ritorna true se Q è primo, false altrimenti
bool primo(unsigned Q) {
    if (Q < 2)
        return false;
    for (unsigned divisore = 2; divisore * divisore <= Q; ++divisore)
        if (Q % divisore == 0)
            return false;
    return true;
}

// Ritorna il più piccolo divisore primo di N
unsigned trova_D(unsigned N) {
    for (unsigned D = 2; D * D <= N; ++D)
        if (N % D == 0)
            return D;
    return N;
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    unsigned N;
    std::cin >> N;

    unsigned D = trova_D(N);
    if (primo(N/D))
        std::cout << D << " " << N/D << std::endl;
    else
        std::cout << -1 << std::endl;
}
