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


class Flower(Plant):
    def __init__(self, name: str, height: float,
                 age: int, color: str,
                 grow_factor: float = 0.8) -> None:
        super().__init__(name, height, age, grow_factor)
        self.color = color
        self._bloomed = False

    def show(self) -> None:
        super().show()
        print(f" Color: {self.color}")
        self.print_bloom()

    def print_bloom(self) -> None:
        if self._bloomed:
            print(f" {self.name} is blooming beautifully!")
        else:
            print(f" {self.name} has not bloomed yet")

    def bloom(self) -> None:
        self._bloomed = True


class Tree(Plant):
    def __init__(self, name: str, height: float,
                 age: int,  trunk_diameter: float,
                 grow_factor: float = 0.8) -> None:
        super().__init__(name, height, age, grow_factor)
        self.trunk_diameter = trunk_diameter

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self.trunk_diameter}cm")

    def produce_shade(self) -> None:
        print(f"Tree {self.name} now produces a shade of {self.get_height()}cm"
              f" long and {self.trunk_diameter}cm wide.")


class Vegetable(Plant):
    def __init__(self, name: str, height: float,
                 age: int,  harvest_season: str,
                 grow_factor: float = 0.8) -> None:
        super().__init__(name, height, age, grow_factor)
        self.harvest_season = harvest_season
        self.nutritional_value = 0.0

    def show(self) -> None:
        super().show()
        print(f" Harvest season: {self.harvest_season}")
        print(f" Nutritional value: {self.nutritional_value:.0f}")

    def age(self) -> None:
        super().age()
        self.nutritional_value += 0.5

    def grow(self) -> None:
        super().grow()
        self.nutritional_value += 0.5


def main() -> None:
    print("=== Garden Plant Types ===")

    print("=== Flower")
    rose = Flower("Rose", 15.0, 10, "red")
    rose.show()
    print("[asking the rose to bloom]")
    rose.bloom()
    rose.show()
    print()

    print("=== Tree")
    oak = Tree("Oak", 200.0, 365, 5.0)
    oak.show()
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    print()

    print("=== Vegetable")
    tomato = Vegetable("Tomato", 5.0, 10, "April", grow_factor=2.1)
    tomato.show()
    print("[make tomato grow and age for 20 days]")
    for _ in range(20):
        tomato.age()
        tomato.grow()
    tomato.show()


if __name__ == "__main__":
    main()
