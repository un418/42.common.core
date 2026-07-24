#!/usr/bin/env python3

import sys
import typing


def main() -> None:
    args = sys.argv[1:]
    if len(args) < 1:
        print("Usage: ft_ancient_text.py <file>")
        return

    print("=== Cyber Archives Recovery ===")
    filename = args[0]
    open_mode = "r"

    try:
        print(f"Accessing file '{filename}'")
        f: typing.IO[str] = open(filename, open_mode)
    except OSError as e:
        print(f"Error opening file '{filename}': {e}")
        return

    try:
        print("---\n")
        print(f.read())
        print("---")
    except OSError as e:
        print(f"Error reading file '{filename}': {e}")
        return
    finally:
        f.close()
        print(f"File '{filename}' closed.")


if __name__ == "__main__":
    main()
