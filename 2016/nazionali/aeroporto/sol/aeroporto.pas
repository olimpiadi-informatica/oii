(* soluzione.cpp riscritta in pascal *)

unit aeroporto;

interface

procedure pianifica(R: longint; var A: array of longint; var B: array of longint; var T: array of longint);

implementation

procedure pianifica(R: longint; var A: array of longint; var B: array of longint; var T: array of longint);
var
    i, left, right, middle, FirstTimeFree : longint;
    feasible : boolean;
begin
    left := 0;
    right := 1000000000;
    while left+1 < right do
    begin
        middle := (left+right) div 2;
        feasible := True;

        FirstTimeFree := 0;
        for i := 0 to R-1 do
        begin
            if FirstTimeFree < A[i] then FirstTimeFree := A[i] + middle
            else if FirstTimeFree <= B[i] then inc(FirstTimeFree, middle)
            else begin
                feasible := False;
                break;
            end;
        end;

        if feasible then left := middle
        else right := middle;
    end;

    FirstTimeFree := 0;
    for i := 0 to R-1 do
    begin
        if FirstTimeFree < A[i] then begin
            T[i] := A[i];
            FirstTimeFree := A[i] + left;
        end else begin
            T[i] := FirstTimeFree;
            inc(FirstTimeFree, left);
        end;
    end;
end;

end.

