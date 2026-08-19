from ex0 import CreatureFactory
from ._grass_heal import HealingCreature, Sproutling, Bloomelle
from ._normal_transform import TransformCreature, Shiftling, Morphagon


class HealingCreatureFactory(CreatureFactory):
    def create_base(self, name: str | None = None) -> HealingCreature:
        return Sproutling(name)

    def create_evolved(self, name: str | None = None) -> HealingCreature:
        return Bloomelle(name)


class TransformCreatureFactory(CreatureFactory):
    def create_base(self, name: str | None = None) -> TransformCreature:
        return Shiftling(name)

    def create_evolved(self, name: str | None = None) -> TransformCreature:
        return Morphagon(name)
