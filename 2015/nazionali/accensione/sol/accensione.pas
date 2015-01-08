unit accensione;

interface
procedure Accendi(N: longint; var acceso, pulsante: array of longint);

implementation
const MAXN = 1000000;

procedure Accendi(N: longint; var acceso, pulsante: array of longint);
var i, x: longint;
begin
    (* Parto dal fondo: ogni volta che trovo un computer da accendere,
    *  controllo se è acceso o spento controllando i suoi multipli
    *  Nel caso sia spento, premo l'interruttore relativo *)

    for i:=N downto 1 do
    begin
        x := 2*i;
        while x <= N do
        begin
            if pulsante[x] = 1 then
                acceso[i] := 1 - acceso[i];
            inc(x, i);
        end;

        if acceso[i] = 0 then
            pulsante[i] := 1;
    end;
end;

end.
