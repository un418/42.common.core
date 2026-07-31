# Truthiness — what `if obj:` really asks

> Branch *shapes* → [python_conditions.md](python_conditions.md) · writing dunders on your own classes → [python_classes.md](python_classes.md). Here = **how any object becomes `True` or `False`**.

---

## The lookup chain

`if obj:` never tests the object directly — Python calls `bool(obj)`, which tries two magic methods in order:

```
bool(obj)
   │
   ├── __bool__ defined? ──yes──▶ return it   (must return a real bool)
   │        │no
   ├── __len__ defined?  ──yes──▶ len(obj) != 0
   │        │no
   └────────────────────────────▶ True        (default: every object is truthy)
```

`list` defines **no** `__bool__`, only `__len__` — so `bool([])` is `len([]) == 0` → `False`.

```python
>>> [].__bool__
AttributeError: 'list' object has no attribute '__bool__'
>>> [].__len__()
0
```

## The falsy set

Everything not in this table is truthy.

| Category | Falsy values | Answered by |
| --- | --- | --- |
| Constants | `None`, `False` | special-cased |
| Numbers | `0`, `0.0`, `0j`, `Decimal(0)`, `Fraction(0)` | `__bool__` |
| Containers | `''`, `()`, `[]`, `{}`, `set()`, `range(0)` | `__len__` |

> ⚠️ Truthy despite looking empty: `[0]`, `[[]]`, `[""]`, `(0,)`, `" "`, `"0"`, `"False"` — a container holding *one falsy item* is still a container of length 1.

## Same context everywhere

The chain above fires identically in every boolean context — not just `if`:

```python
if obj: ...          while obj: ...        not obj
obj and other        obj or other          [x for x in xs if x]
any(xs)              all(xs)               filter(None, xs)
```

`and` / `or` return **an operand, not a bool**: `[] or "fallback"` → `"fallback"`, `[1] and []` → `[]`. Only `not` always yields a real bool.

## On your own classes

```python
class Stack:
    def __init__(self) -> None:
        self._items: list[int] = []

    def __len__(self) -> int:          # enough — bool() falls through to it
        return len(self._items)


class Account:
    def __init__(self, balance: float) -> None:
        self.balance = balance

    def __bool__(self) -> bool:        # wins over __len__ when both exist
        return self.balance > 0
```

Define **neither** and every instance is truthy forever — the classic trap: an object you think of as "empty" still passes `if obj:`.

| You want | Define |
| --- | --- |
| empty ⇔ falsy, and `len(obj)` makes sense | `__len__` |
| a truth value unrelated to a size | `__bool__` |
| both, disagreeing | `__bool__` — it takes priority |

> `__bool__` must return an actual `bool`; returning `0`/`1` raises `TypeError: __bool__ should return bool`.

## Truthiness ≠ equality

Two unrelated questions — don't route one through the other:

```python
[] == False          # False  — different types, list.__eq__ says no
bool([]) == False    # True
0 == False           # True   — bool subclasses int, False IS 0
```

Hence the idioms:

```python
if not items:        # ✓ "is it empty?"
if items == False:   # ✗ never true for a list — silent bug
if items is None:    # ✓ "was anything passed at all?"
```

`not items` and `items is None` are **not** interchangeable: the first lumps "no list" together with "empty list", the second separates them. Pick the one that matches the distinction you actually need — typically `is None` for an optional argument, `not` for a "do I have work to do?" test.

## Defense-day one-liner

> `if obj:` calls `bool(obj)`, which looks for `__bool__`, then falls back to `__len__ != 0`, then defaults to `True`. `list` has only `__len__`, so an empty list is falsy by virtue of its length — no comparison to `False` involved.

See also: [python_collections.md](../03_data_types/python_collections.md) for the containers themselves, [python_idioms.md](../05_style/python_idioms.md) for PEP 8 phrasing.
