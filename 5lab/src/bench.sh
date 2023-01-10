#!/bin/bash
cp cmake-build-debug/solution tests/solution
cp cmake-build-debug/naieve tests/naieve
# shellcheck disable=SC2164
cd tests
TEST_COUNT=8
for ((t = 1; t <= "$TEST_COUNT"; t++)); do
  a=$(cat "$t".in)
  if [[ ("$a" = "") ]]; then
    continue
  fi
  touch "outSolution$t.txt"
  touch "outNaieve$t.txt"
  ./solution <"$t.in" >"outSolution$t.txt"
  ./naieve <"$t.in" >"outNaieve$t.txt"
done
