/**

    Soluzione di Dario Ostuni - O(∞)

    È un BubbleSort randomizzato, riesce a fare fino a ~1000 come N

**/

#include <bits/stdc++.h>

using namespace std;


long long paletta_sort(int n, int v[])
{
    mt19937_64 r(42);
	
    vector<int> moves;
    int act_max = n;
    int start_time = ((clock() * 100) / CLOCKS_PER_SEC);
    while(act_max > 0)
    {
        while(act_max > 0 && v[act_max - 1] == act_max - 1)
            act_max--;
        if(act_max == 0)
            continue;
        if (act_max == 2)
			break;
        int index = (r() % (act_max - 2)) + 1;
        if(v[index - 1] > v[index + 1])
        {
            moves.push_back(index);
            swap(v[index - 1], v[index + 1]);
        }
        if(((clock() * 100) / CLOCKS_PER_SEC) - start_time > 17)
            break;
    }
    if(act_max)
        return -1;
    
    return moves.size();
}
