#!/usr/bin/env python3

import sys
import random

def run(N):
    print(N)
    for i in range(N):
        print(" ".join([str(random.randint(1, 100)) for j in range(i + 1)]))

if __name__ == "__main__":
    N, S = map(int, sys.argv[1:])

    random.seed(S)
    run(N)
