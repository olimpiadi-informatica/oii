/*
  Giovanni Mascellani <mascellani@poisson.phc.unipi.it>

  Soluzione di eso
*/

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

const int MAXN = 1000;

int N, M;

enum Type {
  NUM = 0,
  SQUARE = 1,
  ROUND = 2
};

struct eso {
  
  enum Type type;
  int num;
  struct eso *children;
  int children_len;

  /*eso() {
    this->square = vector< struct eso >();
    this->round = multiset< struct eso >();
  }

  eso(const struct eso &x) {
    this->type = x.type;
    this->num = x.num;
    this->square = x.square;
    this->round = x.round;
  }

  void operator=(const struct eso &x) {
    this->type = x.type;
    this->num = x.num;
    this->square = x.square;
    this->round = x.round;    
    }*/
  
  bool operator<(const eso &x) const {
    if (this->type < x.type) return true;
    else if (this->type > x.type) return false;
    else {
      // The two ESOs have the same type
      if (this->type == NUM) return this->num < x.num;
      else if (this->type == SQUARE) return lexicographical_compare(this->children, this->children + this->children_len,
								    x.children, x.children + x.children_len);
      else if (this->type == ROUND) return lexicographical_compare(this->children, this->children + this->children_len,
								   x.children, x.children + x.children_len);
      else assert("Should not arrive here... :-(" == 0);
    }
  }

  void fix_square_order() {
    assert(this->type == SQUARE);
    struct eso *tmp = (struct eso*) malloc(sizeof(struct eso) * this->children_len);
    for (int i = 0; i < this->children_len; i++) {
      tmp[i] = eso(this->children[this->children_len-i-1]);
    }
    if (lexicographical_compare(tmp, tmp+this->children_len,
				this->children, this->children+this->children_len)) {
      for (int i = 0; i < this->children_len; i++) {
	this->children[i] = eso(tmp[i]);
      }      
    }
  }

  void fix_round_order() {
    assert(this->type == ROUND);
    sort(this->children, this->children+this->children_len);
  }

  void print() {
    if (this->type == NUM) printf("%d ", this->num);
    else {
      if (this->type == SQUARE) printf("[ ");
      else printf("( ");
      for (int i = 0; i < this->children_len; i++) {
	children[i].print();
      }
      if (this->type == SQUARE) printf("] ");
      else printf(") ");
    }
  }

};

struct eso create_eso_num(int num) {

  struct eso tmp;
  tmp.type = NUM;
  tmp.num = num;
  return tmp;

}

struct eso parse_eso(const int *input, int *scan) {

  int starter = input[*scan];
  int terminator = starter - 1;
  eso tmp = eso();
  if (starter == -1) tmp.type = ROUND;
  else if (starter == -3) tmp.type = SQUARE;
  else assert("This shouldn't happen... :-(" == 0);

  tmp.children_len = 0;
  tmp.children = (struct eso*) malloc(sizeof(struct eso) * MAXN);
  for ((*scan)++; input[*scan] != terminator; (*scan)++) {
    if (input[*scan] >= 0) tmp.children[tmp.children_len++] = create_eso_num(input[*scan]);
    else tmp.children[tmp.children_len++] = parse_eso(input, scan);
  }
  if (starter == -1) tmp.fix_round_order();
  else if (starter == -3) tmp.fix_square_order();
    
  return tmp;

}

struct eso scan_line() {

  int *line = (int*) malloc(sizeof(int) * M);
  for (int i = 0; i < M; i++) {
    scanf("%d", &line[i]);
  }

  int scan = 0;
  return parse_eso(line, &scan);

  free(line);

}

int main(void) {
#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  scanf("%d %d", &N, &M);

  struct eso *eso = (struct eso*) malloc(sizeof(struct eso) * N);
  for (int i = 0; i < N; i++) {
    eso[i] = scan_line();
  }

  /*printf("%d\n", eso[0] < eso[0]);
  printf("%d\n", eso[1] < eso[0]);
  printf("%d\n", eso[2] < eso[0]);
  printf("%d\n", eso[0] < eso[1]);
  printf("%d\n", eso[1] < eso[1]);
  printf("%d\n", eso[2] < eso[1]);
  printf("%d\n", eso[0] < eso[2]);
  printf("%d\n", eso[1] < eso[2]);
  printf("%d\n", eso[2] < eso[2]);*/

  /*eso[0].print();
  printf("\n");
  eso[1].print();
  printf("\n");
  eso[2].print();
  printf("\n");*/

  vector< set< int > > classes;
  classes.resize(N);

  for (int i = 0; i < N; i++) {
    classes[i].insert(i);
    for (int j = i+1; j < N; j++) {
      if (!(eso[i] < eso[j]) && !(eso[j] < eso[i])) {
	classes[i].insert(j);
	classes[j].insert(i);
      }
    }
  }

  set< set< int > > real_classes;
  for (int i = 0; i < N; i++) real_classes.insert(classes[i]);

  printf("%d\n", real_classes.size());
  for (set< set< int > >::iterator it = real_classes.begin(); it != real_classes.end(); it++) {
    printf("%d ", it->size());
    for (set< int >::iterator it2 = it->begin(); it2 != it->end(); it2++) {
      printf("%d ", (*it2)+1);
    }
    printf("\n");
  }

  return 0;

}
