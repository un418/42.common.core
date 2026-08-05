#!/usr/bin/env python3

import sys
import typing


def main() -> None:
    args = sys.argv[1:]
    if len(args) != 1:
        print("Usage: ft_archive_creation.py <file>")
        return

    print("=== Cyber Archives Recovery & Preservation ===")
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
        content = f.read()
        print(content)
        print("\n---")
    except OSError as e:
        print(f"Error reading file '{filename}': {e}")
        return
    finally:
        f.close()
        print(f"File '{filename}' closed.")

    print("\nTransform data:")
    archive_content = content.replace("\n", "#\n")
    if not archive_content.endswith("\n"):
        archive_content += "#"
    print("---\n")
    print(archive_content)
    print("\n---")

    try:
        archive_filename = input("Enter new file name (or empty): ")
    except (KeyboardInterrupt, EOFError):
        print("\nProgram interrupted by user.")
        return

    if not archive_filename:
        print("Not saving data.")
        return

    try:
        archive_f = open(archive_filename, "w")
    except OSError as e:
        print(f"Error opening file '{archive_filename}': {e}")
        print("Data not saved.")
        return

    try:
        print(f"Saving data to '{archive_filename}'")
        archive_f.write(archive_content)
    except OSError as e:
        print(f"Error writing in file '{archive_filename}': {e}")
        print("Data not saved.")
        return
    else:
        print(f"Data saved in file '{archive_filename}'.")
    finally:
        archive_f.close()


if __name__ == "__main__":
    main()
