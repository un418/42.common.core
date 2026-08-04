#!/usr/bin/env python3

from typing import Any
from abc import ABC, abstractmethod


def pascal_to_title(pascal: str) -> str:
    title = ""
    for i in range(len(pascal)):
        if (
            pascal[i].isupper() and 0 < i
            and (pascal[i - 1].islower()
                 or (i < len(pascal) - 1 and pascal[i + 1].islower()))
        ):
            title += " " + pascal[i]
        else:
            title += pascal[i]
    return title


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
        processed = self._counter
        return (
            f"{pascal_to_title(type(self).__name__)}: "
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
            and req_keys == data.keys()
        )


class DataStream:

    def __init__(self) -> None:
        # dict will ensure unicity via keys
        self._procs: dict[str, DataProcessor] = {}

    def register_processor(self, proc: DataProcessor) -> None:
        proc_name = type(proc).__name__
        if proc_name in self._procs:
            raise ValueError(
                f"DataProcessor of type '{proc_name}' "
                "already registered in this DataStream"
            )
        self._procs[proc_name] = proc

    def process_stream(self, stream: list[Any]) -> None:
        for item in stream:
            for proc in self._procs.values():
                if proc.validate(item):
                    proc.ingest(item)
                    break
            else:
                print(
                    "DataStream error - Can't process element in stream: "
                    f"{item}"
                )

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")
        if not self._procs:
            print("No processor found, no data")
            return
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
    try:
        ds0.register_processor(np0)
    except ValueError as e:
        print(f"{type(e).__name__}: {e}")
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
    procs_2 = [tp0, lp0]
    for proc in procs_2:
        try:
            ds0.register_processor(proc)
        except ValueError as e:
            print(f"{type(e).__name__}: {e}")

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

    # Test error on duplicate processsors
    print("\n== Registering duplicate processors ==")
    tp1 = TextProcessor()
    try:
        ds0.register_processor(tp1)
    except ValueError as e:
        print(f"{type(e).__name__}: {e}")
    print()


if __name__ == "__main__":
    main()
