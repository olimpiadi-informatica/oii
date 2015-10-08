uses nemesi;

const inbuf_len = 1 shl 16;

var
    fr       : text;
    inbuf    : array [1..inbuf_len] of Byte;
    N, i     : longint;
    nemico   : array of longint;

begin
{$ifdef EVAL}
    assign(fr, 'input.txt');
{$else}
    fr := input;
{$endif}
    reset(fr);
    settextbuf(fr, inbuf);

    readln(fr, N);
    setlength(nemico, N);
    for i:=0 to N-1 do read(fr, nemico[i]);

    smista(N, nemico);

    close(fr);
end.
