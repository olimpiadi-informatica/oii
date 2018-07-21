uses hogwarts, Classes, sysutils;

const MAX_IN_BUF = 4096 * 4;
var
    total_bytes_read, bytes_read : int64;
    input_buffer : array[0..MAX_IN_BUF-1] of char;
    idx_input_buffer : longint;
    input_stream : TFileStream;

function fast_read_next_char(): Char;
begin
    (* Take one char out of the buffer *)
    fast_read_next_char := input_buffer[idx_input_buffer];
    inc(idx_input_buffer);

    if idx_input_buffer = MAX_IN_BUF then (* I'm at the end of the buffer, read another buffer *)
    begin
        if total_bytes_read <= input_stream.Size then (* We haven't reached EOF *)
        begin
            bytes_read := input_stream.Read(input_buffer, sizeof(input_buffer));
            inc(total_bytes_read, bytes_read);
        end;

        idx_input_buffer := 0;
    end;
end;

(* Returns first non whitespace character *)
function fast_read_char() : char;
var c: Char;
begin
    c := fast_read_next_char();
    while (ord(c) = $0020) or (ord(c) = $0009) or
          (ord(c) = $000a) or (ord(c) = $000b) or
          (ord(c) = $000c) or (ord(c) = $000d) do
        c := fast_read_next_char();

    fast_read_char := c;
end;

function fast_read_int() : longint;
var res : longint;
    c : char;
    negative : boolean;
begin
    res := 0;
    negative := False;

    repeat
        c := fast_read_next_char();
    until (c = '-') or (('0' <= c) and (c <= '9'));

    if c = '-' then
    begin
        negative := True;
        c := fast_read_next_char();
    end;

    repeat
        res := res * 10 + ord(c) - ord('0');
        c := fast_read_next_char();
    until not (('0' <= c) and (c <= '9'));

    if negative then
        fast_read_int := -res
    else
        fast_read_int := res;
end;

function fast_read_longint() : int64;
var res : int64;
    c : char;
    negative : boolean;
begin
    res := 0;
    negative := False;

    repeat
        c := fast_read_next_char();
    until (c = '-') or (('0' <= c) and (c <= '9'));

    if c = '-' then
    begin
        negative := True;
        c := fast_read_next_char();
    end;

    repeat
        res := res * 10 + ord(c) - ord('0');
        c := fast_read_next_char();
    until not (('0' <= c) and (c <= '9'));

    if negative then
        fast_read_longint := -res
    else
        fast_read_longint := res;
end;

function fast_read_real() : double;
begin
    (* TODO *)
    fast_read_real := 42.0;
end;

procedure init_fast_input(file_name : string);
begin
    input_stream := TFileStream.Create(file_name, fmOpenRead);
    input_stream.Position := 0;
    bytes_read := input_stream.Read(input_buffer, sizeof(input_buffer));
    inc(total_bytes_read, bytes_read);
    idx_input_buffer := 0;
end;

procedure close_fast_input;
begin
    input_stream.Free;
end;

const MAX_OUT_BUF = 4096 * 4;
var
    output_buffer : array[0..MAX_OUT_BUF-1] of char;
    idx_output_buffer : longint;
    output_stream : TFileStream;

procedure fast_write_char(x : char);
begin
    (* Write one char onto the buffer *)
    output_buffer[idx_output_buffer] := x;
    inc(idx_output_buffer);

    if idx_output_buffer = MAX_OUT_BUF then (* I'm at the end of the buffer, flush it *)
    begin
        output_stream.WriteBuffer(output_buffer, sizeof(output_buffer));

        idx_output_buffer := 0;
    end;
end;

procedure fast_write_int(x : longint);
begin
    if x < 0 then (* Write the sign, then the number *)
    begin
        fast_write_char('-');
        fast_write_int(-x);
    end
    else (* Write the number recursively *)
    begin
        if x >= 10 then
            fast_write_int(x div 10);
        fast_write_char(chr(ord('0') + x mod 10));
    end;
end;

procedure fast_write_longint(x : int64);
begin
    if x < 0 then (* Write the sign, then the number *)
    begin
        fast_write_char('-');
        fast_write_longint(-x);
    end
    else (* Write the number recursively *)
    begin
        if x >= 10 then
            fast_write_longint(x div 10);
        fast_write_char(chr(ord('0') + x mod 10));
    end;
end;

procedure fast_write_real(x : double);
begin
    (* TODO *)
    fast_write_char('4');
    fast_write_char('2');
    fast_write_char('.');
    fast_write_char('0');
end;

procedure init_fast_output(file_name : string);
var
    open_flag: word;
begin
    open_flag := fmCreate;
    if FileExists(file_name) then
        open_flag := fmOpenWrite;

    output_stream := TFileStream.Create(file_name, open_flag);
    output_stream.size := 0;
    idx_output_buffer := 0;
end;

procedure close_fast_output;
begin
    if idx_output_buffer > 0 then (* Gotta flush them bytez *)
    begin
        (* TODO: check if this is OK also when using unicode data *)
        output_stream.Write(output_buffer, idx_output_buffer * sizeof(output_buffer[0]))
    end;

    output_stream.Free;
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
	init_fast_input('input.txt');
	init_fast_output('output.txt');

	{ Reading input }
	N := fast_read_int();
	M := fast_read_int();
	Setlength(A, M);
	Setlength(B, M);
	Setlength(inizio, M);
	Setlength(fine, M);
	for i0 := 0 to M-1 do
	begin
		A[i0] := fast_read_int();
		B[i0] := fast_read_int();
		inizio[i0] := fast_read_int();
		fine[i0] := fast_read_int();
	end;

	{ Calling functions }
	tempo := raggiungi(N, M, A, B, inizio, fine);

	{ Writing output }
	fast_write_int(tempo);
	fast_write_char(chr(10));

	close_fast_input();
	close_fast_output();
end.
