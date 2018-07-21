#include <vector>
#include <set>
#include <unordered_map>
#include <cassert>

typedef int parete_t;
#define SOPRA 1
#define DESTRA 2
#define SOTTO 3
#define SINISTRA 4
typedef struct { parete_t lato; int posizione; } foro_t;

parete_t rifletti(char d, parete_t dir) {
	if (d == '\\') {
		if (dir == SOPRA) return DESTRA;
		if (dir == DESTRA) return SOPRA;
		if (dir == SOTTO) return SINISTRA;
		if (dir == SINISTRA) return SOTTO;
	} else {
		if (dir == SOPRA) return SINISTRA;
		if (dir == DESTRA) return SOTTO;
		if (dir == SOTTO) return DESTRA;
		if (dir == SINISTRA) return SOPRA;
	}
}

const char* strlato(parete_t lato) {
    if (lato == SOPRA)    return "   SOPRA";
    if (lato == SOTTO)    return "   SOTTO";
    if (lato == SINISTRA) return "SINISTRA";
    if (lato == DESTRA)   return "  DESTRA";
    assert(false);
}

struct face_t {
    int r, c;
    parete_t lato;
    char type;
    bool operator<(const face_t& other) const {
        assert((lato + other.lato) % 2 == 0);
        if (lato == SOPRA || lato == SOTTO) {
            assert(c == other.c);
            if (r < other.r) return true;
            if (r > other.r) return false;
            return lato == SOPRA && other.lato == SOTTO;
        } else {
            assert(r == other.r);
            if (c < other.c) return true;
            if (c > other.c) return false;
            return lato == SINISTRA && other.lato == DESTRA;
        }
    }
    bool operator==(const face_t& other) const {
        return r == other.r && c == other.c && lato == other.lato;
    }

    void print(const char* term = "\n") {
        fprintf(stderr, "%s % 2d % 2d %c%s", strlato(lato), r, c, type, term);
    }
};

int N, M;
std::vector<std::vector<std::array<face_t, 4>>> next;

void init() {
    next.resize(N+2);
    for (int i=0; i<N+2; i++) {
        next[i].resize(M+2);
    }
}

void create(face_t) {
    // Nothing to do in the "mirror jump" version
}

void split(face_t a, face_t b) {
    // Nothing to do in the "mirror jump" version
}

void attach(face_t f, face_t to) {
    /*fprintf(stderr, " f: "); f.print();
    fprintf(stderr, "to: "); to.print();
    fprintf(stderr, "----\n");*/
    next[f.r][f.c][f.lato-1] = to;
    next[to.r][to.c][to.lato-1] = f;
}

void join(face_t a, face_t b) {
    // Nothing to do in the "mirror jump" version
}

face_t other_end(face_t cur) {
    while (true) {
        //fprintf(stderr, "cur: "); cur.print();
        cur = next[cur.r][cur.c][cur.lato-1];
        if (cur.type == '-' || cur.type == '|') break;
        cur.lato = rifletti(cur.type, cur.lato);
    }
    //fprintf(stderr, "cur: "); cur.print();
    return cur;
}

std::vector<std::set<face_t>> rows;
std::vector<std::set<face_t>> columns;

void inizia(int N, int M) {
    ::N = N; ::M = M;
    init();
    rows.resize(N+2);
    columns.resize(M+2);
    for (int i=0; i<N; i++) {
        face_t s{i+1, 0, SINISTRA, '|'};
        face_t d{i+1, M+1, DESTRA, '|'};
        rows[i+1].insert(d);
        rows[i+1].insert(s);
        create(d);
        attach(s, d);
    }
    for (int i=0; i<M; i++) {
        face_t u{0, i+1, SOPRA, '-'};
        face_t d{N+1, i+1, SOTTO, '-'};
        columns[i+1].insert(u);
        columns[i+1].insert(d);
        create(u);
        attach(u, d);
    }
}


void aggiungi(int r, int c, char d) {
    auto sotto_it = columns[c].upper_bound({r, c, SOTTO, d});
    assert(sotto_it != columns[c].end());
    assert(sotto_it != columns[c].begin());
    face_t sotto = *sotto_it;
    --sotto_it;
    face_t sopra = *sotto_it;
    columns[c].insert({r, c, SOTTO, d});
    columns[c].insert({r, c, SOPRA, d});
    auto destra_it = rows[r].lower_bound({r, c, DESTRA, d});
    assert(destra_it != rows[r].end());
    assert(destra_it != rows[r].begin());
    face_t destra = *destra_it;
    --destra_it;
    face_t sinistra = *destra_it;
    rows[r].insert({r, c, SINISTRA, d});
    rows[r].insert({r, c, DESTRA, d});
    split(sotto, sopra);
    split(sinistra, destra);
    attach({r, c, SOTTO, d}, sotto);
    attach({r, c, SOPRA, d}, sopra);
    attach({r, c, SINISTRA, d}, sinistra);
    attach({r, c, DESTRA, d}, destra);
    join({r, c, SOTTO, d}, {r, c, rifletti(d, SOTTO), d});
    join({r, c, SOPRA, d}, {r, c, rifletti(d, SOPRA), d});
}


foro_t calcola(foro_t ingresso) {
    face_t cur;
    cur.lato = ingresso.lato;
    if (ingresso.lato == SINISTRA) {
        cur.r = ingresso.posizione;
        cur.c = 0;
        cur.type = '|';
    } else if (ingresso.lato == DESTRA) {
        cur.r = ingresso.posizione;
        cur.c = M+1;
        cur.type = '|';
    } else if (ingresso.lato == SOPRA) {
        cur.r = 0;
        cur.c = ingresso.posizione;
        cur.type = '-';
    } else if (ingresso.lato == SOTTO) {
        cur.r = N+1;
        cur.c = ingresso.posizione;
        cur.type = '-';
    } else assert(false);
    face_t other = other_end(cur);
    foro_t risposta;
    if (other.c == 0) {
        assert(other.type == '|');
        risposta.posizione = other.r;
        risposta.lato = SINISTRA;
    } else if (other.c == M+1) {
        assert(other.type == '|');
        risposta.posizione = other.r;
        risposta.lato = DESTRA;
    } else if (other.r == 0) {
        assert(other.type == '-');
        risposta.posizione = other.c;
        risposta.lato = SOPRA;
    } else if (other.r == N+1) {
        assert(other.type == '-');
        risposta.posizione = other.c;
        risposta.lato = SOTTO;
    } else assert(!!!"Specchio non valido!");
    return risposta;
}
