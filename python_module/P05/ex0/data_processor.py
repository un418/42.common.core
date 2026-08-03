#!/usr/bin/env python3

from typing import Any
from abc import ABC, abstractmethod


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


def main() -> None:
    print("=== Code Nexus - Data Processor ===\n")

    print("Testing Numeric Processor...")
    np0 = NumericProcessor()
    # Validation
    for val_np in (42, 4.2, "Hello", True, [], [24, 2.4, "error"], [4, 2]):
        print(f" Trying to validate input '{val_np}': {np0.validate(val_np)}")
    # Ingestion error
    try:
        print(" Test invalid ingestion of 'foo' without prior validation:")
        np0.ingest("foo")
    except Exception as e:
        print(f" Got exception: {e}")
    # Ingestion OK
    np0_data = ([1, 2, 3, 4, 5], 42, 4.2, [24, 2.4])
    for np0_d in np0_data:
        try:
            print(f" Processing data: {np0_d}")
            np0.ingest(np0_d)
        except Exception as e:
            print(f" Got exception: {e}")
    # Extraction
    s = "" if len(np0) == 1 else "s"
    print(f" Extracting {len(np0)} value{s}...")
    while np0:
        item = np0.output()
        print(f" Numeric value {item[0]}: {item[1]}")
    print()

    print("Testing Text Processor...")
    tp0 = TextProcessor()
    # Validation
    for val_tp in (42, "Hello", [], ["ko", []]):
        print(f" Trying to validate input '{val_tp}': {tp0.validate(val_tp)}")
    # Ingestion error
    try:
        print(" Test invalid ingestion of '{\"not\": \"string\"}' "
              "without prior validation:")
        tp0.ingest({"not": "string"})
    except Exception as e:
        print(f" Got exception: {e}")
    # Ingestion OK
    tp0_data = (["Hello", "Nexus", "World"], "scalar")
    for tp0_d in tp0_data:
        try:
            print(f" Processing data: {tp0_d}")
            tp0.ingest(tp0_d)
        except Exception as e:
            print(f" Got exception: {e}")
    # Extraction
    s = "" if len(tp0) == 1 else "s"
    print(f" Extracting {len(tp0)} value{s}...")
    while tp0:
        item = tp0.output()
        print(f" Text value {item[0]}: {item[1]}")
    print()

    print("Testing Log Processor...")
    lp0 = LogProcessor()
    # Validation
    for val_lp in (
        "Hello", 42,
        {"log_level": "DEBUG", "log_message": "i'm a valid test"},
        {404: "ERROR", "log_message": "invalid test"},
        {},
        {"foo": "bar"},
        [{"42": 24.42}],
        ()
    ):
        print(f" Trying to validate input '{val_lp}': {lp0.validate(val_lp)}")
    # Ingestion error
    try:
        print(" Test invalid ingestion of '"
              '{"log_level": "ERROR", "log_message": 42}'
              "' without prior validation:"
              )
        lp0.ingest({"log_level": "ERROR", "log_message": 42})
    except Exception as e:
        print(f" Got exception: {e}")
    # Ingestion OK
    lp0_data = (
        [{"log_level": "NOTICE", "log_message": "Connection to server"},
         {"log_level": "ERROR", "log_message": "Unauthorized access!!"}],
        {"log_level": "INFO", "log_message": "Scalar input"}
    )
    for lp0_d in lp0_data:
        try:
            print(f" Processing data: {lp0_d}")
            lp0.ingest(lp0_d)
        except Exception as e:
            print(f" Got exception: {e}")
    # Extraction
    s = "" if len(lp0) == 1 else "s"
    print(f" Extracting {len(lp0)} value{s}...")
    while lp0:
        item = lp0.output()
        print(f" Log entry {item[0]}: {item[1]}")


if __name__ == "__main__":
    main()
