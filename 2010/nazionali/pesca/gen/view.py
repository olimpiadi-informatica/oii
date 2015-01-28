#!/usr/bin/env python

"""Visualizza gli input di pesca

"""
import sys
import Image
import numpy as np

def run():
    filename = sys.argv[1]
    fishes = []
    N = 0
    with open(filename) as fin:
        P, M = map(int, fin.next().split())
        i0, j0 = map(int, fin.next().split())
        for i in range(P):
            fishes.append(map(int, fin.next().split()))
            N = max(N, fishes[-1][0], fishes[-1][1])
        code1 = fin.next().replace(' ', '').strip()
        code2 = fin.next().replace(' ', '').strip()

    N += 1
    buf = np.empty((N, N, 3), np.uint8)
    buf.fill(224)

    for x, y in fishes:
        buf[x][y] = (128, 16, 16)

    seq1 = [j0]
    seq2 = [j0]

    for code, seq in ((code1, seq1), (code2, seq2)):
        x, y = i0, j0
        for c in code:
            if c == '1':
                x += 1
            else:
                y += 1

            if (buf[x][y][0] == 224):
                buf[x][y] = (16, 16, 16)
            else:
                buf[x][y] = (128, 128, 128)

    img = Image.fromarray(buf)
    try:
        img.save(sys.argv[2])
    except IndexError:
        img.show(command='eog -n') ## XXX: workaround per eog..

if __name__ == '__main__':
    sys.exit(run())
