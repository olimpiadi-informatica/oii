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
