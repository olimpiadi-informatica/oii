include grattacieli;

srand(42);

int[] H = {3, 8, 9, 6, 9, 1, 6, 7, 7, 9}; // massime altezze
int[] S = {2, 4, 7, 6, 7, 1, 6, 7, 6, 8}; // altezze finali

// vincoli
int[] A = {3, 0, 4, 5, 8, 8, 1, 7, 6};
int[] B = {4, 1, 0, 0, 0, 2, 8, 9, 7};
int[] C = {1, 2, 4, 1, 0, 1, 2, 1, 2};

shipout("fig3", main(H, S, A, B, C));
