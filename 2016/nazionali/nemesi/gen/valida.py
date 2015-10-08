#!/usr/bin/env pypy

from limiti import *

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt [subtask_number]" % \
        os.path.basename(sys.argv[0])
    exit(1)


# 0            -> corretto
# altro numero -> non corretto
# per testare la correttezza dell'input, usate assert()
def run(f, st):
	assert(len(f) == 2)
	N, = map(int, f[0].split())
	assert(1 <= N <= MAXN_ST[st-1])
	
	nemici = map(int, f[1].split())
	assert(len(nemici) == N)
	
	for x in nemici:
		assert(0 <= x < N)

	for i in range(N):
		assert(nemici[i] != i)
	
	if st == 2:
		for i in range(N):
			assert(i == nemici[nemici[i]])

	if st == 3:
		padri = [False]*N
		for i in range(N):
			assert( not padri[nemici[i]] )
			padri[nemici[i]] = True
	return 0 # Input corretto

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    # Di default, ignora i subtask
    st = 0

    if len(sys.argv) == 3:
        st = int(sys.argv[2])

    f = open(sys.argv[1]).readlines()
    exit(run(f, st))
