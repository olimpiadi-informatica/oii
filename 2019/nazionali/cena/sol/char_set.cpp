// Soluzione O(S*P*log(C)), come la quadratica ma una dei set sui char per velocizzare la ricerca
// C è la max frequenza di un carattere in S
#include <bits/stdc++.h>

long long conta(int S, int s[], int P, int p[])
{
  long long out = 0;
  std::array<std::set<int>, 100> f;
  for(int i=0; i<S; i++) f[s[i]].insert(i);
  for(int i=0; i<S; i++)
  {
    int j = 0, k = i;
    do {
      auto it = f[p[j]].lower_bound(k);
      if(it != f[p[j]].end() && s[*it] == p[j])
        k = (*it)+1;
      else break;
    } while(++j < P && k < S);
    if(P == j) out += static_cast<long long>(S-k+1);
    else break;
  }
  return out;
}
