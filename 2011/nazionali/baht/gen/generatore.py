#!/usr/bin/env python2
# Roberto

import sys
from numpy.random import seed, randint, permutation
import numpy as np
from limiti import *

def run():
    try:
        P, Num, Val, See = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4])
    except:
        print 'Usage: %s Iter Num Val Seed' % sys.argv[0]
        return 1

    # check input params and start seed
    assert (1 <= P <= MaxIter)
    assert (1 <= Num <= MaxNum)
    assert (1 <= Val <= MaxVal)
    seed(See)


    # output number of test cases
    out = sys.stdout
    out.write('%d\n' % P)

    for iiii in range(P):
        # generate test case and add items: Val should be relatively small
        left = randint(1, max(2,Num-1) )
        right = Num - left
        S = [randint(1, Val+1) for i in range(left)]
        gap = sum(S) + 2
        S += [randint(gap, min( 2*gap+1, MaxVal+1)) for i in range(right)]

        assert Num == len(S)
        assert sum(S) < MaxSum

        R = permutation(S)

        # output test case
        out.write('%d\n' % len(R))
        for x in R:
            out.write('%d ' % x)
        out.write('\n')

        # print gap, sum(S) # the output of sol.py should be different from approximately gap and sum(S)


# main
if __name__ == '__main__':
    sys.exit(run())
