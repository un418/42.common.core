# Python Module 03 — Concepts Guide (Collections)

> Subject: *Data Quest — Mastering Python Collections* (`_subjects/en.python_mod03.subject.pdf`)
> Python ≥ 3.10, flake8 + mypy clean, graceful exception handling, **no file I/O**.

---

## 0. The big picture — "your data structure is your algorithm"

The foreword tells the Twitter story: code that was clean and correct became a
bottleneck because a **list** was used where a **hash-based structure** belonged.
`"is this already present?"` on a list scans every element (**O(n)**); on a
set/dict it's a hash lookup (**O(1)**). At scale, the container choice *is* the
performance decision.

### The four collections at a glance

| Type      | Ordered?             | Mutable?               | Duplicates?     | Access by             | Typical use                        |
| --------- | -------------------- | ---------------------- | --------------- | --------------------- | ---------------------------------- |
| **list**  | yes (insertion)      | yes                    | yes             | index `lst[0]`        | ordered, growable sequence         |
| **tuple** | yes (insertion)      | **no** (immutable)     | yes             | index `t[0]`          | fixed record — meaning by position |
| **set**   | **no** (hash order)  | yes                    | **no** (unique) | membership `x in s`   | uniqueness + set algebra           |
| **dict**  | yes (insertion, 3.7+) | yes                   | unique **keys** | key `d["k"]`          | key → value association            |

### Complexity you should be able to quote

| Operation                    | list  | tuple | set      | dict               |
| ---------------------------- | ----- | ----- | -------- | ------------------ |
| `x in c` (membership)        | O(n)  | O(n)  | **O(1)** | **O(1)** (on keys) |
| access by index/key          | O(1)  | O(1)  | —        | O(1)               |
| append / add / insert-at-key | O(1)* | —     | O(1)     | O(1)               |

\* amortized — a list occasionally reallocates a bigger internal array.

**Why are set/dict O(1)?** They are **hash tables**: `hash(element)` maps the
value to a slot, so lookup doesn't scan. Consequences: elements/keys must be
**hashable** (str, int, float, tuple — not list, set, dict), and iteration
order carries no meaning for sets.

**Hashable** = has a `hash()` value that never changes during its lifetime →
in practice: immutable objects. This is *the* link between the chapters:
tuples are hashable **because** they're immutable, which is why they can be
set elements or dict keys and lists cannot.

---

## 1. Ex0 — LISTS, discovered through `sys.argv`

### The concept

`sys.argv` is a **list of strings** the interpreter fills at startup — the
Python equivalent of C's `argv`, except there is no `argc`: you use
`len(sys.argv)`.

- `sys.argv[0]` is always the script name **as typed on the command line** —
  so the list is never empty (`Total arguments: 1` with no user args).
- User arguments start at index 1, and they are **always `str`**, even `"42"`.
- The **shell** splits arguments before Python sees them: quoting
  `"Data Quest"` produces **one** argument containing a space.

List operations at play: indexing (`lst[0]`, negative `lst[-1]`), `len()`,
iteration, and **slicing** (`lst[1:]` = new list from index 1 to the end).

### `import sys` — the one authorized import mechanism

`import sys` at the top of the file binds the module object to the name
`sys`; you then access its attribute `sys.argv`. Imports are covered in depth
in a later project — for now, know that this line *executes* the module once
and makes its namespace available.

### Understanding check — from the subject's own hint

**Q: "There are multiple ways to avoid printing the program name again with
the arguments — discuss alternate solutions."**
Be ready to name at least two distinct approaches: one based on *slicing* the
list, one based on *controlling the loop indices* (starting at 1 instead
of 0). Whatever you used, be able to defend why, and demo one alternative
live.

