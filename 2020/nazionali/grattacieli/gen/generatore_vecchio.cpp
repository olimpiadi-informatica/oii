#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

/* random N M L
 * disconnected N M L
 * limited_height N M L H
 * line N L
 * tree N L
 * dijkstra N
 */

void gen_random(int argc, char **argv)
{
    assert(argc == 3);

    int N = atoi(argv[0]);
    int M = atoi(argv[1]);
    int L = atoi(argv[2]);

    assert(N >= 1);
    assert(M <= N*(N-1));
    assert(M >= N);

    srand(N^M^L);

    vector<set<int>> nodes;
    nodes.assign(N, set<int>());

    for(int i = 0; i < N && i < M; i++)
        nodes[i].insert((i + 1) % N);
    
    for(int i = 0; i < M - N; i++)
    {
        int a, b;
        while(true)
        {
            a = rand() % N;
            do
            {
                b = rand() % N;
            }
            while(a == b);
            if(nodes[a].find(b) == nodes[a].end())
                break;
        }
        nodes[a].insert(b);
    }

    vector<int> ids(N, 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    printf("%d %d\n", N, M);
    for(int i = 0; i < N; i++)
        for(int v : nodes[i])
            printf("%d %d %d\n", ids[i], ids[v], rand() % L);
}

void gen_disconnected(int argc, char **argv)
{
    assert(argc == 3);

    int N = atoi(argv[0]);
    int M = atoi(argv[1]);
    int L = atoi(argv[2]);

    assert(N >= 1);
    assert(M <= N*(N-1));

    srand(N^M^L);

    vector<set<int>> nodes;
    nodes.assign(N, set<int>());

    int len1 = (rand() % N) + 1;
    int len2 = N - len1;

    int edges = 0;

    for(int i = 0; i < len1 && edges < M; i++)
    {
        if(i != (i + 1) % len1)
        {
            nodes[i].insert((i + 1) % len1);
            edges++;
        }
    }
    
    for(int i = 0; i < len2 && edges < M; i++)
    {
        if(i != (i + 1) % len2)
        {
            nodes[len1 + i].insert(len1 + ((i + 1) % len2));
            edges++;
        }
    }
    
    // Connect the cycles in only one direction
    for(int i = 0; i < len1; i++)
    {
        nodes[len1 + (rand() % len2)].insert(i);
        edges++;
    }

    // Remaining random edges
    int edges1 = len1, edges2 = len2;
    while(edges < M)
    {
        if(edges1 < len1 * (len1 - 1))
        {
            int a, b;
            while(true)
            {
                a = rand() % len1;
                do { b = rand() % len1; }
                while(a == b);
                if(nodes[a].find(b) == nodes[a].end())
                    break;
            }
            nodes[a].insert(b);
            edges++; edges1++;
        }
        else if(edges2 < len2 * (len2 - 1))
        {
            int a, b;
            while(true)
            {
                a = len1 + (rand() % len2);
                do { b = len1 + (rand() % len2); }
                while(a == b);
                if(nodes[a].find(b) == nodes[a].end())
                    break;
            }
            nodes[a].insert(b);
            edges++; edges2++;
        }
        else assert(("Too many edges for disconnected grap", 0));
    }

    vector<int> ids(N, 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    printf("%d %d\n", N, M);
    for(int i = 0; i < N; i++)
        for(int v : nodes[i])
            printf("%d %d %d\n", ids[i], ids[v], rand() % L);
}

void gen_limited(int argc, char **argv)
{
    assert(("Unimplemented", 0));
}

void gen_line(int argc, char **argv)
{
    assert(argc == 2);

    int N = atoi(argv[0]);
    int L = atoi(argv[1]);

    assert(N >= 1);

    srand(N^L);

    vector<set<int>> nodes;
    nodes.assign(N, set<int>());

    for(int i = 0; i < N - 1; i++)
        nodes[i].insert(i + 1);

    vector<int> ids(N, 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    printf("%d %d\n", N, N - 1);
    for(int i = 0; i < N; i++)
        for(int v : nodes[i])
            printf("%d %d %d\n", ids[i], ids[v], rand() % L);
}

void gen_tree(int argc, char **argv)
{
    assert(argc == 2);

    int N = atoi(argv[0]);
    int L = atoi(argv[1]);

    assert(N >= 1);

    srand(N^L);

    vector<set<int>> nodes;
    nodes.assign(N, set<int>());

    for(int i = 1; i < N; i++)
        nodes[rand() % i].insert(i);

    vector<int> ids(N, 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    printf("%d %d\n", N, N - 1);
    for(int i = 0; i < N; i++)
        for(int v : nodes[i])
            printf("%d %d %d\n", ids[i], ids[v], rand() % L);
}

void gen_dijkstra(int argc, char **argv)
{
    assert(argc == 1);

    int N = atoi(argv[0]);

    assert(N >= 10);

    srand(N);

    vector<set<ii>> nodes;
    nodes.assign(N, set<ii>());

    int right = pow(log2(N), 1);
    int left = N - right;
    assert(("log^k(N) cannot be >= N", left > 0));
    int M = 0;

    for(int i = 0; i < N - 1; i++) if(i != left - 1)
    {
        nodes[i].insert({i + 1, 1});
        M++;
    }

    for(int i = 0; i < left; i++)
    {
        for(int j = 0; j < right; j++)
        {
            nodes[i].insert({left + j, 2*N - 2*i + 2*j});
            M++;
        }
    }

    assert(M <= 500000);

    vector<int> ids(N, 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    printf("%d %d\n", N, M);
    for(int i = 0; i < N; i++)
        for(ii v : nodes[i])
            printf("%d %d %d\n", ids[i], ids[v.first], v.second);
}

void gen_bfs(int argc, char **argv)
{
    assert(argc == 1);

    int H = atoi(argv[0]);
    int M = 0;

    assert(H >= 2);

    vector<vector<ii>> nodes;
    
    nodes.push_back(vector<ii>());
    for(int i = 1; i < 2*H; i++)
    {
        nodes[i - 1].push_back({i, 1});
        M++;
        nodes.push_back(vector<ii>());
    }

    nodes.push_back(vector<ii>());
    for(int i = 0; i < 2*H; i += 2)
    {
        nodes[i].push_back({2*H, 6*H+3 - 3*i/2});
        M++;
    }

    int ctr = 0;
    for(int i = 1; i < H; i++)
    {
        for(int j = 0; j < (1 << i); j++)
        {
            ctr++;
            nodes.push_back(vector<ii>());
            nodes[2*H + (ctr - 1)/2].push_back({2*H + ctr, 1});
            M++;
        }
    }
    
    vector<int> ids(nodes.size(), 0);
    iota(ids.begin(), ids.end(), 0);
    random_shuffle(ids.begin() + 1, ids.end());

    vector<tuple<int, int, int>> perm;

    printf("%zu %d\n", nodes.size(), M);
    for(int i = 0; i < nodes.size(); i++)
        for(ii v : nodes[i])
            perm.push_back({ids[i], ids[v.first], v.second});
    
    random_shuffle(perm.begin(), perm.end());

    for(auto v : perm)
        printf("%d %d %d\n", get<0>(v), get<1>(v), get<2>(v));
}

int main(int argc, char **argv)
{
    assert(argc >= 2);

    if(!strcmp(argv[1], "random")) gen_random(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "disconnected")) gen_disconnected(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "limited_height")) gen_limited(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "line")) gen_line(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "tree")) gen_tree(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "dijkstra")) gen_dijkstra(argc - 2, argv + 2);
    else if(!strcmp(argv[1], "bfs")) gen_bfs(argc - 2, argv + 2);
    else assert(("Invalid mode", 0));
}
