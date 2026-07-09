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


def main() -> None:
    plants: list[Plant] = [
        Plant("Rose", 25.0, 30),
        Plant("Oak", 200.0, 365, 0.3),
        Plant("Cactus", 5.0, 90, 0.1),
        Plant("Sunflower", 80.0, 45, 0.5),
        Plant("Fern", 15.0, 120, 0.4)
    ]

    print("=== Plant Factory Output ===")
    for plant in plants:
        print("Created: ", end="")
        plant.show()


if __name__ == "__main__":
    main()
