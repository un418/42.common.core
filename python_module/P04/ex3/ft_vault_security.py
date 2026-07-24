#!/usr/bin/env python3

def secure_archive(filename: str, mode: str = "r",
                   w_content: str = "") -> tuple[bool, str]:
    if mode not in {"r", "w"}:
        return (False, f"Error: mode {mode} not recognized - 'r' or 'w' only")
    if mode == "w" and not w_content:
        return (False, "Error: 'write' mode selected but content is empty")
    try:
        with open(filename, mode) as f:
            if mode == "r":
                r_content = f.read()
                ret = r_content
            if mode == "w":
                f.write(w_content)
                ret = "Content successfully written to file"
    except OSError as e:
        return (False, f"{e}")
    else:
        return (True, ret)


def main() -> None:
    print("=== Cyber Archives Security ===")
    print()

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))
    print()

    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/master.passwd", "r"))
    print()

    print("Using 'secure_archive' to read from a regular file:")
    memory = secure_archive("../test_subject.txt", "r")
    print(memory)
    print()

    print("Using 'secure_archive' to write previous content to a new file:")
    print(secure_archive("memory.txt", "w", memory[1]))
    print()


if __name__ == "__main__":
    main()
