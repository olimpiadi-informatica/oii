uses spiedini;

const MAXN = 20000000;
var N, K, i   : longint;
    s         : array[0..MAXN-1] of longint;
    fin, fout : text;

begin
    assign(fin, 'input.txt'); reset(fin);
    assign(fout, 'output.txt'); rewrite(fout);
    read(fin, N, K);
    for i:=0 to N-1 do read(fin, s[i]);
    writeln(fout, solve(N, K, s));
    close(fin);
    close(fout);
end.
