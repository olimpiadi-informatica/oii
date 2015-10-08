(* matteo.cpp riscritta in pascal *)

unit nemesi;

interface

procedure smista(N: longint; var nemico: array of longint);

implementation
uses nemesilib;

const
    MAXN = 1000000;
var
    enemy: array[0..MAXN-1] of longint;
    visit_parity, assigned_group: array[0..MAXN-1] of longint;
    ngroups: longint;

procedure visit(curr: longint);
var
    next: longint;
begin
    next := enemy[curr];

    if assigned_group[next] >= 0 then
    begin
        if assigned_group[next] = 0 then
            assigned_group[curr] := 1
        else
            assigned_group[curr] := 0;
        exit;
    end;

    if visit_parity[next]>=0 then
    begin
        if visit_parity[next]=visit_parity[curr] then
        begin
            assigned_group[curr]:=2;
            ngroups:=3;
        end else
            assigned_group[curr]:=1;
        exit;
    end;

    visit_parity[next] := 1 - visit_parity[curr];
    visit(next);
    if assigned_group[next] = 0 then
        assigned_group[curr] := 1
    else
        assigned_group[curr] := 0;
end;

procedure smista(N: longint; var nemico: array of longint);
var
    i, group: longint;
begin
    for i:=0 to N-1 do
    begin
        assigned_group[i] := -1;
        visit_parity[i] := -1;
        enemy[i]:=nemico[i];
    end;    
       
    ngroups:=2;

    for i:=0 to N-1 do
        if visit_parity[i]=-1 then
        begin
            visit_parity[i] := 0;
            visit(i);
        end;

    for group:=0 to ngroups-1 do
    begin
        nuovo_gruppo();
        for i:=0 to N-1 do
            if assigned_group[i] = group then
                aggiungi(i);
    end;
end;

end.
