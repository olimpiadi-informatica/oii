unit aeroporto;

interface
procedure pianifica(R: longint; var A, B, T: array of longint);

implementation

(* qui vanno dichiarate eventuali variabili globali *)

procedure pianifica(R: longint; var A, B, T: array of longint);
begin
    T[0] := 42;
end;

end.
