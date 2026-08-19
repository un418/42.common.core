#!/usr/bin/env python3

from ex0 import CreatureFactory, FlameFactory, AquaFactory


def test_factory(factory: CreatureFactory) -> None:
    try:
        base = factory.create_base()
        evo = factory.create_evolved()
        for creature in base, evo:
            print(creature.describe())
            print(creature.attack())
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


def battle(factory0: CreatureFactory, factory1: CreatureFactory) -> None:
    try:
        crea0 = factory0.create_base()
        crea1 = factory1.create_base()
        print(crea0.describe())
        print(" vs.")
        print(crea1.describe())
        print(" fight!")
        print(crea0.attack())
        print(crea1.attack())
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


def test_named_factory(factory: CreatureFactory) -> None:
    try:
        base = factory.create_base("BaseNamedCreature")
        evo = factory.create_evolved("EvoNamedCreature")
        for creature in base, evo:
            print(creature.describe())
            print(creature.attack())
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


if __name__ == "__main__":
    print("Testing factory")
    test_factory(FlameFactory())
    print()
    print("Testing factory")
    test_factory(AquaFactory())
    print()
    print("Testing battle")
    battle(FlameFactory(), AquaFactory())
    print()
    print("** Bonus - Testing named factory **")
    test_named_factory(FlameFactory())
    print()
