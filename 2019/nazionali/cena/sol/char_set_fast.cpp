// Soluzione O(P*A*log(S))
// A è la max frequenza di un carattere (A <= 1000)

#include <bits/stdc++.h>
long long conta(int S, int s[], int P, int p[]) {

  long long out = 0ll, idx = 0ll;
  std::array<std::vector<long long>, 100> f;

  for(int i=0; i<S; i++) f[s[i]].push_back(i);

  for(long long first_it : f[p[0]]) {
    int j = 0, k = idx;
    do {
      auto it = std::lower_bound(f[p[j]].begin(), f[p[j]].end(), k);
      if(it != f[p[j]].end() && s[*it] == p[j]) k = (*it)+1;
      else break;
    } while(++j < P);
    if(P == j) out += (first_it+1-idx) * static_cast<long long>(S-k+1);
    else break;
    idx = first_it+1;
  }

  return out;
}
