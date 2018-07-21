{Sarebbe un Dijkstra lento}

unit hogwarts;

interface

function raggiungi(N, M: longint; A, B, inizio, fine: array of longint): longint;

implementation

function raggiungi(N, M: longint; A, B, inizio, fine: array of longint): longint;
var distanza: array[0..5000] of longint;
    visitati: array[0..5000] of boolean;
    grafo: array[0..5000, 0..5000, 0..1] of longint;
    i, j, nodo, tempo, tempo_nuovo, infinito: longint;
    
begin
    infinito := 2000000000;
    for i := 0 to N do
    begin
        distanza[i] := infinito;
        visitati[i] := false;
    end;
    distanza[0] := 0;
    
    {va inizializzato il resto della tabella?}
    
    for i := 0 to M-1 do
    begin
        grafo[A[i]][B[i]][0] := inizio[i];
        grafo[A[i]][B[i]][1] := fine[i];
        grafo[B[i]][A[i]][0] := inizio[i];
        grafo[B[i]][A[i]][1] := fine[i];
    end;
        
    for i := 1 to N do
    begin
        {Trovare il nodo piu' vicino}
        tempo := infinito;
        for j := 0 to N-1 do
        begin
            if visitati[j] = false then
                if distanza[j] < tempo then
                begin
                    tempo := distanza[j];
                    nodo := j;
                end;            
        end;
        if tempo = infinito then break;
        
        {espandersi da tale nodo}
        visitati[nodo] := true;
        for j := 0 to N-1 do
        begin
            if tempo < grafo[nodo][j][1] then {vuol dire che l'arco c'e' ancora}
            begin
                if tempo < grafo[nodo][j][0] then
                    tempo_nuovo := grafo[nodo][j][0] + 1
                else
                    tempo_nuovo := tempo + 1;
                    
                if tempo_nuovo < distanza[j] then
                    distanza[j] := tempo_nuovo;
            end;
        end;
        
    end;
	
    if distanza[N-1] <> infinito then
        raggiungi := distanza[N-1]
    else
        raggiungi := -1;
end;

end.
