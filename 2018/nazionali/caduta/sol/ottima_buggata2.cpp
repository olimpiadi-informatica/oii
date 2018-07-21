#include <algorithm>
#include <vector>
#include <assert.h>
#include <stdio.h>
typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;



stato_t correggi(int N, int altezze[], coppia_t* scambio) {
    for (int i=0; i<N; i++) {
        altezze[i] = altezze[i]-1;
        if (altezze[i] > N) altezze[i] = N;
    }

    // Calcola fin dove cadono le tessere se si parte da un certo punto.
    // Complessità O(N).
    std::vector<int> fall_until(N);
    fall_until[N-1] = altezze[N-1] + N;
    for (int i=N-1; i>-1; i--) {
        if (altezze[i] == 0) {
            fall_until[i] = i;
            continue;
        }
        int j = i+1;
        while (j <= i+altezze[i] && j < N) {
            if (j != fall_until[j]) {
                j = fall_until[j];
            } else if (j < i+altezze[i]) {
                j++;
            } else break;
        }
        fall_until[i] = j;
    }
    if (fall_until[0] >= N-1) return OK;
    // Calcolo di varie informazioni ausiliari.

    // Ultima tessera che cade partendo dall'inizio.
    int last_first_segment = fall_until[0];
    // Prima tessera possibile da cui partire perchè cada tutto da lì in fondo.
    int first_last_segment = N-1;
    for (int i=N-1; i>-1; i--) {
        if (fall_until[i] >= N-1) {
            first_last_segment = i;
        }
    }
    assert(last_first_segment < first_last_segment);
    // Tessera subito dopo la tessera i da cui partire perchè cada tutto da
    // quella tessera fino alla fine di quel segmento. È utile (e calcolato)
    // solo per il primo e l'ultimo segmento.
    std::vector<int> next_start(N, N-1);
    int next_to_reach = N-1;
    for (int i=N-1; i>first_last_segment; i--) {
        next_start[i] = next_to_reach;
        if (fall_until[i] >= N-1) {
            next_to_reach = i;
        }
    }
    next_to_reach = last_first_segment;
    for (int i=last_first_segment; i>-1; i--) {
        next_start[i] = next_to_reach;
        if (fall_until[i] >= last_first_segment) {
            next_to_reach = i;
        }
    }
    // Fin dove cadrebbero le tessere nell'ultimo segmento se assumo che da i
    // in poi abbiano tutte quante altezza 0 e che si parta dalla prima
    // tessera di ogni segmento. È utile solo per il primo e l'ultimo segmento.
    std::vector<int> last_fall(N, 0);
    int endpoint = 0;
    for (int i=0; i<N; i++) {
        last_fall[i] = endpoint;
        if (i+altezze[i]>endpoint) endpoint = i+altezze[i];
    }

    // Primo tentativo: cerco una tessera nell'ultimo segmento che sia
    // abbastanza alta per poter essere messa nel primo segmento e raggiungere
    // start_last_segment, ovvero
    //          last_first_segment + altezze[i] >= first_last_segment
    // e che inoltre sia tale che, anche se fosse sostituita con una tessera
    // di altezza 0, arriverei comunque a far cadere next_start[i], quindi
    //              last_fall[i] >= next_start[i]
    // Se trovo una tessera che soddisfa entrambe le caratteristiche, mi basta
    // scambiarla con last_first_segment.
    //
    // Un'altra possibilità analoga è se esiste un domino abbastanza alto per
    // coprire dalla fine del primo all'inizio dell'ultimo segmento, tale che
    // mettere un domino alto 0 al suo posto non rompe il primo segmento. Ovvero,
    // vale che
    //          last_first_segment + altezze[i] >= first_last_segment
    // e che
    //              last_fall[i] >= next_start[i]
    // come nel caso di uno scambio primo <--> ultimo segmento.
    for (int i=0; i<N; i++) {
        // Solo nel primo e nell'ultimo segmento
        if (i > last_first_segment && i < first_last_segment) continue;
        if (last_first_segment + altezze[i] < first_last_segment) continue;
        if (last_fall[i] < next_start[i]) continue;
        scambio->domino1 = last_first_segment;
        scambio->domino2 = i;
        return RISOLTO;
    }

    // Secondo tentativo: cerco una tessera nell'ultimo segmento che sia
    // abbastanza alta per poter essere messa nel primo segmento e raggiungere
    // next_start[i], ovvero per cui valga
    //          last_first_segment + altezze[i] >= next_start[i]
    // Questo tentativo funziona chiaramente solo per uno scambio con l'ultimo
    // segmento, visto che una tessera messa dopo non può far cadere tessere
    // che la precedono.
    for (int i=first_last_segment; i<N; i++) {
        if (last_first_segment + altezze[i] < next_start[i]) continue;
        scambio->domino1 = last_first_segment;
        scambio->domino2 = i;
        return RISOLTO;
    }

    // Terzo tentativo: se non sono in nessuna di queste situazioni, mi serve
    // una tessera i dall'ultimo segmento e una tessera j dal primo segmento
    // tali che 
    //              j+altezze[i] >= first_last_segment
    // e che
    //              i+altezze[j] >= next_start[i]
    // ovvero tali che dal primo segmento si arrivi all'ultimo e che l'ultimo
    // segmento non rimanga spezzato in due. Dato i, i candidati per j sono
    // compresi nel segmento
    //          [first_last_segment-altezze[i], last_first_segment]
    // e posso scegliere j come la tessera di massima altezza in
    // quell'intervallo. A quel punto rimane solo da verificare la seconda
    // condizione. Per fare tutto ciò, processo le tessere dell'ultimo
    // segmento in ordine crescente di altezza.
    //
    // Alternativamente, potrebbe essere sufficiente portare avanti una tessera
    // del primo segmento in modo da arrivare a coprire fino all'ultimo segmento
    // ma contemporaneamente da non spezzare il primo segmento: le condizioni
    // necessarie sono le stesse.
    std::vector<int> candidates;
    for (int i=first_last_segment; i<N; i++) candidates.push_back(i);
    for (int i=0; i<last_first_segment; i++) candidates.push_back(i);
    // TODO: sostituire con un radix/counting/... sort, se è più veloce.
    std::sort(candidates.begin(), candidates.end(), [&] (const int& a, const int& b) {
        return altezze[a] < altezze[b] || (altezze[a] == altezze[b] && a < b);
    });
    // Poichè altezze[last_first_segment] = 0, finchè il candidato non migliora
    // sappiamo che non avremo risposta, o altrimenti la avremmo avuta nei
    // tentativi precedenti.
    int best_j_candidate = last_first_segment;
    int last_tested_j_candidate = last_first_segment;
    for (auto i: candidates) {
        for (int jc = last_tested_j_candidate; jc >= first_last_segment-altezze[i]; jc--) {
            last_tested_j_candidate = jc;
            if (altezze[jc] > altezze[best_j_candidate])
                best_j_candidate = jc;
        }
        if (best_j_candidate == last_first_segment) continue;
        if (i+altezze[best_j_candidate] < next_start[i]) continue;
        scambio->domino1 = best_j_candidate;
        scambio->domino2 = i;
        return RISOLTO;
    }

    // Nessun altro scambio è possibile: chiaramente il primo dei due domini
    // deve appartenere al primo segmento (altrimenti non si arriva mai al
    // secondo segmento). Scambiare internamente al primo segmento è già stato
    // considerato, scambiare con l'ultimo anche. In entrambi i casi è
    // necessario che il domino messo nel primo segmento arrivi a coprire fino
    // all'inizio dell'ultimo, e che lo scambio non spezzi l'altro segmento.
    // Questo può avvenire solo se la tessera rimossa era inutile per chiudere
    // il segmento, se la tessera che l'ha sostituita è comunque abbastanza
    // alta o se la tessera che arriva all'inizio dell'ultimo segmento ripara
    // il gap che si viene a creare, da cui i tre casi considerati sopra.
    // Uno scambio tra una tessera del primo segmento e un qualsiasi altro
    // segmento che non sia nè il primo nè l'ultimo richiede che entrambi i
    // domini arrivino a coprire più avanti di dove arrivavano prima, ovvero
    // che
    //          altezze[i] + j > altezze[j] + j
    //          altezze[j] + i > altezze[i] + i
    // che però è chiaramente impossibile.

    // Se nessuno scambio funziona, il problema è impossibile
    return IMPOSSIBILE;
}
