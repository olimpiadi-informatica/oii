import sys

lines = open('input.txt').readlines()
A = int(lines[0])
assert(A <= 10 and len(lines) == A + 1)

lines = map(lambda x: map(int, x.strip().split()), lines[1:])
for i in xrange(A):
  assert len(lines[i]) == i + 1
  for j in xrange(i + 1):
    assert lines[i][j] in range(1, 101)

dp = [[lines[0][0]]]
for i in xrange(1, A):
  dp.append([])
  for j in xrange(i + 1):
    upLeft = 0
    upRight = 0
    if j - 1 >= 0:
      upLeft = dp[i - 1][j - 1]
    if j < i:
      upRight = dp[i - 1][j]
    dp[i].append(lines[i][j] + max(upLeft, upRight))

open('output.txt', 'w').write('%d\n' % max(dp[-1]))
