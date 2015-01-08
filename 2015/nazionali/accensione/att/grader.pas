uses accensione;

const MAXN = 1000000;
var N : longint;
    acceso, pulsante : array[0..MAXN] of longint;
    i : longint;
    fr, fw : text;

begin
    assign(fr, 'input.txt');
    assign(fw, 'output.txt');
    reset(fr);
    rewrite(fw);

    readln(fr, N);
    for i:=1 to N do read(fr, acceso[i]);
    close(fr);

    Accendi(N, acceso, pulsante);
    for i:=1 to N do
    begin
        if i > 1 then write(fw, ' ');
        write(fw, pulsante[i]);
    end;
    writeln(fw);
    close(fw);
end.
