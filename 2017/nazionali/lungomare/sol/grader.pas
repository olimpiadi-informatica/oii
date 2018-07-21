uses lungomare, Classes, sysutils;

var
    input_file : File;
    bytes_read : int64;
	N : int64;
	L : int64;
	D : array of int64;
	P : array of int64;

begin
    assign(input_file, 'input.txt');
    reset(input_file, 1); {1 is right because of reasons}

    BlockRead(input_file, N, sizeof(N), bytes_read);
    assert(bytes_read = 8);

    BlockRead(input_file, L, sizeof(L), bytes_read);
    assert(bytes_read = 8);

    Setlength(D, N);
    Setlength(P, N);

    BlockRead(input_file, D[0], N*sizeof(N), bytes_read); {D[0] is megl che D}
    assert(bytes_read = N*sizeof(N));

    BlockRead(input_file, P[0], N*sizeof(N), bytes_read); {P[0] is megl che P}
    assert(bytes_read = N*sizeof(N));

    close(input_file);
    writeln(percorri(N, L, D, P));
end.
