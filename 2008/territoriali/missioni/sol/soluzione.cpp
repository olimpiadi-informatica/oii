#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <list>
#include <cassert>

#define NDEBUG

using namespace std;

const int MinN = 1;
const int MaxN = 100;
const int MinD = 1;
const int MaxD = 365;
const int MinS = 1;
const int MaxS = 365;

int main()
{
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

  // lettura dell'input
  int N;
  in >> N;

  assert(MinN <= N && N <= MaxN);

  typedef list<pair<int, int> > list_type;
  list_type S; // vettore (scadenza, durata) degli appuntamenti --
               // l'input invece e' (durata, scadenza)

  for (int i = 0; i < N; ++i) {
    int d, s;
    in >> d >> s;

    assert(MinD <= d && d <= MaxD);
    assert(MinS <= s && s <= MaxS);

    S.push_back(make_pair(s, d));
  }

  // ordina S per scadenza
  //S.sort();  -- gia' ordinato nell'input

  bool done = false;
  while (!done) {
    done = true;
    int time = 0;
    list_type::iterator longest = S.begin();
    for (list_type::iterator curr = S.begin(); curr != S.end(); ++curr) {
      if (longest->second < curr->second) {
        longest = curr;
      }
      time += curr->second;
      if (curr->first < time) {
        S.erase(longest);
        done = false;
        break;
      }
    }
  }

  out << S.size() << endl;
#if !defined(NDEBUG)
  for (list_type::iterator curr = S.begin(); curr != S.end(); ++curr) {
    cerr << curr->second << " " << curr->first << endl;
  }
#endif
}
