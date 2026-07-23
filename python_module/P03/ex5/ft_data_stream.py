#!/usr/bin/env python3

import typing
import random


def gen_event() -> typing.Generator[tuple[str, str], None, None]:
    names = ["alice", "bob", "charlie", "dylan", "maria", "ines"]
    actions = ["climb", "eat", "grab", "move", "release",
               "run", "sleep", "swim", "use", "code", "chill"]
    while True:
        yield (random.choice(names), random.choice(actions))


def consume_event(events: list[tuple[str, str]]
                  ) -> typing.Generator[tuple[str, str], None, None]:
    while events:
        rand_i = random.randrange(len(events))
        yield events.pop(rand_i)


def main() -> None:
    print("=== Game Data Stream Processor ===")
    for i in range(1000):
        name, action = next(gen_event())
        print(f"Event {i}: Player {name} did action {action}")
    events = []
    for i in range(10):
        events.append(next(gen_event()))
    print(f"Built list of 10 events: {events}")
    for event in consume_event(events):
        print(f"Got event from list: {event}")
        print(f"Remains in list: {events}")


if __name__ == "__main__":
    main()
