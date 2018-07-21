#include <cassert>
#include <iostream>
#include <set>
#include <unistd.h>

// ================================================================================================================================
// ================================================================================================================================
// ================================================================================================================================
// ================================================================================================================================
#include "smart_vector_slow.hpp"
// ================================================================================================================================
// ================================================================================================================================
// ================================================================================================================================
// ================================================================================================================================

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

// SOPRA <-> SOTTO     SINISTRA <-> DESTRA
parete_t inverti_dir(parete_t l) { return (parete_t)((l - 1 + 2) % 4 + 1); }

// riflette un raggio che va in direzione dir su uno specchio d
parete_t rifletti(char d, parete_t dir) {
  if (d == '/') {
    if (dir == SOPRA)
      return DESTRA;
    if (dir == DESTRA)
      return SOPRA;
    if (dir == SOTTO)
      return SINISTRA;
    if (dir == SINISTRA)
      return SOTTO;
  } else {
    if (dir == SOPRA)
      return SINISTRA;
    if (dir == DESTRA)
      return SOTTO;
    if (dir == SOTTO)
      return DESTRA;
    if (dir == SINISTRA)
      return SOPRA;
  }
}

parete_t dir_from_delta(int dr, int dc) {
  if (dr > 0)
    return SOTTO;
  if (dr < 0)
    return SOPRA;
  if (dc > 0)
    return DESTRA;
  if (dc < 0)
    return SINISTRA;
  assert(false && "I delta non sono validi");
}

class specchio_t {
public:
  // id dello specchio
  int id;
  // posizione
  int r, c;
  // tipo di specchio
  char d;
  // next[d] = prossimo specchio verso d. nullptr se non esiste
  specchio_t *next[5];
  // puntatore interno della struttura con il percorso, direzione uscente dallo
  // specchio
  void *internal[5];

  specchio_t() : id(-1), r(-1), c(-1), d('/') {
    next[0] = next[1] = next[2] = next[3] = next[4] = nullptr;
  }

  // specchio successivo arrivando da dir
  specchio_t *succ(parete_t dir) { return next[rifletti(d, dir)]; }

  void debug() {
    cerr << "   specchio " << this << " in (" << r << ", " << c << ") = " << d
         << endl;
    cerr << "        next[] = [ ";
    for (int i = 1; i <= 4; i++)
      cerr << next[i] << " ";
    cerr << "]" << endl;
  }
};

struct set_elem_t {
  int pos;
  specchio_t *s;

  bool operator<(const set_elem_t &o) const { return pos < o.pos; }
};

struct specchio_faccia_t {
  specchio_t *s;
  parete_t dir;

  bool operator==(const specchio_faccia_t &o) const {
    return o.s == s && o.dir == dir;
  }
};

typedef smart_vector<specchio_faccia_t> svec;

void stampa_svec(svec &vec) {
  size_t size = vec.size();
  for (int i = 0; i < size; i++) {
    auto x = vec[i];
    x.s->debug();
  }
}

void callback(specchio_faccia_t s, void *ptr) { s.s->internal[s.dir] = ptr; }

// ==========================================================================================================================

vector<specchio_t> specchi;

vector<set<set_elem_t>> righe;
vector<set<set_elem_t>> colonne;

vector<svec> percorsi[5];

int N, M;

// ==========================================================================================================================

void inizia(int N, int M) {
  ::N = N;
  ::M = M;
  righe.resize(N + 1);
  colonne.resize(M + 1);
  percorsi[SOPRA].resize(M + 1);
  percorsi[SOTTO].resize(M + 1);
  percorsi[SINISTRA].resize(N + 1);
  percorsi[DESTRA].resize(N + 1);
  for (int i = 0; i <= N; i++) {
    percorsi[SINISTRA][i].set_callback(callback);
    percorsi[DESTRA][i].set_callback(callback);
  }
  for (int i = 0; i <= M; i++) {
    percorsi[SOPRA][i].set_callback(callback);
    percorsi[SOTTO][i].set_callback(callback);
  }
}

pair<pair<svec *, size_t>, pair<svec *, size_t>>
aggiungi(set<set_elem_t> &linea, specchio_t *s, int pos, int pos2,
         parete_t prevDir, parete_t nextDir) {
  specchio_t *next = nullptr;
  specchio_t *prev = nullptr;

  // cerca lo specchio dopo quello da aggiungere
  auto succ_it = linea.upper_bound({pos, nullptr});
  // se tale specchio esiste
  if (succ_it != linea.end())
    next = succ_it->s;

  if (next)
    prev = next->next[prevDir];
  else if (!linea.empty() && linea.rbegin()->pos < pos)
    prev = linea.rbegin()->s;

  pair<svec *, size_t> prevOwner, nextOwner;

  // se esiste aggiusta i collegamenti col precedente
  if (prev) {
    prev->next[nextDir] = s;
    s->next[prevDir] = prev;

    specchio_faccia_t f = {prev, inverti_dir(prevDir)};
    void *internal = prev->internal[f.dir];
    prevOwner = svec::find_owner(f, internal);
  } else
    prevOwner = {&percorsi[prevDir][pos2], -1};

  // se esiste aggiusta i collegamenti col successivo
  if (next) {
    next->next[prevDir] = s;
    s->next[nextDir] = next;

    specchio_faccia_t f = {next, inverti_dir(nextDir)};
    void *internal = next->internal[f.dir];
    nextOwner = svec::find_owner(f, internal);
  } else
    nextOwner = {&percorsi[nextDir][pos2], -1};

  // aggiunge lo specchio al set
  linea.insert({pos, s});
  return {prevOwner, nextOwner};
}

