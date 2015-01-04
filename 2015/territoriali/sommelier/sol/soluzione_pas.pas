(*
 *  Soluzione di sommelier.
 *
 *  Autore: Luca Versari
 *
 *  Descrizione: Dinamica O(N²).
 *)

const
    MAXN = 99;

var
    N, i, j, max : longint;
    din : array[1..MAXN] of longint;
    vini: array[1..MAXN] of longint;

begin
    assign(input, 'input.txt');
    assign(output, 'output.txt');
    reset(input);
    rewrite(output);
    read(N);
    for i:=1 to N do
    begin
        read(vini[i]);
        din[i] := 0;
    end;
    for i:=N downto 1 do
    begin
        max := 0;
        for j:=i+2 to N do
            if (vini[j] >= vini[i]) and (din[j] > max) then
                max := din[j];
        din[i] := max + 1;
    end;
    max := 0;
    for i:=1 to N do
        if din[i] > max then
            max := din[i];
    writeln(max);
end.
