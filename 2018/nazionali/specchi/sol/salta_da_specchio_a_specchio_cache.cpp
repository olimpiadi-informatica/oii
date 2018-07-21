#include <iostream>
#include <set>
#include <cassert>
#include <vector>
#include <unistd.h>
#include <unordered_map>
using namespace std;

typedef int parete_t;
#define SOPRA 1
#define DESTRA 2
#define SOTTO 3
#define SINISTRA 4

struct foro_t {
	parete_t lato;
	int posizione;
	bool operator==(const foro_t& o) const {
		return lato == o.lato && posizione == o.posizione;
	}
};

// SOPRA <-> SOTTO     SINISTRA <-> DESTRA
parete_t inverti_dir(parete_t l) {
	return (parete_t)((l - 1 + 2) % 4 + 1);
}

// riflette un raggio che va in direzione dir su uno specchio d
parete_t rifletti(char d, parete_t dir) {
	if (d == '/') {
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

class specchio_t {
	public:
		// posizione
		int r, c;
		// tipo di specchio
		char d;
		// next[d] = prossimo specchio verso d. nullptr se non esiste
		specchio_t* next[5];

		specchio_t() : r(-1), c(-1), d('/') {
			next[0] = next[1] = next[2] = next[3] = next[4] = nullptr;
		}

		// specchio successivo arrivando da dir
		specchio_t* succ(parete_t dir) {
			return next[rifletti(d, dir)];
		}

		void debug() {
			cerr << "   specchio " << this << " in (" << r << ", " << c << ") = " << d << endl;
			cerr << "        next[] = [ ";
			for (int i = 1; i <= 4; i++) cerr << next[i] << " ";
			cerr << "]" << endl;
		}
};

struct set_elem_t {
	int pos;
	specchio_t* s;

	bool operator<(const set_elem_t& o) const { return pos < o.pos; }
};

namespace std {
template <>
struct hash<foro_t> {
	std::size_t operator()(const foro_t& k) const {
		return (k.lato-1) | (k.posizione<<2);
	}
};
}

vector<set<set_elem_t>> righe;
vector<set<set_elem_t>> colonne;
std::unordered_map<foro_t, foro_t> cache;

void inizia(int N, int M) {
	righe.resize(N+1);
	colonne.resize(M+1);
}

void aggiungi(set<set_elem_t>& linea, specchio_t* s, int pos, int prevDir, int nextDir) {
	// cerca lo specchio dopo quello da aggiungere
	auto succ_it = linea.upper_bound({pos, nullptr});
	// se tale specchio esiste
	if (succ_it != linea.end()) {
		auto succ = succ_it->s;
		// lo specchio prima di quello da aggiungere
		specchio_t* prev = succ->next[prevDir];
		// se esiste aggiusta i collegamenti col precedente
		if (prev) {
			prev->next[nextDir] = s;
			s->next[prevDir] = prev;
		}
		// aggiusta i collegamenti col successivo
		succ->next[prevDir] = s;
		s->next[nextDir] = succ;
	}
	// se l'ultimo specchio è prima di s
	if (!linea.empty() && linea.rbegin()->pos < pos) {
		// trova l'ultimo specchio e sistema i collegamenti
		specchio_t* prev = linea.rbegin()->s;
		prev->next[nextDir] = s;
		s->next[prevDir] = prev;
	}
	// aggiunge lo specchio al set
	linea.insert({pos, s});
	cache.clear();
}

void aggiungi(int r, int c, char diagonale) {
	r++;
	c++;
	// inserisce gli specchi nei set delle righe e delle colonne
	// O(logQ)
	specchio_t* s = new specchio_t;
	s->r = r;
	s->c = c;
	s->d = diagonale;

	// aggiunge lo specchio alla sua r e alla sua c
	aggiungi(righe[r], s, c, SINISTRA, DESTRA);
	aggiungi(colonne[c], s, r, SOPRA, SOTTO);
}

foro_t calcola(foro_t ingresso) {
	ingresso.lato += 1;
	ingresso.posizione += 1;
	if (cache.count(ingresso) == 1) return cache[ingresso];
	// Trova il primo specchio e salta da uno specchio al successivo
	// O(# specchi nel percorso)
	int p = ingresso.posizione;
	specchio_t* s = nullptr;
	// cerca lo specchio iniziale se esiste, altrimenti risponde immediatamente
	switch (ingresso.lato) {
		case SOPRA:
			if (colonne[p].size() == 0) return {SOTTO-1, p-1};
			s = colonne[p].begin()->s;
			break;
		case DESTRA:
			if (righe[p].size() == 0) return {SINISTRA-1, p-1};
			s = righe[p].rbegin()->s;
			break;
		case SOTTO:
			if (colonne[p].size() == 0) return {SOPRA-1, p-1};
			s = colonne[p].rbegin()->s;
			break;
		case SINISTRA:
			if (righe[p].size() == 0) return {DESTRA-1, p-1};
			s = righe[p].begin()->s;
			break;
	}

	// la direzione di movimento è opposta al lato di partenza
	parete_t dir = inverti_dir(ingresso.lato);
	while (s) {
		// cerca lo specchio successivo
		specchio_t* next = s->succ(dir);
		// corrette la direzione in base allo specchio
		dir = rifletti(s->d, dir);
		// se non c'è uno specchio successivo allora si esce dalla matrice
		if (next == nullptr) {
			if (dir == DESTRA || dir == SINISTRA)
				return cache[ingresso] = {dir-1, s->r-1};
			else
				return cache[ingresso] = {dir-1, s->c-1};
		}
		// si salta allo specchio dopo
		s = next;
	}

	assert(false && "Il while non doveva uscire");
}
