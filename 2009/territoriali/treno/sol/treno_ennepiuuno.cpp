/*
 Stefano Maggiolo
*/

#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 1000;

int N;
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

void
o(int x)
{
  static int vuoto = 2*N+1;
  out << x+1 << " " << vuoto << endl;
  vuoto = x+1;
}

int
main(void)
{
  in >> N;
  out << N+1 << " " << N << endl;
  if (N == 3)
    {
      o(1);
      o(5);
      o(3);
      o(6);
    }
  else if (N == 4)
    {
      o(3);
      o(1);
      o(5);
      o(2);
      o(8);
    }
  else if (N % 4 == 0)
    {
      int M = N/4;

      o(3);
      o(2*N-3);
      o(2*N-1);
      for (int i = 1; i < M-1; i++)
        {
          o(N-2+4*i);
          o(3+4*i);
        }
      o(2*(N-3));

      for (int i = 0; i < M; i++)
        {
          o(4*i);
          o(N-1+4*i);
        }
      o(2*N);
    }
  else if (N % 4 == 2)
    {
      int M = (N-2)/4;

      o(1);
      o(2*N-3);
      o(2*N-1);
      for (int i = 1; i < M; i++)
        {
          o(N-2+4*i);
          o(1+4*i);
        }
      o(2*N-5);

      for (int i = 0; i < M; i++)
        {
          o(2+4*i);
          o(N-1+4*i);
        }
      o(2*N);
    }
  else if (N % 4 == 1)
    {
      int M = (N-1)/4;

      o(2);
      o(2*N-3);
      o(2*N-1);
      for (int i = 1; i < M; i++)
        {
          o(N-2+4*i);
          o(2+4*i);
        }
      o(2*(N-2));

      for (int i = 0; i < M-1; i++)
        {
          o(1+4*i);
          o(N+1+4*i);
        }
      o(N-4);
      o(2*N);
    }
  else if (N % 4 == 3)
    {
      int M = (N-3)/4;

      o(1);
      o(2*N-3);
      o(2*N-1);
      for (int i = 1; i <= M; i++)
        {
          o(N-3+4*i);
          o(1+4*i);
        }

      for (int i = 0; i < M; i++)
        {
          o(2+4*i);
          o(N+2+4*i);
        }
      o(2*N);
    }

  return 0;
}
