uses maree;

const MAXM = 3000000;
var i, N, M, T : longint;
    S, E       : array[0..MAXM-1] of longint;
    fin, fout  : text;

begin
    assign(fin, 'input.txt'); reset(fin);
    assign(fout, 'output.txt'); rewrite(fout);
    read(fin, N, M, T);
    for i:=0 to M-1 do read(fin, S[i], E[i]);
    writeln(fout, solve(N, M, T, S, E));
    close(fin);
    close(fout);
end.
