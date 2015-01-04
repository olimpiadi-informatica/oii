unit bufale;

interface

function solve(N: longint; var M: array of longint; var P: array of longint): int64;

implementation

const MAXN = 10000000;
var D : array[0..MAXN] of longint;


procedure Sort(l,r:longint);
var
  i, j, x, tmp: longint;
begin
  i:=l; j:=r;
  x:=D[l+random(r-l+1)];
  repeat
    while D[i] < x do inc(i);
    while x < D[j] do dec(j);
    if i <= j then
    begin
      tmp:=D[i]; D[i]:=D[j]; D[j]:=tmp;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then Sort(l,j);
  if i < r then Sort(i,r);
end;

function solve(N: longint; var M: array of longint; var P: array of longint): int64;
var tot : int64;
    i: longint;
begin
    randseed := 123;
    tot := 0;
    for i:=0 to N-1 do
    begin
        D[i] := M[i] - P[i];
        inc(tot, M[i] + P[i]);
    end;
    Sort(0, N-1);
    for i:=0 to (N div 2)-1 do dec(tot, D[i]);
    for i:=(N div 2) to N-1 do inc(tot, D[i]);
    solve := tot div 2;
end;

end.
