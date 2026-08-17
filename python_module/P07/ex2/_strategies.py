from ._base import BattleStrategy
from ex0 import Creature
from ex1 import TransformCapability, HealCapability


class NormalStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, Creature)

    def act(self, creature: Creature) -> None:
        if not isinstance(creature, Creature):
            raise TypeError(
                "Invalid Creature "
                f"'{type(self).__name__}' for this normal strategy")
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, TransformCapability)

    def act(self, creature: Creature) -> None:
        if not isinstance(creature, TransformCapability):
            raise TypeError(
                "Invalid Creature "
                f"'{type(self).__name__}' for this aggressive strategy")
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


class DefensiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, HealCapability)

    def act(self, creature: Creature) -> None:
        if not isinstance(creature, HealCapability):
            raise TypeError(
                "Invalid Creature"
                f"'{type(self).__name__}' for this defensive strategy")
        print(creature.attack())
        print(creature.heal())
