#include <cassert>
#include <algorithm>
#include <cstdio>

#ifdef EVAL
#define dprintf(...)
#else
#define dprintf printf
#endif

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

using namespace std;

stato_t correggi(int N, int altezze[], coppia_t* scambio) {

    for (int i = 0; i < N; i++) {
        altezze[i]--;
    }

    /*
    scorro da sinistra a destra,
    mi mantengo i due blocchi che cadranno piu' a destra
    */
    int node[2] = {-1, -1};
    int node_fall_right[2] = {-1, -1};
    
    bool critical_fall[N] = {false};
    int critical_fall_right[N] = {0};
    
    int min_uncovered = N+1;
    int max_uncovered = -1;

    for(int i = 0; i < N; i++) {
        // check how well position i is covered by previous dominos
        if(i >= 1 && node_fall_right[1] < i) {
            if(node_fall_right[0] >= i) {
                // position i is covered by only one domino
                assert(node[0] != -1);
                critical_fall[node[0]] = true;
                critical_fall_right[node[0]] =
                    max (
                        critical_fall_right[node[0]],
                        i
                    );
            } else {
                // position i is not covered by any domino
                min_uncovered = min(min_uncovered, i);
                max_uncovered = max(max_uncovered, i);
            }
        }
        // else we have two or more dominoes, and we don't care
        
        // now let i-th domino fall and update data
    
        int i_fall_right = i + altezze[i];
        if(i_fall_right > node_fall_right[1]) {
            node[1] = i;
            node_fall_right[1] = i_fall_right;
        }
        if(node_fall_right[1] > node_fall_right[0]) {
            swap(node[0], node[1]);
            swap(node_fall_right[0], node_fall_right[1]);
        }
        
        // dprintf("node[0] = %d, node[1] = %d\n", node[0], node[1]);
        
        assert(node[0] != node[1]);
        assert(node_fall_right[0] >= node_fall_right[1]);
    }
    
    // helper structure
    // hbmu = highest_before_min_uncovered
    int hbmu[min_uncovered];
    hbmu[min_uncovered-1] = min_uncovered-1;
    for(int i = min_uncovered-2; i >= 0; i--) {
        if(altezze[i] > altezze[hbmu[i+1]])
            hbmu[i] = i;
        else
            hbmu[i] = hbmu[i+1];
    }
    
    // dprintf("min_uncovered = %d, max_uncovered = %d\n", min_uncovered, max_uncovered);
    
    // ok, now we look for a "big" domino to cover
    // min_uncovered..max_uncovered (inclusive)
    
    // dominoes to swap, can be the same
    int big = -1, small = -1;
    
    for(int i = 0; i < N; i++) {
        // first valid position to place i in order to cover
        // the last uncovered position
        int min_location = max(max_uncovered - altezze[i], 0);
        int max_location = min_uncovered - 1;
        
        dprintf("i=%d, min_location=%d, max_location=%d\n", i, min_location, max_location);
        
        // we cannot cover the first uncovered location, give up this domino
        if(min_location > max_location)
            continue;
        
        dprintf("critical_fall[i]=%d, critical_fall_right[i]=%d\n",
                critical_fall[i], critical_fall_right[i]);

        if(!critical_fall[i]) {
            // not critical, easy win
            dprintf("not critical, choose min_location\n");
            big = i;
            small = min_location;
            break;
        }
        
        if(
            min_location < critical_fall_right[i] &&
            min_location + altezze[i] >= critical_fall_right[i])
        {
            dprintf("choose min_location\n");
            big = i;
            small = min_location;
            break;
        }
        
        if(
            max_location < critical_fall_right[i] &&
            max_location + altezze[i] >= critical_fall_right[i])
        {
            dprintf("choose max_location\n");
            big = i;
            small = max_location;
            break;
        }
        
        int candidate = hbmu[min_location];
        if(i + altezze[candidate] >= critical_fall_right[i]) {
            // we found a valid substitute
            dprintf("choose candidate=%d\n", candidate);
            big = i;
            small = candidate;
            break;
        }
        
    }
    
    dprintf("big=%d, small=%d\n", big, small);
    assert(
        false
        || !critical_fall[big]
        || big + altezze[small] >= critical_fall_right[big]
        || small >= big && small + altezze[big] >= critical_fall_right[big]
    );
    
    assert(
        small == -1 && big == -1 ||
        small < min_uncovered && small + altezze[big] >= max_uncovered
    );

    if(small == -1 && big == -1) {
        return IMPOSSIBILE;
    }
    
    if(small == big) {
        return OK;
    }
    
    scambio->domino1 = small;
    scambio->domino2 = big;
    return RISOLTO;
}

