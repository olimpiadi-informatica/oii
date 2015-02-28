#!/usr/bin/env python

import os, sys
import random

MinN, MaxN = 1, 1000
MinM, MaxM = 1, 1000

def run():
   global MinN, MinM, MaxN, MaxM

   if len(sys.argv) < 4:
      print 'Usage: %s N M seed' % os.path.basename(sys.argv[0])
      return 1

   N, M, Seed = sys.argv[1:]
   N = int(N)
   M = int(M)
   assert ( MinN <= N <= MaxN )
   assert ( MinM <= M <= MaxM )

   random.seed(int(Seed))

   print "%d %d" % ( N, M ) 

   points = {}
   for i in xrange(int(N)) :
      r, c = random.randint(MinM, M), random.randint(MinM, M)
      while ( (r,c) in points):
         r, c = random.randint(MinM, M), random.randint(MinM, M)
      points[(r,c)] = 1
    
   for e in points.keys():
      print "%d %d" % (e[0], e[1])

if __name__ == '__main__':
   sys.exit(run())
   

