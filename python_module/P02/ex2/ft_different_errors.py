#!/usr/bin/env python3

def garden_operations(operation_number: int) -> None:
    match operation_number:
        case 0:
            _ = int("abc")
        case 1:
            _ = 7 / 0
        case 2:
            _ = open("/non/existent/file")
        case 3:
            _ = "abc" + 5
        case _:
            return


def test_error_types() -> None:
    for op in range(5):
        print(f"Testing operation {op}...")
        try:
            garden_operations(op)
        except (ValueError, ZeroDivisionError,
                FileNotFoundError, TypeError) as e:
            print(f"Caught {e.__class__.__name__}: {e}")
        else:
            print("Operation completed successfully")
    print()


def main() -> None:
    print("=== Garden Error Types Demo ===")
    test_error_types()
    print("All error types tested successfully!")


if __name__ == "__main__":
    main()
