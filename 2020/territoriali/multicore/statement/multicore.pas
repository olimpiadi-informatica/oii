var
    T, tt, i, N, B : longint;
    C, P : array[0..300] of longint;
    nc: longint; (* scrivi in queste variabili le risposte *)

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

    for tt := 1 to T do begin
        readln(); (* ignora la riga vuota *)
        readln(N, B);
        for i := 0 to N-1 do
            readln(C[i], P[i]);

        (* RISOLVI QUI IL PROBLEMA!! *)

        writeln('Case #', tt, ': ', nc);
    end;
end.
