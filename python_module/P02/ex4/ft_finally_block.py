#!/usr/bin/env python3

class GardenError(Exception):
    """A basic error for garden problems"""

    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    """For problems with plants"""

    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


def water_plant(plant_name: str) -> None:
    if plant_name == plant_name.capitalize():
        print(f"Watering {plant_name}: [OK]")
    else:
        raise PlantError(f"Invalid plant name to water: '{plant_name}'")


def test_watering_system() -> None:
    try:
        print("Testing valid plants...")
        print("Opening watering system")
        for plant in ("Tomato", "Lettuce", "Carrots"):
            water_plant(plant)
    except PlantError as e:
        print(f"Caught {e.__class__.__name__}: {e}")
        print(".. ending tests and returning to main")
        return
    finally:
        print("Closing watering system\n")

    try:
        print("Testing invalid plants...")
        print("Opening watering system")
        for plant in ("Tomato", "lettuce", "Carrots"):
            water_plant(plant)
    except PlantError as e:
        print(f"Caught {e.__class__.__name__}: {e}")
        print(".. ending tests and returning to main")
        return
    finally:
        print("Closing watering system\n")


def main() -> None:
    print("=== Garden Watering System ===\n")
    test_watering_system()
    print("Cleanup always happens, even with errors!")


if __name__ == "__main__":
    main()
