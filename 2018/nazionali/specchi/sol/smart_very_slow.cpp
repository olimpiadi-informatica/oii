#include <cassert>
#include <set>
#include <unordered_map>
#include <vector>

#include "smart_vector_very_slow.hpp"

//#define DEBUG

typedef int parete_t;
#define SOPRA 1
#define DESTRA 2
#define SOTTO 3
#define SINISTRA 4

typedef struct {
  parete_t lato;
  int posizione;
} foro_t;

parete_t rifletti(char d, parete_t dir) {
  if (d == '\\') {
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
  assert(false);
}

const char *strlato(parete_t lato) {
  if (lato == SOPRA)
    return "   SOPRA";
  if (lato == SOTTO)
    return "   SOTTO";
  if (lato == SINISTRA)
    return "SINISTRA";
  if (lato == DESTRA)
    return "  DESTRA";
  assert(false);
}

struct face_data_t {
  int r, c;
  parete_t lato;
  char type;
  bool operator<(const face_data_t &other) const {
    assert((lato + other.lato) % 2 == 0);
    if (lato == SOPRA || lato == SOTTO) {
      assert(c == other.c);
      if (r < other.r)
        return true;
      if (r > other.r)
        return false;
      return lato == SOPRA && other.lato == SOTTO;
    } else {
      assert(r == other.r);
      if (c < other.c)
        return true;
      if (c > other.c)
        return false;
      return lato == SINISTRA && other.lato == DESTRA;
    }
  }
  bool operator==(const face_data_t &other) const {
    return r == other.r && c == other.c && lato == other.lato;
  }

  void print(const char *term = "\n") {
    fprintf(stderr, "%s % 2d % 2d %c%s", strlato(lato), r, c, type, term);
  }
};

std::vector<face_data_t> faces;

struct face_t {
  unsigned id;
  bool operator<(const face_t &other) const {
    return faces[id] < faces[other.id];
  }
  void print(const char *term = "\n") const { faces[id].print(term); }
  const face_data_t &data() const { return faces[id]; }
  bool operator==(const face_t &other) const { return id == other.id; }
};

int N, M;
std::vector<void *> ptrs;
std::vector<smart_vector<face_t>> paths;

void print_path(const smart_vector<face_t> &path) {
  fprintf(stderr, "PATH_START\n");
  for (unsigned i = 0; i < path.size(); i++) {
    path[i].print();
  }
  fprintf(stderr, "PATH_END\n\n");
}

void print_paths() {
#ifdef DEBUG
  fprintf(stderr, "------------------\n");
  for (const auto &path : paths) {
    print_path(path);
  }
  fprintf(stderr, "------------------\n\n");
#endif
}

void init() {
  // Nothing to do here.
}

void create(face_t init) {
  paths.emplace_back();
  paths.back().set_callback([](face_t face, void *ptr) {
#ifdef DEBUG
    fprintf(stderr, "CALLBACK: ");
    face.print(" ");
    fprintf(stderr, "%p\n", ptr);
#endif
    if (ptrs.size() <= face.id)
      ptrs.resize(face.id + 1);
    ptrs[face.id] = ptr;
  });
  paths.back().push_back(init);
}

void split(face_t a, face_t b) {
#ifdef DEBUG
  fprintf(stderr, " SPLIT: ");
  a.print(" -> ");
  b.print();
#endif
  auto data1 = smart_vector<face_t>::find_owner(a, ptrs.at(a.id));
  auto data2 = smart_vector<face_t>::find_owner(b, ptrs.at(b.id));
#ifdef DEBUG
  fprintf(stderr, "%lu %lu\n", data1.second, data2.second);
  fprintf(stderr, "%p %p\n", data1.first, data2.first);
#endif
  assert(data1.first->size() > 1);
  assert(data2.first->size() > 1);
  assert(data1.first == data2.first);
  if (data1.second > data2.second)
    std::swap(data1, data2);
  assert(data1.second + 1 == data2.second);
#ifdef DEBUG
  print_path(*data1.first);
#endif
  smart_vector<face_t> rest = data1.first->split(data2.second);
  // If this path was a cycle...
  if (data1.first->front().data().r == rest.back().data().r &&
      data1.first->front().data().c == rest.back().data().c) {
#ifdef DEBUG
    fprintf(stderr, "CYCLE!\n");
#endif
    data1.first->reverse();
    rest.reverse();
    data1.first->append(rest);
#ifdef DEBUG
    print_path(*data1.first);
#endif
  } else {
    paths.push_back(std::move(rest));
#ifdef DEBUG
    print_path(*data1.first);
    print_path(paths.back());
#endif
  }
}

void attach(face_t f, face_t to) {
#ifdef DEBUG
  fprintf(stderr, "ATTACH: ");
  f.print(" to ");
  to.print();
#endif
  auto data = smart_vector<face_t>::find_owner(to, ptrs.at(to.id));
  assert(data.first->size() > 0);
  assert(data.second == 0 || data.second == data.first->size() - 1);
  if (data.second == 0)
    data.first->push_front(f);
  else
    data.first->push_back(f);
}

void join(face_t a, face_t b) {
#ifdef DEBUG
  fprintf(stderr, "JOIN: ");
  a.print(" and ");
  b.print();
#endif
  auto data1 = smart_vector<face_t>::find_owner(a, ptrs.at(a.id));
  auto data2 = smart_vector<face_t>::find_owner(b, ptrs.at(b.id));
  assert(data1.first->size() > 1);
  assert(data2.first->size() > 1);
#ifdef DEBUG
  fprintf(stderr, "%p %p\n", data1.first, data2.first);
#endif
  assert(data1.second == 0 || data1.second == data1.first->size() - 1);
  assert(data2.second == 0 || data2.second == data2.first->size() - 1);
  // If we would create a cycle, do nothing.
  if (data1.first == data2.first)
    return;
#ifdef DEBUG
  print_path(*data1.first);
  print_path(*data2.first);
#endif
  if (data1.second == 0)
    data1.first->reverse();
  if (data2.second != 0)
    data2.first->reverse();
  data1.first->append(*data2.first);
#ifdef DEBUG
  print_path(*data1.first);
#endif
  *data2.first = std::move(paths.back());
  paths.pop_back();
}

face_t other_end(face_t cur) {
  auto data = smart_vector<face_t>::find_owner(cur, ptrs.at(cur.id));
  assert(data.second == 0 || data.second == data.first->size() - 1);
#ifdef DEBUG
  fprintf(stderr, "%lu %lu\n", data.second, data.first->size());
  fprintf(stderr, "  CUR: ");
  cur.print();
  fprintf(stderr, "FRONT: ");
  data.first->front().print();
  fprintf(stderr, " BACK: ");
  data.first->back().print();
#endif
  return (*data.first)[data.first->size() - 1 - data.second];
}

std::vector<std::set<face_t>> rows;
std::vector<std::set<face_t>> columns;

face_t create_face(int r, int c, parete_t lato, char d) {
  faces.push_back({r, c, lato, d});
  return face_t{(unsigned)faces.size() - 1};
}

std::vector<face_t> lati[4];

void inizia(int N, int M) {
  ::N = N;
  ::M = M;
  init();
  rows.resize(N + 2);
  columns.resize(M + 2);
  lati[SOPRA - 1].resize(M + 2);
  lati[SOTTO - 1].resize(M + 2);
  lati[DESTRA - 1].resize(N + 2);
  lati[SINISTRA - 1].resize(N + 2);
  for (int i = 0; i < N; i++) {
    face_t s = create_face(i + 1, 0, SINISTRA, '|');
    face_t d = create_face(i + 1, M + 1, DESTRA, '|');
    lati[DESTRA - 1][i + 1] = d;
    lati[SINISTRA - 1][i + 1] = s;
    rows[i + 1].insert(d);
    rows[i + 1].insert(s);
    create(d);
    attach(s, d);
  }
  for (int i = 0; i < M; i++) {
    face_t u = create_face(0, i + 1, SOPRA, '-');
    face_t d = create_face(N + 1, i + 1, SOTTO, '-');
    lati[SOPRA - 1][i + 1] = u;
    lati[SOTTO - 1][i + 1] = d;
    columns[i + 1].insert(u);
    columns[i + 1].insert(d);
    create(u);
    attach(d, u);
  }
}

void aggiungi(int r, int c, char d) {
  r++;
  c++;
#ifdef DEBUG
  fprintf(stderr, "INSERT %d %d %c\n", r, c, d);
#endif
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
#ifdef DEBUG
  fprintf(stderr, "FIND %s %d\n", strlato(ingresso.lato), ingresso.posizione);
#endif
  face_t cur = lati[ingresso.lato - 1][ingresso.posizione];
  face_data_t other = other_end(cur).data();
  foro_t risposta;
  if (other.c == 0) {
    assert(other.type == '|');
    risposta.posizione = other.r;
    risposta.lato = SINISTRA;
  } else if (other.c == M + 1) {
    assert(other.type == '|');
    risposta.posizione = other.r;
    risposta.lato = DESTRA;
  } else if (other.r == 0) {
    assert(other.type == '-');
    risposta.posizione = other.c;
    risposta.lato = SOPRA;
  } else if (other.r == N + 1) {
    assert(other.type == '-');
    risposta.posizione = other.c;
    risposta.lato = SOTTO;
  } else
    assert(!!!"Specchio non valido!");
  risposta.lato -= 1;
  risposta.posizione -= 1;
  return risposta;
}
