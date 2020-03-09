const MAXN = 1000;

procedure solve(test: longint);
var
    N1, N2, N3, N4: longint;
    M: longint;
    F1, F2, F3, F4: ansistring;

    (* scrivi in queste variabili la risposta *)
    p1, p2, p3, p4: longint;

begin

    readln(N1, N2, N3, N4);
    readln(M);
    readln(F1);
    readln(F2);
    readln(F3);
    readln(F4);

    (* RISOLVI QUI IL PROBLEMA!! *)

    writeln('Case #', test, ': ', p1, ' ', p2, ' ', p3, ' ', p4);
end;


var
    T, test: longint;

begin
    (* le seguenti due righe possono essere utili per leggere e scrivere da file *)

    (*
    assign(input, 'input.txt'); reset(input);
    assign(output, 'output.txt'); rewrite(output);
    *)

    readln(T);

    for test := 1 to T do
        solve(test);
end.
