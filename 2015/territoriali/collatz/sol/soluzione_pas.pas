(*
 *  Soluzione di collatz.
 *
 *  Autore: William Di Luigi
 *
 *  Descrizione: Banale simulazione.
 *)

var N, cnt: longint;
begin
{$ifdef EVAL}
    assign(input, 'input.txt'); reset(input);
    assign(output, 'output.txt'); rewrite(output);
{$endif}
    read(N);
    cnt := 1;
    while N <> 1 do
    begin
        inc(cnt);
        if N mod 2 <> 0 then
            N := 3 * N + 1
        else
            N := N div 2;
    end;
    writeln(cnt);
end.
