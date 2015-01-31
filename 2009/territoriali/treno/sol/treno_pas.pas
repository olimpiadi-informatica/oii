(* Problema: TRENO, selezioni territoriali 2009                       *)
(* Autore: William Di Luigi <williamdiluigi[at]gmail[dot]com>         *)

(* Questa e' un'implementazione iterativa in linguaggio Pascal della  *)
(* soluzione al problema "TRENO", per una versione ricorsiva e in     *)
(* linguaggio C++ si veda il seguente link:                           *)
(*
http://www.imparando.net/elearning/INF0002/document/Territoriali_2009/soluzione_treno.html
*)

(* L'osservazione chiave della soluzione e' che posso ridurre un      *)
(* input di "dimensione" N in un'altro di dimensione (N-1) con tre    *)
(* spostamenti di coppie di vagoni, ad esempio supponiamo che N=5:    *)

(* Treno iniziale :                                 AAAAABBBBB**      *)
(* Sposto in fondo i due vagoni "AB" adiacenti:     AAAA**BBBBAB      *)
(* [corrisponde allo spostamento: (5, 11) ovvero (N, 2*N+1)]          *)
(* Sposto i primi due vagoni nel buco:              **AAAABBBBAB      *)
(* [corrisponde allo spostamento: (1, 5) ovvero (1, N)]               *)
(* Sposto i vagoni "AB" di prima all'inizio:        ABAAAABBBB**      *)
(* [corrisponde allo spostamento: (11, 1) ovvero (2*N+1, 1)]          *)

(* Notare che ora ho due vagoni "AB" seguiti da: "AAAABBBB**", quindi *)
(* mi rimane da risolvere un problema con N=4 (prima era N=5).        *)

(* NOTA BENE: Adesso non e' mai piu' necessario toccare i primi due   *)
(* vagoni!, dobbiamo semplicemente "risolvere" il treno con N=4, in   *)
(* cui ogni operazione sara' "traslata" di +2 dato che ignoriamo le   *)
(* prime due posizioni!                                               *)

(* Dal momento che per ridurre dalla grandezza N alla grandezza N-1   *)
(* faccio una trasformazione composta da TRE spostamenti, per andare  *)
(* da N a 1 impiego 3*N spostamenti, che MOLTO PROBABILMENTE NON E'   *)
(* IL NUMERO MINIMO ASSOLUTO di spostamenti necessari per effettuare  *)
(* la trasformazione, ma il testo non richiede il minimo assoluto!    *)

(* Inoltre, quando arrivo a N=3 (che e' il minimo valore possibile,   *)
(* guardare la sezione "Assunzioni" nel testo), so gia' fare la       *)
(* trasformazione in soli 4 passi (invece che 3*N = 9), quindi quando *)
(* dovro' risolvere un treno di "dimensione" N, mi fermero' al        *)
(* "sottotreno" di "dimensione" 3 dato che lo so risolvere (guardare  *)
(* il primo caso di esempio illustrato nel testo del problema).       *)
(* Quindi impieghero' leggermente meno di 3*N spostamenti.            *)

var
    N, risposta, traslazione, copia_di_N, i : longint;
    spostamento : array[1..3*1000, 1..2] of longint; (* Al massimo 3*N spostamenti! *)
begin
    (* Redireziona l'input/output da tastiera sui relativi files txt *)
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input);
    rewrite(output);
    (* Leggi N *)
    read(N);
    (* Salva il valore di N perche' dopo devo stamparlo (Ma chissa' perche' poi???) *)
    copia_di_N := N;
    (* Inizializza la risposta a zero *)
    risposta := 0;
    (* All'inizio, sto considerando il treno intero, quindi: *)
    traslazione := 0;
    (* Finche' il treno ha "dimensione" troppo grande, riducila di uno! *)
    while N > 3 do
    begin
        (* Ricorda che in ogni spostamento, dobbiamo tener conto della traslazione accumulata! *)
        (* Sposta "AB" in fondo: *)
        inc(risposta);
        spostamento[risposta][1] := (N) + traslazione;       (* Da: N      *)
        spostamento[risposta][2] := (2*N+1) + traslazione;   (* A:  2*N+1  *)
        (* Sposta "AA" iniziale nel buco: *)
        inc(risposta);
        spostamento[risposta][1] := (1) + traslazione;       (* Da: 1      *)
        spostamento[risposta][2] := (N) + traslazione;       (* A:  N      *)
        (* Sposta "AB" di prima all'inizio: *)
        inc(risposta);
        spostamento[risposta][1] := (2*N+1) + traslazione;   (* Da: 2*N+1  *)
        spostamento[risposta][2] := (1) + traslazione;       (* A:  1      *)
        (* Adesso ho "risolto" i primi due vagoni, devo "tagliarli via" *)
        (* Mi basta aumentare di 2 la traslazione!                      *)
        inc(traslazione, 2);
        (* Inoltre, adesso N e' diminuito di uno! *)
        dec(N);
    end;
    (* Quando arrivo qui, N e' diventato uguale a 3, oppure l'input aveva N=3  *)
    (* in ogni caso, ho ancora la variabile "traslazione" che mi fa capire se  *)
    (* l'input era proprio N=3 (traslazione=0) oppure no.                      *)
    (* Non ci rimane che eseguire "A MANO" gli ultimi 4 spostamenti!           *)
    (* Gli ultimi spostamenti sono: (2, 7), (6, 2), (4, 6), (7, 4).            *)
    (* Nell'eseguirli, dobbiamo di nuovo tenere conto della traslazione!       *)
    (* Spostamento (2, 7) *)
    inc(risposta);
    spostamento[risposta][1] := (2) + traslazione;
    spostamento[risposta][2] := (7) + traslazione;
    (* Spostamento (6, 2) *)
    inc(risposta);
    spostamento[risposta][1] := (6) + traslazione;
    spostamento[risposta][2] := (2) + traslazione;
    (* Spostamento (4, 6) *)
    inc(risposta);
    spostamento[risposta][1] := (4) + traslazione;
    spostamento[risposta][2] := (6) + traslazione;
    (* Spostamento (7, 4) *)
    inc(risposta);
    spostamento[risposta][1] := (7) + traslazione;
    spostamento[risposta][2] := (4) + traslazione;
    (* Ho finito! Ora devo solo stampare tutto! *)
    writeln(risposta, ' ', copia_di_N);
    for i:=1 to risposta do
        writeln(spostamento[i][1], ' ', spostamento[i][2]);
end.
