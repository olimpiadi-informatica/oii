include grattacieli;

srand(42);

int[] H = {2, 4, 10, 7}; // massime altezze
int[] S = {2, 3, 6,  5}; // altezze finali

// vincoli
int[] A = {0, 1, 1, 3, 3, 0};
int[] B = {1, 2, 3, 2, 0, 3};
int[] C = {1, 3, 2, 2, 0, 4};

shipout("fig2", main(H, S, A, B, C));
