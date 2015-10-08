uses paletta;

var	
	fr, fw : text;

{ Declaring variables }
	N : Longint;
	V : array of Longint;
	numero_ribaltamenti : Int64;

{ iterators used in for loops }
	i0: Longint;

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
	Setlength(V, N);
	for i0 := 0 to N-1 do
	begin
		read(fr, V[i0]);
	end;

	{ Calling functions }
	numero_ribaltamenti := paletta_sort(N, V);

	{ Writing output }
	writeln(fw, numero_ribaltamenti);
	
	close(fr);
    close(fw);
end.
