include util;

int N = 6;
int M = 2;
string[] grid = {
    '..',
    '//',
    '..',
    '..',
    '\\/',
    '..'
};
pair inizio = (2,2);
int[] percorso = {sx, dw, dw, dw, sx, up, up, up, dx, up, up};


luce(N, M, inizio, percorso, penna_luce);
luce(N, M, inizio, percorso, penna_luce_2);
griglia(N, M);
numeri(N, M);
specchi(N, M, grid);
