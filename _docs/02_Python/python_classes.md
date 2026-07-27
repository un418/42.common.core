# Classes — anatomy & layout

> Naming judgment → [python_naming.md](python_naming.md) · PEP 8 mechanics → [python_idioms.md](python_idioms.md).
> Here = **how a class body is organized**, and the two axes people confuse.

---

## At a glance

```
class X:
    """docstring"""                 what it IS
    CONSTANTS / class attributes    ─────────────
    __init__ / dunders              how it is BORN
    public methods                  its INTERFACE   (what callers may call)
    _private helpers                its KITCHEN     (implementation detail)
```

| Axis | Question it answers | Expressed by |
| --- | --- | --- |
| **Binding** | does it need the instance? | `@staticmethod` / `@classmethod` / plain `def` |
| **Visibility** | may an outside caller call it? | the `_` name prefix — **nothing else** |

These two are **independent**. `_helper` as a `@staticmethod` is a perfectly
normal combination.

---

## Part A — Class body ordering

PEP 8 imposes no order. The convention below is near-universal, and it exists
for two concrete reasons.

**1 · Top-down reading.** A reader wants to know what the object *is made of*
(constants, state) before what it *does*. State first, behavior after.

**2 · Visual ambiguity.** A bare assignment wedged between two `def`s reads at
a glance as if it belonged to the previous method's body:

```python
class Parser:
    def __init__(self) -> None:
        self._depth = 0

    SEPARATOR = ","        # ✗ looks like a leftover line of __init__
                           #   (indentation is identical)
    def parse(self, line: str) -> list[str]:
        ...
```

```python
class Parser:
    SEPARATOR = ","        # ✓ unmistakably a class attribute

    def __init__(self) -> None:
        self._depth = 0

    def parse(self, line: str) -> list[str]:
        ...
```

**3 · Interface before implementation.** Public methods are the contract;
helpers are the means. Putting a helper *before* the methods that use it forces
the reader through the plumbing before they know what the class is for.

> **Test** → *Reading strictly top to bottom, do I ever meet a detail before
> the thing it serves?* If yes, the order is wrong.

## Part B — Visibility is only a convention

Python has no `private` keyword. Visibility is communicated by **naming only**.

| Name | Means | Enforced? |
| --- | --- | --- |
| `name` | public — part of the contract | — |
| `_name` | internal, may change without warning | ✗ purely conventional |
| `__name` | name-mangled to `_Class__name` | ✗ avoids *collisions*, not access |

`__name` is **not** "more private" — it exists to stop subclasses from
accidentally reusing the same attribute name. Reach for `_name` by default.

> ⚠️ Consistency is the whole point. Marking state `_queue` / `_counter` but
> leaving a helper public sends contradictory signals about where the boundary is.

## Part C — Binding: which `def` shape?

| Shape | First arg | Use when the method… |
| --- | --- | --- |
| `def m(self)` | instance | reads or mutates **instance** state |
| `@classmethod def m(cls)` | the class | needs the class (alt. constructors, subclass-aware) |
| `@staticmethod def m()` | none | uses **neither** — a pure function that belongs to the class *namespace* |

```python
class Temperature:
    SCALE = "celsius"                       # class attribute

    def __init__(self, value: float) -> None:
        self._value = value

    def warmer_than(self, other: float) -> bool:
        return self._value > other          # uses self  → instance method

    @classmethod
    def from_fahrenheit(cls, f: float) -> "Temperature":
        return cls((f - 32) / 1.8)          # uses cls   → classmethod

    @staticmethod
    def _is_finite(value: float) -> bool:
        return value == value               # uses neither → staticmethod
```

**Test** → *Does the body mention `self`?* No → it does not belong to the
instance; `@staticmethod` says so explicitly, and the reader stops looking for
hidden state.

> Taking `self` "just in case" is a lie about coupling: it tells every reader
> the result may depend on instance state when it cannot.
