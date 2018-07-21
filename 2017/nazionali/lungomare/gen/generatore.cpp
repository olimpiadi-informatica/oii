#include <iostream>
#include <vector>
#include <random>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <algorithm>

#define MAXN 10000000
#define MAXL 1000000000000000000ll

using namespace std;

mt19937 rgen;

const char* usage = "Generatore di \"lungomare\".\n\n"
    "Parametri:\n"
    "* N (numero)\n"
    "* L (lunghezza totale del lungomare)\n"
    "* P (lunghezza massima di una passerella)\n"
    "* U (tipo generazione, 0: tutto uguale, 1: passerelle uguali, 2: random, 3: da soluzione)\n"
    "* S (seed)\n"
    "\n"
    "Constraint:\n"
    "* 1 <= N <= %d\n"
    "* 1 <= L <= %lld\n"
    "* 1 <= P <= %lld\n";

/*
 * Funzioni di stampa modulari per file binari o in chiaro
 */
#define BINARY

#ifdef BINARY
void print_vectors(bool interleaved) {
}

template<typename T, typename ... Types>
void print_vectors(bool interleaved, const vector<T>& v, Types... args) {
    assert(write(STDOUT_FILENO, v.data(), v.size()*sizeof(T)) == v.size()*sizeof(T));
    print_vectors(interleaved, args ...);
}

template<typename T>
void write_stuff(T v) {
    assert(write(STDOUT_FILENO, &v, sizeof(T)) == sizeof(T));
}

template<>
void write_stuff(const char v[]) {
    assert(write(STDOUT_FILENO, v, strlen(v)) == strlen(v));
}

template<>
void write_stuff(string v) {
    int x = v.size();
    assert(write(STDOUT_FILENO, &x, sizeof(int)) == sizeof(int));
    assert(write(STDOUT_FILENO, v.data(), x) == x);
}

void print_nums() {
}

template<typename T, typename ... Types>
void print_nums(T v, Types... args) {
    write_stuff(v);
    print_nums(args ...);
}

#else

void print_line(int i) {
    cout << endl;
}

template<typename T, typename ... Types>
void print_line(int i, const vector<T>& v, Types... args) {
    cout << v[i] << ' ';
    print_line(i, args ...);
}

void print_vectors(bool interleaved) {
}

template<typename T, typename ... Types>
void print_vectors(bool interleaved, const vector<T>& v, Types... args) {
    if (interleaved) {
        for (int i=0; i<v.size(); i++)
            print_line(i, v, args ...);
    } else {
        for (const auto& x : v) cout << x << ' ';
        cout << endl;
        print_vectors(false, args ...);
    }
}

void print_nums() {
}

template<typename T>
void print_nums(T v) {
    cout << v << endl;
}

template<typename T, typename TT, typename ... Types>
void print_nums(T v, TT vv, Types... args) {
    cout << v << ' ';
    print_nums(vv, args ...);
}
#endif
/*
 * Fine
 */

long long randint(long long a, long long b) { // b incluso
    assert(a <= b);
    uniform_int_distribution<long long> dis(a,b);
    return dis(rgen);
}

template<typename T>
vector<T> sample(T mn, T mx, int N) { // mx escluso
    vector<T> v(N);
    for (int i=0; i<N; i++) v[i] = randint(mn, mx-N);
    sort(v.begin(), v.end());
    for (int i=0; i<N; i++) v[i] += i;
    return v;
}


struct pr {
    long long D, P;
    
    pr(long long DD, long long PP) : D(DD), P(PP) {}
    bool operator<(const pr& o) const {
        return (D < o.D);
    }
};


