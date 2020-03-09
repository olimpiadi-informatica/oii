var
    T, tt, N, F, C : longint;
    nf, nc: longint; (* scrivi in queste variabili le risposte *)

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
        readln(N, F, C);

        (* RISOLVI QUI IL PROBLEMA!! *)

        writeln('Case #', tt, ': ', nf, ' ', nc);
    end;
end.
