#!/usr/bin/env python3

import random


def main() -> None:
    print("=== Game Data Alchemist ===\n")

    PLAYERS = ['Alice', 'bob', 'Charlie', 'dylan', 'Emma',
               'Gregory', 'john', 'kevin', 'Liam']
    print(f"Initial list of players: {PLAYERS}")

    capitalized_players = [p.capitalize() for p in PLAYERS]
    print(f"New list with all names capitalized: {capitalized_players}")

    capitalize_players_only = [p for p in PLAYERS if p.istitle()]
    print(f"New list of capitalized names only: {capitalize_players_only}")
    print()

    scores = {p: random.randrange(1000) for p in capitalized_players}
    print(f"Score dict: {scores}")

    avg = sum(scores.values()) / len(scores)
    print(f"Score average is {avg:.2f}")

    high_scores = {k: v for k, v in scores.items() if v > avg}
    print(f"High scores: {high_scores}")


if __name__ == "__main__":
    main()
