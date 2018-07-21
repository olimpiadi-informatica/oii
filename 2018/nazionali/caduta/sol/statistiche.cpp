/**
 *  Soluzione lineare di caduta.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione:
 *      Come la soluzione, ma anziche' risolvere il problema stampa solo le statistiche
 *      di quanti scambi risolventi ci sono di ciascun tipo.
 */

#include <iostream>
using namespace std;

const int MAXN = 100000000;

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;


typedef enum {
    NESSUNO,
    UNO,
    MOLTI
} quanti_t;

// struttura che mantiene i due massimi di un insieme (con tag)
struct due_max {
    int m1, m2; // primo e secondo massimo
    int t1, t2; // rispettivi tag

    // costruttore vuoto
    due_max() {
        m1 = -1;
        m2 = -1;
    }
    
    // inserisci elemento con tag
    void inserisci(int x, int t) {
        if (x > m1) { // se x massimo
            m2 = m1;
            t2 = t1;
            m1 = x;
            t1 = t;
        }
        else if (x > m2) { // se x secondo massimo
            m2 = x;
            t2 = t;
        }
    }
    
    // quanti >= x, se uno il suo tag
    quanti_t maggiori(int x) {
        if (m2 >= x) return MOLTI;
        if (m1 >= x) return UNO;
        return NESSUNO;
    }
    
    // ritorna il tag del massimo
    int max() {
        return t1;
    }
};

int responsabile_dx[MAXN]; // pos. max di cui sono responsabile
int scambiabile_dx[MAXN];  // pos. max in competenza scambiabile senza rompere
int in_piedi_sx = 0;       // prima tessera che non cade
int in_piedi_dx = 0;       // ultima tessera che non cade

int NONCRITICO, AVANTI_PRESERVA, INDIETRO_PRESERVA, AVANTI_POCO, INDIETRO_ALTO;

const char* delim = "#><";

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
    due_max domini; // mantengo i due domini piu' coprenti
    for (int i=1; i<N; ++i) {
        domini.inserisci(i-1+altezze[i-1]-1, i-1); // inserisco domino precedente
        responsabile_dx[i] = i; // non sono ancora responsabile di niente
        quanti_t coprenti = domini.maggiori(i); // quanti mi coprono
        // ho trovato un domino che non cade
        if (coprenti == NESSUNO) {
            in_piedi_dx = i;
            if (in_piedi_sx == 0) in_piedi_sx = i;
            continue;
        }
        // se il competente e' responsabile di me
        int competente = domini.max();
        if (coprenti == UNO)
            responsabile_dx[competente] = i;
        // verifico se sono scambiabile con competente
        if (competente+altezze[i]-1 >= responsabile_dx[competente])
            scambiabile_dx[competente] = i;
    }
    
//    for (int i=0; i<N; i++) cout << altezze[i] << "\t";
//    cout << endl;
//    for (int i=0; i<N; i++) cout << responsabile_dx[i] << "\t";
//    cout << endl;
//    for (int i=0; i<N; i++) cout << scambiabile_dx[i] << "\t";
//    cout << endl;
//    for (int i=0; i<N; i++) cout << i << "\t";
//    cout << endl;
//    cout << "[" << in_piedi_sx << "," << in_piedi_dx << "]\n";
    
    // se non ho trovato tessere che cadono
    if (in_piedi_sx == 0) return OK;
    // calcolo domini piu' alti che cadono
    int cade_dx_alto[in_piedi_sx];  // pos. del piu' alto a dx che gia' cade
    cade_dx_alto[in_piedi_sx-1] = in_piedi_sx-1;
    for (int i=in_piedi_sx-2; i>=0; --i)
        if (altezze[i] > altezze[cade_dx_alto[i+1]])
             cade_dx_alto[i] = i;
        else cade_dx_alto[i] = cade_dx_alto[i+1];
    // provo i domini che sperano di risolvere la situazione
    for (int i=0; i<N; ++i) if (in_piedi_sx-1+altezze[i]-1 >= in_piedi_dx) {
        int idelim;
        // provo il domino piu' alto da cui raggiungo chi non cade
        int alto = cade_dx_alto[in_piedi_dx-(altezze[i]-1)];
        if (i+altezze[alto]-1 >= responsabile_dx[i]) { // se non mi rovina
            if (responsabile_dx[i] == i) NONCRITICO++, idelim=0;
            else if (i < in_piedi_sx) AVANTI_PRESERVA++, idelim=1;
            else INDIETRO_PRESERVA++, idelim=2;
            cerr << "(" << i << delim[idelim] << alto << ") ";
        }
        // provo pos. in competenza piu' avanti che non rovina
        if (i < in_piedi_sx and scambiabile_dx[i]+altezze[i]-1 >= in_piedi_dx) {
            AVANTI_POCO++;
            cerr << "<" << i << "," << scambiabile_dx[i] << "> ";
        }
        // provo se anche da indietro copro le mie responsabilita'
        if (i >= in_piedi_sx and in_piedi_sx-1+altezze[i]-1 >= responsabile_dx[i]) {
            INDIETRO_ALTO++;
            cerr << "[" << i << "," << in_piedi_sx-1 << "] ";
        }
    }
    cerr << endl;
    cerr << "non critico:       " << NONCRITICO << endl;
    cerr << "avanti preserva:   " << AVANTI_PRESERVA << endl;
    cerr << "indietro preserva: " << INDIETRO_PRESERVA << endl;
    cerr << "avanti poco:       " << AVANTI_POCO << endl;
    cerr << "indietro alto:     " << INDIETRO_ALTO << endl;
    exit(0);
}
