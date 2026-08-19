from abc import ABC, abstractmethod
from typing import TypeGuard
from ex0 import Creature


class BattleStrategy(ABC):
    @abstractmethod
    def is_valid(self, creature: Creature) -> TypeGuard[Creature]:
        ...

    @abstractmethod
    def act(self, creature: Creature) -> None:
        ...


class StrategyError(Exception):
    """Exception raised for strategy/creature combination error."""

    def __init__(self, creature: Creature, stgy_name: str):
        self.message = (
            f"Invalid Creature '{creature.name}' for this {stgy_name} strategy"
            )
        super().__init__(self.message)
