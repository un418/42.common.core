#!/usr/bin/env python3

from ex1 import HealingCreatureFactory, TransformCreatureFactory


def test_healing(factory: HealingCreatureFactory) -> None:
    try:
        base = factory.create_base()
        evo = factory.create_evolved()
        for label, creature in (" base:", base), (" evolved:", evo):
            print(label)
            print(creature.describe())
            print(creature.attack())
            print(creature.heal())
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


def test_transform(factory: TransformCreatureFactory) -> None:
    try:
        base = factory.create_base()
        evo = factory.create_evolved()
        for label, creature in (" base:", base), (" evolved:", evo):
            print(label)
            print(creature.describe())
            print(creature.attack())
            print(creature.transform())
            print(creature.attack())
            print(creature.revert())
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


def test_healing_target(factory: HealingCreatureFactory) -> None:
    try:
        healer = factory.create_base()
        target = factory.create_evolved("EvoTarget")
        label = " base with target:"
        print(label)
        print(healer.describe())
        print(healer.attack())
        print(healer.heal(target))
    except Exception as e:
        print(f"Error: {type(e).__name__} - {e}")


if __name__ == "__main__":
    print("Testing Creature with healing capability")
    test_healing(HealingCreatureFactory())
    print()
    print("Testing Creature with transform capability")
    test_transform(TransformCreatureFactory())
    print()
    print("** Bonus - Testing healing target  **")
    test_healing_target(HealingCreatureFactory())
