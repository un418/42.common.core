# Python idioms & code philosophies

> The *judgment* layer of Python, as opposed to the *mechanics* layer.
> **Mechanism** = what the language can do (unpacking, comprehensions, `try/except`).
> **Idiom / philosophy** = when and why to use it. Idioms are trade-offs, not rules —
> for each one, know *when it applies* and *when it doesn't*: that's exactly what an
> evaluator probes to tell understanding from recitation.

---

## The PEPs to cite

A **PEP** (Python Enhancement Proposal) is the design document process of the
language — [peps.python.org](https://peps.python.org/). The ones behind this note:

| PEP | Title | What it defines |
| --- | --- | --- |
| [PEP 8](https://peps.python.org/pep-0008/) | Style Guide for Python Code | Layout, naming conventions, and the style flake8 enforces |
| [PEP 20](https://peps.python.org/pep-0020/) | The Zen of Python | 19 aphorisms — the philosophy behind all the rest |
| [PEP 257](https://peps.python.org/pep-0257/) | Docstring Conventions | How to write docstrings |
| [PEP 3132](https://peps.python.org/pep-3132/) | Extended Iterable Unpacking | The `first, *rest = values` starred form |
| [PEP 484](https://peps.python.org/pep-0484/) | Type Hints | The annotation system mypy checks |

---

## PEP 20 — The Zen of Python

Written by Tim Peters; displayed by the easter egg `import this` (whose own source
is deliberately ROT13-obfuscated — the module preaching readability is unreadable,
on purpose). Not a rulebook, a compass: it guides the call when several solutions
work. The most-quoted lines:

> - Beautiful is better than ugly.
> - **Explicit is better than implicit.**
> - Simple is better than complex.
> - **Readability counts.**
> - **Errors should never pass silently.**
> - There should be one — and preferably only one — obvious way to do it.
> - If the implementation is hard to explain, it's a bad idea.

Concrete mappings from module 03 work:

| Aphorism                          | Where it showed up                                                                                             |
| --------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| Errors should never pass silently | reprint the `ValueError` message instead of swallowing it; why `# type: ignore` is the worst mypy "fix"        |
| Explicit is better than implicit  | a 3-element tuple *literal* makes the length visible — to the reader and to mypy — where `tuple(gen)` hides it |
| Readability counts                | naming: no `str`/`lst`/`d1`, name the *content* not the *type*                                                 |
| Simple is better than complex     | restructure `try` blocks rather than sniffing exception message text                                           |

---

## EAFP vs LBYL — the error-handling philosophies

Both are official [Python glossary](https://docs.python.org/3/glossary.html) entries.

- **LBYL — "Look Before You Leap"**: check preconditions first, then act.
  `if len(parts) != 3: ...` — test, act only if safe.
- **EAFP — "Easier to Ask Forgiveness than Permission"**: act directly, handle the
  failure if it comes. `try: float(item) / except ValueError:`.

Side by side, on a dict lookup — same task, two philosophies:

```python
# LBYL — check first, then act
if "fertilizer" in tank:
    dose = tank["fertilizer"]

# EAFP — act, then catch the exact exception
try:
    dose = tank["fertilizer"]
except KeyError:
    ...
```

Python culture leans **EAFP**. Why:

1. **No double work** — the conversion *is* the validation; LBYL often re-implements
   the check the operation already performs.
2. **No race condition** — LBYL has a gap between test and action (classic: check a
   file exists, then open it — it can vanish in between). EAFP is atomic.
3. **Readable nominal path** — the happy path reads straight down; the exceptional
   case lives in the `except`.

When LBYL still wins: the check is trivial and cheap, the exception is ambiguous
(two failure modes raising the same type — e.g. unpacking *and* `float()` both raise
`ValueError`), or failure is the common case rather than the exception.

**Defense one-liner:**
> EAFP means the operation itself is the test: try it, catch the specific exception.
> I use it because the conversion already validates, and there's no test/act gap.
> LBYL is fine when the check is trivial — it's a trade-off, not a dogma.

---

## PEP 8 — naming, the part evaluators actually check

Section "Naming Conventions". The rules that matter daily (mechanics —
for the judgment layer: role vs. type, verb/noun contracts, compound-name
head placement, see [python_naming.md](python_naming.md)):

- Functions and variables: `snake_case`, lowercase — `calc_3D_dist` violates it
  (uppercase `D`); `calc_dist_3d` doesn't.
- **Never shadow builtins**: `str = input(...)` legally hides the `str` type for the
  whole scope — a later `str(...)` call would blow up. If a name really must clash,
  the convention is a trailing underscore (`str_`), but a real name is better
  (`user_input`, `raw`, `line`).
- Never single characters `l`, `O`, `I` (unreadable in some fonts).
- Name the **content**, not the type: `lst` says nothing; `parts`, `coords` do.
- Exception aliases: `except ValueError as e` — `e` is the universal convention.
- Short names (`p1`, `d1`) are defensible in *short scopes* (math-style parameters,
  a 10-line `main`); the cost of terse names grows with scope length.

---

## Other idioms in the "philosophy" category

- **Pythonic** — the umbrella adjective: code that uses the language's intended
  idioms instead of transliterating C/Java (e.g. `for item in lst` instead of
  indexing with a counter; unpacking instead of `[0]`/`[1]`/`[2]`).
- **Duck typing** — "if it quacks like a duck": rely on what an object *can do*
  (its methods), not what it *is* (its class). Why `for` works on lists, tuples,
  generators and files alike.
- **Sequence unpacking as an idiom** — `x, y, z = values` is the mechanism;
  *preferring it* over index access is the idiom (names + implicit length check for
  free). Extended form `first, *rest = values` is PEP 3132. The idiomatic swap
  `a, b = b, a` is the same mechanism.
- **`= None` rather than a mutable default** — a signature default is built once at
  definition time, so `def f(x=[])` shares one list across every call. Defaulting to
  `None` and building the object in the body is the idiom; the mechanics, the
  instance-sharing variant on `__init__` and the `_MISSING` sentinel are in
  [python_functions.md](../02_syntax_flow/python_functions.md#optional-parameters).
- Language-agnostic principles that live in the same drawer: **DRY** (Don't Repeat
  Yourself), **KISS** (Keep It Simple, Stupid), **YAGNI** (You Aren't Gonna Need
  It).

---

See also: [python_naming.md](python_naming.md) (naming, the judgment layer),
[python_module03_concepts.md](../../99_Projects/M2_Python_3_concepts.md) (module 03
exercise-by-exercise), [python_main_guard.md](../02_syntax_flow/python_main_guard.md) (the guard
pattern — itself a PEP 8-endorsed idiom), [python_custom_exceptions.md](../04_errors/python_custom_exceptions.md), [python_exception.md](../04_errors/python_exception.md).