Careful with the tools you name here: ex0's authorized list is only
`import sys, sys.argv, len(), print()`. Builtins like `enumerate()` and
`range()` are **not** in it (`range()` only appears in ex5's list), and the
intro rule only unlocks an introduced *data structure and its class methods*
— indexing/slicing on the list are operations of the type, `enumerate`/
`range` are separate builtins. So the alternatives you present must be built
from indexing, slicing, and loop constructs (`for`/`while`) alone.

---

## 2. Ex1 — LISTS you build yourself + defensive input handling

### The concept

Two ideas combine here:

1. **Building a list incrementally** — start from `[]`, then `append()` valid
   items as you validate them. (Since lists are "properly introduced" from
   ex0, their methods are now allowed.)
2. **Graceful validation with try/except** — `int("abc")` raises
   `ValueError`; catching it *per argument* lets you discard invalid values
   with a message and keep going, instead of crashing.

The processing pipeline the subject asks for: *validate each argument →
collect the valid ones → if none remain, print usage → else compute stats*.

### The stats toolbox

| Stat    | Tool                                | Note                                                   |
| ------- | ----------------------------------- | ------------------------------------------------------ |
| count   | `len(scores)`                       |                                                        |
| total   | `sum(scores)`                       |                                                        |
| average | `sum(scores) / len(scores)`         | `/` **always returns float** → `1930.0` in the example |
| max/min | `max(scores)`, `min(scores)`        | authorized in this exercise                            |
| range   | `max - min`                         | one number, "spread" of the scores                     |

Printing a list directly (`print(scores)`) shows its `repr`:
`[1500, 2300, ...]` — that's exactly what the expected output uses.

### Defense points

- Why check *before* computing: `max([])` / `min([])` raise `ValueError`,
  and `sum([]) / len([])` divides by zero — the "no valid scores" branch must
  come first.
- Mixed input rule: invalid values are discarded **with a message each**, the
  rest is processed — only if *nothing* remains do you print the usage line.

---

## 3. Ex2 — TUPLES (immutable records)

### The concept

A **tuple** is an ordered, **immutable** sequence: once created, its contents
can never change ("written in stone"). Position carries meaning —
`(x, y, z)` — which makes tuples the natural type for coordinates.

```python
pos = (1.0, 2.5, 3.0)      # creation (parentheses optional: pos = 1.0, 2.5, 3.0)
pos[0]                     # indexing works like a list
x, y, z = pos              # unpacking: three variables in one statement
pos[0] = 9.9               # TypeError: 'tuple' object does not support item assignment
```

Traps worth knowing: a one-element tuple needs the comma — `(5,)`, not
`(5)` (that's just a parenthesized int).

### Why a tuple and not a list here? (classic defense question)

- **Fixed structure**: a 3D point *is* exactly three numbers; a container that
  can't grow/shrink states that in the type.
- **Immutability = safety**: no function can accidentally modify your
  position; to "move", you build a *new* tuple.
- **Hashable**: a tuple of floats can be a dict key or set element
  (`visited = {(0, 0, 0), ...}`) — a list can't.

### The input loop pattern

`get_player_pos()` must *ask → validate → retry until valid → return a
tuple*. Concepts involved:

- `input(prompt)` returns a **str**; you split it on `','` and convert each
  part with `float()`.
- Two distinct failure modes to distinguish (see the expected output): wrong
  *shape* (not three comma-separated parts → `Invalid syntax`) vs wrong
  *content* (`float("abc")` → `ValueError`, whose **original message** is
  reprinted: `could not convert string to float: 'abc'`).
- The example accepts `1.0 , 2.5, 3.0` — spaces around items are not an
  error. Useful fact: `float(" 2.5 ")` works — the conversion itself
  tolerates surrounding whitespace.
- The retry is a loop that only exits by `return` — the function *guarantees*
  its caller a valid tuple.

### Euclidean distance & `round()`

Distance between `(x1,y1,z1)` and `(x2,y2,z2)`:
`math.sqrt((x2-x1)**2 + (y2-y1)**2 + (z2-z1)**2)` — the 3D Pythagorean
theorem. Distance to center = same formula against `(0, 0, 0)`.

Output shows 4 decimals (`4.0311`) → `round(value, 4)`. Remember from
`python_floats.md`: `round()` uses banker's rounding (half to even) and
floats are binary — fine here, but say "floating-point display" not "exact".

---

## 4. Ex3 — SETS (uniqueness & set algebra)

### The concept

A **set** is an unordered collection of **unique**, hashable elements backed
by a hash table. Adding a duplicate is a silent no-op. There is **no
indexing** (`s[0]` → `TypeError`) because there is no order to index into.

```python
{"a", "b"}        # set literal
set()             # EMPTY set — see the trap below
"a" in s          # O(1) membership — the whole point
```

### The subject's explicit question — know this cold

**Q: "How does Python print an empty set, and why?"**
It prints `set()`, **not** `{}` — because the `{}` literal was already taken
by the **empty dict** (dicts existed before set literals). `repr` output must
be unambiguous and re-evaluable, so the empty set falls back to the
constructor form. (`{1, 2}` is a set literal; `{}` will always be a dict.)

### Set algebra — map each subject requirement to an operation

| Requirement                                | Operation                                  |
| ------------------------------------------ | ------------------------------------------ |
| unique achievements among all players      | **union** of all sets (`\|` / `.union()`)  |
| achievements shared by all players         | **intersection** (`&` / `.intersection()`) |
| achievements only player X has             | **difference**: X minus the union of everyone else (`-` / `.difference()`) |
| achievements X is missing                  | **difference**: full catalog minus X       |

Both the operator (`|`, `&`, `-`) and method (`union`, `intersection`,
`difference`) spellings exist; methods are what the authorized list names.
One nuance: operators require two sets, methods accept any iterable.

### Randomness (`random.*` is authorized)

`gen_player_achievements()` needs *a random count*, then *that many distinct
picks* from a fixed catalog. The `random` module has a function that samples
**without replacement** — the right fit for building a set of distinct
achievements; picking one-by-one with a replacement-style function would need
duplicate handling (which the set absorbs, but then the size isn't what you
asked). Know the difference between the sampling functions you considered.

The hint about tuning: with too few total achievements or too many picks per
player, "only X has" collapses to `set()` everywhere and "common to all"
explodes — pick numbers where all requested sets are *likely* non-empty.

### Defense nuances

- Set display order is arbitrary **and changes between runs** for strings:
  Python randomizes `str` hashing per process (security feature,
  `PYTHONHASHSEED`). Don't be surprised if your output ordering differs from
  the subject — that's expected and worth *saying* at defense.
- Elements must be hashable: a set of tuples works, a set of lists raises
  `TypeError: unhashable type: 'list'`.

Watch for the classic **mutable default argument** trap on constructors that
take a set/list/dict — see [python_idioms.md](python_idioms.md).

---

## 5. Ex4 — DICTIONARIES (key → value)

### The concept

A **dict** maps unique, hashable **keys** to arbitrary **values** — the
hash-table workhorse of Python. Since Python 3.7 dicts **preserve insertion
order** (a language guarantee, not an implementation detail) — this is what
makes "in case of a tie, choose the first from the command line" work
naturally if you insert in command-line order.

```python
inv = {}                    # start empty ("at the beginning of the game...")
inv["sword"] = 1            # insert / overwrite
"sword" in inv              # O(1) membership — ON KEYS
inv.keys(); inv.values()    # views over keys / values
inv.update({"magic": 1})    # merge another dict in
```

`dict.keys()` / `dict.values()` return **views**, not lists: live windows on
the dict (they see later changes). `list(inv.keys())` materializes a real
list — that's the "list of all items" step.

### Parsing `<item>:<quantity>` — three error classes

The expected output distinguishes three failures, each with its own message:

1. **Invalid syntax** — the parameter doesn't split into a name and a
   quantity (`hello`).
2. **Quantity error** — the quantity part isn't an int (`key:value` →
   `ValueError`, reprint its original message).
3. **Redundant item** — the key is *already in the dict* (`in` test) →
   discard the later one (`sword:2` loses to `sword:1`).

Quantities are stored as **int** so arithmetic works later.

### Computing the stats under the authorized list

- Total = `sum()` over the **values** view.
- Percentage per item = value / total × 100, `round(x, 1)` → `8.3`.
- Most/least abundant: `max()`/`min()` are **not** in this exercise's
  authorized list — you need a manual best-so-far scan. A strict `>` / `<`
  comparison while scanning in insertion order gives you the tie-break rule
  (first seen wins) for free. Be ready to explain that.
- Iterating a dict directly iterates its **keys** — combine with `inv[key]`
  to reach values (`.items()` isn't in the authorized list either).

---

## 6. Ex5 — GENERATORS (lazy streams)

### The concept

A **generator function** is a function containing `yield`. Calling it does
**not** run the body — it returns a **generator object**. Each `next()` call
resumes the body until the next `yield`, hands that value out, and **freezes
the function** (locals + position preserved) until the following `next()`.

```python
def countdown(n: int):
    while n > 0:
        yield n          # pause here, hand n out
        n -= 1           # resumes HERE on the next next()

g = countdown(3)         # nothing ran yet
next(g)                  # 3
next(g)                  # 2
```

When the function body returns, the generator raises **`StopIteration`** —
that's how iteration "ends". A `for x in gen` loop calls `next()` for you and
swallows `StopIteration` silently: that's why the subject says
`consume_event` "must be used directly in the `for .. in ..` construct".

### Why generators exist — the memory argument

A list of 1,000,000 events lives entirely in RAM before you process item 1.
A generator produces **one value on demand** and holds only its paused frame.
This is the ex5 tagline "how games handle millions of events without
crashing". Bonus fact: `range()` itself is lazy (a lazy sequence object, not
a generator, but same spirit).

### The two generators asked for

- **`gen_event()` — an *infinite* generator**: `while True: yield ...` with a
  random `(name, action)` tuple each time. It never raises `StopIteration`,
  so you must **not** exhaust it with a bare `for` over the generator — the
  subject has you pull exactly 1000 values (hence `next()` and `range()` in
  the authorized list).
- **`consume_event(events)` — a *finite*, destructive generator**: yields a
  randomly chosen element **removed from the list** each time, until the list
  is empty; then the body ends → `StopIteration` → the `for` loop terminates
  by itself.

### Aliasing — the concept hiding inside `consume_event`

The list you pass in is **not copied**: the generator mutates *the same
object* the caller still holds. That's why the expected output can print
"Remains in list: [...]" shrinking after each event — Python passes
**references** to objects, and both names point to one list. Classic defense
question territory (mutable default/shared state).

### Typing a generator (mypy)

The authorized `typing.Generator` takes three parameters:
`Generator[YieldType, SendType, ReturnType]` — for a simple generator that
only yields, the last two are `None`, e.g.
`Generator[tuple[str, str], None, None]`.

---

## 7. Ex6 — COMPREHENSIONS (the condensed form)

### The concept

A **comprehension** builds a collection from an iterable in a single
*expression*. It replaces the `[]`-plus-append loop, and comes in list, dict
**and set** flavors (the subject's hint: sets too).

```python
[expr(x) for x in iterable]              # MAP: transform every element
[x for x in iterable if cond(x)]         # FILTER: keep some elements
[expr(x) for x in iterable if cond(x)]   # both at once
{k_expr: v_expr for k in iterable}       # dict comprehension
{expr(x) for x in iterable}              # set comprehension
```

Reading order to say out loud: *"for each x in the iterable, if the
condition holds, produce the expression"* — the expression comes first in the
code but runs last.

### Mapping the four required comprehensions

| Subject requirement                       | Shape                                  |
| ----------------------------------------- | -------------------------------------- |
| all names capitalized                     | list comprehension, **map** form       |
| only the already-capitalized names        | list comprehension, **filter** form    |
| name → random score                       | **dict** comprehension over the names  |
| scores above average                      | **dict** comprehension, filter form    |

Concepts you'll need around them:

- `str.capitalize()` returns a **new** string (str is immutable), first
  letter upper, rest lower. "Is this name capitalized?" can be expressed by
  comparing a name with a transformed version of itself, or via the `str`
  "is-" test methods — str methods are globally allowed, pick one and be able
  to justify it.
- The average must be computed **before** the second dict comprehension —
  computing it inside the comprehension would redo the work per element (and
  reads badly). Compute once, then filter against it.
- Iterating the score dict in the filter comprehension: iterating a dict
  yields keys; you need key *and* value in the result. (Same
  authorized-list question as ex4 — the intro chapter says a structure's
  methods unlock once the structure is introduced; decide your reading and be
  consistent, it's a likely defense discussion.)

### Style rules from the subject

- **One comprehension = one line**, unless it exceeds the flake8 line limit
  (79 chars) — then break it. If a comprehension needs several logical steps
  or nesting to work, that's the signal to fall back to a plain loop:
  comprehensions are for *clarity*, not code golf.

---

## 8. Module-wide rules & traps

- **Python ≥ 3.10** — you can use `tuple[str, str]` style generics in hints
  (no `typing.Tuple` needed), but not 3.11+ features.
- **flake8 + mypy** on every file; **all functions need type hints**
  (including `-> None` for procedures, and the `Generator[...]` form for
  ex5).
- **Graceful exceptions**: nothing the user types may crash a script —
  `try/except` around every conversion of external input (`sys.argv`,
  `input()`). Catch the *specific* exception (`ValueError`), not bare
  `except`.
- **No file I/O** — everything comes from `sys.argv` or `input()`.
- **Authorized lists are per-exercise** — e.g. `max()`/`min()` allowed in
  ex1 but absent in ex4; `input()` only in ex2. Re-read the header of each
  exercise before coding. The intro adds: once an exercise introduces a data
  structure, that structure **and its class methods** are usable from then
  on; `str`, `int`, `float` and all their methods are always allowed.
- **The main guard** (`if __name__ == "__main__":`) and shebang habits from
  module 01 still apply — see `python_main_guard.md`.

---

## 9. Concept cheat-sheet (one-sentence definitions)

| Keyword            | One-sentence definition to say out loud                                                                                     |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------- |
| **LIST**           | Ordered, mutable, indexable sequence that allows duplicates — the general-purpose growable container.                        |
| **TUPLE**          | Ordered, **immutable** sequence — a fixed record where position carries meaning, hashable so usable as dict key/set element. |
| **SET**            | Unordered hash-based collection of unique elements — O(1) membership and set algebra (union/intersection/difference).        |
| **DICT**           | Hash-based mapping of unique hashable keys to values, preserving insertion order since Python 3.7.                           |
| **HASHABLE**       | Has a hash value that never changes (immutable in practice) — required for set elements and dict keys.                       |
| **GENERATOR**      | A function with `yield` that returns a paused, resumable iterator producing values one at a time, on demand.                 |
| **`yield`**        | Hands a value out and freezes the function (locals + position) until the next `next()` call.                                 |
| **StopIteration**  | The exception a finished generator raises; `for` loops catch it silently to end iteration.                                   |
| **LAZY EVALUATION**| Producing values only when requested instead of building everything upfront — constant memory for arbitrarily long streams.  |
| **COMPREHENSION**  | A single expression that builds a list/dict/set from an iterable, combining a transform (map) and an optional filter.        |
| **`sys.argv`**     | The list of command-line strings, program name at index 0 — Python's `argv`, with `len()` playing the role of `argc`.        |
| **ALIASING**       | Two names referencing the same object — mutations through one are visible through the other; passing a list passes a reference, not a copy. |
| **MUTABLE DEFAULT ARG** | A default value is built once at definition time; a mutable default (`set()`/`[]`/`{}`) is then shared across every call that omits it (see [python_idioms.md](python_idioms.md)). Fix: default to `None`, build fresh inside the body. |

---
