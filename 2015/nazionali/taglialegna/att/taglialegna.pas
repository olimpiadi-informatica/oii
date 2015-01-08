unit taglialegna;

interface
procedure Pianifica(N: longint; var altezza: array of longint);

implementation
uses taglialegnalib;

(* qui vanno dichiarate eventuali variabili globali *)

procedure Pianifica(N: longint; var altezza: array of longint);
begin
    Abbatti(0, 1);
end;

end.
