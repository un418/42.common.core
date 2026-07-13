#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self._height = 0.0
        self._age = 0

        self.set_height(height)
        self.set_age(age)

    def __str__(self) -> str:
        return f"{self.name}: {self._height:.1f}cm, {self._age} days old"

    def show(self) -> None:
        print(self)

    def grow(self, amount: float) -> None:
        self._height = round(self._height + amount, 1)

    def age(self, days: int = 1) -> None:
        self._age += days

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
                 age: int, color: str) -> None:
        super().__init__(name, height, age)
        self.color = color
        self._bloomed = False

    def __str__(self) -> str:
        return (f"{super().__str__()}\n"
                f" Color: {self.color}\n"
                f"{self.bloom_status()}")

    def bloom_status(self) -> str:
        if self._bloomed:
            return f" {self.name} is blooming beautifully!"
        return f" {self.name} has not bloomed yet"

    def bloom(self) -> None:
        self._bloomed = True


class Tree(Plant):
    def __init__(self, name: str, height: float,
                 age: int, trunk_diameter: float) -> None:
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter

    def __str__(self) -> str:
        return (f"{super().__str__()}\n"
                f" Trunk diameter: {self.trunk_diameter}cm")

    def produce_shade(self) -> None:
        print(f"Tree {self.name} now produces a shade of {self.get_height()}cm"
              f" long and {self.trunk_diameter}cm wide.")


class Vegetable(Plant):
    def __init__(self, name: str, height: float,
                 age: int,  harvest_season: str) -> None:
        super().__init__(name, height, age)
        self.harvest_season = harvest_season
        self._nutritional_value = 0.0

    def __str__(self) -> str:
        return (f"{super().__str__()}\n"
                f" Harvest season: {self.harvest_season}\n"
                f" Nutritional value: {self._nutritional_value:.0f}")

    def age(self, days: int = 1) -> None:
        super().age(days)
        self._nutritional_value += 0.5 * days

    def grow(self, amount: float) -> None:
        super().grow(amount)
        self._nutritional_value += 0.5


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
    tomato = Vegetable("Tomato", 5.0, 10, "April")
    tomato.show()
    print("[make tomato grow and age for 20 days]")
    for _ in range(20):
        tomato.age()
        tomato.grow(2.1)
    tomato.show()


if __name__ == "__main__":
    main()
