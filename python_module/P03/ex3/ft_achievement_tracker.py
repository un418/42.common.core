#!/usr/bin/env python3

import random


class Player:
    def __init__(self, name: str,
                 achievements: set[str] | None = None) -> None:
        self.name = name
        self.achievements = achievements if achievements is not None else set()
        # Mutable default argument best practice


def gen_player_achievements(achievements_list: list[str]) -> set[str]:
    return set(random.sample(achievements_list, random.randint(4, 10)))


def main() -> None:
    print("=== Achievement Tracker System ===\n")

    achievements_list = [
        'Crafting Genius',
        'Strategist',
        'World Savior',
        'Speed Runner',
        'Survivor',
        'Master Explorer',
        'Treasure Hunter',
        'Unstoppable',
        'First Steps',
        'Collector Supreme',
        'Untouchable',
        'Sharp Mind',
        'Boss Slayer',
        'Hidden Path Finder'
        ]

    players = [
        Player("Alice"),
        Player("Bob"),
        Player("Charlie"),
        Player("Dylan"),
    ]

    for player in players:
        player.achievements = gen_player_achievements(achievements_list)
        print(f"Player {player.name}: {player.achievements}")
    print()

    distinct_ach: set[str] = set()
    for player in players:
        distinct_ach |= player.achievements
    print(f"All distinct achievements: {distinct_ach}\n")

    players_achievements = [p.achievements for p in players]
    commons = set.intersection(*players_achievements)
    print(f"Common achievements: {commons}\n")

    # difference b/w player and union.(others players)
    for player in players:
        others_players_ach = set.union(*[p.achievements for p in players
                                         if p is not player])
        unique = player.achievements - others_players_ach
        print(f"Only {player.name} has: {unique}")
    print()

    for player in players:
        missing = set(achievements_list) - player.achievements
        print(f"{player.name} is missing: {missing}")


if __name__ == "__main__":
    main()

"""
    # Building the list of achievement from the subject.
    # print("-- debug ach list--")
    # print(achievements_list)
    # print(gen_list_achievement())
    # print("diff:",
    #       set.difference(set(gen_list_achievement()),
    #                      set(achievements_list)))

def gen_list_achievement() -> list[str]:

    all_subject_output: list[set[str]] = [
        {'Crafting Genius', 'World Savior', 'Master Explorer',
         'Collector Supreme', 'Untouchable', 'Boss Slayer'},
        {'Crafting Genius', 'Strategist', 'World Savior',
         'Master Explorer', 'Unstoppable', 'Collector Supreme',
         'Untouchable'},
        {'Strategist', 'Speed Runner', 'Survivor', 'Master Explorer',
         'Treasure Hunter', 'First Steps', 'Collector Supreme',
         'Untouchable', 'Sharp Mind'},
        {'Strategist', 'Speed Runner', 'Unstoppable', 'Untouchable',
         'Boss Slayer'},
        {'Crafting Genius', 'Strategist', 'World Savior', 'Speed Runner',
         'Survivor', 'Master Explorer', 'Treasure Hunter', 'Unstoppable',
         'First Steps', 'Collector Supreme', 'Untouchable', 'Sharp Mind',
         'Boss Slayer'},
        {'Untouchable'},
        {'Survivor', 'Treasure Hunter', 'First Steps', 'Sharp Mind'},
        {'Strategist', 'Speed Runner', 'Survivor', 'Treasure Hunter',
         'Unstoppable', 'Hidden Path Finder', 'First Steps',
         'Sharp Mind'},
        {'Speed Runner', 'Survivor', 'Treasure Hunter',
         'Hidden Path Finder', 'First Steps', 'Sharp Mind',
         'Boss Slayer'},
        {'Crafting Genius', 'World Savior', 'Hidden Path Finder',
         'Unstoppable', 'Boss Slayer'},
        {'Crafting Genius', 'World Savior', 'Survivor', 'Master Explorer',
         'Treasure Hunter', 'Hidden Path Finder', 'First Steps',
         'Collector Supreme', 'Sharp Mind'}
    ]
    return list(set.union(*all_subject_output))
 """
