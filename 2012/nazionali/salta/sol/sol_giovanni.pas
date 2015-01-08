Program salta;
const MAXN = 1000000;
var N	   : longint;
   pos	   : array [1..MAXN] of longint;
   occ	   : array [1..MAXN] of boolean;
   i, curr : longint;
   outputf : text;
   inputf  : text;
   libere  : longint;

begin
{$ifdef EVAL}
   assign(inputf, 'input.txt');
   assign(outputf, 'output.txt');
   reset(inputf);
   rewrite(outputf);
{$else}
   inputf := input;
   outputf := output;
{$endif}
   
   read(inputf, N);
   for i := 1 to N do begin
      read(inputf, pos[i]);
      occ[i] := FALSE;
   end;

   libere := N;
   curr := 1;
   while not occ[curr] do begin
      occ[curr] := TRUE;
      libere := libere - 1;
      curr := ((curr + pos[curr]) mod N) + 1;
   end;

   writeln(outputf, libere);
   for i := 1 to N do
      if not occ[i] then
	 write(outputf, i, ' ');

   close(inputf);
   close(outputf);
end.
