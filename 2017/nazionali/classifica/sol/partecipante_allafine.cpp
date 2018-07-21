/*
 *  Soluzione di classifica.
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Tiene una lista con links a precedente e successivo e alla prima chiamata a partecipanti trasforma la lista in un array.
 */

#include <vector>
using namespace std;

const int MAXN = 1000000;

int N;

int prec[MAXN+1];
int succ[MAXN+1];

bool partecipante_chiamato = false;
vector <int> classifica;


void inizia(int N, int ids[]) {
    ::N = N;
    for (int i = 0; i < N; i++) {
        if (i >= 1) prec[ids[i]] = ids[i-1];
        else {
            prec[ids[i]] = N;
            succ[N] = ids[i];
        }
        
        if (i <= N-2) succ[ids[i]] = ids[i+1];
        else {
            succ[ids[i]] = N;
            prec[N] = ids[i];
        }
    }
}

void supera(int id) {
    int id_prec, id_precprec, id_succ;
    id_prec = prec[id];
    id_precprec = prec[id_prec];
    id_succ = succ[id];
    
    succ[id_precprec] = id;
    prec[id_prec] = id;
    succ[id_prec] = id_succ;
    prec[id] = id_precprec;
    succ[id] = id_prec;
    prec[id_succ] = id_prec;
}

void squalifica(int id) {
    int id_prec, id_succ;
    id_prec = prec[id];
    id_succ = succ[id];
    succ[id_prec] = id_succ;
    prec[id_succ] = id_prec;
}

int partecipante(int pos) {
    if (!partecipante_chiamato) {
        int id_at = succ[N];
        while (id_at != N) {
            classifica.push_back(id_at);
            id_at = succ[id_at];
        }
        partecipante_chiamato = true;
    }
    return classifica[pos-1];
}


