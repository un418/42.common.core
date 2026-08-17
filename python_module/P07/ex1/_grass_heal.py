from ex0 import Creature
from ._capabilities import HealCapability


class HealingCreature(Creature, HealCapability):
    ...


class Sproutling(HealingCreature):
    CREATURE_TYPE = "Grass"

    def attack(self) -> str:
        return f"{self.name} uses Vine Whip!"

    def heal(self) -> str:
        return f"{self.name} heals itself for a small amount"


class Bloomelle(HealingCreature):
    CREATURE_TYPE = "Grass/Fairy"

    def attack(self) -> str:
        return f"{self.name} uses Petal Dance!"

    def heal(self) -> str:
        return f"{self.name} heals itself and others for a large amount"
