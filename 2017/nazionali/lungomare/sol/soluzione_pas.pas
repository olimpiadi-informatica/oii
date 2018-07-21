unit lungomare;

interface

function percorri(N: longint; L: int64; var D, P: array of int64): int64;

implementation

uses math;


const
    MAXN = 10240000;

var
    Stack    : array[0..MAXN, 0..1] of int64;


function percorri(N: longint; L: int64; var D, P: array of int64): int64;
var
    size, a, b, i : int64;
begin
    size := 1;
    Stack[0, 0] := -L;
    Stack[0, 1] := L;
    for i := N-1 downto 0 do begin
        a := P[i] - D[i];
        b := P[i] + D[i];
        while (size > 0) and (a  <= Stack[size-1, 0]) do size := size-1;
        if b < Stack[size-1, 1] then begin
            Stack[size, 0] := a;
            Stack[size, 1] := b;
            size := size+1;
        end;
    end;
    while (size > 0) and (0  <= Stack[size-1, 0]) do size := size-1;
    Stack[size, 0] := 0;
    Stack[size, 1] := 0;
    size := size+1;
    percorri := 0;
    for size := size-1 downto 0 do begin
        percorri := max(percorri, Stack[size+1, 0] + Stack[size, 1]);
    end;
end;

end.
