#!/usr/bin/env pypy
# Usare pypy2 solo quando necessario. La compilazione richiede tempo e viene ricompilato per ogni testcase.

from limiti import *
from varie import *
from sys import argv, exit, stderr
from copy import copy
import os
from random import random, randint, choice, sample, shuffle, seed

usage="""Generatore di "classifica".

Parametri:
* N (numero di partecipanti)
* Q (numero di query)
* ST (subtask [2,6,7=tutto ammesso; 3=no squalifica(), 4=partecipante() dopo le altre query, 5=no supera())
* X (quale query deve essere molto frequente: 0= nessuna, 1= supera, 2= squalifica, 3 = partecipante)
* S (seed)

Constraint:
* 2 <= N <= %d
* 0 <= Q <= %d
* 2 <= ST <= 7
* 0 <= X <= 3
""" % (MAXN, MAXQ)



def run(N, Q, ST, X):
	possible_queries = []
	if ST == 2 or ST == 6 or ST == 7:
		possible_queries = ['supera', 'squalifica', 'partecipante']
	elif ST == 3:
		possible_queries = ['supera', 'partecipante']
	elif ST == 4:
		possible_queries = ['supera', 'squalifica']
	elif ST == 5:
		possible_queries = ['squalifica', 'partecipante']
		
	if X == 1 and 'supera' not in possible_queries:
		print 'X = 1 non ammesso nel subtask', ST
		exit(1)
		
	if X == 2 and 'squalifica' not in possible_queries:
		print 'X = 2 non ammesso nel subtask', ST
		exit(1)
	
	ids = list(range(N))
	shuffle(ids)
	print N, Q
	for i in range(N):
		print ids[i],
	print

	sfruttato_X = False
	# Aggiunge un buco di squalificati prima di iniziare e poi fa tanti 
	# sorpassi da una parte all'altra.
	if X in [1, 2] and 'supera' in possible_queries and 'squalifica' in possible_queries and N > 10 and Q > 2*(N//3):
		sfruttato_X = True
		for it in range(N//3, 2*(N//3)):
			Q -= 1
			print 'x', ids[it]
		ids = ids[0:N//3] + ids[2*(N//3):N]
		a = ids[N//3 - 1]
		b = ids[N//3]
		for _ in range(N//6):
			Q -= 2
			print 's', a
			print 's', b

	first_one_rank = 0
	rank2id = copy(ids)   
	id2rank = [-1]*N
	for i in range(len(ids)):
		id2rank[ids[i]] = i
	
	
	partecipante_num = Q//3
	if not sfruttato_X and X == 1:
		possible_queries.append('supera')
		possible_queries.append('supera')
	if not sfruttato_X and X == 2:
		possible_queries.append('squalifica')
		possible_queries.append('squalifica')
	if X == 3 and 'partecipante' in possible_queries:
		possible_queries.append('partecipante')
		possible_queries.append('partecipante')
		partecipante_num = 2*(Q//3)
		
	for _ in xrange(Q):
		if ST == 4 and _ == partecipante_num:
			possible_queries = ['partecipante']
		
		if len(ids) == 1:
			possible_queries = ['partecipante']
			
		query = choice(possible_queries)
		if query == 'squalifica':
			it = randint(0, len(ids)-1)
			
			id1 = ids[it]
			
			print 'x', id1
			ids[it] = ids[-1]
			ids.pop()
			
			rank = id2rank[id1]
			rank2id[rank] = -1
			while rank2id[first_one_rank] == -1 and first_one_rank < len(rank2id):
				first_one_rank += 1
				
			
		if query == 'supera': # Non deve essere chiamato sul primo!
			while 1:
				id1 = choice(ids)
				if id2rank[id1] ==  first_one_rank:
					continue
				
				print 's', id1
				rank1 = id2rank[id1]
				rank2 = rank1-1
				# Potrebbe essere lento al caso pessimo, ma in media va bene.
				while rank2id[rank2] == -1:
					rank2 -= 1
				id2 = rank2id[rank2]
				rank2id[rank1], rank2id[rank2] = rank2id[rank2], rank2id[rank1]
				id2rank[id1], id2rank[id2] = id2rank[id2], id2rank[id1]				
				break
			
		if query == 'partecipante':
			print 'p', randint(0, len(ids)-1)+1
    

if __name__ == "__main__":
	if len(argv) != 6:
		print usage
		exit(1)

	N, Q, ST, X, S = map(int, argv[1:])

	assert (1 <= N <= MAXN)
	assert (1 <= Q <= MAXQ)
	assert (2 <= ST <= 7)
	assert (0 <= X <= 3)
	seed(S)
	run(N, Q, ST, X)
