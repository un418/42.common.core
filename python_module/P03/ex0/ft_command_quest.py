#!/usr/bin/env python3

import sys


def print_arg_list_slice() -> None:
    i = 1
    for arg in sys.argv[1:]:
        print(f"Argument {i}: {arg}")
        i += 1


# Not pythonic -> C-Like
def print_arg_list_while() -> None:
    i = 1
    while i < len(sys.argv):
        print(f"Argument {i}: {sys.argv[i]}")
        i += 1


# Not in authorized functions
def print_arg_list_range() -> None:
    for i in range(1, len(sys.argv)):
        print(f"Argument {i}: {sys.argv[i]}")


# Not in authorized functions
def print_arg_list_enumerate() -> None:
    for i, arg in enumerate(sys.argv[1:], start=1):
        print(f"Argument {i}: {arg}")


def main() -> None:
    print("=== Command Quest ===")
    print(f"Program name: {sys.argv[0]}")

    total_arg = len(sys.argv)
    if total_arg == 1:
        print("No arguments provided!")
    else:
        print(f"Arguments received: {total_arg - 1}")
        print_arg_list_slice()

    print(f"Total arguments: {total_arg}")


if __name__ == "__main__":
    main()
