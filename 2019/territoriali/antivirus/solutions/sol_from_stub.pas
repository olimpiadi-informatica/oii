const MAXN = 1000;

procedure solve(test: longint);
var
    N1, N2, N3, N4: longint;
    M: longint;
    F1, F2, F3, F4: ansistring;

    (* scrivi in queste variabili la risposta *)
    p1, p2, p3, p4: longint;

    i: longint;
    ok: boolean;

begin

    readln(N1, N2, N3, N4);
    readln(M);
    readln(F1);
    readln(F2);
    readln(F3);
    readln(F4);

    for p1 := 0 to (N1 - M) do
        for p2 := 0 to (N2 - M) do
            for p3 := 0 to (N3 - M) do
                for p4 := 0 to (N4 - M) do
                begin
                    ok := True;
                    for i := 1 to M do
                        if (F1[p1 + i] <> F2[p2 + i]) or (F2[p2 + i] <> F3[p3 + i]) or (F3[p3 + i] <> F4[p4 + i]) then
                            ok := False;

                    if ok then
                        writeln('Case #', test, ': ', p1, ' ', p2, ' ', p3, ' ', p4);
                end;
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
