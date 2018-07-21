typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

stato_t correggi(int N, int altezze[], coppia_t* scambio) {
	scambio->domino1 = 0;
	scambio->domino2 = 1;
	return RISOLTO;
}
