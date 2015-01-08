unit accensione;

interface
procedure Accendi(N: longint; var acceso, pulsante: array of longint);

implementation

(* qui vanno dichiarate eventuali variabili globali *)

procedure Accendi(N: longint; var acceso, pulsante: array of longint);
begin
    pulsante[1] := 1;
end;

end.
