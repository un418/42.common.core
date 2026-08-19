from ._base import Creature, CreatureFactory
from ._flame import Flameling, Pyrodon
from ._aqua import Aquabub, Torragon


class FlameFactory(CreatureFactory):
    def create_base(self, name: str | None = None) -> Creature:
        return Flameling(name)

    def create_evolved(self, name: str | None = None) -> Creature:
        return Pyrodon(name)


class AquaFactory(CreatureFactory):
    def create_base(self, name: str | None = None) -> Creature:
        return Aquabub(name)

    def create_evolved(self, name: str | None = None) -> Creature:
        return Torragon(name)
