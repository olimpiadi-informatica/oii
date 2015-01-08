uses bottleneck;

const MAXN = 100000;
      MAXM = 1000000;
var N, M, W, L, R, C : longint;
    arco_da, arco_a, capacita : array[0..MAXM-1] of longint;
    i : longint;
    fr, fw : text;

begin
    assign(fr, 'input.txt');
    assign(fw, 'output.txt');
    reset(fr);
    rewrite(fw);

    readln(fr, N, M, W, L, R, C);
    for i:=0 to M-1 do
        readln(fr, arco_da[i], arco_a[i], capacita[i]);

    writeln(fw, Analizza(N, M, W, L, arco_da, arco_a, capacita, R, C));

    close(fr);
    close(fw);
end.
