from ._base import Creature


class Aquabub(Creature):
    CREATURE_TYPE = "Water"

    def attack(self) -> str:
        return f"{self.name} uses Water Gun!"


class Torragon(Creature):
    CREATURE_TYPE = "Water"

    def attack(self) -> str:
        return f"{self.name} uses Hydro Pump!"
