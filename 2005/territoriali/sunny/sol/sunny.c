#include <stdio.h>
#include <stdlib.h>

/* #define DEBUG */

typedef struct n {
  int node;
  int brightness;

  struct n *next;
} node;

int N, M, H, S;
node** adjList;

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
  case 4:
    fprintf(stderr, "Errore: c'e' un arco duplicato oppure un self-loop.\n");
    break;
  default:
    fprintf(stderr, "Errore sconosciuto.\n");
  }

  exit(err);
}

int main() {
  FILE *in, *out;

  node* temp;
  node* chosen;
  int A, B, L;
  int last;
  int i;

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

  /* Vogliamo che i nodi siano indicizzati a partire da 0 */
  H--;
  S--;

  adjList = (node**) calloc(N, sizeof(node*));

  for ( i = 0 ; i < M ; i++ ) {
    if ( fscanf(in, " %d %d %d", &A, &B, &L) != 3 )
      error(2);

    if ( A < 1 || A > N ||
         B < 1 || B > N ||
         L < 1 || L > M )
      error(3);

    /* Vogliamo che i nodi siano indicizzati a partire da 0 */
    A--;
    B--;

    for ( temp = adjList[A] ; temp != NULL ; temp = temp->next )
      if ( temp->node == B )
        error(4);

    temp = (node*) malloc(sizeof(node));
    temp->node = B;
    temp->brightness = L;
    temp->next = adjList[A];
    adjList[A] = temp;

    for ( temp = adjList[B] ; temp != NULL ; temp = temp->next )
      if ( temp->node == A )
        error(4);

    temp = (node*) malloc(sizeof(node));
    temp->node = A;
    temp->brightness = L;
    temp->next = adjList[B];
    adjList[B] = temp;
  }

  /* L'unico modo per, arrivati ad un nodo, tornare indietro
     e` quello di ripercore l'ultimo arco: ricordare l'ultimo nodo visitato
     e` sufficiente.
  */

  last = -1;
  for ( i = 0 ; H != S ; i++ ) {
    chosen = NULL;

    for ( temp = adjList[H] ; temp != NULL ; temp = temp->next )
      if ( chosen == NULL || temp->brightness < chosen->brightness )
        chosen = temp;

#ifdef DEBUG
    if ( chosen != NULL )
      fprintf(stderr, "%d (%d) ", H + 1, chosen->brightness);
#endif

    /* Se il nodo in cui siamo ha grado 0 oppure l'arco scelto ci fa tornare indietro
       Harmony non raggiungera` Spike */
    if ( chosen == NULL || chosen->node == last )
      break;

    last = H;
    H = chosen->node;

  }

#ifdef DEBUG
  fprintf(stderr, "%d\n", H + 1);
#endif

  if ( H == S )
    fprintf(out, "%d\n", i);
  else
    fprintf(out, "-1\n");

  return 0;
}
