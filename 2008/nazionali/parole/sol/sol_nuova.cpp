/* Soluzione O(N*T), dove T = numero di prefissi di S che sono anche
   suffissi.

   La base sono due array: hanno e hanno_un_po.

   hanno[k] = # di stringhe di lunghezza k che contengono S
   hanno_un_po[k] = # di stringhe di lunghezza k che contengono S e
                    terminano con S[0...M-2]

           

  *** Passo base k = 0, M-1:

  hanno[k] = hanno_un_po[k] = 0;

  *** Passo k = M, ..., N

  Aggiornare hanno e` facile: hanno[k] conta stringhe della forma:

  ... S ... 0   # = hanno[k-1]
  ... S ... 1   # = hanno[k-1]
  ...   ... S   # = 2^{k-M}

  ma conta due volte quelle della forma

  ... S ... S   # = hanno_un_po[k-1]

  quindi hanno[k] = 2*hanno[k-1] + 2^{k-M} - hanno_un_po[k-1]

  Invece, hanno_un_po[k] conta i seguenti:

  ... S ... S[0...M-2]              # = h[i-M+1]
  ... S[0...M-t-1]S[0...M-2]        # = 2^{i-M+1 - (M-t)} (per ogni t in sovrapposizioni)
  
  Ma conto due volte quelle della forma

  ... S ... S[0...M-t-1]S[0...M-2]  # = hp[i-(M-t)]

  Quindi hp[i] = h[i-M+1] + sum_{t in s} (2^{i-M+1-(M-t)} - hp[i-(M-t)])

*/

#include <vector>
#include <cstdio>

using namespace std;

const int MAXM = 100000;
const int MAXN = 100000;
const int MODULO = 2011;

void calcola_sovrapposizioni(void);
void calcola_potenze(void);
int hanno_S_nelle_prime_i(int i);
int non_hanno_S_nelle_prime_i(int i);
int hanno_S_nelle_prime_i_con_un_po_di_S(int i);
int non_hanno_S_nelle_prime_i_con_un_po_di_S(int i);

int N, M;
char S[MAXM];
vector<int> sovrapposizione; // indici dei suffissi di S che sono anche prefissi
int numero_sovrapposizioni = 0;
vector<int> hanno(MAXN+1);
vector<int> hanno_un_po(MAXN+1);
vector<int> potenze; // potenze di 2 modulate e precalcolate

int
main(void)
{
    FILE * fin, *fout;
#if !defined(EVAL)
    fin = stdin; fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    fscanf(fin, "%d %d", &M, &N);
    fscanf(fin, "%s", S+1); // qui l'array parte da 1, 0 = stringa vuota

    calcola_sovrapposizioni();
    calcola_potenze();
    //    for (vector<int>::iterator j = sovrapposizione.begin(); j != sovrapposizione.end(); ++j)
    //      fprintf(stderr, "Sovrapposizione: %d\n", *j);

    for (int i = 0; i < M; i++)
      {
        hanno[i] = hanno_un_po[i] = 0;
      }
    for (int i = M; i <= N; i++)
      {
        hanno_un_po[i] = hanno_S_nelle_prime_i_con_un_po_di_S(i);
        hanno[i] = hanno_S_nelle_prime_i(i);
      }
    fprintf(fout, "%d\n", (MODULO + potenze[N] - hanno_S_nelle_prime_i(N)) % MODULO);
    
    fflush(fout);
    return 0;
}

void
calcola_sovrapposizioni(void)
{
  for (int i = M-1; i >= 1; --i)
    {
      bool uguali = true;
      for (int j = 1; j <= i; j++)
        if (S[j] != S[j+M-i])
          {
            uguali = false;
            break;
          }
      if (uguali)
        {
          sovrapposizione.push_back(i);
          ++numero_sovrapposizioni;
        }
    }
}

void
calcola_potenze(void)
{
  int risultato = 1;
  potenze.push_back(risultato);
  for (int i = 0; i < N; i++)
    {
      risultato = (risultato << 1) % MODULO;
      potenze.push_back(risultato);
    }
}

// Numero di stringhe di lunghezza i contenenti S
int
hanno_S_nelle_prime_i(int i)
{
  int risultato = 0;
  risultato = (MODULO + 2 * hanno[i-1] + potenze[i-M] - hanno_un_po[i-1]) % MODULO;
  //  fprintf(stderr, "Hanno S nelle prime %d: %d\n", i, risultato);
  return risultato % MODULO;
}

// Numero di stringhe di lunghezza i, terminanti con i primi M-1 caratteri
// di S, contenenti S
int
hanno_S_nelle_prime_i_con_un_po_di_S(int i)
{
  int risultato;
  risultato = hanno[i-M+1] % MODULO;
  for (int j = 0; j < numero_sovrapposizioni; ++j)
    if (2 * M - 1 - sovrapposizione[j] <= i)
      risultato = risultato + MODULO + potenze[i-2*M+sovrapposizione[j]+1] - hanno_un_po[i-M+sovrapposizione[j]];
    else
      break;
  //  fprintf(stderr, "Hanno S nelle prime %d con un po di S: %d\n", i, risultato);
  return risultato % MODULO;
}
