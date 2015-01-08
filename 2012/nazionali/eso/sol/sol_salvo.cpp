/*
  Autore: Salvatore Ingala

  Descrizione: O(NMlog(M)), probabilità di fallimento in caso di collisioni della funzione hash (ma è trascurabile).
  Uso i long per ridurre la probabilità di collisioni, ma anche con int a 32 bit la probabilità dovrebbe essere minima.

  Applico ripetutamente questa trasformazione: prendo una sotto-ESO che contiene solo numeri, normalizzo (ordino nel caso di
  sotto-ESO (), fisso uno dei due ordinamenti possibili nel caso di []) e rimpiazzo tutta la sotto-eso con un hash del vettore
  dei numeri contenuti (con seed diverso a seconda che sia di tipo () o []). Alla fine, per ogni ESO ottengo un unico numero,
  che è una "fingerprint" per la classe di equivalenza (a meno di collisioni).
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int N, M;
vector<pair<unsigned long int, int> > V;

unsigned long int _hash(unsigned long int seed, vector<unsigned long int> &values){
	unsigned long int result = seed;
	for (unsigned int i = 0; i < values.size(); i++)
		result += values[i] * 3613571249989LLU + 230563453LLU;
	return result;
}

//Legge un'ESO, la normalizza e restituisce la sua fingerprint
unsigned long int readESO(int first){
	int n;
	vector<unsigned long int> v;
	if (first == -1){ //(
		for (in >> n; n != -2; in >> n)
			v.push_back(readESO(n));
		sort(v.begin(), v.end());
		return _hash(1, v);
	} else if (first == -3){ //[
		for (in >> n; n != -4; in >> n)
			v.push_back(readESO(n));

		//Fisso uno dei due possibili ordinamenti in modo univoco
		//(prendo il vettore lessicograficamente minore tra v e il suo inverso)
		for (unsigned int i = 0; i <= v.size()/2; i++)
			if (v[i] > v[v.size()-i-1]){
				reverse(v.begin(), v.end());
				break;
			} else if (v[i] < v[v.size()-i-1])
				break;

		return _hash(2, v);
	} else if (first >= 0) //numero
		return first;
	else
		assert(false);
}

void print_row(vector<int> &row){
	out << row.size();
	for (unsigned int j = 0; j < row.size(); j++)
		out << " " << row[j] + 1;
	out << "\n";
}

int main(){
	in >> N >> M;

	for (int i = 0; i < N; i++){
		int n;
		in >> n;
		V.push_back(make_pair(readESO(n), i));
	}

	sort(V.begin(), V.end());

	int count = 1;
	for (unsigned int i = 1; i < V.size(); i++)
		if (V[i].first != V[i-1].first)
			count++;

	out << count << endl;
	
	vector<int> row;
	for (unsigned int i = 0; i < V.size(); i++){
		if (i > 0 && V[i].first != V[i-1].first){
			print_row(row);
			row.clear();
		}
		row.push_back(V[i].second);
	}
	print_row(row);
	
	return 0;
}

