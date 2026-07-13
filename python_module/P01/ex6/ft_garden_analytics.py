#!/usr/bin/env python3

class Plant:
    class Statistics:
        def __init__(self) -> None:
            self._count = {
                "grow": 0,
                "age": 0,
                "show": 0
            }

        def record(self, key: str) -> None:
            self._count[key] += 1

        def get(self, key: str) -> int:
            return self._count[key]

        def report(self) -> None:
            print(f"Stats: {self._count['grow']} grow,"
                  f" {self._count['age']} age, "
                  f"{self._count['show']} show")

    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self._height = 0.0
        self._age = 0

        self.set_height(height)
        self.set_age(age)
        self._stats = self.Statistics()

    def __str__(self) -> str:
        return f"{self.name}: {self._height:.1f}cm, {self._age} days old"

    def show(self) -> None:
        print(self)
        self._stats.record("show")

    def grow(self, amount: float) -> None:
        self._height = round(self._height + amount, 1)
        self._stats.record("grow")

    def age(self, days: int = 1) -> None:
        self._age += days
        self._stats.record("age")

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

    def get_stats(self) -> Statistics:
        return self._stats

    @staticmethod
    def is_older_1y(days: int) -> bool:
        return days > 365

    @classmethod
    def anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0.0, 0)


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
        self._stats.record("shade")

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

    def __str__(self) -> str:
        return (f"{super().__str__()}\n"
                f" Seeds: {self._seed}")


def print_stats(plant: Plant) -> None:
    plant.get_stats().report()


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
