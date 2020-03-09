#!/usr/bin/env escript
-module(main).
-export([main/1]).

main(_) -> 
    {ok, [T]} = io:fread("", "~d"),
    solve(1, T, false).

solve(_, _, true) -> {};

solve(C, N, false) ->
    {ok, [T]} = io:fread("", "~d"),
    io:format("Case #~w: ~w~n", [C, sum(0, T)]),
    solve(C + 1, N, C == N).

positive(Acc, K, true) -> Acc + K;

positive(Acc, _, false) -> Acc.

sum(Acc, 0) -> Acc;

sum(Acc, N) ->
    {ok, [K]} = io:fread("", "~d"),
    sum(positive(Acc, K, K > 0), N - 1).
