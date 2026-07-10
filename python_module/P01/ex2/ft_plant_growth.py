#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float, days: int) -> None:
        self.name = name
        self.height = height
        self.days = days

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.days} days old")

    def grow(self, amount: float) -> None:
        self.height = round(self.height + amount, 1)

    def age(self, days: int = 1) -> None:
        self.days += days


if __name__ == "__main__":
    print("=== Garden Plant Growth ===")
    rose = Plant("Rose", 25.0, 30)
    rose.show()
    base_height = rose.height
    for i in range(1, 8):
        print(f"=== Day {i} ===")
        rose.grow(0.8)
        rose.age()
        rose.show()
    print(f"Growth this week: {round(rose.height - base_height, 1)}cm")
