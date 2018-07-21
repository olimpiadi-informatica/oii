/**
 *  Soluzione errata di caduta.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione: cerco il domino piu' alto in una posizione non-critica,
 *  e vedo se e' abbastanza alto per coprire la parte centrale di domino
 *  non cadono.
 */

#include <algorithm>

const int MAXN      = 10240000;
const int NONCRITIC = 0;

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

typedef enum {
    NESSUNO,
    UNO,
    MOLTI
} coperto_t;

struct twomax {
    int i1, i2;
    int max1 = -1, max2 = -1;
    
    void push(int x, int i) {
        if (x > max1) {
            i2 = i1;
            max2 = max1;
            i1 = i;
            max1 = x;
        }
        else if (x > max2)
            i2 = i;
            max2 = x;
    }
    
    int covered(int x) {
        if (max2 >= x) return MOLTI;
        if (max1 >= x) return i1;
        return NESSUNO;
    }
};

int hcritic[MAXN];
int primononcade, ultimononcade, maxnoncritic, imaxnoncritic;

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
    twomax idxs;
    idxs.push(altezze[0]-1, 0);
    for (int i=1; i<N; ++i) {
        int r = idxs.covered(i);
        switch (r) {
            case NESSUNO:
                ultimononcade = i;
                if (primononcade == 0) primononcade = i;
                break;
            case MOLTI:
                break;
            default:
                hcritic[r] = std::max(hcritic[r], i-r+1);
        }
        idxs.push(i+altezze[i]-1, i);
    }
    if (primononcade == 0) return OK;
    for (int i=0; i<N; ++i) if (hcritic[i] == NONCRITIC) {
        maxnoncritic = std::max(maxnoncritic, altezze[i]);
        imaxnoncritic = i;
    }
    if (primononcade+maxnoncritic-2 >= ultimononcade) {
        scambio->domino1 = imaxnoncritic;
        scambio->domino2 = primononcade-1;
        return RISOLTO;
    }
    return IMPOSSIBILE;
}
