/**
 *  Soluzione lineare di caduta.
 *
 *  Autore: Giorgio Audrito
 *
 *  Descrizione:
 *      Scandisco i domini per individuare chi e' coperto da nessuno, uno o piu' domini.
 *      Quelli coperti da piu' domini saranno sempre coperti e quindi non sono un problema.
 *      Di quelli coperti da nessuno mi tengo il primo e l'ultimo, che delimitano l'area critica.
 *      Per tutti quelli coperti da uno, segno nel domino che li copre l'altezza minima che deve
 *      avere per continuare a coprirlo.
 *      Inoltre, mi segno per ogni domino importante quanto avanti puo' essere scambiato nel suo
 *      intervallo di competenza (dove e' il max) senza rompere l'esistente.
 *      Precomputo anche quanto e' lungo il piu' alto domino nei suffissi dei domini che cadono.
 *      A questo punto per ogni domino determino in tempo costante se risolve il problema.
 */

#include<vector>

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

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
    std::vector<int> responsabile_dx(N); // pos. max di cui sono responsabile
    std::vector<int> scambiabile_dx(N);  // pos. max in competenza scambiabile senza rompere
    int in_piedi_sx = 0;            // prima tessera che non cade
    int in_piedi_dx = 0;            // ultima tessera che non cade
    
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
    // se non ho trovato tessere che cadono
    if (in_piedi_sx == 0) return OK;
    // calcolo domini piu' alti che cadono
    std::vector<int> cade_dx_alto(in_piedi_sx); // pos. del piu' alto a dx che gia' cade
    cade_dx_alto[in_piedi_sx-1] = in_piedi_sx-1;
    for (int i=in_piedi_sx-2; i>=0; --i)
        if (altezze[i] > altezze[cade_dx_alto[i+1]])
             cade_dx_alto[i] = i;
        else cade_dx_alto[i] = cade_dx_alto[i+1];
    // provo i domini che sperano di risolvere la situazione
    for (int i=0; i<N; ++i) if (in_piedi_sx-1+altezze[i]-1 >= in_piedi_dx) {
        scambio->domino1 = i;
        // provo il domino piu' alto da cui raggiungo chi non cade
        int alto = cade_dx_alto[in_piedi_dx-(altezze[i]-1)];
        if (i+altezze[alto]-1 >= responsabile_dx[i]) { // se non mi rovina
            scambio->domino2 = alto;
            return RISOLTO;
        }
        // provo pos. in competenza piu' avanti che non rovina
        if (i < in_piedi_sx and scambiabile_dx[i]+altezze[i]-1 >= in_piedi_dx) {
            scambio->domino2 = scambiabile_dx[i];
            return RISOLTO;
        }
        // provo se anche da indietro copro le mie responsabilita'
        if (i >= in_piedi_sx and in_piedi_sx-1+altezze[i]-1 >= responsabile_dx[i]) {
            scambio->domino2 = in_piedi_sx-1;
            return RISOLTO;
        }
    }
    return IMPOSSIBILE; // non ci sono altri casi
}
