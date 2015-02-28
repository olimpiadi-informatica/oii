#!/usr/bin/env python

import pydot
import sys

def run():
    if len(sys.argv) != 2:
        print >> sys.stderr, 'Usage: %s filename' % os.path.basename(sys.argv[0])
        return 1
        
    edges = [map(int, l[:-1].split()) for l in open(sys.argv[1])][1:]
    
    g = pydot.graph_from_edges(edges)
    basename = sys.argv[1][:sys.argv[1].rfind('.')]
    g.write_png(basename + '.png')

if __name__ == '__main__':
    sys.exit(run())
    
