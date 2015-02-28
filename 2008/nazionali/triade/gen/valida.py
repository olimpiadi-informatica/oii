#!/usr/bin/env python

import sys
import os

def usage():
    print >> sys.stderr, "Usage: %s file_input.txt" % \
        os.path.basename(sys.argv[0])
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
                
