const
    MAXN = 1000;
var
    T, testcase, N, i : longint;
    R, C: array [0..MAXN-1] of longint;
    sol: longint; (* scrivi in questa variabile la risposta *)

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

    for testcase := 1 to T do begin
        readln(); (* ignora la riga vuota *)
        readln(N);

        for i := 0 to N-1 do begin
            readln(R[i], C[i]);
        end;

        (* RISOLVI QUI IL PROBLEMA!! *)

        writeln('Case #', testcase, ': ', sol);
    end;
end.
