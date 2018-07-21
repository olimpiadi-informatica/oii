#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#ifdef EVAL
#define NDEBUG
#define dprintf(...)
#else
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#endif

#include <cassert>

using namespace std;

typedef int parete_t;
#define SOPRA 1
#define DESTRA 2
#define SOTTO 3
#define SINISTRA 4

typedef struct {
	parete_t lato;
	int posizione;
} foro_t;

const int SIZE_MAX = 10000;
const int LOG_MAX = 40;

char dir2char[2][2] = { { '>', '<', }, { 'v', '^' } };

struct Raggio {
    int D; // direzione del raggio (0 = su-giu, 1 = destra-sinistra)
    int V; // verso del raggio (0 = sotto/destra, 1 = su/sinistra)
    int P; // r/c del raggio
    int S; // specchio da cui parte il raggio (-1 se entra)
    int E; // specchio su cui arriva il raggio (-1 se esce)
    
    void print() {
        dprintf("[%c], P=%d, (%2d -> %2d)\n", dir2char[D][V], P, S, E);
    }
    
};


struct Specchio {
    int P[2]; // P[0], P[1] = (y, x) = coordinate dello specchio
    int O; // O = diagonale dello specchio
};

vector<Specchio> specchi;

struct cmp {
    int d;
    
    bool operator()(int s, int t) {
        return specchi[s].P[1-d] < specchi[t].P[1-d];
    }
};

// S[0][y] = specchi lungo la r y da sinistra a destra
// S[1][x] = specchi lungo la c x dall'alto al basso
set<int, cmp> S[2][SIZE_MAX+1];

// D[0] = N, D[1] = M
int D[2];

Raggio inverti(Raggio r) {
    return { r.D, !r.V, r.P, r.E, r.S };
}

void inizia(int N, int M) {
	D[0] = N;
	D[1] = M;
	
	for(int d = 0; d < 2; d++) {
        for(int x = 0; x <= D[d]; x++) {
            S[d][x] = set<int, cmp>(cmp { d });
        }
    }
}

Raggio entra(int d, int v, int p) {
    auto& line = S[d][p];

    if(line.empty()) {
        return Raggio { d, v, p, -1, -1 };
    }

    int e;
    if(v == 0) {
        auto it = line.begin();
        e = it != line.end() ? *it : -1;
    } else {
        auto it = line.rbegin();
        e = it != line.rend() ? *it : -1;
    }

    return Raggio { d, v, p, -1, e };
}

Raggio propaga(int d, int v, int s) {
    dprintf("propaga(d=%d,v=%d,s=%d): ->  ", d, v, s);

    int p = specchi[s].P[d];
    auto& line = S[d][p];
    
    auto it = line.find(s);
    assert(it != line.end());

    int e;
    if(v == 0) {
        it++;
        e = (it != line.end() ? *it : -1);
    } else {
        e = (it != line.begin() ? *(--it) : -1);
    }

    Raggio r { d, v, p, s, e };
    
    r.print();
    
    return r;
}

Raggio rifletti(Raggio r) {
    assert(r.E != -1);
    
    Raggio rr = propaga(!r.D, r.V ^ specchi[r.E].O, r.E);
    r.print();
    dprintf("===>  ");
    rr.print();
    
    return rr;
}


void aggiungi(int r, int c, char diagonale) {
    r++;
    c++;
    int s = specchi.size();
    specchi.push_back({
        { r, c },
        (diagonale == '/' ? 1 : 0)
    });
    auto& specchio = specchi[s];

    dprintf("Inserisci specchio %d (P[0]=%d, P[1]=%d, O=%d):\n", s, specchio.P[0], specchio.P[1], specchio.O);

    int neighbor[2][2] = { {-1, -1}, {-1, -1} };
	for(int d = 0; d < 2; d++) {
	    int p = specchio.P[d];
        auto& line = S[d][p];
        assert(line.lower_bound(s) == line.upper_bound(s));
	    line.insert(s);
    }
}

foro_t calcola(foro_t ingresso) {
    ingresso.lato += 1;
    ingresso.posizione += 1;
    int d, v;
    switch(ingresso.lato) {
        case SINISTRA: d=0; v=0; break;
        case DESTRA: d=0; v=1; break;
        case SOPRA: d=1; v=0; break;
        case SOTTO: d=1; v=1; break;
    }
    int p = ingresso.posizione;
    
    dprintf("calcola: %c p=%d:\n", dir2char[d][v], p);
    
    Raggio r = entra(d, v, p);

    while(r.E != -1) {
        r = rifletti(r);
    }

    parete_t lati[2][2] = {
        { DESTRA, SINISTRA },
        { SOTTO, SOPRA },
    };

    dprintf("esce: ");
    r.print();
        
    // calcola il punto di uscita del raggio
	foro_t uscita;
	uscita.lato = lati[r.D][r.V];
	uscita.posizione = r.P;
	uscita.lato -= 1;
	uscita.posizione -= 1;
	return uscita;
}