void aggiungi(int r, int c, char d) {
  r++;
  c++;
  // inserisce gli specchi nei set delle righe e delle colonne
  // O(logQ)

  // cerr << "AGGIUNGI SPECCHIO" << endl;

  specchio_t real_s;
  specchi.push_back(real_s);
  specchio_t *s = &specchi.back();
  s->id = specchi.size();
  s->r = r;
  s->c = c;
  s->d = d;
  // s->debug();

  // aggiunge lo specchio alla sua r e alla sua c
  auto oriz =
      aggiungi(righe[r], s, c, r, SINISTRA, DESTRA); // first = SX  second = DX
  auto vert =
      aggiungi(colonne[c], s, r, c, SOPRA, SOTTO); // first = UP  second = DW

  // cerr << "----------------------------" << endl;
  // cerr << "oriz: " << oriz.first.first->size() << " " <<
  // oriz.second.first->size() << endl;  cerr << "vert: " <<
  // vert.first.first->size() << " " << vert.second.first->size() << endl;  cerr
  // << "oriz (lung): " << oriz.first.second+1 << " " << oriz.second.second+1 <<
  // endl;  cerr << "vert (lung): " << vert.first.second+1 << " " <<
  // vert.second.second+1 << endl;  cerr << "oriz (svec): " << oriz.first.first <<
  // " " << oriz.second.first << endl;  cerr << "vert (svec): " <<
  // vert.first.first << " " << vert.second.first << endl;

  // i percorsi devono avere la stessa lunghezza nelle due direzioni
  assert(oriz.first.first->size() == oriz.second.first->size());
  assert(vert.first.first->size() == vert.second.first->size());

  // spezza i due percorsi nel punto dello specchio
  // il nome della variabile è la direzione, 1 = entrante, 2 = uscente
  auto &dx1 = *(oriz.first.first);
  auto dx2 = dx1.split(oriz.first.second + 1);
  auto &sx1 = *(oriz.second.first);
  auto sx2 = sx1.split(oriz.second.second + 1);
  auto &dw1 = *(vert.first.first);
  auto dw2 = dw1.split(vert.first.second + 1);
  auto &up1 = *(vert.second.first);
  auto up2 = up1.split(vert.second.second + 1);

  // cerr
  //	<< "dx " << dx1.size() << " " << dx2.size() << endl
  //	<< "sx " << sx1.size() << " " << sx2.size() << endl
  //	<< "dw " << dw1.size() << " " << dw2.size() << endl
  //	<< "up " << up1.size() << " " << up2.size() << endl << endl;

  if (d == '/') {
    up1.push_back({s, DESTRA});
    up1.append(dx2);
    dx1.push_back({s, SOPRA});
    dx1.append(up2);
    dw1.push_back({s, SINISTRA});
    dw1.append(sx2);
    sx1.push_back({s, SOTTO});
    sx1.append(dw2);
  } else {
    up1.push_back({s, SINISTRA});
    up1.append(sx2);
    dx1.push_back({s, SOTTO});
    dx1.append(dw2);
    dw1.push_back({s, DESTRA});
    dw1.append(dx2);
    sx1.push_back({s, SOPRA});
    sx1.append(up2);
  }

  /*for (int i = 1; i <= M; i++) {
          //cerr << "----  PARTENDO DA SOPRA DA " << i << " " <<
  &percorsi[SOPRA][i] << endl; stampa_svec(percorsi[SOPRA][i]);
  }
  for (int i = 1; i <= N; i++) {
          //cerr << "----  PARTENDO DA DESTRA DA " << i << " " <<
  &percorsi[DESTRA][i] << endl; stampa_svec(percorsi[DESTRA][i]);
  }
  for (int i = 1; i <= M; i++) {
          //cerr << "----  PARTENDO DA SOTTO DA " << i << " " <<
  &percorsi[SOTTO][i] << endl; stampa_svec(percorsi[SOTTO][i]);
  }
  for (int i = 1; i <= N; i++) {
          //cerr << "----  PARTENDO DA SINISTRA DA " << i << " " <<
  &percorsi[SINISTRA][i] << endl; stampa_svec(percorsi[SINISTRA][i]);
  }*/
}

foro_t calcola(foro_t ingresso) {
  ingresso.lato += 1;
  ingresso.posizione += 1;
  // cerr << "PREVEDI POSIZIONE" << endl;

  // Trova il primo specchio e salta da uno specchio al successivo
  // O(# specchi nel percorso)
  parete_t l = ingresso.lato;
  int p = ingresso.posizione;
  svec &vec = percorsi[l][p];
  size_t size = vec.size();
  // stampa_svec(vec);

  if (size == 0)
    return {inverti_dir(l) - 1, p - 1};

  specchio_faccia_t back = vec.back();
  parete_t dir = back.dir;
  if (dir == SOPRA || dir == SOTTO)
    return {dir - 1, back.s->c - 1};
  else
    return {dir - 1, back.s->r - 1};
}
