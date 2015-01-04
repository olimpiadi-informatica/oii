const
  MAXX = 100;
  MAXY = 100;
  MAXN = 100;
var
  N, X, Y: longint;
  MX, MY: longint;
  RX, RY, PX, PY: array[0..MAXN-1] of longint;
  visited: array[0..MAXN-1] of boolean;

(* Funzione che calcola, dati due punti, la loro distanza *)
function dist(x1: longint; y1: longint; x2: longint; y2: longint): longint;
begin
  dist := abs(x1-x2) + abs(y1-y2);
end;

(* Funzione che, dati due punti, dice se il primo e' "minore" del secondo *)
function isless(x1: longint; y1: longint; x2: longint; y2: longint): boolean;
begin
  isless := (x1 < x2) or ((x1 = x2) and (y1 < y2));
end;

function nearest(x: longint; y: longint): longint;
var
  i: longint;
  di, dn: longint;
begin
  nearest := 0;
  for i:=1 to N-1 do
  begin
    di := dist(x, y, RX[i], RY[i]);
    dn := dist(x, y, RX[nearest], RY[nearest]);
    if (di < dn) or ((di = dn) and isless(RX[i], RY[i], RX[nearest], RY[nearest])) then
      nearest := i;
  end;
end;

var
  i: longint;
  count, nx: longint;
begin
  (* Inizializza a False l'array visited *)
  fillchar(visited, sizeof(Visited), False);
  (* Legge da input.txt e scrive su output.txt *)
  assign(input, 'input.txt');
  assign(output, 'output.txt');
  reset(input);
  rewrite(output);
  (* Legge le dimensioni della griglia e la posizione di Mojito *)
  readln(X, Y, MX, MY, N);
  (* Legge la posizione e "la cella target" di ciascun ragazzo *)
  for i:=0 to N-1 do
    readln(RX[i], RY[i], PX[i], PY[i]);
  (* Inizializza a zero la risposta *)
  count := 0;
  (* Ripeti all'infinito *)
  while True do
  begin
    (* Trova il ragazzo piu' vicino *)
    nx := nearest(MX, MY);
    (* Se l'ho gia' visto, mi fermo (altrimenti vado in loop) *)
    if visited[nx] then
      break;
    (* Segno come "visto" questo ragazzo *)
    visited[nx] := True;
    (* Aumenta il numero di ragazzi visti *)
    inc(count);
    (* Aggiorna la posizione di Mojito *)
    MX := PX[nx];
    MY := PY[nx];
  end;
  (* Scrivi il risultato *)
  writeln(count);
end.
