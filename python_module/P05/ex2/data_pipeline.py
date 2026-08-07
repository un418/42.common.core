#!/usr/bin/env python3

from typing import Any, Protocol
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


class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...


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
            and req_keys == data.keys()
            and all(isinstance(v, str)
                    for v in data.values())
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

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for proc in self._procs.values():
            limit = min(nb, len(proc))
            if limit > 0:
                proc_outputs = []
                for _ in range(limit):
                    proc_outputs.append(proc.output())
                plugin.process_output(proc_outputs)


class CSVPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        print("CSV Output:")
        csv_body = ",".join([d[1] for d in data])
        print(csv_body)


class JSONPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        print("JSON Output:")
        json_body = ", ".join([f'"item_{d[0]}": "{d[1]}"' for d in data])
        print(f"{{{json_body}}}")


def main() -> None:
    print("=== Code Nexus - Data Pipeline ===\n")

    print("Initialize Data Stream...\n")
    ds0 = DataStream()
    ds0.print_processors_stats()
    print()

    print("Registering Processors")
    for proc in [NumericProcessor(), TextProcessor(), LogProcessor()]:
        try:
            ds0.register_processor(proc)
        except ValueError as e:
            print(f"{type(e).__name__}: {e}")
    print()

    batch1 = [
        "Hello world",
        [3.14, -1, 2.71],
        [{"log_level": "WARNING",
          "log_message": "Telnet access! Use ssh instead"},
         {"log_level": "INFO", "log_message": "User wil is connected"}],
        42,
        ["Hi", "five"],
    ]

    print(f"Send first batch of data on stream: {batch1}")
    print()

    ds0.process_stream(batch1)
    ds0.print_processors_stats()
    print()

    print("Send 3 processed data from each processor to a CSV plugin:")
    ds0.output_pipeline(3, CSVPlugin())
    print()
    ds0.print_processors_stats()
    print()

    batch2 = [
        21,
        ['I love AI', 'LLMs are wonderful', 'Stay healthy'],
        [
            {
                'log_level': 'ERROR',
                'log_message': '500 server crash'
            },
            {
                'log_level': 'NOTICE',
                'log_message': 'Certificate expires in 10 days'
            }
        ],
        [32, 42, 64, 84, 128, 168],
        'World hello'
    ]

    print(f"Send another batch of data: {batch2}")
    print()
    ds0.process_stream(batch2)
    ds0.print_processors_stats()
    print()

    print("Send 5 processed data from each processor to a JSON plugin:")
    ds0.output_pipeline(5, JSONPlugin())
    print()
    ds0.print_processors_stats()


if __name__ == "__main__":
    main()
