unit taglialegnalib;

interface

procedure Abbatti(indice: longint; direzione: longint);

implementation
var fw: text;

procedure Abbatti(indice: longint; direzione: longint);
begin
    writeln(fw, indice, ' ', direzione);
end;

initialization

assign(fw, 'output.txt');
rewrite(fw);

finalization

close(fw);

end.
