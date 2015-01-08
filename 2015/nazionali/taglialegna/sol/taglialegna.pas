unit taglialegna;

interface
procedure Pianifica(N: longint; var H: array of longint);

implementation
uses taglialegnalib;

const MAXN = 2000000;
var n_candidati: longint;
    lep, rep, memo, first_tree, candidati, min_candidati, direzione:
        array[0..MAXN-1] of longint;

procedure Pianifica(N: longint; var H: array of longint);
var i, j, k, test: longint;
begin
    lep[0] := 0;
    for i:=1 to N-1 do
    begin
        j := i-1;
        while (j >= 0) and (i - j < H[i]) do
            j := lep[j] - 1;
        lep[i] := j + 1;
    end;

    rep[N-1] := N-1;
    for i:=N-2 downto 0 do
    begin
        j := i + 1;
        while (j < N) and (j - i < H[i]) do
            j := rep[j] + 1;
        rep[i] := j - 1;
    end;

    for i:=0 to N-1 do
    begin
        (* Primo caso: butto i a sinistra *)
        k := lep[i] - 1;

        test := 1;
        if k >= 0 then
            inc(test, memo[k]);

        memo[i] := test;
        first_tree[i] := i;
        direzione[i] := 0;

        (* Secondo caso: abbatto a destra un albero che abbatte i nella caduta *)
        while (n_candidati > 0) and (rep[candidati[n_candidati - 1]] < i) do
            dec(n_candidati);

        if n_candidati > 0 then
        begin
            k := min_candidati[n_candidati - 1] - 1;

            test := 1;
            if k >= 0 then
                inc(test, memo[k]);

            if test < memo[i] then
            begin
                memo[i] := test;
                first_tree[i] := k + 1;
                direzione[i] := 1;
            end;
        end;

        k := i;
        if n_candidati > 0 then
        begin
            if (min_candidati[n_candidati - 1] = 0) or
                (memo[min_candidati[n_candidati - 1] - 1] < memo[i - 1]) then
            begin
                k := min_candidati[n_candidati - 1];
            end;
        end;

        inc(n_candidati);
        candidati[n_candidati - 1] := i;
        min_candidati[n_candidati - 1] := k;
    end;

    (* Ricostruisci la soluzione *)
    i := N - 1;
    while i >= 0 do
    begin
        Abbatti(first_tree[i], direzione[i]);

        if direzione[i] = 0 then (* A sinistra *)
            i := lep[i] - 1
        else
            i := first_tree[i] - 1;
    end;
end;

end.
