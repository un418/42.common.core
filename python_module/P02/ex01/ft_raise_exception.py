#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    temp = int(temp_str)
    if temp < 0:
        raise ValueError(f"{temp}°C is too cold for plants (min 0°C)")
    elif temp > 40:
        raise ValueError(f"{temp}°C is too hot for plants (max 40°C)")
    else:
        return temp


def test_temperature() -> None:
    data = ["25", "abc", "100", "-50"]

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
