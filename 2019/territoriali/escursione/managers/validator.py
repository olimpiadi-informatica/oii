#!/usr/bin/env python3
from limits import MAXA, MAXL
import sys


def main():
    f = sys.stdin.readlines()
    T = int(f[0])
    row = 0
    for i in range(T):
        row += 1
        # print("DEBUG", f[row])
        assert len(f[row].strip()) == 0
        row += 1
        # print("DEBUG", f[row])
        H, W = map(int, f[row].split())
        assert 1 <= H <= MAXL
        assert 1 <= W <= MAXL
        for i in range(H):
            row += 1
            # print("DEBUG", f[row])
            riga = list(map(int, f[row].split()))
            assert len(riga) == W
            assert all(0 <= x <= MAXA for x in riga)
    assert len(f) == row + 1


if __name__ == "__main__":
    main()