void run(long long N, long long L, long long P, int U) {
    assert(1 <= N and N <= MAXN);
    assert(N < L and L <= MAXL);
    assert(1 <= P and P <= MAXL);
    assert(0 <= U and U <= 4);
    print_nums(N, L);
    vector<long long> DD, PP;
    if (U == 0) {
        long long a = max(randint(1, (L-2)/(N-1)), randint(1, (L-2)/(N-1)));
        long long b = randint(1, L-1-(N-1)*a);
        if (randint(0,1)) P = L/2-a/2;
        DD.resize(N);
        PP.resize(N);
        for (int i=0; i<N; i++) DD[i] = a*i+b;
        for (int i=0; i<N; i++) PP[i] = P;
    }
    if (U == 1) {
        if (L <= 2*P) {
            DD = sample(1ll, L-1, N);
            PP.resize(N);
            for (int i=0; i<N; i++) PP[i] = P;
        }
        else {
            assert(L > 2*N);
            long long diff;
            int prima = randint(0,N-1);
            int dopo = randint(0,N-1);
        	if (dopo < prima) swap(prima, dopo);
            for (int j=0; j<100; j++) {
                DD.clear();
                DD.push_back(0);
                diff = randint((2*L-4*P)/(4+dopo-prima), 2*L/(4+dopo-prima));
                for (int i=prima; i<dopo; i++) DD.push_back(DD.back() + randint(1,diff-1));
                if (max(prima+diff, L-DD.back()-P-diff) <= min(P+diff, L-DD.back()-diff+dopo+1-N)) {
                    DD[0] = randint(max(prima+diff, L-DD.back()-P-diff),min(P+diff, L-DD.back()-diff+dopo+1-N));
                    break;
                }
                assert(j < 99);
            }
            for (int i=1; i<DD.size(); i++) DD[i] += DD[0];
//            for (const auto& x : DD) cout << x << ' ';
//            cout << endl;
            if (prima > 0) {
                long long frontier = randint(prima, DD[0]-diff);
//                cout << "ecco " << prima << ' ' << DD[0] << " @ " << diff << " : " << frontier << endl;
                auto v = sample(1ll, frontier, prima-1);
                v.push_back(frontier);
                DD.insert(DD.begin(), v.begin(), v.end());
//            for (const auto& x : DD) cout << x << ' ';
//            cout << endl;
            }
            if (dopo < N-1) {
                DD.push_back(randint(DD.back()+diff, L-N+dopo+1));
                auto v = sample(DD.back()+1, L, N-dopo-2);
                DD.insert(DD.end(), v.begin(), v.end());
//            for (const auto& x : DD) cout << x << ' ';
//            cout << endl;
            }
            PP.resize(N);
            for (int i=0; i<N; i++) PP[i] = P;
        }
    }
    if (U == 2) {
        DD = sample(1ll, L, N);
        PP.resize(N);
        for (int i=0; i<N; i++) PP[i] = randint(1, P);
    }
    if (U == 3) {
        vector<long long> Dsol, Psol, Dadd, Padd;
        long long C;
        for (int j=0; j<10; j++) {
            C = max(randint((L-1)/(N+1)+3, L), randint((L-1)/(N+1)+3, L));
            Dsol.clear();
            Dsol.push_back(0);
            Psol.clear();
            Psol.push_back(0);
            for (int i=0; i<N and Dsol.back() < L; i++) {
                Dsol.push_back(randint(1, C-1-Psol.back())+Dsol.back());
                Psol.push_back(C-Psol.back()-Dsol.back()+Dsol[Dsol.size()-2]);
            }
            if (Dsol.size() < 0.75*N) break;
            assert(j < 9);
        }
        Dadd = sample<long long>(1ll, L-Dsol.size()+2, N-Dsol.size()+2);
        Padd.resize(Dadd.size());
        int j = 1;
        for (int i=0; i<Dadd.size(); i++) {
            while (Dsol[j] <= Dadd[i]+j-1) j++;
            Dadd[i] += j-1;
            Padd[i] = C-(Dadd[i]-Dsol[j-1]+Psol[j-1]);
            Padd[i] = max(Padd[i], C-(Dsol[j]-Dadd[i]+Psol[j]));
            Padd[i] = randint(min(Padd[i],P),P);
        }
        //~ cout << Dsol.size() << " " << Dadd.size() << "\n";
        vector<pr> V;
        for (int i=1; i<Dsol.size()-1; i++)
            V.push_back(pr(Dsol[i],Psol[i]));
        for (int i=0; i<Dadd.size(); i++)
            V.push_back(pr(Dadd[i],Padd[i]));
        sort(V.begin(), V.end());
        DD.resize(N);
        PP.resize(N);
        for (int i=0; i<N; i++) {
            DD[i] = V[i].D;
            PP[i] = V[i].P;
        }
    }
    print_vectors(false, DD, PP);
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        FILE *fin = fopen(argv[1], "r");
        long long N;
        long long L;
        assert(fscanf(fin, "%lld %lld", &N, &L) == 2);
        vector<long long> DD(N), PP(N);
        for (int i=0; i<N; i++) assert(fscanf(fin, "%lld", &DD[i]) == 1);
        for (int i=0; i<N; i++) assert(fscanf(fin, "%lld", &PP[i]) == 1);
        print_nums(N, L);
        print_vectors(false, DD, PP);
        return 0;
    }
    if (argc != 6) {
        printf(usage, MAXN, MAXL, MAXL);
        return 1;
    }
    rgen.seed(stoi(argv[5]));
    run(stoi(argv[1]), stoll(argv[2]), stoll(argv[3]), stoi(argv[4]));
}
