#!/usr/bin/env python3

from ex0 import CreatureFactory, FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import BattleStrategy, StrategyError
from ex2 import NormalStrategy, AggressiveStrategy, DefensiveStrategy


def battle(opponents: list[tuple[CreatureFactory, BattleStrategy]]) -> None:
    try:
        print("*** Tournament ***")
        nb_oppo = len(opponents)
        print(f"{nb_oppo} opponents involved")
        for i, (factA, stratA) in enumerate(opponents):
            for factB, stratB in opponents[i + 1:]:
                playerA = factA.create_base()
                playerB = factB.create_base()
                print("\n* Battle *")
                print(playerA.describe())
                print(" vs.")
                print(playerB.describe())
                print(" now fight!")
                stratA.act(playerA)
                stratB.act(playerB)
    except (StrategyError, Exception) as e:
        # others exception to filter later
        print(f"Battle error, aborting tournament: {e}")


if __name__ == "__main__":
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()
    heal_factory = HealingCreatureFactory()
    trans_factory = TransformCreatureFactory()

    norm_strat = NormalStrategy()
    aggr_strat = AggressiveStrategy()
    def_strat = DefensiveStrategy()

    print("Tournament 0 (basic)")
    print("[ (Flameling+Normal), (Healing+Defensive) ]")
    t0 = [(flame_factory, norm_strat), (heal_factory, def_strat)]
    battle(t0)

    print("Tournament 1 (error)")
    print("(Flameling+Aggressive), (Healing+Defensive) ]")
    t1 = [(flame_factory, aggr_strat), (heal_factory, def_strat)]
    battle(t1)

    print("Tournament 2 (multiple)")
    print("[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ")
    t2 = [(aqua_factory, norm_strat),
          (heal_factory, def_strat),
          (trans_factory, aggr_strat)]
    battle(t2)
