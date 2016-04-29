#!/usr/bin/env python2

import sys

lines = open(sys.argv[1]).readlines()
A = int(lines[0])
assert(A <= 10 and len(lines) == A + 1)

lines = map(lambda x: map(int, x.strip().split()), lines[1:])
for i in xrange(A):
  assert len(lines[i]) == i + 1
  for j in xrange(i + 1):
    assert lines[i][j] in range(1, 101)
