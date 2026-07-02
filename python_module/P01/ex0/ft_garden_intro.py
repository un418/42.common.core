#!/usr/bin/env python3

def garden_intro() -> None:
    plant: str = "Rose"
    height: int = 25
    age: int = 30

    print("=== Welcome to My Garden ===")
    print("Plant:", plant)
    print(f"Height: {height}cm")
    print("Age:", age, "days")
    print("")
    print("=== End of Program ===")


if __name__ == "__main__":
    garden_intro()
