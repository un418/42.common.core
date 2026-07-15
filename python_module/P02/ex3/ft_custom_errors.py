#!/usr/bin/env python3

class GardenError(Exception):
    '''A basic error for garden problems'''

    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    '''For problems with plants'''

    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


class WaterError(GardenError):
    '''For problems with watering'''

    def __init__(self, message: str = "Unknown water error") -> None:
        super().__init__(message)


def test_custom_errors() -> None:

    print("Testing PlantError...")
    try:
        raise PlantError("The tomato plant is wilting!")
    except PlantError as e:
        print(f"Caught {e.__class__.__name__}: {e}")
    print()

    print("Testing WaterError...")
    try:
        raise WaterError("Not enough water in the tank!")
    except WaterError as e:
        print(f"Caught {e.__class__.__name__}: {e}")
    print()

    print("Testing catching all garden errors...")
    try:
        raise PlantError("The tomato plant is wilting!")
    except GardenError as e:
        print(f"Caught GardenError: {e}")
    try:
        raise WaterError("Not enough water in the tank!")
    except GardenError as e:
        print(f"Caught GardenError: {e}")
    print()


def main() -> None:
    print("=== Custom Garden Errors Demo ===\n")
    test_custom_errors()
    print("All custom error types work correctly!")

    """
    print("\n=== Custom Garden Errors - Test Default Message ===")
    for error_class in (GardenError, PlantError, WaterError):
        try:
            raise error_class
        except GardenError as e:
            print(e)
    """


if __name__ == "__main__":
    main()
