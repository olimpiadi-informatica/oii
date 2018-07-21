/*
 *  Soluzione subtask con tutto uguale.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: prova tutto, niente oppure una sola.
 */

#include <iostream>
#include <utility>

using namespace std;

long long percorri(int N, long long L, long long D[], long long P[]) {
    long long sol = max(D[0]+P[0], L-D[N-1]+P[N-1]);
    for (int i=1; i<N; i++)
        sol = max(sol, D[i]-D[i-1]+P[i]+P[i-1]);
    sol = min(sol, L);
    for (int i=0; i<N; i++)
        sol = min(sol, max(D[i], L-D[i])+P[i]);
    return sol;
}
