from ex0 import CreatureFactory
from ._grass_heal import HealingCreature, Sproutling, Bloomelle
from ._normal_transform import TransformCreature, Shiftling, Morphagon


class HealingCreatureFactory(CreatureFactory):
    def create_base(self) -> HealingCreature:
        return Sproutling()

    def create_evolved(self) -> HealingCreature:
        return Bloomelle()


class TransformCreatureFactory(CreatureFactory):
    def create_base(self) -> TransformCreature:
        return Shiftling()

    def create_evolved(self) -> TransformCreature:
        return Morphagon()
