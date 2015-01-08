/*
  Giovanni Mascellani <mascellani@poisson.phc.unipi.it>
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <set>
#include <cstring>

using namespace std;

int N, M;
bool real_scan = false;

void ex(const char *msg, float res)
{
  if(msg) {
    fprintf(stderr, "%s ", msg);
  }
  printf("%f\n", res);
  exit(0);
}

void maybe_ex(const char *msg, float res) {

  /* Esegue ex solo se l'errore è stato trovato nel file dell'utente;
     se l'errore è nel file "corretto", allora fallisce e basta per
     segnalare il problema agli amministratori. */

  if (real_scan) ex(msg, res);
  else {
    cerr << msg << endl;
    exit(1);
  }

}

set< set< int > > parse_file(FILE *f) {

  int G;

  char *line = NULL;
  size_t getline_len;
  int res;
  res = getline(&line, &getline_len, f);
  if (res < 0) maybe_ex("Output malformattato (manca la prima riga).", 0.0);
  int line_len = strlen(line);
  if (line[line_len-1] == '\n') line[line_len-1] = '\0';
  res = sscanf(line, "%d", &G);
  if (res != 1) maybe_ex("Output malformattato (non trovo nessun numero nella prima riga).", 0.0);

  set< set< int > > data;
  set< int > check_set;
  int number_num = 0;

  for (int i = 0; i < G; i++) {
    res = getline(&line, &getline_len, f);
    if (res < 0) maybe_ex("Output malformattato (mancano delle righe).", 0.0);
    line_len = strlen(line);
    if (line[line_len-1] == '\n') line[line_len-1] = '\0';
    set< int > line_data;
    char *strtok_param = line;
    int line_tok_num = -1;

    while (true) {
      char *token = strtok(strtok_param, " ");
      strtok_param = NULL;
      if (!token) {
	if (line_tok_num != 0) maybe_ex("Output malformato (mancano dei token).", 0.0);
	else break;
      }
      // Non ci scandalizziamo se ci sono spazi multipli
      if (strcmp(token, "") == 0) continue;
      int tmp;
      res = sscanf(token, "%d", &tmp);
      if (res != 1) maybe_ex("Output malformato (non trovo nessun numero).", 0.0);
      // TODO - Aggiungere un controllo che non ci sia altra roba dopo
      // la fine della riga
      if (tmp <= 0) maybe_ex("Output malformato (trovato un numero <= 0).", 0.0);
      if (tmp > N) maybe_ex("Output malformato (trovato un numero > N).", 0.0);

      if (line_tok_num == -1) {
	line_tok_num = tmp;
      } else {
	if (line_tok_num == 0) maybe_ex("Output malformato (troppi numeri su una riga).", 0.0);
	line_data.insert(tmp);
	check_set.insert(tmp);
	number_num++;
	line_tok_num--;
      }
    }

    data.insert(line_data);
  }

  // TODO - Aggiungere un controllo che non ci sia altra roba dopo le
  // G righe dichiarate

  // Quanti numeri ho trovato in tutto?
  if (check_set.size() != N) {
    maybe_ex("L'output prodotto non è una partizione (mancano alcuni numeri).", 0.0);
  } else if (number_num != N) {
    maybe_ex("L'output prodotto non è una partizione (alcuni numeri sono doppi).", 0.0);
  }

  return data;

}

int main(int argc, char *argv[])
{
  if(argc < 4)
    {
      cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
      return 1;
    }

  FILE *fin = fopen(argv[1], "r");
  FILE *fcor = fopen(argv[2], "r");
  FILE *fout = fopen(argv[3], "r");

  if(!fin)
    {
      cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
      return 1;
    }
  if(!fcor)
    {
      cerr << "Impossibile aprire il file di output corretto " << argv[2] << "." << endl;
      return 1;
    }
  if(!fout)
    ex("Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0);

  fscanf(fin, "%d %d", &N, &M);

  real_scan = false;
  set< set< int > > cor_sol = parse_file(fcor);
  real_scan = true;
  set< set< int > > out_sol = parse_file(fout);

  if (cor_sol == out_sol) ex("Output corretto.", 1.0);
  else ex("Output errato.", 0.0);

  return 0;
}
