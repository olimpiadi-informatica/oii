include grattacieli;

srand(42);

int[] H = {2, 3, 6, 3}; // massime altezze
int[] S;                // altezze finali

// vincoli
int[] A = {0, 1, 2, 0, 3};
int[] B = {1, 2, 0, 3, 2};
int[] C = {4, 1, 1, 0, 2};

S = new int[] {2, 2, 5, 3};
shipout("fig1a", main(H, S, A, B, C));

S = new int[] {2, 2, 3, 1};
shipout("fig1b", main(H, S, A, B, C));

S = new int[] {2, 3, 4, 2};
shipout("fig1c", main(H, S, A, B, C));
