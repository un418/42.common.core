#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    return int(temp_str)


def test_temperature() -> None:
    data = ['25', 'abc']

    for input in data:
        print(f"Input data is '{input}'")
        try:
            output = input_temperature(input)
            print(f"Temperature is now {output}°C")
        except ValueError as e:
            print(f"Caught input_temperature error: {e}")
        finally:
            print()


def main() -> None:
    print("=== Garden Temperature ===\n")
    test_temperature()
    print("All tests completed - program didn't crash!")


if __name__ == "__main__":
    main()
