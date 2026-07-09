#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float,
                 age: int, grow_factor: float = 0.8) -> None:
        self.name = name
        self._height = 0.0
        self._age = 0
        self.grow_factor = grow_factor

        self.set_height(height)
        self.set_age(age)

    def show(self) -> None:
        print(f"{self.name}: {self._height:.1f}cm, {self._age} days old")

    def grow(self) -> None:
        self._height = round(self._height + self.grow_factor, 1)

    def age(self) -> None:
        self._age += 1

    def get_height(self) -> float:
        return self._height

    def set_height(self, height: float) -> bool:
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            return False
        else:
            self._height = height
            return True

    def get_age(self) -> int:
        return self._age

    def set_age(self, age: int) -> bool:
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            return False
        else:
            self._age = age
            return True


def update_plant_height(plant: Plant, height: float) -> None:
    if plant.set_height(height):
        print(f"Height updated: {plant.get_height()}cm")
    else:
        print("Height update rejected")


def update_plant_age(plant: Plant, age: int) -> None:
    if plant.set_age(age):
        print(f"Age updated: {plant.get_age()} days")
    else:
        print("Age update rejected")


def main() -> None:
    print("=== Garden Security System ===")
    # intstantiate & init rose Plant
    rose = Plant("Rose", 15.0, 10)
    # rose = Plant("Rose", -1, -2) # invalid value create obj with def val
    print("Plant created: ", end="")
    rose.show()
    print()

    update_plant_height(rose, 25)
    update_plant_age(rose, 30)
    print()

    update_plant_height(rose, -1)
    update_plant_age(rose, -99)
    print()

    # Protected attributes are just a naming convention,
    # they only trigger a linter alert in best case ...
    # rose._height = -1
    # rose._age = -1

    print("Current state: ", end="")
    rose.show()


if __name__ == "__main__":
    main()
