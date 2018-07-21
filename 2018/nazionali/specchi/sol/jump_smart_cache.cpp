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


struct face_data_t {
    int r, c;
    parete_t lato;
    char type;
    bool operator<(const face_data_t& other) const {
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
    bool operator==(const face_data_t& other) const {
        return r == other.r && c == other.c && lato == other.lato;
    }

    void print(const char* term = "\n") {
        fprintf(stderr, "%s % 2d % 2d %c%s", strlato(lato), r, c, type, term);
    }
};

std::vector<face_data_t> faces;

struct face_t {
    unsigned id;
    bool operator<(const face_t& other) const {
        return faces[id] < faces[other.id];
    }
    void print(const char* term = "\n") {
        faces[id].print(term);
    }
    const face_data_t& data() const {
        return faces[id];
    }
    bool operator==(const face_t& other) const {
        return id == other.id;
    }
};

int N, M;
std::vector<face_t> next;
std::vector<face_t> mirror;

face_t dummy_face;

std::vector<unsigned> path_id;
std::vector<bool> is_valid;
std::vector<std::pair<face_t, face_t>> cache;

template<typename T>
void vset(std::vector<T>& v, unsigned pos, T val) {
    if (v.size() <= pos) v.resize(pos+1);
    v[pos] = val;
}

template<>
void vset(std::vector<unsigned>& v, unsigned pos, unsigned val) {
    if (v.size() <= pos) v.resize(pos+1);
    v[pos] = val;
}

template<>
void vset(std::vector<bool>& v, unsigned pos, bool val) {
    if (v.size() <= pos) v.resize(pos+1);
    v[pos] = val;
}

template<>
void vset(std::vector<face_t>& v, unsigned pos, face_t val) {
    if (v.size() <= pos) v.resize(pos+1);
    v[pos] = val;
}

template<typename T>
T vget(std::vector<T>& v, unsigned pos) {
    if (v.size() > pos) return v.at(pos);
}

template<typename T>
T vget(std::vector<T>& v, unsigned pos, T def) {
    if (v.size() > pos) return v[pos];
    return def;
}

void init() {
    // Nothing to do with an hashmap
}

void create(face_t f) {
    vset(path_id, f.id, (unsigned)is_valid.size());
    vset(is_valid, f.id, false);
}

void split(face_t a, face_t b) {
    vset(is_valid, vget(path_id, a.id), false);
    vset(is_valid, vget(path_id, b.id), false);
}

void attach(face_t f, face_t to) {
    vset(path_id, f.id, (unsigned)is_valid.size());
    vset(next, f.id, to);
    vset(next, to.id, f);
    vset(is_valid, vget(path_id, f.id), false);
    vset(is_valid, vget(path_id, to.id), false);
}

void join(face_t a, face_t b) {
    vset(mirror, a.id, b);
    vset(mirror, b.id, a);
    vset(is_valid, vget(path_id, a.id), false);
    vset(is_valid, vget(path_id, b.id), false);
}

face_t other_end(face_t cur) {
    face_t start = cur;
    unsigned path = vget(path_id, cur.id, cur.id);
    if (vget(is_valid, path, false)) {
        auto ext = cache[path];
        return cur == ext.first ? ext.second : ext.first;
    }
    path = is_valid.size();
    vset(path_id, cur.id, path);
    while (true) {
        cur = next[cur.id];
        vset(path_id, cur.id, path);
        if (cur.data().type == '-' || cur.data().type == '|') break;
        cur = mirror[cur.id];
    }
    vset(cache, path, {cur, start});
    vset(is_valid, path, true);
    return cur;
}

std::vector<std::set<face_t>> rows;
std::vector<std::set<face_t>> columns;

face_t create_face(int r, int c, parete_t lato, char d) {
    faces.push_back({r, c, lato, d});
    return face_t{(unsigned)faces.size()-1};
}

std::vector<face_t> lati[4];

void inizia(int N, int M) {
    dummy_face = create_face(-1, -1, SOTTO, 'd');
    ::N = N; ::M = M;
    init();
    rows.resize(N+2);
    columns.resize(M+2);
    lati[SOPRA-1].resize(M+2);
    lati[SOTTO-1].resize(M+2);
    lati[DESTRA-1].resize(N+2);
    lati[SINISTRA-1].resize(N+2);
    for (int i=0; i<N; i++) {
        face_t s = create_face(i+1, 0, SINISTRA, '|');
        face_t d = create_face(i+1, M+1, DESTRA, '|');
        lati[DESTRA-1][i+1] = d;
        lati[SINISTRA-1][i+1] = s;
        rows[i+1].insert(d);
        rows[i+1].insert(s);
        create(d);
        attach(s, d);
    }
    for (int i=0; i<M; i++) {
        face_t u = create_face(0, i+1, SOPRA, '-');
        face_t d = create_face(N+1, i+1, SOTTO, '-');
        lati[SOPRA-1][i+1] = u;
        lati[SOTTO-1][i+1] = d;
        columns[i+1].insert(u);
        columns[i+1].insert(d);
        create(u);
        attach(d, u);
    }
}


void aggiungi(int r, int c, char d) {
    r++;
    c++;
    face_t my_sotto = create_face(r, c, SOTTO, d);
    face_t my_sopra = create_face(r, c, SOPRA, d);
    face_t my_destra = create_face(r, c, DESTRA, d);
    face_t my_sinistra = create_face(r, c, SINISTRA, d);
    auto sotto_it = columns[c].upper_bound(my_sotto);
    assert(sotto_it != columns[c].end());
    assert(sotto_it != columns[c].begin());
    face_t sotto = *sotto_it;
    --sotto_it;
    face_t sopra = *sotto_it;
    columns[c].insert(my_sotto);
    columns[c].insert(my_sopra);
    auto destra_it = rows[r].lower_bound(my_destra);
    assert(destra_it != rows[r].end());
    assert(destra_it != rows[r].begin());
    face_t destra = *destra_it;
    --destra_it;
    face_t sinistra = *destra_it;
    rows[r].insert(my_sinistra);
    rows[r].insert(my_destra);
    split(sotto, sopra);
    split(sinistra, destra);
    attach(my_sotto, sotto);
    attach(my_sopra, sopra);
    attach(my_sinistra, sinistra);
    attach(my_destra, destra);
    join(my_sotto, rifletti(d, SOTTO) == SINISTRA ? my_sinistra : my_destra);
    join(my_sopra, rifletti(d, SOPRA) == SINISTRA ? my_sinistra : my_destra);
}


foro_t calcola(foro_t ingresso) {
    ingresso.lato += 1;
    ingresso.posizione += 1;
    face_t cur = lati[ingresso.lato-1][ingresso.posizione];
    face_data_t other = other_end(cur).data();
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
    risposta.lato -= 1;
    risposta.posizione -= 1;
    return risposta;
}
