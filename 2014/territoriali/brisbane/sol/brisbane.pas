(* Problema: BRISBANE, selezioni territoriali 2013                    *)
(* Autore: William Di Luigi <williamdiluigi@gmail.com>                *)
(* Questa e' una traduzione in Pascal della versione di Luca Versari  *)
(* Per semplificare la soluzione, non uso le maschere di bit          *)
(* per selezionare i tipi di archi da prendere, rimpiazzandole con 2  *)
(* parametri booleani (prendi bus, prendi traghetto).                 *)

(* La soluzione essenzialmente consiste di 4 visite del grafo:        *)
(*   (1) usando solo gli archi gratuiti                               *)
(*   (2) usando archi gratuiti e autobus                              *)
(*   (3) usando archi gratuiti e traghetti                            *)
(*   (4) usando archi gratuiti, autobus e traghetti                   *)

var
    N, A, totArchi : longint;
    M : array[1..3] of longint; (* M[1] = Mg, M[2] = Mb, M[3] = Mt *)
    archi : array[1..20000, 1..3] of longint;
    (* 10000 archi + 10000 rovesciati *)
    isAttrazione, visto : array[1..1000] of boolean;

(* DFS = Depth First Search = Visita in profondita'.                  *)
(* Funzione di visita del grafo. Se "usaAutobus" vale True, allora    *)
(* vengono utilizzati gli archi degli autobus, altrimenti vengono     *)
(* ignorati. Analogo comportamento se "usaTraghetto" vale True/False. *)
(* La funzione restituisce il numero di attrazioni raggiungibili.     *)
function dfs(nodo : longint; usaAutobus : boolean; usaTraghetto : boolean)
    : longint;
var
    i : longint;
begin
    (* Segna come "visto" questo nodo *)
    visto[nodo] := True;
    (* Inizializza a zero il risultato,
    ovvero il numero di attrazioni visibili *)
    dfs := 0;
    (* Se il nodo in cui mi trovo e' un'attrazione,
    aumento di 1 il risultato *)
    if isAttrazione[nodo] then
        inc(dfs);
    (* Prova a guardare tutti gli archi *)
    for i:=1 to totArchi do
        (* E' un arco uscente da "nodo"?
        Mi porta ad un nuovo nodo non gia' visto? *)
        if (archi[i][1] = nodo) and not visto[archi[i][2]] then
            (* E' un arco gratis? Se no, ho comprato i biglietti adatti? *)
            if (archi[i][3] = 1) or ((archi[i][3] = 2) and usaAutobus)
            or ((archi[i][3] = 3) and usaTraghetto) then
                (* In tal caso, visita il vicino e
                aumenta le attrazioni viste di conseguenza *)
                inc(dfs, dfs(archi[i][2], usaAutobus, usaTraghetto));
end;

var
    i, j, nodo : longint;
begin
    (* Redireziona l'input/output da tastiera sui relativi files txt *)
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input);
    rewrite(output);
    (* Leggi N, A, Mg, Mb, Mt *)
    read(N, A, M[1], M[2], M[3]);
    (* Inizializza a False l'array isAttrazione *)
    for i:=1 to N do isAttrazione[i] := False;
    (* Leggi quali nodi sono attrazioni *)
    for i:=1 to A do
    begin
        read(nodo);
        isAttrazione[nodo] := True;
    end;
    (* Inizializza a zero il totale degli archi *)
    totArchi := 0;
    (* Per ogni tipo di arco... *)
    for j:=1 to 3 do
        (* ...Leggi gli archi di quel tipo *)
        for i:=1 to M[j] do
        begin
            inc(totArchi);
            (* Inserisci un nuovo arco nel grafo *)
            read(archi[totArchi][1], archi[totArchi][2]);
            archi[totArchi][3] := j;
            (* j = 1/2/3 = gratis/autobus/traghetto *)
            inc(totArchi);
            (* Inserisci lo stesso arco, pero' rovesciato *)
            archi[totArchi][1] := archi[totArchi-1][2];
            archi[totArchi][2] := archi[totArchi-1][1];
            archi[totArchi][3] := archi[totArchi-1][3];
        end;
    (* Inizializza a False l'array "visto" e poi chiama la visita *)
    for i:=1 to N do
        visto[i] := False;
    writeln(dfs(0, False, False)); (* Usa solo mezzi gratis *)
    for i:=1 to N do
        visto[i] := False;
    writeln(dfs(0, True, False)); (* Usa anche autobus *)
    for i:=1 to N do
        visto[i] := False;
    writeln(dfs(0, False, True)); (* Usa anche traghetti *)
    for i:=1 to N do
        visto[i] := False;
    writeln(dfs(0, True, True)); (* Usa anche autobus e traghetti *)
end.
