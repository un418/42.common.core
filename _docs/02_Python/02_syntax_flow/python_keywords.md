# Python keywords

The fundamental language keywords mentioned in the module subjects ("Python keywords
such as `class` and `def` are fundamental language keywords").

Source: `import keyword; keyword.kwlist` — **35 hard keywords** + **4 soft keywords**
(Python 3.14). Hard keywords are reserved: they can never be used as variable, function
or class names.

```python
import keyword
keyword.kwlist      # the 35 reserved keywords
keyword.softkwlist  # ['_', 'case', 'match', 'type']
```

## Full list

```text
False    None     True     and      as       assert   async    await
break    class    continue def      del      elif     else     except
finally  for      from     global   if       import   in       is
lambda   nonlocal not      or       pass     raise    return   try
while    with     yield
```

---

## Constants

| Keyword | Meaning |
|---------|---------|
| `True`  | Boolean true |
| `False` | Boolean false |
| `None`  | Absence of value (the return value of a function without `return`) |

**Pythonic:** compare to `None` with `is`, never `==`:

```python
if result is None:
    ...
```

## Boolean logic

| Keyword | Meaning |
|---------|---------|
| `and` | Logical AND (short-circuits) |
| `or`  | Logical OR (short-circuits) |
| `not` | Logical negation |
| `in`  | Membership test (also drives `for` loops) |
| `is`  | Identity test (same object, not same value) |

**Pythonic:** rely on truthiness instead of explicit comparisons:

```python
if items:            # not: if len(items) > 0
if not name:         # not: if name == ""
if key in my_dict:   # not: if key in my_dict.keys()
if 0 <= x < 10:      # chained comparison, not: x >= 0 and x < 10
```

See [python_collections.md](../03_data_types/python_collections.md) for what `in` actually tests on
a dict.

## Conditionals

| Keyword | Meaning |
|---------|---------|
| `if`   | Condition |
| `elif` | "else if" |
| `else` | Fallback branch (also used with loops and `try`) |

```python
status = "adult" if age >= 18 else "minor"   # conditional expression
```

## Loops

| Keyword | Meaning |
|---------|---------|
| `for`      | Iterate over any iterable (no index needed) |
| `while`    | Loop while a condition holds |
| `break`    | Exit the loop immediately |
| `continue` | Skip to the next iteration |
| `pass`     | Do nothing (placeholder for an empty block) |
| `else`     | On a loop: runs only if the loop finished **without** `break` |

**Pythonic:** iterate directly over items, never over indexes:

```python
for fruit in fruits:                  # not: for i in range(len(fruits))
for i, fruit in enumerate(fruits):    # when the index is really needed
for name, age in people.items():      # dict iteration

evens = [n for n in numbers if n % 2 == 0]   # comprehension: for + in + if
```

## Functions

| Keyword | Meaning |
|---------|---------|
| `def`      | Define a function (or method) |
| `return`   | Return a value (default: `None`) |
| `lambda`   | Small anonymous function (single expression) |
| `yield`    | Produce a value from a generator (function becomes lazy) |
| `global`   | Declare a name as module-level inside a function |
| `nonlocal` | Declare a name from the enclosing function scope |

```python
def count_up(limit: int):
    n = 0
    while n < limit:
        yield n          # generator: values produced one at a time
        n += 1

sorted(words, key=lambda w: len(w))  # lambda as a sort key
```

**Pythonic:** `global` is almost always a design smell — prefer parameters and
return values.

## Classes

| Keyword | Meaning |
|---------|---------|
| `class` | Define a class |

```python
class Plant:
    def __init__(self, name: str) -> None:
        self.name = name
```

## Imports

| Keyword | Meaning |
|---------|---------|
| `import` | Import a module |
| `from`   | Import specific names from a module (also `raise ... from ...` and `yield from`) |
| `as`     | Rename an import (also used by `with` and `except`) |

```python
import sys
from dataclasses import dataclass
import numpy as np
```

## Exceptions

| Keyword | Meaning |
|---------|---------|
| `try`     | Block where an exception may occur |
| `except`  | Handle a specific exception type |
| `finally` | Always runs (cleanup), exception or not |
| `raise`   | Throw an exception |
| `assert`  | Debug-time sanity check (raises `AssertionError`) |
| `else`    | On a `try`: runs only if **no** exception was raised |

```python
try:
    value = int(user_input)
except ValueError as exc:
    print(f"invalid input: {exc}")
else:
    print(value)
finally:
    print("done")
```

**Pythonic:** EAFP ("Easier to Ask Forgiveness than Permission") — try the operation
and catch the failure, rather than pre-checking every condition. Catch specific
exceptions, never a bare `except:`.

Full statement, including what `finally` guarantees that code placed after the
try/except does not: [[python_try_except_raise]].

## Context managers

| Keyword | Meaning |
|---------|---------|
| `with` | Acquire a resource and release it automatically, even on error |

```python
with open("garden.txt") as f:        # file is closed automatically
    data = f.read()
```

**Pythonic:** always open files with `with` — no manual `close()`, no leak on
exception.

## Async

| Keyword | Meaning |
|---------|---------|
| `async` | Define a coroutine (`async def`), async loop/context (`async for`, `async with`) |
| `await` | Suspend until an awaitable completes |

Only meaningful with an event loop (`asyncio`); not needed in the early modules.

## Deletion

| Keyword | Meaning |
|---------|---------|
| `del` | Unbind a name, or remove an item/slice (`del d[key]`, `del lst[0]`) |

---

## Soft keywords

Only keywords in their specific context — elsewhere they are valid identifiers.

| Keyword | Meaning |
|---------|---------|
| `match` / `case` | Structural pattern matching (Python ≥ 3.10) |
| `type` | Type alias statement, `type Vector = list[float]` (Python ≥ 3.12) |
| `_` | Wildcard in `case _:`; by convention, a throwaway variable |

```python
match command:
    case "help":
        show_help()
    case "quit" | "exit":
        sys.exit(0)
    case _:
        print("unknown command")

for _ in range(3):       # loop where the value is irrelevant
    print("ha")
```
