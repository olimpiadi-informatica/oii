#!/usr/bin/env python3
# -*- coding: utf8 -*-

from limits import *
from sys import argv, exit
from random import randint, seed, shuffle

usage = """Generatore di "escursione".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""

cases = 0


def start_case(H, W):
    global cases
    print()
    print(H, W)
    cases += 1


def generandom(H, W, A):
    start_case(H, W)
    for _ in range(H):
        values = [randint(10**(A - 1), (10**A) - 1) for _ in range(W)]
        print(*values)


def dfs(H, W, stack, visited):
    if not stack:
        return

    x, y = stack.pop()

    if x not in range(W):
        return
    if y not in range(H):
        return

    assert (x, y) in visited

    dirs = [
        (+1, 0),
        (-1, 0),
        (0, +1),
        (0, -1),
    ]
    shuffle(dirs)
    for dx, dy in dirs:
        next = x + 2 * dx, y + 2 * dy
        if next in visited:
            continue
        visited.add((x + dx, y + dy))
        visited.add(next)
        stack.append(next)


def connettivita(H, W, connesso):
    assert H % 2 and W % 2

    start_case(H, W)

    if connesso:
        stack = [(0, 0)]
        visited = set(stack)
        while stack:
            dfs(H, W, stack, visited)
    else:
        stack1 = [(0, 0)]
        stack2 = [(W - 1, H - 1)]
        visited = set(stack1 + stack2)
        while stack1 or stack2:
            dfs(H, W, stack1, visited)
            dfs(H, W, stack2, visited)

    for y in range(H):
        values = [0 if (x, y) in visited else 1 for x in range(W)]
        print(*values)


def main():
    if len(argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, argv[1:])
    seed(S)
    print(T)

    # esempi/a mano
    generandom(5, 5, 1)  # a mano
    generandom(10, 10, 1)  # a mano
    generandom(15, 1, 3)  # linea
    connettivita(19, 19, connesso=randint(0, 1))

    # esponenziale
    generandom(5, 6, 3)
    generandom(5, 5, 6)
    generandom(4, 5, 6)
    generandom(5, 5, 6)

    # connettivita'
    connettivita(39, 59, connesso=randint(0, 1))
    connettivita(99, 99, connesso=randint(0, 1))

    # linee
    generandom(1, 30, 3)
    generandom(50, 1, 6)
    generandom(1, 100, 6)

    # numeri piccoli e grandi
    for a in (3, 6):
        generandom(randint(50, 65), randint(50, 65), a)
        generandom(randint(65, 75), randint(65, 75), a)
        generandom(randint(75, 85), randint(75, 85), a)
        generandom(randint(85, 90), randint(85, 90), a)
        generandom(randint(90, 95), randint(90, 95), a)
        generandom(randint(95, 100), randint(95, 100), a)
        generandom(100, 100, a)

    assert cases == T


if __name__ == "__main__":
    main()
