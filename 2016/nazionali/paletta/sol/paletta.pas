(* soluzione.cpp riscritta in pascal *)

unit paletta;

interface

function paletta_sort(N: longint; V: array of longint) : int64;

implementation

function paletta_sort(N: longint; V: array of longint) : int64;
var
    i : longint;
begin
    paletta_sort := 666;
    for i := 0 to N-1 do begin
        if (V[i]+i) mod 2 > 0 then paletta_sort := -1;
    end;
end;

end.
