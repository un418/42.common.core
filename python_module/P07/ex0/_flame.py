from ._base import Creature


class Flameling(Creature):
    CREATURE_TYPE = "Fire"

    def attack(self) -> str:
        return f"{self.name} uses Ember!"


class Pyrodon(Creature):
    CREATURE_TYPE = "Fire/Flying"

    def attack(self) -> str:
        return f"{self.name} uses Flamethrower!"
