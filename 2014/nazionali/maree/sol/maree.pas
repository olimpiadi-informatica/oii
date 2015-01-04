unit maree;

interface

function solve(N, M, T: longint; var S, E: array of longint): longint;

implementation

const MAXN  = 200000;
      QSIZE = 5000000;
var _n, _m, _t : longint;
    graph : array[0..MAXN-1] of array of longint;
    gsize, gcapa : array[0..MAXN-1] of longint;
    visited : array[0..MAXN-1] of boolean;
    dist, rdist : array[0..MAXN-1] of longint;
    q1, q2 : array[0..QSIZE-1] of longint;

procedure bfs(b : longint; var res : array of longint);
var qhead, qcount, first, second, i, j : longint;
begin
    q1[0] := b; q2[0] := 0;
    qhead := 0; qcount := 1;
    for i:=0 to _n-1 do visited[i] := False;
    while qcount > 0 do
    begin
        first := q1[qhead];
        second := q2[qhead];
        inc(qhead); if qhead = QSIZE then qhead := 0;
        dec(qcount);
        if visited[first] then continue;
        visited[first] := True;
        res[first] := second;
        for j:=0 to gsize[first]-1 do
        begin
            q1[(qhead + qcount) mod QSIZE] := graph[first][j];
            q2[(qhead + qcount) mod QSIZE] := second + 1;
            inc(qcount);
        end;
    end;
end;

function solve(N, M, T: longint; var S, E: array of longint): longint;
var a, b, i, best : longint;
begin
    _n := N; _m := M; _t := T;
    for i:=0 to _n-1 do
    begin
        setlength(graph[i], 1);
        gsize[i] := 0;
        gcapa[i] := 1;
        dist[i]  := maxlongint;
        rdist[i] := maxlongint;
    end;
    for i:=0 to _m-1 do
    begin
        a := S[i]; b := E[i];
        if gsize[a] = gcapa[a] then
        begin
            gcapa[a] := gcapa[a] shl 1;
            setlength(graph[a], gcapa[a]);
        end;
        graph[a][gsize[a]] := b;
        inc(gsize[a]);
    end;
    bfs(0, dist);
    bfs(_n-1, rdist);
    if dist[_n-1] <= _t then
    begin
        solve := dist[_n-1];
        exit;
    end;
    best := maxlongint;
    for i:=0 to _n-1 do
        if (dist[i] <= _t) and (rdist[i] < maxlongint) then
            if _t + rdist[i] < best then
                best := _t + rdist[i];
    if best = maxlongint then solve := -1
    else solve := best;
end;

end.
