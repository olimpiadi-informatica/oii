// Soluzione O(CP)

#include <bits/stdc++.h>

long long conta(int S, int s[], int P, int p[]) {

  long long out = 0ll, idx = 0ll;

  std::array<std::vector<long long>, 100> din;
  std::array<bool, 100> f;

  for(int i=0; i<100; i++) f[i] = false;
  for(int i=0; i<P; i++) f[p[i]] = true;

  for(int i=0; i<100; i++)
  {
    if(!f[i]) continue;
    din[i].reserve(S+1);
    din[i][S] = S+1;
    for(int j=S-1; j>=0; j--) din[i][j] = (s[j] == i) ? j : din[i][j+1];
  }

  for(int i=din[p[0]][0]; i<S-P+1; i=din[p[0]][i+1])
  {
    int j = 0, k = idx;

    do k = din[p[j]][k]+1;
    while(k < S+1 && ++j < P);

    if(P == j) out += (i+1-idx) * static_cast<long long>(S-k+1);
    else break;

    idx = i+1;

  }

  return out;
}
