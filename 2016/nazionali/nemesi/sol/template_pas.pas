unit nemesi;

interface
procedure smista(N: longint; var nemico: array of longint);

implementation
uses nemesilib;

(* qui vanno dichiarate eventuali variabili globali *)

procedure smista(N: longint; var nemico: array of longint);
var
    i: longint;
begin
	for i:=0 to N-1 do
    begin
        nuovo_gruppo();
        aggiungi(i);
    end;
end;

end.
