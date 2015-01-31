/*
 Stefano Maggiolo

 Soluzione quasi lineare. Si riconduce al problema del sottoarray
 contiguo di somma massima in un array A di interi (positivi o negativi)
 lungo N-1. L'unica differenza e` che si richiede che il sottoarray
 abbia lunghezza al piu` K.

 In pratica, il massimo sottoarray lungo al piu` K di A[0..i] che
 termina in posizione i (d'ora in poi M(i)) e`:
 
 - caso 1: M(i-1) ha lunghezza < K (cioe`, posso allungarlo), allora:
   - se aggiungere sum(M(i-1)) + A[i] > 0, allora M(i) = M(i-1) unito A[i];
   - viceversa, M(i) = vuoto;
 - caso 2: M(i-1) ha lunghezza = K, allora computo a mano M(i) (costo K).

 Ovviamente, il massimo e` il massimo tra gli M(i).
*/

#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 10000;

int N, K, valore[MAXN+1];
#if !defined(EVAL)
  istream &in(cin);
  ostream &out(cout);
#else
  ifstream in("input.txt");
  ofstream out("output.txt");
#endif

void
ricomputa_massimo_qui(int n, int &massimo_qui, int &massimo_qui_l)
{
  int corrente = 0;
  massimo_qui = 0;
  massimo_qui_l = 0;
  for (int i = n; i > n-K && i >= 1; i--)
    {
      corrente += valore[i] - valore[i-1];
      if (corrente > massimo_qui)
        {
          massimo_qui = corrente;
          massimo_qui_l = n-i+1;
        }
    }
}

int
main(void)
{
  int massimo = 0;
  int massimo_qui = 0;
  int massimo_qui_l = 0;
  in >> K >> N;
  in >> valore[0];
  
  for (int i = 1; i < N; i++)
    {
      int nuovo_valore;
      in >> valore[i];
      nuovo_valore = valore[i] - valore[i-1];
      
      if (massimo_qui_l < K)
        if (massimo_qui + nuovo_valore <= 0)
          {
            massimo_qui = 0;
            massimo_qui_l = 0;
          }
        else
          {
            massimo_qui += nuovo_valore;
            massimo_qui_l++;
          }
      else if (massimo_qui_l == K)
        ricomputa_massimo_qui(i, massimo_qui, massimo_qui_l);
      else
        fprintf(stderr, "Troppo lungo!");

      if (massimo_qui > massimo)
        massimo = massimo_qui;
      fprintf(stderr, "%5d %5d %5d %5d\n", i, massimo_qui, massimo_qui_l, massimo);
    }
  out << massimo << endl;
  return 0;
}
