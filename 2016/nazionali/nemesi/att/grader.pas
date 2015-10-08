uses nemesi;

var	
	fr, fw : text;

{ Declaring variables }
	N : Longint;
	nemico : array of Longint;

{ iterators used in for loops }
	i0: LongInt;

begin
{$ifdef EVAL}
    assign(fr, 'input.txt');
    assign(fw, 'output.txt');
{$else}
    fr := input;
    fw := output;
{$endif}
    reset(fr);
    rewrite(fw);

	{ Reading input }
	read(fr, N);
	Setlength(nemico, N);
	for i0 := 0 to N-1 do
	begin
		read(fr, nemico[i0]);
	end;

	{ Calling functions }
	smista(N, nemico);

	{ Writing output }
	
	close(fr);
    close(fw);
end.
