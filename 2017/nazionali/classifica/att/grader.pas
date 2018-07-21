uses classifica;

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
	Q : longint;
	ids : array of longint;
	types : array of char;
	params : array of longint;
	answers : array of longint;

{ Declaring iterators used in for loops }
	i0: longint;

{ Functions ad-hoc for this grader }
procedure make_calls(var Q: longint; types: array of char; params: array of longint; var answers: array of longint);
var
	i, cnt: longint;
begin
	cnt := 0;
	for i := 0 to Q-1 do
    begin
		answers[i] := 0;
		if types[i] = 's' then
   			supera(params[i])
		else if types[i] = 'x' then
			squalifica(params[i])
		else if types[i] = 'p' then begin
			answers[cnt] := partecipante(params[i]);
			cnt := cnt + 1;
		end;
    end;
	Q := cnt;
end;


begin
	fr := input;
	fw := output;
    reset(fr);
    rewrite(fw);

	{ Reading input }
	read(fr, N);
	read(fr, Q);
	Setlength(ids, N);
	for i0 := 0 to N-1 do
	begin
		read(fr, ids[i0]);
	end;
	Setlength(types, Q);
	Setlength(params, Q);
	for i0 := 0 to Q-1 do
	begin
		types[i0] := read_char_skip_whitespaces();
		read(fr, params[i0]);
	end;

	{ Calling functions }
	inizia(N, ids);
	Setlength(answers, Q);
	make_calls(Q, types, params, answers);

	{ Writing output }
	for i0 := 0 to Q-1 do
	begin
		write(fw, answers[i0], ' ');
	end;
	writeln(fw);

	close(fr);
    close(fw);
end.
