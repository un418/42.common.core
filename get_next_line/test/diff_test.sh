#!/bin/sh
# diff_test.sh — validate get_next_line output against the source files.

# Use the first argument as BUFFER_SIZE, default to 1 if none is given.
BUFFER_SIZE="${1:-1}"
# Use the second argument as the folder holding the generated .output files.
OUT_DIR="${2:-output}"

FILES="test0.txt
test_empty_file.txt
test_one_line.txt
test_only_nl.txt"

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
fail=0

for f in $FILES; do
	out="$OUT_DIR/$f.$BUFFER_SIZE.output"
	if diff -q "$f" "$out" > /dev/null 2>&1; then
		printf "${GREEN}DIFF PASS${RESET}  %s (buf=%s)\n" "$f" "$BUFFER_SIZE"
	else
		printf "${RED}DIFF FAIL${RESET}  %s (buf=%s)\n" "$f" "$BUFFER_SIZE"
		diff "$f" "$out"
		fail=1
	fi
done

exit $fail
