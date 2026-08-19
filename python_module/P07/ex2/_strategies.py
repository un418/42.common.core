from typing import TypeGuard

from ._base import BattleStrategy, StrategyError
from ex0 import Creature
from ex1 import TransformCreature, HealingCreature


class NormalStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> TypeGuard[Creature]:
        return isinstance(creature, Creature)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise StrategyError(creature, "normal")
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> TypeGuard[TransformCreature]:
        return isinstance(creature, TransformCreature)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise StrategyError(creature, "aggressive")
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


class DefensiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> TypeGuard[HealingCreature]:
        return isinstance(creature, HealingCreature)

    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise StrategyError(creature, "defensive")
        print(creature.attack())
        print(creature.heal())
