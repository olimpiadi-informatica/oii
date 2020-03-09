#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using ll = long long;
using ii = std::pair<ll, ll>;

const double PUNTI_COSTO = 0.6;
const double PUNTI_SOLUZIONE = 0.4;

#define MALFORMED       "Malformed output"
#define COST_MISSING    "Cost: missing; "
#define COST_CORRECT    "Cost: correct; "
#define COST_WRONG      "Cost: wrong; "
#define SEED_UNCOVERED  "Sprinklers: some seeds aren't covered!"
#define SEED_SUBOPTIMAL "Sprinklers: suboptimal disposition!"
#define SEED_OPTIMAL    "Sprinklers: optimal disposition!"
#define CHECKER_ERROR   "Checker error, contact the admins"


void ex(float score, std::string mex) {
  std::cout << score << std::endl;
  std::cerr << mex << std::endl;
  exit(0);
}

bool reachable(const ii& seed, const ii& irr) {
  return abs(seed.first - irr.first) + seed.second <= irr.second;
}

int main(int argc, char** argv) {
  assert(argc == 4);
  std::ifstream in(argv[1]);
  std::ifstream cor(argv[2]);
  std::ifstream test(argv[3]);

  ll C, N;
  in >> C >> N;
  std::vector<ii> seeds(N);
  for (ll i = 0; i < N; i++) {
    in >> seeds[i].first >> seeds[i].second;
  }
  std::sort(seeds.begin(), seeds.end());

  ll costo_ottimo;
  cor >> costo_ottimo;

  ll costo_riportato;
  ll num_irrigatori;
  test >> costo_riportato >> num_irrigatori;
  std::vector<ii> sol(num_irrigatori);
  for (ll i = 0; i < num_irrigatori; i++) {
    test >> sol[i].first >> sol[i].second;
  }
  std::sort(sol.begin(), sol.end());

  ll to_cover = 0;
  ll costo_calcolato = 0;
  for (const ii& irr : sol) {
    costo_calcolato += C;
    costo_calcolato += irr.second;
    if (irr.first <= 0 || irr.second <= 0) {
      ex(0.0, MALFORMED);
    }

    while (to_cover < N && reachable(seeds[to_cover], irr)) {
      to_cover += 1;
    }
  }

  double esito = 0.0;
  std::string messaggio = "";

  if (costo_riportato == -1) {
    messaggio += COST_MISSING;
  } else if (costo_riportato == costo_ottimo) {
    esito += PUNTI_COSTO;
    messaggio += COST_CORRECT;
  } else {  // minore o maggiore dell'ottimo
    messaggio += COST_WRONG;
  }

  if (to_cover < N) {
    messaggio += SEED_UNCOVERED;
  } else if (costo_calcolato > costo_ottimo) {
    messaggio += SEED_SUBOPTIMAL;
  } else if (costo_calcolato == costo_ottimo) {
    esito += PUNTI_SOLUZIONE;
    messaggio += SEED_OPTIMAL;
  } else {  // minore dell'ottimo
    ex(0.0, CHECKER_ERROR);
  }

  ex(esito, messaggio.c_str());
}
