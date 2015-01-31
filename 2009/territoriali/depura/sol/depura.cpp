// soluzione quadratica: scandiamo tutte le volte l'array delle regole "aperte"
// finche' non ne troviamo una soddisfacibile, quindi assegniamo il punteggio.
// se e' una regola valida per la sostanza 0 allora abbiamo finito.
// Nota: si potrebbe fare di meglio ma questa dovrebbe bastare dato che R e'
// piccolo.
//
// Maurizio

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

const int MinR = 1;
const int MaxR = 1000;
const int MinK = 1;
const int MaxK = 1000;
const int MaxN = MaxR + MaxK;
const int MaxS = MaxN;

int main()
{
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif
  
  int R, K;
  in >> K;
  in >> R;

  assert (MinR <= R && R <= MaxR);
  assert (MinK <= K && K <= MaxK);

  int S[MaxN];
  for (int i = 0; i < MaxN; ++i) {
    S[i] = MaxS;
  }

  for (int i = 0; i < K; ++i) {
    int x;
    in >> x;
    --x;
    S[x] = -1;
  }

  vector<int> rules[MaxN];
  int rule_owner[MaxN];
  
  for (int i = 0; i < R; ++i) {
    int u;
    in >> u;
    --u;
    int n;
    in >> n;
    for (int j = 0; j < n; ++j) {
      int v;
      in >> v;
      --v;
      rules[i].push_back(v);
    }
    rule_owner[i] = u;
  }

  vector<int> remove_rule;
  while (S[0] == MaxS && R) {
    for (int i = 0; i < R; ++i) {
      int u = rule_owner[i];
      if (S[u] == MaxS) {
	int sol = 0;
	for (vector<int>::iterator iter = rules[i].begin();
	     iter != rules[i].end(); ++iter) {
	  sol = max(sol, S[*iter]);
	  if (S[*iter] == MaxS) {
	    break;
	  }
	}
	if (sol < MaxS) {
	  S[u] = sol + 1;
	}
      } else {
	// questa regola permette di inserire una sostanza
	// di cui gia' disponiamo la soluzione
	remove_rule.push_back(i);
      }
    }

    // nota: scorriamo la lista al contrario, cosi' abbiamo una sequenza di
    // numberi decrescenti, in questo modo siamo sicuri che le regole
    // eliminate abbiano l'indice corretto
    for (vector<int>::reverse_iterator iter = remove_rule.rbegin();
	 iter != remove_rule.rend(); ++iter) {
      if (*iter != R-1) {
	rules[*iter] = rules[R-1];
	rule_owner[*iter] = rule_owner[R-1];
      }
      --R;
    }
    remove_rule.clear();
  }

  out << S[0] << endl;
}

