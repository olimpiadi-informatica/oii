// Soluzione O(S²), per ogni inizio controlla se c'è compare P
#include <bits/stdc++.h>
long long conta(int S, int s[], int P, int p[])
{
  long long out = 0;
  for(int i=0; i<S-P+1; i++)
  {
    int j = 0, k = i;
    do if(s[k] == p[j]) j++;
    while(j < P && ++k < S);
    if(P == j) out += static_cast<long long>(S-k);
    else break;
  }
  return out;
}
