/** 
 * Sorpasso in O(1)
 * Squalifica in O(log N)
 * Risposta in O(log N)
 * 
 **/

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#define MAXN 2000100

using namespace std;

struct nodo {
	int lb, ub;
	int to_do; // è la cosa da fare sui figli, che su di lui è già stata fatta
	int val_min, val_max; // contiene il valore minimo e massimo del sottoalbero
};

int N;
int posizioni[MAXN]; // posizioni[i] contiene l'id dell'i-esimo in classifica
int inverso[MAXN];
bool squalificato[MAXN]; // (serve davvero questo array?)
int precedente[MAXN]; // vale 0 se sono il primo della lista, precedente[i] dice l'id del tizio prima di i
int successivo[MAXN]; // idem con il tizio dopo

int in_gara;

nodo RT[MAXN*2];

void inizializza_RT();
void cancella_elemento_RT(int el, int root);
int cerca_elemento_RT(int el, int root);
void aggiorna_todo_RT(int root);

void inizia(int N, int* ids) {
	for (int i=1; i<=N; i++) posizioni[i] = ids[i-1]+1;
	in_gara = N;
    
	// Trovo la giusta potenza di 2
	int pow2 = 1;
	while (pow2 < N) pow2 = pow2*2;
	for (int i=N+1; i<=pow2; i++) posizioni[i] = i;
	::N = pow2;
	N = pow2;
	
	for (int i=1; i<=N; i++) inverso[posizioni[i]] = i;
	for (int i=1; i<=N; i++) precedente[i] = posizioni[inverso[i]-1];
	for (int i=1; i<=N; i++) successivo[i] = posizioni[inverso[i]+1];
	
	inizializza_RT();
}

void squalifica(int id) {
	id++;
	//assert(!squalificato[id]);
    
	in_gara--;
	squalificato[id] = true;
	int pos = inverso[id];
	precedente[successivo[id]] = precedente[id];
	successivo[precedente[id]] = successivo[id];
	
	cancella_elemento_RT(pos, 1);
}

void supera(int id) {
	id++;
	//assert(precedente[id] > 0);
	//assert(squalificato[id] == false);
	
	int pos1 = inverso[id];
	int pos2 = inverso[precedente[id]];
	swap(posizioni[pos1], posizioni[pos2]);
	swap(inverso[id], inverso[precedente[id]]);
	
	int prec = precedente[id];
	int succ = successivo[id];
	int precprec = precedente[prec];
	
	precedente[id] = precprec;
	precedente[prec] = id;
	precedente[succ] = prec;
	
	successivo[id] = prec;
	successivo[precprec] = id;
	successivo[prec] = succ;
	
	//cout << "Il precedente è " << prec << endl;
	//for (int i=1; i<=N; i++) cout << precedente[i] << " "; cout << endl;
	//for (int i=1; i<=N; i++) cout << successivo[i] << " "; cout << endl;
}

int partecipante(int id) {
	int pos = id;
	return posizioni[cerca_elemento_RT(pos, 1)]-1;
}

void inizializza_RT() {
	// Nodo root:
	RT[1].lb = 1;
	RT[1].ub = N;
	RT[1].to_do = 0;
	RT[1].val_min = 1;
	RT[1].val_max = N;
	
	// Nodi sotto
	for (int i=2; i<=N*2-1; i++) {
		if (i%2 == 0) {
			RT[i].lb = RT[i/2].lb;
			RT[i].ub = (RT[i/2].lb + RT[i/2].ub)/2;
		}
		else {
			RT[i].ub = RT[i/2].ub;
			RT[i].lb = (RT[i/2].lb + RT[i/2].ub)/2 + 1;
		}
		RT[i].to_do = 0;
		RT[i].val_min = RT[i].lb;
		RT[i].val_max = RT[i].ub;
	}
}

void cancella_elemento_RT(int el, int root) { // devo togliere 1 all'intervallo [el+1, N]
	// Controllo se sono fuori dal bound
	if (el+1 > RT[root].ub) return;
	
	// Controllo se sono interamente dentro
	if (el + 1 <= RT[root].lb) {
		RT[root].val_min = RT[root].val_min - 1;
		RT[root].val_max = RT[root].val_max - 1;
		RT[root].to_do = RT[root].to_do - 1;
		return;
	}
	
	// Controllo di non essere in una foglia, altrimenti ho sbagliato qualcosa...
	//assert(RT[root].lb != RT[root].ub);
	
	// Altrimenti, devo spezzare sui due figli
	// (Prima di tutto, propago il mio to_do sui figli)
	// Non è necessario in questo caso aggiornare il mio val_min perché resta lo stesso. Il val_max diminuisce di 1
	aggiorna_todo_RT(root);
	RT[root].val_max = RT[root].val_max - 1;
	
	cancella_elemento_RT(el, root*2);
	cancella_elemento_RT(el, root*2 + 1);
	
	//assert(RT[root].val_min == RT[root*2].val_min);
	//assert(RT[root].val_max == RT[root*2+1].val_max);
}

int cerca_elemento_RT(int el, int root) { // cerco l'indice più a destra che abbia "el" come valore
	// Se sono fuori, ritorno -1
	if (RT[root].val_min > el || RT[root].val_max < el) return -1;
	
	// Se sono in una foglia, ritorno il suo lb = ub
	if (RT[root].ub == RT[root].lb) {
		//assert(RT[root].val_min == RT[root].val_max);
		if (RT[root].val_min == el) return RT[root].lb;
		return -1;
	}
	
	// Altrimenti prima di tutto aggiorno i to_do
	aggiorna_todo_RT(root);
	
	// Poi chiedo ai figli e prendo la risposta più alta
	// return max(cerca_elemento_RT(el, root*2), cerca_elemento_RT(el, root*2+1)); // QUESTA DOVREBBE ESSERE LA COSA LENTA
    if (RT[root*2+1].val_min <= el) return cerca_elemento_RT(el, root*2+1);
    else return cerca_elemento_RT(el, root*2);
    
}

void aggiorna_todo_RT(int root) {
	int dx = root*2+1;
	int sx = root*2;
	
	RT[dx].val_min = RT[dx].val_min + RT[root].to_do;
	RT[sx].val_min = RT[sx].val_min + RT[root].to_do;
	RT[dx].val_max = RT[dx].val_max + RT[root].to_do;
	RT[sx].val_max = RT[sx].val_max + RT[root].to_do;
	
	RT[dx].to_do += RT[root].to_do;
	RT[sx].to_do += RT[root].to_do;
	RT[root].to_do = 0;
}
