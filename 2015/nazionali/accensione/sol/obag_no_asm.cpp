#include <cstddef>
 
const int MAXN = 1000000;
const int MAXL = 14000000;
 
struct node_t {
    int value;
    node_t* next = NULL;
};
 
node_t pool[MAXL];
node_t *pool_ptr;
node_t *end[MAXN + 1];
 
void Accendi(int N, int acceso[], int pulsante[]) {
    pool_ptr = pool + N + 1;
    for (int i = 1; i <= N; i++) {
        pool[i].value = 1;
        end[i] = pool + i;
    }
 
    for (int i = 2; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            pool_ptr->value = i;
            end[j]->next = pool_ptr;
            end[j] = pool_ptr++;
        }
    }
 
    for (int i = N; i >= 1; i--) {
        if (!acceso[i]) {
            pulsante[i] = true;
 
            for (node_t* j = pool + i; j != end[i]; j = j->next)
                acceso[j->value] ^= 1;
        }
    }
}
