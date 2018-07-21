uses hogwarts;

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
	M : longint;
	A : array of longint;
	B : array of longint;
	inizio : array of longint;
	fine : array of longint;
	tempo : longint;

{ Declaring iterators used in for loops }
	i0: longint;

begin
	fr := input;
	fw := output;
    reset(fr);
    rewrite(fw);

	{ Reading input }
	read(fr, N);
	read(fr, M);
	Setlength(A, M);
	Setlength(B, M);
	Setlength(inizio, M);
	Setlength(fine, M);
	for i0 := 0 to M-1 do
	begin
		read(fr, A[i0]);
		read(fr, B[i0]);
		read(fr, inizio[i0]);
		read(fr, fine[i0]);
	end;

	{ Calling functions }
	tempo := raggiungi(N, M, A, B, inizio, fine);

	{ Writing output }
	writeln(fw, tempo);

	close(fr);
    close(fw);
end.
