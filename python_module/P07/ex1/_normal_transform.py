from ex0 import Creature
from ._capabilities import TransformCapability


class TransformCreature(Creature, TransformCapability):
    ...


class Shiftling(TransformCreature):
    CREATURE_TYPE = "Normal"

    def transform(self) -> str:
        self._transform_state = True
        return f"{self.name} shifts into a sharper form!"

    def revert(self) -> str:
        self._transform_state = False
        return f"{self.name} returns to normal."

    def attack(self) -> str:
        if self._transform_state:
            return f"{self.name} performs a boosted strike!"
        return f"{self.name} attacks normally."


class Morphagon(TransformCreature):
    CREATURE_TYPE = "Normal/Dragon"

    def transform(self) -> str:
        self._transform_state = True
        return f"{self.name} morphs into a dragonic battle form!"

    def revert(self) -> str:
        self._transform_state = False
        return f"{self.name} stabilizes its form."

    def attack(self) -> str:
        if self._transform_state:
            return f"{self.name} unleashes a devastating morph strike!"
        return f"{self.name} attacks normally."
