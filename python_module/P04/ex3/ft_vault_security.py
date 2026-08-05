#!/usr/bin/env python3

def secure_archive(filename: str, mode: str = "r",
                   w_content: str = "") -> tuple[bool, str]:
    try:
        match mode:
            case "r":
                with open(filename, mode) as f:
                    r_content = f.read()
                return (True, r_content)
            case "w":
                if not w_content:
                    return (
                        False,
                        "Error: 'write' mode selected but content is empty")
                with open(filename, mode) as f:
                    f.write(w_content)
                return (True, 'Content successfully written to file')
            case _:
                return (False,
                        f"Error: mode {mode} not recognized - 'r' or 'w' only")
    except OSError as e:
        return (False, f"{e}")


def main() -> None:
    print("=== Cyber Archives Security ===")
    print()

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))
    print()

    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/shadow", "r"))
    print()

    print("Using 'secure_archive' to read from a regular file:")
    memory = secure_archive("../test.txt", "r")
    print(memory)
    print()

    if memory[0]:
        print(
            "Using 'secure_archive' to write previous content to a new file:")
        print(secure_archive("test_memory.txt", "w", memory[1]))
        print()
    else:
        print("ERROR: can't use 'secure_archive' "
              "to write previous content to a new file.\n"
              "Please create ../test.txt first")
        print()

    print("Using 'secure_archive' with unauthorized file mode for open():")
    print(secure_archive("/etc/passwd", "rw"))
    print()

    print("Using 'secure_archive' to write with empty content:")
    print(secure_archive("test_empty_write.txt", "w", ""))
    print()


if __name__ == "__main__":
    main()
