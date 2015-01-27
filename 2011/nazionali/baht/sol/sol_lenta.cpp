/*
  Stefano Maggiolo.

  Soluzione lenta: per ogni valore, controllo se e` possibile comporlo
  con le monete di valore inferiore. Qualche taglio usando
  l'ordinamento delle monete.
*/

#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXP = 1000;
const int MAXN = 10000;
const int MAXV = 1 << 20;
const int MAXSUM = ((unsigned int)1 << 31) - 1;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int P;
int N;
int SUM;
int valori[MAXN];

int v;
int top;
int sum;
int st;
int rem[MAXN+1];

bool
calcola()
{
  if (sum == v)
    return true;
  else if (sum > v)
    return false;
  else if (sum + rem[st] < v)
    return false;
  else if (sum + rem[st] == v)
    return true;
  else if (st == top)
    return false;
  else
    {
      st++;
      if (calcola())
        return true;

      sum += valori[st-1];
      if (calcola())
        return true;
      sum -= valori[st-1];
      st--;
    }
  return false;
}

int
possibile(int w)
{
  v = w;
  for (top = 0; top < N && valori[top] < v; top++);
  if (top < N && valori[top] == v)
    return true;
  else
    {
      sum = 0;
      for (int i = top-1; i >= 0; i--)
        {
          sum += valori[i];
          rem[i] = sum;
        }
      rem[top] = 0;
      sum = 0;
      st = 0;
      return calcola();
    }
}

int
main(void)
{
  in >> P;
  assert(1 <= P && P <= MAXP);
  for (int p = 0; p < P; p++)
    {
      in >> N;
      SUM = 0;
      assert(1 <= N && N <= MAXN);
      for (int n = 0; n < N; n++)
        {
          in >> valori[n];
          assert(1 <= valori[n] && valori[n] <= MAXV);
          SUM += valori[n];
        }
      assert(1 <= SUM && SUM <= MAXSUM);
      sort(valori, valori+N);
      int sol = 1;
      while (possibile(sol)) sol++;
      out << sol << endl;
    }
  return 0;
}
