uses aeroporto;

var	
	fr, fw : text;

{ Declaring variables }
	R : Longint;
	A : array of Longint;
	B : array of Longint;
	T : array of Longint;

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
	read(fr, R);
	Setlength(A, R);
	Setlength(B, R);
	for i0 := 0 to R-1 do
	begin
		read(fr, A[i0]);
		read(fr, B[i0]);
	end;

	{ Calling functions }
	Setlength(T, R);
	pianifica(R, A, B, T);

	{ Writing output }
	for i0 := 0 to R-1 do
	begin
		write(fw, T[i0], ' ');
	end;
	writeln(fw);
	
	close(fr);
    close(fw);
end.
