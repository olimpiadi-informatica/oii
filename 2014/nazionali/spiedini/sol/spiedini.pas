unit spiedini;

interface

function solve(N: longint; K: longint; var S: array of longint): longint;

implementation

function solve(N: longint; K: longint; var S: array of longint): longint;
var ze, zb, se, sb, i, p1, p2, res : longint;
begin
    ze:=0; zb:=0; se:=0; sb:=0;
    for i:=0 to N-1 do
    begin
        if S[i] = 0 then inc(ze);
        inc(se, S[i]);
    end;
    p1 := 0;
    p2 := 0;
    res := 0;
    while p1 < N do
    begin
        while (p2 < N) and (se+sb>K) do
        begin
            if S[p2] = 0 then dec(ze);
            dec(se, S[p2]);
            inc(p2);
        end;
        if (p2 = N) and (se+sb>K) then break;
        if (p1 <= p2) and (ze+zb > res) then res := ze+zb;
        if s[p1] = 0 then inc(zb);
        inc(sb, s[p1]);
        inc(p1);
    end;
    solve := res;
end;

end.
