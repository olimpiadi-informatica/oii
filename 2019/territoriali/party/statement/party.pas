var
    T, test, N, i, sol, A: longint;

begin
    (* le seguenti due righe possono essere utili per leggere e scrivere da file *)

    (*
    assign(input, 'input.txt'); reset(input);
    assign(output, 'output.txt'); rewrite(output);
    *)

    readln(T);

    for test := 1 to T do
    begin
        (* scrivi in questa variabile la soluzione *)
        sol := 0;

        readln(N);

        for i := 1 to N do
        begin
            read(A);

            (* il valore A rappresenta il valore di amicizia dell'i-esimo amico *)
        end;
        readln;

        writeln('Case #', test, ': ', sol);
    end;
end.
