program quasipal;

type matrice=array[1..8,1..8] of '0'..'9';

var     M,N:integer;
    mat:matrice;
    i,j:integer;
    usato:array[1..8] of boolean;
    griglia:matrice;
    ok:boolean;

procedure qpal(index:integer);
var i,j:integer;
begin
     if ok then exit;
     if index<=M then begin
        for i:=1 to M do
            if not usato[i] then begin
               if ok then exit;
               griglia[index]:=mat[i];
               usato[i]:=true;
               qpal(index+1);
               usato[i]:=false;
            end
     end
     else begin
         ok:=true;
         for j:=1 to N do
         for i:=1 to M div 2 do
         if (griglia[i,j]<>griglia[M-i+1,j]) and (griglia[i,j]<>'0') and (griglia[M-i+1,j]<>'0') then
            ok:=false;
     end;
end;


begin
     readln(M,N);
     for i:=1 to M do begin
         for j:=1 to N do
             read(mat[i,j]);
         readln();
         usato[i]:=false;
     end;

     ok:=false;

     qpal(1);

     for i:=1 to M do begin
         for j:=1 to N do write(griglia[i,j]);
         writeln();
     end;

end.
