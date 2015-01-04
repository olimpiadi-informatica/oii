uses bufale;

const MAXN = 10000000;
var N, i      : longint;
    M, P      : array[0..MAXN-1] of longint;
    fin, fout : text;

begin
    assign(fin, 'input.txt'); reset(fin);
    assign(fout, 'output.txt'); rewrite(fout);
    read(fin, N);
    for i:=0 to N-1 do read(fin, M[i], P[i]);
    writeln(fout, solve(N, M, P));
    close(fin);
    close(fout);
end.
