#!/usr/bin/env python3
# -*- coding: utf8 -*-

import sys
import random

from limits import *

usage = """Generatore di "tornello".

Parametri:
* S - seed
* 0 - il valore zero, molto importanteh!!!!
"""


def gen_all_same(N):
    return [["+1", "-1"][random.randrange(2)]] * random.randint(N // 2, N)


def gen_sum_to_0(N):
    assert N % 2 == 0
    plus = N // 2
    minus = N // 2
    assert plus + minus == N

    result = []
    while plus > 0 and minus > 0:
        v = random.choice(["+1", "-1"])
        if v == "+1":
            plus -= 1
        else:
            minus -= 1
        result.append(v)

    while plus > 0:
        result.append("+1")
        plus -= 1
    while minus > 0:
        result.append("-1")
        minus -= 1

    return result


def gen_random(N):
    return [random.choice(["+1", "-1"]) for _ in range(N)]


def gen_all_above_0(N):
    result = []
    value = 0

    for _ in range(N):
        if value > 0:
            result.append(random.choice(["+1", "-1"]))
        else:
            result.append("+1")

    return result


def gen_all_below_0(N):
    result = []
    value = 0

    for _ in range(N):
        if value < 0:
            result.append(random.choice(["+1", "-1"]))
        else:
            result.append("-1")

    return result


def print_case(generate):
    print()
    vals = generate()
    assert 1 <= len(vals) <= MAXN
    print(len(vals))
    print(" ".join(vals))


cases = [
    lambda: gen_random(30),
    lambda: gen_random(100),
    lambda: gen_all_above_0(1000),
    lambda: gen_all_below_0(1000),
    lambda: gen_sum_to_0(1000),
    lambda: gen_random(1000),
    lambda: gen_random(3000),
    lambda: gen_random(5000),
    lambda: gen_all_same(9999),
    lambda: gen_all_same(9999),
    lambda: gen_random(9999),
    lambda: gen_random(9999),
]

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(usage)
        exit(1)

    S, _ = map(int, sys.argv[1:])
    random.seed(S)

    assert len(cases) == T

    print(T)
    for gen in cases:
        print_case(gen)
