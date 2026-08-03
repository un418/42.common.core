#!/usr/bin/env python3

from typing import Any
from abc import ABC, abstractmethod


def pascal_case_to_title(str: str) -> str:
    uppercase_alphabet = [chr(i) for i in range(ord('A'), ord('Z') + 1)]
    print(uppercase_alphabet)
    for letter in uppercase_alphabet:
        str = str.replace(letter, " " + letter)
    return str.strip()


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._queue: list[tuple[int, str]] = []
        self._counter: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        ...

    @abstractmethod
    def ingest(self, data: Any) -> None:
        ...

    def output(self) -> tuple[int, str]:
        return self._queue.pop(0)

    def __len__(self) -> int:
        return len(self._queue)

    def report_stats(self) -> str:
        remaining = len(self)
        processed = self._counter - remaining
        return (
            f"{pascal_case_to_title(type(self).__name__)}: "
            f"total {processed} items processed, "
            f"remaining {remaining} on processor"
        )


class NumericProcessor(DataProcessor):
    ERR_MSG = "Improper numeric data"

    def validate(self, data: Any) -> bool:
        if isinstance(data, list) and len(data) > 0:
            return all(self._is_valid(d) for d in data)
        return self._is_valid(data)

    def ingest(self, data: int | float | list[int] | list[int | float]
               ) -> None:
        if not self.validate(data):
            raise TypeError(self.ERR_MSG)
        items = data if isinstance(data, list) else [data]
        for item in items:
            self._queue.append((self._counter, str(item)))
            self._counter += 1

    @staticmethod
    def _is_valid(data: Any) -> bool:
        return (isinstance(data, (int, float))
                and not isinstance(data, bool))


class TextProcessor(DataProcessor):
    ERR_MSG = "Improper text data"

    def validate(self, data: Any) -> bool:
        if isinstance(data, list) and len(data) > 0:
            return all(self._is_valid(d) for d in data)
        return self._is_valid(data)

    def ingest(self, data: str | list[str]) -> None:
        if not self.validate(data):
            raise TypeError(self.ERR_MSG)
        items = data if isinstance(data, list) else [data]
        for item in items:
            self._queue.append((self._counter, str(item)))
            self._counter += 1

    @staticmethod
    def _is_valid(data: Any) -> bool:
        return isinstance(data, str)


class LogProcessor(DataProcessor):
    ERR_MSG = "Improper log data"

    def validate(self, data: Any) -> bool:
        if isinstance(data, list) and len(data) > 0:
            return all(self._is_valid(d) for d in data)
        return self._is_valid(data)

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        if not self.validate(data):
            raise TypeError(self.ERR_MSG)
        items = data if isinstance(data, list) else [data]
        for item in items:
            payload = f'{item["log_level"]}: {item["log_message"]}'
            self._queue.append((self._counter, payload))
            self._counter += 1

    @staticmethod
    def _is_valid(data: Any) -> bool:
        req_keys = {"log_level", "log_message"}
        return (
            isinstance(data, dict)
            and len(data) == 2
            and all(isinstance(k, str)
                    and isinstance(v, str)
                    for k, v in data.items())
            and not req_keys.difference(data.keys())
        )


class DataStream():

    def __init__(self) -> None:
        # dict will ensure unicity via keys
        self._procs: dict[str, DataProcessor] = {}

    def register_processor(self, proc: DataProcessor) -> None:
        if type(proc).__name__ in self._procs:
            raise ValueError("Error: DataProcessor type already register in this Datastream")
        self._procs[type(proc).__name__] = proc

    def process_stream(self, stream: list[Any]) -> None:
        for item in stream:
            validated = False
            for proc in self._procs.values():
                if proc.validate(item):
                    proc.ingest(item)
                    validated = True
                    break
            if not validated:
                print("DataStream error - Can't process element in stream: Hello world")

    def print_processors_stats(self) -> None:
        for proc in self._procs.values():
            print(proc.report_stats())


def main() -> None:
    print("=== Code Nexus - Data Stream ===\n")

    # Empty stream: no processor registered yet
    print("Initialize Data Stream...")
    ds0 = DataStream()
    ds0.print_processors_stats()
    print()

    # Only one processor: the rest of the stream must be rejected
    print("Registering Numeric Processor")
    np0 = NumericProcessor()
    ds0.register_processor(np0)
    print()

    batch: list[Any] = [
        "Hello world",
        [3.14, -1, 2.71],
        [{"log_level": "WARNING",
          "log_message": "Telnet access! Use ssh instead"},
         {"log_level": "INFO", "log_message": "User wil is connected"}],
        42,
        ["Hi", "five"],
    ]
    print(f"Send first batch of data on stream: {batch}")
    ds0.process_stream(batch)
    ds0.print_processors_stats()
    print()

    # Same batch, full routing: every element finds its processor
    print("Registering other data processors")
    tp0 = TextProcessor()
    lp0 = LogProcessor()
    ds0.register_processor(tp0)
    ds0.register_processor(lp0)
    print("Send the same batch again")
    ds0.process_stream(batch)
    ds0.print_processors_stats()
    print()

    # Consumption: total must not move, remaining must drop
    print("Consume some elements from the data processors: "
          "Numeric 3, Text 2, Log 1")
    for proc, nb in ((np0, 3), (tp0, 2), (lp0, 1)):
        for _ in range(nb):
            proc.output()
    ds0.print_processors_stats()


if __name__ == "__main__":
    main()
