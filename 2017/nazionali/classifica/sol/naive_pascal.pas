{
* Soluzione di classifica.
* 
* Autore: Giada Franz
* 
* Descrizione: Soluzione in pascal che simula i sorpassi e le eliminazioni
}

unit classifica;

interface

procedure inizia(N: longint; ids: array of longint);

procedure supera(id: longint);

procedure squalifica(id: longint);

function partecipante(pos: longint): longint;

implementation

const
    MAXN = 1000000;
var
    actives: longint;
    rank: array[0..MAXN+1] of longint;

procedure inizia(N: longint; ids: array of longint);
var
    i: longint;
begin
    actives := N;
    for i := 0 to N-1 do
    begin
        rank[i] := ids[i];
    end;
end;

procedure supera(id: longint);
var
    i, x, pos: longint;
begin
    for i := 0 to actives-1 do
    begin
        if rank[i] = id then
        begin
            pos := i;
        end;
    end;
    
    x := rank[pos];
    rank[pos] := rank[pos-1];
    rank[pos-1] := x;
end;

procedure squalifica(id: longint);
var
    i, pos: longint;
begin
    for i := 0 to actives-1 do
    begin
        if rank[i] = id then
        begin
            pos := i;
        end;
    end;
    
    for i := pos to actives-2 do
    begin
        rank[i] := rank[i+1];
    end;
    
    actives := actives-1;
end;

function partecipante(pos: longint): longint;
begin
    partecipante := rank[pos-1];
end;

end.
