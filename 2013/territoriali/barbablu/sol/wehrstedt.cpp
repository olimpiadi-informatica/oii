/*
  Luca Wehrstedt

  L'idea consiste nel prendere uno alla volta tutti i nodi senza aria e
  rimuoverli dal grafo, al fine di rimanere solo con i nodi pieni d'aria.
  Durante la rimozione del nodo v consideriamo ogni arco entrante (u, v) e
  ogni arco uscente (v, w). Se la somma dei loro pesi non supera 20, allora
  aggiungiamo l'arco (u, w) avente come peso la somma dei loro pesi.
  Una volta ottenuto un grafo con solo nodi pieni d'aria sara' sufficiente
  applicare l'algoritmo di Dijkstra per ottenere il risultato desiderato.
*/
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int n;
int m;
int c;
int k;

vector< vector< pair<int,int> > > edges;

vector<int> aired;

void leggi ()
{
    in >> n >> m >> c >> k;
    c -= 1;

    edges.assign(n, vector< pair<int,int> > ());

    int a, b, w;

    for (int i = 0; i < k; i += 1)
    {
        in >> a;
        aired.push_back(a-1);
    }

    for (int i = 0; i < m; i += 1)
    {
        in >> a >> b >> w;
        if (w <= 20)
        {
            edges[a-1].push_back(make_pair(b-1, w));
            edges[b-1].push_back(make_pair(a-1, w));
        }
    }
}

void remove_node (int idx)
{
    for (int i = 0; i < edges[idx].size(); i += 1)
    {
        // Per ogni arco (u, idx)
        int u = edges[idx][i].first;
        for (int j = i+1; j < edges[idx].size(); j += 1)
        {
            // Per ogni arco (idx, w)
            int w = edges[idx][j].first;
            if (edges[idx][i].second + edges[idx][j].second <= 20 &&
                edges[u].size() > 0 && edges[w].size() > 0)
            {
                edges[u].push_back(make_pair(w, edges[idx][i].second + edges[idx][j].second));
                edges[w].push_back(make_pair(u, edges[idx][i].second + edges[idx][j].second));
            }
        }
    }
    /* Non rimuoviamo gli archi entranti in questo nodo ma solo quelli uscenti.
       In questo modo creiamo un pozzo, che "non da fastidio" a Dijkstra.
     */
    edges[idx].clear();
}

void elabora ()
{
    // Rimuovi i nodi senza aria
    sort(aired.begin(), aired.end());
    for (int i = n-1; i > 0; i -= 1)
    {
        if (aired.back() == i)
        {
            aired.pop_back();
        }
        else
        {
            remove_node(i);
        }
    }

    // Calcola il cammino minimo con Dijkstra
    vector<int> d(n, 2000000000);

    priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > coda;

    d[0] = 0;
    coda.push(make_pair(0, 0));

    while (!coda.empty())
    {
        pair<int,int> top = coda.top();
        coda.pop();

        if (d[top.second] == top.first)
        {
            for (int i = 0; i < edges[top.second].size(); i += 1)
            {
                if (d[edges[top.second][i].first] > d[top.second] + edges[top.second][i].second)
                {
                    d[edges[top.second][i].first] = d[top.second] + edges[top.second][i].second;
                    coda.push(make_pair(d[edges[top.second][i].first], edges[top.second][i].first));
                }
            }
        }
    }

    if (d[c] < 2000000000)
    {
        out << d[c] << endl;
    }
    else
    {
        out << -1 << endl;
    }
}

int main ()
{
    leggi();
    elabora();
}
