#include <algorithm>  // per std::swap
const int MAXID = 1000010, MAXN = 1<<20;

int N, rt[2*MAXN]; // range-tree
int id2pos[MAXID], classifica[MAXN], successivo[MAXN], precedente[MAXN];

// Aggiorno il range tree squalificando il concorrente pos-esimo
void azzera(int pos) {
    int it = MAXN+pos;
    while (it != 0) {
        rt[it]--;
        it >>= 1;
    }
}
// Trova l'indice del pos-esimo 1
int pos2rank(int pos) {
    int it = 1;
    while (it < MAXN) {
        if (rt[it<<1] < pos) {
            pos -= rt[it<<1];
            it = (it<<1)|1;
        }
        else it = it<<1;
    }
    return it-MAXN;
}
void inizia(int N, int* ids) {
    ::N = N;
    // Inizializzo gli array per ogni concorrente inizialmente in gara
    for (int i = 0; i < N; i++) {
        id2pos[ids[i]] = i;
        classifica[i] = ids[i];
        successivo[i] = i+1;
        precedente[i] = i-1;
        rt[MAXN+i] = 1;
    }
    // Inizializzo range tree
    for (int i = MAXN-1; i >= 1; i--) rt[i] = rt[i<<1] + rt[(i<<1)|1];
}
void squalifica(int id) {
    // Ritrovo gli indici in classifica del precedente e successivo
    // del concorrente che vogliamo eliminare
    int pos = id2pos[id];
    int succ = successivo[pos];
    int prec = precedente[pos];
    // Se esistono, aggiorno precedente e successivo
    if (prec >= 0) successivo[prec] = succ;
    if (succ < N) precedente[succ] = prec;
    azzera(pos); // Aggiorno la bitmask
}
// Trovo gli indici corretti del concorrente e del suo successivo in classifica
// infine scambio i valori in classifica e posizione
void supera(int id1) {
    int pos1 = id2pos[id1];
    int pos2 = precedente[pos1];
    int id2 = classifica[pos2];
    std::swap(id2pos[id1], id2pos[id2]);
    std::swap(classifica[pos1], classifica[pos2]);
}
// Ritrovo l'indice del pos-esimo "1" nella bitmask e stampo il concorrente richiesto
int partecipante(int pos) {
    int rank = pos2rank(pos);
    return classifica[rank];
}
