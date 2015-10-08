unit nemesilib;

interface

procedure nuovo_gruppo;
procedure aggiungi(bambino: longint);

implementation

const outbuf_len = 1 shl 16;
var fw : text;
    outbuf : array [1..outbuf_len] of Byte;
    call_n : int64;

procedure nuovo_gruppo;
begin
    if call_n > 0 then
        writeln(fw);
    inc(call_n);
end;

procedure aggiungi(bambino: longint);
begin
    write(fw, bambino, ' ');
end;

initialization

{$ifdef EVAL}
assign(fw, 'output.txt');
{$else}
fw := output;
{$endif}
rewrite(fw);
settextbuf(fw, outbuf);

finalization

close(fw);

end.
