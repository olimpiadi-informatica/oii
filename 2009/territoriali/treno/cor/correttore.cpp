/*
  Stefano Maggiolo (modificato da Roberto)
  (con qualche adattamento di William, gennaio 2015)
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAXN = 1000;

int N;
int K;
int actual_N;

void
ex(const char *msg, float res)
{
  if (msg) {
    fprintf(stderr, "[\x1b[1m\x1b[31m%s\x1b[m] ", msg);
  }
  printf("%f\n", res);
  exit(0);
}


int
main(int argc, char *argv[])
{
  /* In questo modo funziona sia se si vuole un correttore
     standalone (correttore file_da_testare), sia se si vuole
     testare con make test_*
  */
  if(argc != 4)
    {
      cerr << "Usage: " << argv[0] << "  <input.txt>  <output.txt>  <output_elaborato.txt>" << endl;
      return 1;
    }

  ifstream fin(argv[1]);
  ifstream fout(argv[2]);
  ifstream fout_elab(argv[3]);

  if (!fin) {
    ex("Impossibile aprire in lettura il file di input.", 0.0f);
  }

  if (!fout) {
    ex("Impossibile aprire in lettura il file di output.", 0.0);
  }

  if (!fout_elab) {
    ex("Impossibile aprire in lettura il file output generato dal codice sottoposto al problema.", 0.0);
  }

  fin >> actual_N;
  fout_elab >> K >> N;

  if (N != actual_N)
    ex("Valore di N errato.", 0.0f);
  if (!fout_elab)
    ex("Output malformato.", 0.0f);
  if (K > 3*N)
    ex("Numero di scambi troppo elevato.", 0.0f);
  else
    {
      int libero = 2 * N + 1;
      int a, b;
      int posizioni[2*MAXN+3];
      for (int i = 1; i <= 2*N; i++)
        posizioni[i] = i;
      posizioni[2*N+1] = 0;
      posizioni[2*N+2] = 0;

      for (int i = 0; i < K; i++)
        {
          fout_elab >> a >> b;
          if (!fout_elab)
            ex("Output malformato.", 0.0f);
          if (b != libero)
            ex("Punto di arrivo non valido.", 0.0f);
          if (a == libero || a == libero-1 || a == libero+1 || a < 1 || a > 2*N+1)
            ex("Punto di partenza non valido.", 0.0f);
          posizioni[b] = posizioni[a];
          posizioni[b+1] = posizioni[a+1];
          posizioni[a] = 0;
          posizioni[a+1] = 0;
          libero = a;
        }

      int corretto = 0;
      if (libero != 2 * N + 1)
        corretto = 1;
      else
        for (int i = 1; i <= 2*N; i++)
          {
            if ((i % 2 == 1 && posizioni[i] > N) || (i % 2 == 0 && posizioni[i] <= N))
              {
                corretto = 2;
                break;
              }
          }

      if (corretto == 0) {
        float voto = 3 * N - K;
        voto /= 2 * N - 1;
        voto *= 4;
        voto += 6;
        stringstream ss;
        ss << "Output corretto (voto: " << setprecision(2) << fixed << voto << " / 10.00).";
        ex(ss.str().c_str(), 1.0f);
      } else if (corretto == 1)
        ex("Ultime posizioni non libere.", 0.0f);
      else
        ex("Vagoni in posizione errata.", 0.0f);
    }
}
