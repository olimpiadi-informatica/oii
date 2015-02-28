#!/usr/bin/env python2

import sys
import os

from limiti import *

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt" % \
        os.path.basename(sys.argv[0])
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    bucket = set()
    counter = dict()

    with open(sys.argv[1]) as f:
        lines = f.readlines()

    n = int(lines[0])
    assert MINN <= n <= MAXN
    assert len(lines) == n+1
    for s in lines[1:]:
        s = s.strip()
        assert len(s) <= MAXLEN
        bucket.add(s)
        ss = "".join(sorted(s))
        try:
            counter[ss] += 1
        except:
            counter[ss] = 1

    assert len(bucket) == n

    for key, value in counter.iteritems():
        assert value <= len(key)
