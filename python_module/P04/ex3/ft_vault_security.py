#!/usr/bin/env python3

def secure_archive(filename: str, mode: str = "r",
                   w_content: str = "") -> tuple[bool, str]:
    try:
        with open(filename, mode) as f:
            match mode:
                case "r":
                    r_content = f.read()
                    return (True, r_content)
                case "w":
                    if not w_content:
                        return (
                            False,
                            "Error: 'write' mode selected but content is empty"
                            )
                    f.write(w_content)
                    return (True, 'Content successfully written to file')
                case _:
                    return (
                        False,
                        f"Error: mode {mode} not recognized - 'r' or 'w' only"
                        )
    except OSError as e:
        return (False, f"{e}")


def main() -> None:
    print("=== Cyber Archives Security ===")
    print()

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))
    print()

    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/passwd", "r"))
    print()

    print("Using 'secure_archive' to read from a regular file:")
    memory = secure_archive("../test.txt", "r")
    print(memory)
    print()

    print("Using 'secure_archive' to write previous content to a new file:")
    print(secure_archive("memory.txt", "w", memory[1]))
    print()


if __name__ == "__main__":
    main()
