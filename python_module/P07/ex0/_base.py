from abc import ABC, abstractmethod


class Creature(ABC):
    def __init__(self, name: str | None = None) -> None:
        if name is None:
            name = type(self).__name__
        self.name = name

    def describe(self) -> str:
        return f"{self.name} is a {self.CREATURE_TYPE} type Creature"

    @property
    @abstractmethod
    def CREATURE_TYPE(self) -> str:
        ...

    @abstractmethod
    def attack(self) -> str:
        ...


class CreatureFactory(ABC):
    @abstractmethod
    def create_base(self, name: str | None = None) -> Creature:
        ...

    @abstractmethod
    def create_evolved(self, name: str | None = None) -> Creature:
        ...
