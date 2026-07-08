#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float,
                 days: int, grow_factor: float = 0.8) -> None:
        self.name = name
        self.height = height
        self.days = days
        self.grow_factor = grow_factor

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.days} days old")

    def grow(self) -> None:
        self.height = round(self.height + self.grow_factor, 1)

    def age(self) -> None:
        self.days += 1


if __name__ == "__main__":
    print("=== Garden Plant Growth ===")
    rose = Plant("Rose", 25.0, 30)
    # sunflower = Plant("Sunflower", 80.0, 45, 0.5)
    # cactus = Plant("Cactus", 15.0, 120, 0.1)
    rose.show()
    base_height = rose.height
    for i in range(1, 8):
        print(f"=== Day {i} ===")
        rose.grow()
        rose.age()
        rose.show()
    print(f"Growth this week: {round(rose.height - base_height, 1)}cm")
