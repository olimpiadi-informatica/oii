(* Problema: GARDALAND, selezioni territoriali 2013                   *)
(* Autore: William Di Luigi <williamdiluigi@gmail.com>                *)
(* L'idea e' di mantenere un array, nella cui posizione i-esima       *)
(* teniamo il numero di atleti di cui la squadra i-esima e' composta. *)
(* Man mano che otteniamo informazioni sugli studenti che sono gia'   *)
(* saliti sui pulman, decrementiamo in modo opportuno e dalla         *)
(* posizione opportuna il numero di studenti che sono saliti.         *)

var
    N, L, i, idSquadra, atletiOk, risposta : longint;
    squadra : array[1..100] of longint;

begin
    (* Redireziona l'input/output da tastiera sui relativi files txt *)
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input);
    rewrite(output);
    (* Leggi N e L *)
    read(N, L);
    (* Leggi il numero di studenti di ciascuna squadra *)
    for i:=1 to N do
        read(squadra[i]);
    (* Leggi tutte le L informazioni *)
    for i:=1 to L do
    begin
        read(idSquadra, atletiOk);
        (* Aumenta di uno l'id della squadra, per averlo 1-based *)
        inc(idSquadra);
        (* Sottrai il numero di atleti gia' saliti al totale di quella squadra *)
        dec(squadra[idSquadra], atletiOk);
    end;
    (* Contiamo quante sono le squadre che hanno atleti mancanti *)
    risposta := 0;
    for i:=1 to N do
        if squadra[i] > 0 then
            inc(risposta);
    (* Scrivi la risposta *)
    writeln(risposta);
    (* Scrivi quanti atleti mancano ad ogni squadra, in ordine crescente di idSquadra *)
    for i:=1 to N do
        if squadra[i] > 0 then
            writeln(i-1, ' ', squadra[i]); (* Stampa idSquadra 0-based *)
end.
