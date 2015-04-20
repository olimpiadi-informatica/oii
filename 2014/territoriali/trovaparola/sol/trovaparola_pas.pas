(* Problema: TROVAPAROLA, selezioni territoriali 2013                 *)
(* Autore: William Di Luigi <williamdiluigi@gmail.com>                *)
(* La soluzione implementa una visita in profondita' (DFS) per        *)
(* cercare di comporre la parola P partendo dal suo idx-esimo         *)
(* carattere, sapendo che ci troviamo in posizione (i, j) nella       *)
(* griglia di lettere. Usiamo l'accortezza di evitare di passare due  *)
(* volte per la stessa cella, dato che la lunghezza di qualsiasi      *)
(* percorso che va da (1, 1) a (i, j) e' sempre uguale, e quindi ci   *)
(* ritroveremmo ogni volta nella stessa cella (i, j) ma con lo stesso *)
(* indice idx da cui "ripartire", e gia' sappiamo che non riusciremo  *)
(* a comporre la parola (se cosi' non fosse l'avremmo trovata prima). *)

var
    R, C : longint;
    M : array[1..100, 1..100] of char;
    P : ansistring;
    visto : array[1..100, 1..100] of boolean;

(* La funzione restituisce direttamente la stringa richiesta in       *)
(* output dall'esercizio. La "stringa soluzione" viene costruita      *)
(* concatenando un carattere ('B' o 'D' = Basso o Destra) a sinistra  *)
(* della "stringa soluzione" per il sottoproblema che viene generato  *)
(* rispettivamente aprendo "in basso" o "a destra". Stiamo attenti    *)
(* a restituire 'ASSENTE' quando le due chiamate ricorsive hanno      *)
(* entrambe esito 'ASSENTE'.                                          *)
function dfs(i : longint; j : longint; idx : longint) : ansistring;
var
    temp : ansistring;
begin
    (* Se sono fuori dalla griglia, o ho gia' visto questa cella,
    o il carattere non combacia *)
    if (i > R) or (j > C) or visto[i][j] or (M[i][j] <> P[idx]) then
    begin
        dfs := 'ASSENTE';
        exit;
    end;
    (* Se ho fatto combaciare tutti i caratteri *)
    if idx = length(P) then
    begin
        (* Allora restituisco la stringa vuota,
        in modo che verra' "compilata" dal chiamante *)
        dfs := '';
        exit;
    end;
    (* Segna che ho visto questa posizione
    cosi' non ci ripasso due volte *)
    visto[i][j] := True;
    (* Prova ad "aprire in basso" *)
    temp := dfs(i+1, j, idx+1);
    if temp <> 'ASSENTE' then
    begin
        (* Se va bene, restituisci la soluzione *)
        dfs := 'B' + temp;
        exit;
    end;
    (* Prova ad "aprire a destra" *)
    temp := dfs(i, j+1, idx+1);
    if temp <> 'ASSENTE' then
    begin
        (* Se va bene, restituisci la soluzione *)
        dfs := 'D' + temp;
        exit;
    end;
    (* Se arrivo qui, questo ramo ricorsivo non ha soluzione *)
    dfs := 'ASSENTE';
end;

var
    i, j : longint;
begin
    (* Redireziona l'input/output da tastiera sui relativi files txt *)
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input);
    rewrite(output);
    (* Leggi R, C *)
    readln(R, C);
    (* Leggi la parola P *)
    readln(P);
    (* Leggi i singoli caratteri, e intanto
    inizializza a False l'array "visto" *)
    for i:=1 to R do
        for j:=1 to C do
        begin
            repeat
                read(M[i][j]);
            until ('A' <= M[i][j]) and (M[i][j] <= 'Z');
            visto[i][j] := False;
        end;
    (* Cerca partendo da (1, 1) e dall'indice 1 nella stringa P *)
    writeln(dfs(1, 1, 1));
end.
