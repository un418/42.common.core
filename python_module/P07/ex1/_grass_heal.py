from abc import abstractmethod

from ex0 import Creature
from ._capabilities import HealCapability


class HealingCreature(Creature, HealCapability):
    @abstractmethod
    def heal(self, target: Creature | None = None) -> str:
        ...


class Sproutling(HealingCreature):
    CREATURE_TYPE = "Grass"

    def attack(self) -> str:
        return f"{self.name} uses Vine Whip!"

    def heal(self, target: Creature | None = None) -> str:
        target_name = "itself" if target is None else target.name
        return f"{self.name} heals {target_name} for a small amount"


class Bloomelle(HealingCreature):
    CREATURE_TYPE = "Grass/Fairy"

    def attack(self) -> str:
        return f"{self.name} uses Petal Dance!"

    def heal(self, target: Creature | None = None) -> str:
        target_name = "itself" if target is None else target.name
        return f"{self.name} heals {target_name} and others for a large amount"
