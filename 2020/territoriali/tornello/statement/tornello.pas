function solve(): longint;
var
    N, i: longint;
    variazione: longint;
    risposta: longint;
begin
    readln(N);

    risposta := 0;  (* scrivi qui la risposta *)

    for i:=1 to N do
    begin
        read(variazione);

        (* aggiungi codice... *)
    end;

    solve := risposta;
end;


var
    T, test_index: longint;
begin
    (*
    se preferisci leggere e scrivere da file
    ti basta decommentare le seguenti due righe:
    *)

    (*
    assign(input, 'input.txt'); reset(input);
    assign(output, 'output.txt'); rewrite(output);
    *)

    readln(T);

    for test_index := 1 to T do begin
        readln(); (* ignora la riga vuota *)
        writeln('Case #', test_index, ': ', solve());
    end;
end.
