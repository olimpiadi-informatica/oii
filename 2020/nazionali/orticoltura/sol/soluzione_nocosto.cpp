/**
 * Complessità: Lineare a meno dell'ordinamento iniziale.
 * Descrizione: Identifichiamo un irrigatore col segmento [l,r] (di lunghezza
 * dispari) delle posizioni da lui raggiunte. Le seguenti due osservazioni sono
 * quelle fondamentali per la soluzione. Esiste una soluzione ottima tale che:
 *  1. Due irrigatori distinti sono distanti almeno 2C+2.
 *  2. Un buco di 2C+4 posizioni senza semi divide in due il problema.
 * Per gestire il da farsi nel caso di buchi 2C+2 e 2C+3 (che e' l'unica cosa
 * che resta da fare) si fa una bella dinamica.
 * A posteriori probabilmente basta e avanza fare una dinamica!
 * Autore: Federico Glaudo
 */

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

void posiziona(int D, int T);

void budget(int B);

void irriga(int C, int N, vector<int>& X, vector<int>& P)
{
    vector<pair<int, int>> seeds;
    vector<int> W(N), T(N);
    for (int i = 0; i < N; i++)
        seeds.push_back({ X[i] - (P[i] - 1), X[i] + (P[i] - 1) });
    sort(seeds.begin(), seeds.end());
    vector<pair<int, int>> vec;
    int cl = seeds[0].first, cr = seeds[0].second;
    for (int i = 1; i < N; i++) {
        if (seeds[i].first > 2 * (C + 1) + cr) {
            vec.push_back({ cl, cr });
            cl = seeds[i].first, cr = seeds[i].second;
        } else
            cr = max(cr, seeds[i].second);
    }
    vec.push_back({ cl, cr });
    N = vec.size();
    vec.push_back({ 1e9, 1e9 });
    vector<int> din[2];
    din[0].resize(N + 1), din[1].resize(N + 1);
    din[0][0] = 1, din[1][0] = 0;
    for (int k = 1; k <= N; k++) {
        int len = vec[k - 1].second - vec[k - 1].first + 1;
        int space = vec[k].first - vec[k - 1].second - 1;
        for (int e = 0; e < 2; e++) {
            din[e][k] = din[len % 2][k - 1] + (1 - e);
            if (space <= 2 * C + 3)
                din[e][k] = min(din[e][k], din[(len + space + e) % 2][k - 1] + space - (2 * C + 2));
        }
    }
    vec.pop_back();
    int num = 0;
    cl = vec.back().first, cr = vec.back().second;
    for (int k = N - 1; k >= 1; k--) {
        int e = (cr - cl + 1) % 2;
        int len = vec[k - 1].second - vec[k - 1].first + 1;
        if (din[e][k] == (1 - e) + din[len % 2][k - 1]) {
            W[num] = (cl + cr) / 2, T[num] = (cr - cl + 1) / 2 + 1;
            num++;
            cl = vec[k - 1].first, cr = vec[k - 1].second;
        } else
            cl = vec[k - 1].first;
    }
    W[num] = (cl + cr) / 2, T[num] = (cr - cl + 1) / 2 + 1;
    num++;

    int out = 0;
    for (int i = 0; i < num; i++) {
        out += C + T[i];
        posiziona(W[i], T[i]);
    }
    // budget(out);
}
