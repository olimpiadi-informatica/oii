/*
 *  Soluzione di lungomare.
 *
 *  Autore: Giada Franz
 *
 *  Descrizione: Soluzione lineare che sfrutta il seguente lemma:
 *               Lemma: Mi trovo nel lido u. Sia v tale che minimizza P[v]+D[v] tra i v tali che
 *                      1) u < v
 *                      2) P[v] < P[u]+D[v]-D[u] (o equivalentemente P[v]-D[v] < P[u]-D[u] ) 
 *                      Allora esiste un percorso ottimale (cioè che minimizza la massima distanza percorsa sotto il sole)
 *                      dal lido u al lido N-1 tale che come prima "mossa" va dal lido u al lido v.
 * 
 *               Ricordiamo che la distanza fra il lido u e il lido v, con u < v, è (P[u]-D[u])+(P[v]+D[v]).
 *               
 *               Inoltre, dati due nodi u e v, i possibili casi sono 2:
 *               1) P[u]+D[u] <= P[v]+D[v] e P[u]-D[u] <= P[v]-D[v], allora non mi converrà mai fermarmi al lido v;
 *               2) P[u]+D[u] <= P[v]+D[v] e P[u]-D[u] >= P[v]-D[v], allora sommando le disuguaglianze ottengo D[u] <= D[v], cioè u <= v.
 * 
 */

#include <stdlib.h>
#include <iostream>
#include <stack>
using namespace std;

long long percorri(int N, long long L, long long D[], long long P[]) {
    
    /* risolvi è uno stack che contiene le coppie (P+D, P-D) */
    stack < pair <long long, long long> > risolvi;
    risolvi.push(make_pair(L, -L)); /* Coppia corrispondente alla fine del lungomare (D = L, P = 0) */
    
    for (int i = N-1; i >= 0; i--) {
        pair <long long, long long> u = risolvi.top();
        bool fatto = false;
        while (!fatto) {
            /* Se P[i] + D[i] e P[i] - D[i] sono maggiori uguali dei corrispondenti al top dello stack, 
             * sicuramente non mi converrà passare per quel lido */
            if (P[i] + D[i] >= u.first and P[i] - D[i] >= u.second) fatto = true;
            /* analogamente, se invece sono entrambi minori o uguali posso */
            else if (P[i] + D[i] <= u.first and P[i] - D[i] <= u.second) {
                risolvi.pop();
                u = risolvi.top();
            }
            /* per l'osservazione nei commenti, l'unico caso rimanente è quello in cui 
             * P[u]+D[u] <= u.first e P[u]-D[u] >= u.second e quindi aggiungo u allo stack */
            else {
                risolvi.push(make_pair(P[i] + D[i], P[i] - D[i]));
                fatto = true;
            }
        }
    }
    
    /* Modifico lo stack in modo da partire dall'inizio del lungomare (con P+D = 0, P-D = 0) */
    while (risolvi.top().second >= 0) risolvi.pop();
    risolvi.push(make_pair(0,0));
    
    /* Ora lo stack contiene i valori relativi a una successione di lidi u_1,...,u_k tali che u_{i+1} rispetta le condizioni del lemma per u_i
     * (cioè minimizza P[v]+D[v] tra quelli per cui u_i < v e P[v] < P[u_i]+D[v]-D[u_i]).
     * Quindi fermarsi nei lidi u_1,..,u_k è ottimale e mi rimane solo da calcolare la relativa risposta. */
    
    long long res = 0;
    pair <long long, long long> prec = risolvi.top();
    pair <long long, long long> at;
    risolvi.pop();
    
    while (!risolvi.empty()) {
        at = risolvi.top();
        risolvi.pop();
        res = max(res, at.first + prec.second); /* at.first + prec.second è la distanza fra il lido attuale e quello precedente (P[u_{i-1}]-D[u_{i-1}])+(P[u_i]+D[u_i]) */
        prec = at;
    }
    
    return res;
}
