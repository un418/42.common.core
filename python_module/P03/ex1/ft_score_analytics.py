#!/usr/bin/env python3

import sys


def score_parser(argv: list[str]) -> list[int]:
    score_list: list[int] = []
    for arg in argv[1:]:
        try:
            score_list.append(int(arg))
        except ValueError:
            print(f"Invalid parameter: '{arg}'")
    return score_list


def gen_report(lst: list[int]) -> str:
    return (f"Scores processed: {lst}\n"
            f"Total players: {len(lst)}\n"
            f"Total score: {sum(lst)}\n"
            f"Average score: {sum(lst) / len(lst)}\n"
            f"High score: {max(lst)}\n"
            f"Low score: {min(lst)}\n"
            f"Score range: {max(lst) - min(lst)}")


def main() -> None:
    print("=== Player Score Analytics ===")

    scores = score_parser(sys.argv)
    scores_len = len(scores)
    if scores_len == 0:
        print("No scores provided. "
              "Usage: python3 ft_score_analytics.py <score1> <score2> ...")
    else:
        print(gen_report(scores))


if __name__ == "__main__":
    main()
