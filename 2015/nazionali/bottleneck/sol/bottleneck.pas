unit bottleneck;

interface
function Analizza(N, M, W, L: longint; var arco_da, arco_a, capacita: array of longint; R, C: longint): longint;

implementation
const MAXM  = 1000000;
      MAXN  = 100000;
      QSIZE = MAXM;
      INF   = 1000000001;
var _n, _m : longint;
    graph : array[0..MAXN] of array of longint;
    gsize, gcapa : array[0..MAXN] of longint;
    visited : array[0..MAXN] of boolean;
    dist, rdist : array[0..MAXN] of longint;
    q1, q2 : array[0..QSIZE-1] of longint;

procedure addEdge(a, b: longint);
begin
    graph[a][gsize[a]] := b;
    if gsize[a] + 1 = gcapa[a] then
    begin
        gcapa[a] := gcapa[a] shl 1;
        setlength(graph[a], gcapa[a]);
    end;
    inc(gsize[a]);
end;

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

function Analizza(N, M, W, L: longint; var arco_da, arco_a, capacita: array of longint; R, C: longint): longint;
var a, b, i, minimo, distWL : longint;
begin
    _n := N; _m := M;

    for i:=1 to _n do
    begin
        setlength(graph[i], 2);
        gsize[i] := 0;
        gcapa[i] := 1;
        dist[i]  := INF;
        rdist[i] := INF;
    end;

    for i:=0 to _m-1 do
    begin
        a := arco_da[i]; b := arco_a[i];
        addEdge(a, b);
        addEdge(b, a);
    end;

    bfs(W, dist);
    bfs(L, rdist);

    (* BFS da W e poi da L *)
    BFS(W, dist);
    BFS(L, rdist);

    (* Trovo il minimo degli archi che sono su percorsi di distanza minima *)
    minimo := maxlongint;
    distWL := dist[L];

    (* assert(distanza[L][0] == distanza[W][1]); *)

    for i:=0 to _m-1 do
        if (dist[arco_a[i]] + rdist[arco_da[i]] + 1 = distWL) or
           (dist[arco_da[i]] + rdist[arco_a[i]] + 1 = distWL) then
        begin
            if capacita[i] < minimo then
                minimo := capacita[i];
        end;

    Analizza := minimo;
end;

end.
