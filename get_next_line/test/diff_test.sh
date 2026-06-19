#!/bin/sh
# diff_test.sh — validate get_next_line output against the source inputs.
#   $1 = tag used in the output file name (buffer size, or "bonus")
#   $2 = list of source inputs (their relative path, e.g. "inputs/test0.txt")
# The generated files are always read from the hardcoded "output/" folder.

TAG="${1:-1}"
FILES="$2"

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
fail=0

for src in $FILES; do
	out="output/$(basename "$src").$TAG.output"
	if diff -q "$src" "$out" > /dev/null 2>&1; then
		printf "${GREEN}DIFF PASS${RESET}  %s (buf=%s)\n" "$src" "$TAG"
	else
		printf "${RED}DIFF FAIL${RESET}  %s (buf=%s)\n" "$src" "$TAG"
		diff "$src" "$out"
		fail=1
	fi
done

exit $fail
