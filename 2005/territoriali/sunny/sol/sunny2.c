#include <stdio.h>
#include <stdlib.h>

typedef struct n {
  int next;   /* Unica galleria percorribile dallo svincolo corrente */
  int brightness;
  int visited;
} node;

int N, M, H, S;
node *V;

int error(int err) {
  switch (err) {
  case 1:
    fprintf(stderr, "Errore di apertura files.\n");
    break;
  case 2:
    fprintf(stderr, "Errore di lettura.\n");
    break;
  case 3:
    fprintf(stderr, "Errore in un arco.\n");
    break;
  default:
    fprintf(stderr, "Errore sconosciuto.\n");
  }

  exit(err);
}


int main() {
  FILE *in, *out;

  int i, c;
  int a, b, L;

#ifdef EVAL
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
#else
  in = stdin;
  out = stdout;
#endif

  if ( in == NULL || out == NULL )
    error(1);

  if ( fscanf(in, " %d %d %d %d", &N, &M, &H, &S) != 4 )
    error(2);

  V = (node*) malloc( sizeof(node) * N);

  for ( i = 0; i < N; i++ ) {
    V[i].next = i;
    V[i].brightness = M+1;
    V[i].visited = 0;
  }

  /* Vogliamo che i nodi siano indicizzati a partire da 0 */
  H--;
  S--;

  for ( i = 0 ; i < M ; i++ ) {
    if ( fscanf(in, " %d %d %d", &a, &b, &L) != 3 )
      error(2);

    if ( a < 1 || a > N ||
         b < 1 || b > N ||
         L < 1 || L > M )
      error(3);

    /* Vogliamo che i nodi siano indicizzati a partire da 0 */
    a--;
    b--;

    if (V[a].brightness > L) {
      V[a].next = b;
      V[a].brightness = L;
    }

    if (V[b].brightness > L) {
      V[b].next = a;
      V[b].brightness = L;
    }
  }

  /* E' praticamente equivalente a scorrere la lista che contiene H */

  i = H;
  c = 0;
  while ( i != S ) {
    V[i].visited = 1;
    i = V[i].next;
    c++;
    if ( V[i].visited ) {
      fprintf(out, "-1\n");
      return 0;
    }
  }

  fprintf(out, "%d\n", c);

  return 0;
}
