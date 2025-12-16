#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "usage: run.sh <day>" >&2
  exit 1
fi

DAY="$1"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j

EXE="build/aoc2025"
"$EXE" "$DAY"
