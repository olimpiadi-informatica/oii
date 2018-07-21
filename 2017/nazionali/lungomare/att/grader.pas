uses lungomare;

var
	fr, fw : text;

{ used to read char ignoring whitespaces (space, newline, tab...) }
function read_char_skip_whitespaces() : char;
var
   c : char;
begin
   read(fr, c);
   while (ord(c) = $0020) or (ord(c) = $0009) or
         (ord(c) = $000a) or (ord(c) = $000b) or
         (ord(c) = $000c) or (ord(c) = $000d) do
       read(fr, c);

   read_char_skip_whitespaces := c;
end;

var

{ Declaring variables }
	N : longint;
	L : int64;
	D : array of int64;
	P : array of int64;
	C : int64;

{ Declaring iterators used in for loops }
	i0: longint;

begin
	fr := input;
	fw := output;
    reset(fr);
    rewrite(fw);

	{ Reading input }
	read(fr, N);
	read(fr, L);
	Setlength(D, N);
	for i0 := 0 to N-1 do
	begin
		read(fr, D[i0]);
	end;
	Setlength(P, N);
	for i0 := 0 to N-1 do
	begin
		read(fr, P[i0]);
	end;

	{ Calling functions }
	C := percorri(N, L, D, P);

	{ Writing output }
	writeln(fw, C);

	close(fr);
    close(fw);
end.
