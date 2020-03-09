/**
 * Descrizione: mette un irrigatore sopra ad ogni seme, con la potenza giusta
 * per coprire il seme.
 * Autore: Edoardo Morassutto
 * Complessità: O(N)
 */

#include <vector>

void posiziona(int D, int T);

void budget(int B);

void irriga(int C, int N, std::vector<int>& X, std::vector<int>& P)
{
    int out = 0;
    for (int i = 0; i < N; i++) {
        out += C + P[i];
        posiziona(X[i], P[i]);
    }
    budget(out);
}
