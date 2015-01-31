/*
 Stefano Maggiolo

 N e` il numero di vagoni di tipo A (o equivalentemente di tipo B).

 Se N e` pari, mi riconduco al caso N dispari (piu` precisamente,
 tolgo 3 da N) in questo modo:

                     12
           1         ++
           +        NNN
 123...   NN...     222      Mossa

 AAAAAA..AABB..BBBBBB**      N     2N+1
 AAAAAA..A**B..BBBBBBAB      2N-2  N
 AAAAAA..ABBB..BBB**BAB      2     2N-2
 A**AAA..ABBB..BBBAABAB      2N-3  2
 ABAAAA..ABBB..BB**ABAB      
   ================      <-- istanza N-3 ... risolvo ...
 ABABAB..ABAB..AB**ABAB      2N+1  2N-3
 ABABAB..ABAB..ABABAB**

 Se N e` dispari, mi riconduco al caso N-2 (ancora dispari)

                   12
          1        ++
          +       NNN
 123...  NN...    222      Mossa

 AAAAA..AABB..BBBBB**      2     2N+1
 A**AA..AABB..BBBBBAA      2N    2
 ABAAA..AABB..BBBB**A      2N-2  2N
 ABAAA..AABB..BB**BBA      2N+1  2N-2
 ABAAA..AABB..BBBAB**      2N+1  2N-2
   ==============  ==  <-- istanza N-2, il fatto che sia spezzata
                           non importa, perche' la lettera prima
                           delle posizioni vuote e` una B ed e`
                           l'unica cosa che mi serve

 Quindi per la ricorsione passo N, inizio (la posizione della prima A)
 e ultimi, la posizione del primo *). L'unica cosa da capire e` quando
 usare ultimi e quando usare 2N+1, ma dopo un piccolo esempio si
 capisce. Notare che queste soluzioni funzionano anche nei casi
 limite, cioe` per N=3 si arriva all'istanza N=1 con le posizioni
 libere alla fine, cioe` alla soluzione; per N=4 si arriva ancora a
 N=1.
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
esegui_dispari(int N, int inizio, int ultimi)
{
  out << 2+inizio << " " << ultimi << endl;
  out << ultimi-1 << " " << 2+inizio << endl;
  out << 2*N-2+inizio << " " << ultimi-1 << endl;
  out << ultimi << " " << 2*N-2+inizio << endl;
  if (N > 3)
    esegui_dispari(N-2, inizio+2, ultimi);
}

void
esegui_pari(int N, int inizio, int ultimi)
{
  out << N+inizio << " " << ultimi << endl;
  out << 2*N-2+inizio << " " << N+inizio << endl;
  out << 2+inizio << " " << 2*N-2+inizio << endl;
  out << 2*N-3+inizio << " " << 2+inizio << endl;
  if (N > 4)
      esegui_dispari(N-3, inizio+2, ultimi-4);
  out << 2*N+1+2*inizio << " " << 2*N-3+inizio << endl;
    
}

int
main(void)
{

  in >> N;
  if (N % 2 == 0)
    {
      out << 2*N-3 << " " << N << endl;
      esegui_pari(N, 0, 2*N+1);
    }
  else
    {
      out << 2*N-2 << " " << N << endl;
      esegui_dispari(N, 0, 2*N+1);
    }
  
  return 0;
}
