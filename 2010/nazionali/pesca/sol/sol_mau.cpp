// Soluzione di pesci (si spera)
//
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

const int MaxN = (1UL << 31) - 1;
const int MaxP = 1000000;
const int MaxM = 1000000;

typedef vector<pair<int, int> > pesci_t;
typedef vector<int> seq_t;
void leggi_seq(seq_t &seq);

int main()
{
  pesci_t pesci;
  seq_t seqA;
  seq_t seqB;

  // lettura dell'input...
  int P;
  in >> P;

  assert (1 <= P && P <= MaxP);
  
  pesci.reserve(P);
  seqA.reserve(MaxM);
  seqB.reserve(MaxM);

  int sx, sy;
  in >> sx >> sy;
  assert (1 <= sx && sx <= MaxN);
  assert (1 <= sy && sy <= MaxN);
  --sx;
  --sy;

  for (int i = 0; i < P; ++i) {
    int x, y;
    in >> x >> y;
    assert (in);
    assert (1 <= x && x <= MaxN);
    assert (1 <= y && y <= MaxN);
    --x; --y;
    
    // inseriamo solo i pesci con coordinate >= rispetto al
    // punto di partenza
    if (y >= sy && x >= sx) {
      pesci.push_back(make_pair(x, y));
    }
  }

  leggi_seq(seqA);
  leggi_seq(seqB);

  if (seqA[0] < 0) {
    seqA.swap(seqB);
  }
  
  // ordiniamo i pesci...
  sort(pesci.begin(), pesci.end());

  // per ogni x attraversata...
  int cx, ay, by, count;
  seq_t::iterator ai = seqA.begin();
  seq_t::iterator bi = seqB.begin();
  cx = sx;
  ay = sy + *ai++;
  by = sy;
  pesci_t::iterator pbegin = pesci.begin();
  pesci_t::iterator pend = pesci.end();
  count = 0;

  seqB.pop_back();
  assert(seqA[seqA.size() - 1] < 0);
  assert(seqB[seqB.size() - 1] < 0);
  
  while (true) {
    while (pbegin != pend && pbegin->first <= cx) {
      if (pbegin->first == cx && pbegin->second > ay) {
	break;
      }
      if (pbegin->second >= by && pbegin->second <= ay) {
	//cerr << "preso: " << pbegin->first+1 << " " << pbegin->second+1 << endl;
	++count;
      }
      ++pbegin;
    }

    if (pbegin == pend) {
      break;
    }

    if (ai != seqA.end() && *ai > 0) {
      ay += *ai++;
    }

    if (bi == seqB.end()) {
      assert(ai == seqA.end());
      break;
    } else if (*bi > 0) {
      by += *bi++;
    }

    int s = max(*ai, *bi);
    //cerr << "passo: " << s << endl;
    assert (s < 0);
    
    cx -= s;
    *ai -= s;
    *bi -= s;
    if (!*ai) {
      ++ai;
    }
    if (!*bi) {
      ++bi;
    }
  }

  out << count << endl;
}

void leggi_seq(seq_t &seq)
{
  int prev;
  in >> prev;
  while (true) {
    int c;
    in >> c;
    assert(c <= MaxN);
    if (c == 0)
      break;
    assert (prev != 0 && c != 0);
    if (((c>>31) & 1) == ((prev>>31) & 1)) {
      prev += c;
    } else {
      seq.push_back(prev);
      prev = c;
    }
    assert (in);
  }
  assert (prev != 0);
  seq.push_back(prev);
  assert (seq.size() <= unsigned(MaxM));
}  

