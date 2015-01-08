uses taglialegna;

const MAXN = 2000000;
var N, i     : longint;
    altezza  : array[0..MAXN-1] of longint;
    fr       : text;

begin
    assign(fr, 'input.txt');
    reset(fr);

    readln(fr, N);
    for i:=0 to N-1 do read(fr, altezza[i]);

    Pianifica(N, altezza);

    close(fr);
end.
