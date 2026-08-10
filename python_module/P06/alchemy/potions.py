from .elements import create_earth, create_air
from elements import create_fire, create_water


def healing_potion() -> str:
    return ("Healing potion brewed with "
            f"'{create_earth()}' and '{create_air()}'")


def strength_potion() -> str:
    return ("Strength potion brewed with "
            f"'{create_fire()}' and '{create_water()}'")


def main() -> None:
    print(healing_potion())
    print(strength_potion())


if __name__ == "__main__":
    main()

    # Error of import if we run the file directly
    # cwd = .../P06 - py alchemy/potions.py
    #   -> ImportError: attempted relative import with no known parent package
    # cwd = .../P06/alchemy - py potions.py
    #   -> ImportError: attempted relative import with no known parent package
    # cwd = .../P06/alchemy - py -m potions
    #   -> ImportError: attempted relative import with no known parent package

    # Work only with python -m
    # cwd = .../P06 - py -m alchemy.potions
    # Works because -m from the root is able to detect the package alchemy
    #   and make the relative import works
