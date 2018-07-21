#include <algorithm>  // for std::swap
const int MAXID = 1000010, MAXN = 1<<20;

int N, rt[2*MAXN]; // range-tree
int id2pos[MAXID], ranking[MAXN], next[MAXN], prev[MAXN];

// Update the range tree disqualifying the pos-th contestant
void erase(int pos) {
    int it = MAXN+pos;
    while (it != 0) {
        rt[it]--;
        it >>= 1;
    }
}
// Find the index of the pos-th one
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
    // Initialize the array for every contestant initially in race
    for (int i = 0; i < N; i++) {
        id2pos[ids[i]] = i;
        ranking[i] = ids[i];
        next[i] = i+1;
        prev[i] = i-1;
        rt[MAXN+i] = 1;
    }
    // Initialize the range tree
    for (int i = MAXN-1; i >= 1; i--) rt[i] = rt[i<<1] + rt[(i<<1)|1];
}
void squalifica(int id) {
    // Find the rank indexes of the previous and the next
    // of the contestant we want to disqualify
    int pos = id2pos[id];
    int nxt = next[pos];
    int prv = prev[pos];
    // If they exist, update the previous and the next ones
    if (nxt >= 0) prev[nxt] = prv;
    if (prv < N) next[prv] = nxt;
    erase(pos); // Update the bitmask
}
// Find the indexes of the contestant and his next one and swap
void supera(int id1) {
    int pos1 = id2pos[id1];
    int pos2 = prev[pos1];
    int id2 = ranking[pos2];
    std::swap(id2pos[id1], id2pos[id2]);
    std::swap(ranking[pos1], ranking[pos2]);
}
// Find the index of the pos-th one in the bitmask and return
int partecipante(int pos) {
    int rank = pos2rank(pos);
    return ranking[rank];
}
