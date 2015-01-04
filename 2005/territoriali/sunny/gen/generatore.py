#!/usr/bin/env python2

# N: numero nodi
# M: numero archi
# L: se >= 0 allora L = lunghezza cammino,
#    se == -1 allora H singoletto,
#    se == -2 e` completamente casuale
# Seed: seme

import sys, random

N = int(sys.argv[1])
M = int(sys.argv[2])
L = int(sys.argv[3])
Seed = int(sys.argv[4])

if M > (N * (N - 1)):
	sys.stderr.write("M troppo grande per N.\n")
	sys.exit(1)

random.seed( Seed )

nodes = range(1, N + 1)
random.shuffle(nodes)

H = 0

if L != 0:
	if L > 0:
		S = L
	else:
		S = len( nodes ) - 1
else:
	S = 0

#sys.stderr.write(str(S) + " " + str(len(nodes)))

harmony = nodes[H]
spike   = nodes[S]

if L == -1:
	# Eliminiamo il singoletto

	del nodes[H]
	S = S - 1

edges = set()

if L > 0:
	limit = M - L
else:
	limit = M

while ( len( edges ) < limit ):
	a = random.randint(1, N)
	b = random.randint(1, N)

	a, b = min(a, b), max(a, b)
	if a == b:
		continue

	if (a, b) in edges:
		edges.remove( (a, b) )

	edges.add( (a, b) )

sys.stderr.write("andata\n");

output = []

if L > 0:
	sys.stderr.write("Output: " + str(L) + "\n")

	if M < L:
		sys.stderr.write("M troppo piccolo")
		sys.exit(1)

	conta = 0
	for i in range(L):
		a, b = min(nodes[i], nodes[i+1]), max(nodes[i], nodes[i+1])
		if (a, b) in edges:
			edges.remove( (a, b) )
			conta += 1

		output.append( (a, b, L - i) )

	bright = range(L + 1, M + 1 - conta)
else:
	sys.stderr.write("Grafo completamente casuale\n")
	bright = range(1, M + 1)

edges = list(edges)
random.shuffle(edges)
random.shuffle(bright)

for i in range(len(bright)):
	output.append( (edges[i][0], edges[i][1], bright[i]) )
random.shuffle( output )

print N, len(output), harmony, spike

for (a, b, l) in output:
	print str(a) + " " + str(b) + " " + str(l)
