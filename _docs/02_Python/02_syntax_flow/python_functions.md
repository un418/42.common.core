# Functions

## Optional parameters

An "optional" parameter is one the caller may omit — i.e. one with a **default value** in the signature. Python has three levels of it, and picking the right one *is* the idiom.

### Signature anatomy

Every parameter kind, in the only order Python accepts:

```python
def f(pos_only, /, normal, normal_opt=1, *args, kw_only, kw_only_opt=2, **kwargs):
      └─────────┘   └────────────────────┘        └──────────────────────┘
       before /      either position or name        after * : name required
```

| Marker | Meaning |
| --- | --- |
| `/` | everything **before** it is positional-only (can't be passed by name) |
| `*` (bare) | everything **after** it is keyword-only (can't be passed by position) |
| `*args` | absorbs the extra positionals — also opens the keyword-only zone |
| `**kwargs` | absorbs the extra keywords, always last |

Default values are only allowed on parameters, never on `*args` / `**kwargs` (those default to `()` and `{}` on their own).

### 1. Plain default value

```python
def greet(name: str, greeting: str = "Hello") -> str:
    return f"{greeting}, {name}"
```

Use it when the default is **immutable**: `int`, `float`, `str`, `bool`, `tuple`, `frozenset`, `None`. Nothing can mutate it, so sharing it between calls is harmless.

PEP 8 note: no spaces around `=` for a default (`greeting="Hello"`)… **unless** the parameter is annotated, and then spaces are required (`greeting: str = "Hello"`). flake8 enforces both (E252 / E251).

### 2. The `None` sentinel — for everything mutable or computed

- https://docs.python-guide.org/writing/gotchas/#default-args

The default expression is evaluated **once, at definition time**, so a mutable default is shared by every call that omits it:

```python
def bad(items: list[int] = []) -> list[int]:            # ✗ one list for all calls
    items.append(1)
    return items

def good(items: list[int] | None = None) -> list[int]:  # ✓ fresh list each call
    if items is None:
        items = []
    items.append(1)
    return items
```

Same for anything that must be *re-evaluated* per call: `datetime.now()` in a signature freezes the import time forever.

| Default kind | Idiom |
| --- | --- |
| immutable (`0`, `""`, `None`, `()`) | write it directly in the signature |
| mutable (`[]`, `{}`, `set()`) | `= None`, rebuild in the body |
| computed at call time (`now()`, `uuid4()`) | `= None`, compute in the body |

`if items is None` and **not** `if not items`: an explicitly-passed empty list means "the caller gave me a list" and must be respected, not silently replaced.

#### On a method: the same trap becomes instance sharing

`__init__` is where it bites hardest — the shared object is not just reused across calls, it becomes shared *state* between objects that should be independent:

```python
class Player:
    def __init__(self, name: str, achievements: set[str] = set()):
        self.name = name
        self.achievements = achievements

p1 = Player("Alice")
p2 = Player("Bob")
p1.achievements.add("first_blood")
p2.achievements                     # {'first_blood'} — leaked from p1
p1.achievements is p2.achievements  # True — literally the same set
```

Same fix, in the body:

```python
def __init__(self, name: str, achievements: set[str] | None = None):
    self.name = name
    self.achievements = achievements if achievements is not None else set()
```

Same underlying mechanism as **aliasing** (two names, one object) — see [python_module03_concepts.md](../../99_Projects/M2_Python_3_concepts.md) ex5, where a generator mutates the caller's list in place instead of a copy.

### 3. Keyword-only parameters

A bare `*` in the signature forces every following argument to be passed **by name**:

```python
def connect(host: str, *, timeout: float = 5.0, retries: int = 3) -> None: ...

connect("localhost", timeout=1.0)   # ✓
connect("localhost", 1.0)           # ✗ TypeError: takes 1 positional argument
```

Rule of thumb: **two or more optional parameters → make them keyword-only.** It kills unreadable call sites like `f(x, None, None, True)`, and it lets you add or reorder options later without breaking any caller. Straight from the Zen: *explicit is better than implicit*.

### When `None` is a legitimate value

Rare, but then `None` can't double as "not given". The idiom is a private sentinel object — unique by identity, so no caller can ever pass it by accident:

```python
_MISSING = object()

def pop(key: str, default: object = _MISSING) -> object:
    ...
    if default is _MISSING:      # nothing was passed → error out
        raise KeyError(key)
    return default               # None passed on purpose → return None
```

This is exactly how `dict.pop()` distinguishes "no default" from "default is `None`".

### Anti-patterns

| ✗ Avoid | Why |
| --- | --- |
| `def f(x=[])`, `def f(x={})` | mutable state shared across calls |
| `**kwargs` used to fake optional params | no autocomplete, no type check, and a typo becomes a silent no-op instead of a `TypeError` — keep it for pure forwarding |
| 3+ boolean flags | make them keyword-only, or pass an enum / config object |
| `if x == None` | use `is None` — identity, not `__eq__` (see [python_conditions.md](python_conditions.md#related-is-vs----identity-vs-equality)) |
| a default that hides a required value | if there's no sensible default, make the parameter required |

### Typing note

`Optional[T]` (from `typing`) and `T | None` (PEP 604, Python ≥ 3.10) are strictly identical; `T | None` is the modern spelling. Careful: `Optional` means **"can be `None`"**, not **"has a default"** — the two are independent:

```python
def f(a: int | None, b: int = 0) -> None: ...
#      └ required, but may be None   └ optional, never None
```

mypy will not let you write `def f(x: list[int] = None)`: the annotation must become `list[int] | None` for the `None` default to type-check.

### Defense-day one-liner

> A default is evaluated once, at definition time — so a mutable default is shared by every call. The idiom is `= None` plus building the object in the body; and past one or two options, put them behind a bare `*` so they must be passed by name.

---

See also: [python_idioms.md](../05_style/python_idioms.md) (the mutable-default trap in depth), [python_conditions.md](python_conditions.md) (`is` vs `==`, guard clauses), [python_naming.md](../05_style/python_naming.md).
