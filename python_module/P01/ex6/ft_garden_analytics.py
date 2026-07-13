#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self._height = 0.0
        self._age = 0

        self.set_height(height)
        self.set_age(age)
        self.stats = self.Statistics()

    def show(self) -> None:
        print(f"{self.name}: {self._height:.1f}cm, {self._age} days old")
        self.stats._count["show"] += 1

    def grow(self, amount: float) -> None:
        self._height = round(self._height + amount, 1)
        self.stats._count["grow"] += 1

    def age(self, days: int = 1) -> None:
        self._age += days
        self.stats._count["age"] += 1

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

    @staticmethod
    def is_older_1y(days: int) -> bool:
        return days > 365


    @classmethod
    # mypy forward reference -PEP484
    def anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0.0, 0)

    class Statistics:
        def __init__(self) -> None:
            self._count = {
                "grow": 0,
                "age": 0,
                "show": 0
            }

        def report(self) -> None:
            print(f"Stats: {self._count['grow']} grow,"
                  f" {self._count['age']} age, "
                  f"{self._count['show']} show")


class Flower(Plant):
    def __init__(self, name: str, height: float,
                 age: int, color: str) -> None:
        super().__init__(name, height, age)
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
                 age: int, trunk_diameter: float) -> None:
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self.trunk_diameter}cm")

    def produce_shade(self) -> None:
        print(f"Tree {self.name} now produces a shade of {self.get_height()}cm"
              f" long and {self.trunk_diameter}cm wide.")
        self.stats._count["shade"] += 1

    class Statistics(Plant.Statistics):
        def __init__(self) -> None:
            super().__init__()
            self._count["shade"] = 0

        def report(self) -> None:
            super().report()
            print(f" {self._count['shade']} shade")


class Seed(Flower):
    def __init__(self, name: str, height: float, age: int, color: str) -> None:
        super().__init__(name, height, age, color)
        self._seed = 0

    def bloom(self) -> None:
        super().bloom()
        self._seed = round((self.get_age() + self.get_height()) * 0.24)

    def show(self) -> None:
        super().show()
        print(f" Seeds: {self._seed}")


def print_stats(plant: Plant) -> None:
    plant.stats.report()


def main() -> None:
    print("=== Garden statistics ===")
    print("=== Check year-old")
    print("Is 30 days more than a year? ->", Plant.is_older_1y(30))
    print("Is 400 days more than a year? ->", Plant.is_older_1y(400))
    print()

    print("=== Flower")
    rose = Flower("Rose", 15.0, 10, "red")
    rose.show()
    print("[statistics for Rose]")
    print_stats(rose)
    print("[asking the rose to grow and bloom]")
    rose.grow(8.0)
    rose.bloom()
    rose.show()
    print("[statistics for Rose]")
    print_stats(rose)
    print()

    print("=== Tree")
    oak = Tree("Oak", 200.0, 365, 5.0)
    oak.show()
    print("[statistics for Oak]")
    print_stats(oak)
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    print("[statistics for Oak]")
    print_stats(oak)
    print()

    print("=== Seed")
    sunflower = Seed("Sunflower", 80.0, 45, "yellow")
    sunflower.show()
    print("[make sunflower grow, age and bloom]")
    sunflower.grow(30.0)
    sunflower.age(20)
    sunflower.bloom()
    sunflower.show()
    print("[statistics for Sunflower]")
    print_stats(sunflower)
    print()

    print("=== Anonymous")
    anon = Plant.anonymous()
    anon.show()
    print("[statistics for Unknown plant]")
    print_stats(anon)


if __name__ == "__main__":
    main()
