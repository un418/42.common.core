# Comprehensions & generator expressions

> Same syntax family, two very different behaviours: **build a collection now**
> vs **produce values on demand**. The brackets are what decide.

---

## The forms

| Form                         | Syntax                    | Returns     | Built in memory |
| ---------------------------- | ------------------------- | ----------- | --------------- |
| List comprehension           | `[x**2 for x in it]`      | `list`      | yes, entirely   |
| Set comprehension            | `{x**2 for x in it}`      | `set`       | yes, entirely   |
| Dict comprehension           | `{x: x**2 for x in it}`   | `dict`      | yes, entirely   |
| **Generator expression**     | `(x**2 for x in it)`      | `generator` | **no — lazy**   |
| *(tuple — no comprehension)* | `tuple(x**2 for x in it)` | `tuple`     | yes, entirely   |

```python
[x**2 for x in range(5)]        # [0, 1, 4, 9, 16]
{x**2 for x in range(5)}        # {0, 1, 4, 9, 16}
{x: x**2 for x in range(5)}     # {0: 0, 1: 1, 2: 4, 3: 9, 4: 16}
(x**2 for x in range(5))        # <generator object <genexpr> at 0x...>
tuple(x**2 for x in range(5))   # (0, 1, 4, 9, 16)
```

The last row is the odd one: there is **no tuple comprehension**, because
`( ... )` is already taken by the generator. A tuple is obtained by *wrapping*
a generator expression — `tuple()` consumes it and freezes the result. Same
mechanism as `list(...)`, `set(...)`, `sum(...)`: the genexp is the source, the
call decides the container.

---

## Anatomy

```
[  expression   for  item  in  iterable   if  condition  ]
   └─ what to      └─ the loop variable    └─ optional filter,
      produce         and its source          skips falsy cases
```

Read it in execution order: **`for` first, then `if`, then `expression`.**

```python
[n * 2 for n in numbers if n > 0]     # filter, then transform
```

The `if` **after** the `for` filters. A conditional **inside the expression**
(`if/else` ternary) transforms instead — it cannot skip items:

```python
[n if n > 0 else 0 for n in numbers]  # replaces, keeps every item
```

---

## Eager vs lazy — the real difference

| | Comprehension `[...]` | Generator expression `(...)` |
| --- | --- | --- |
| Evaluation | immediate (**eager**) | on demand (**lazy**) |
| Memory | O(n) — whole collection | O(1) — one value at a time |
| Reusable | yes, it's a real object | **no — consumed once** |
| `len()` / indexing | yes | no |
| Best for | you need the collection itself | you iterate once and throw away |

**The one-shot gotcha:**

```python
gen = (x for x in range(3))
list(gen)   # [0, 1, 2]
list(gen)   # []  <- exhausted, silently returns empty
```

A generator does not "reset". If a second pass is needed, either build a list
or rebuild the generator.

**Reach for a generator when:**

- feeding a one-pass consumer — `all()`, `any()`, `sum()`, `max()`, `min()`,
  `"".join(...)`, a `for` loop (no intermediate list built for nothing).
- the source is huge or infinite — a big file, a stream (constant memory).

**Anti-patterns — all rooted in "lazy + one-shot":**

- **Indexing / `len()`** it → `TypeError`, it's not a sequence.
- **Iterating it twice** → the second pass is silently empty.
- **Materialising then throwing away** — `list(x for x in it)` is just a worse
  `[x for x in it]`; skip the wrapper.
- **Storing it to use later** while the source keeps changing — the values are
  computed at consumption, not at creation (see below).

### What does it actually generate?

Not a list — **values, one at a time**. Exactly the values the equivalent list
comprehension would have stored, just never all present together. The generator
object is an *iterator*, not a container: no `len()`, no indexing, nothing to
look inside.

The yielded value can be of **any type** — whatever the expression produces:

```python
(x**2 for x in it)              # yields ints
({"id": x} for x in it)         # yields dicts   <- a generator OF dicts, fine
((x, x**2) for x in it)         # yields tuples
```

So "a generator of dicts" exists in that sense. What does **not** exist is a
generator that *is* a dict — a lazy stream of `key: value` pairs:

```python
(k: v for k, v in pairs)        # SyntaxError — one value per step, never a pair
```

A generator yields a single object per iteration. Key/value comes back only by
yielding 2-tuples, and turning them into a dict re-collapses everything into
memory anyway:

```python
dict((k, k**2) for k in range(3))   # {0: 0, 1: 1, 2: 4}
{k: k**2 for k in range(3)}         # identical — this IS the dict comprehension
```

| Question                             | Answer                                                      |
| ------------------------------------ | ----------------------------------------------------------- |
| A genexp returns a list?             | No — a `generator` object                                   |
| It can yield dicts / lists / tuples? | Yes, any type, it's just the expression                     |
| A "lazy dict" genexp exists?         | No — `(k: v for ...)` is a `SyntaxError`                    |
| Lazily build a dict then?            | `dict(pairs_genexp)` — but `dict()` consumes it all at once |

### If the source changes before the generator is consumed

A generator holds a **reference to the source object**, not a copy — so changes
made before consumption leak in. 
**In-place** mutation is seen; **rebinding** the name is not (the generator still points at the old object).

**Mutating while iterating** fails differently per container:

| Source         | On size change during iteration                                      |
| -------------- | -------------------------------------------------------------------- |
| `list`         | **silent** — index-based, a delete shifts items and one gets skipped |
| `dict` / `set` | **loud** — `RuntimeError: changed size during iteration`             |

The list case is the trap — no error, just a wrong result. 
**Rule: never mutatea collection while iterating it.** 
Need both? `list(gen)` it first, or iterate a copy.

---

## `all()` and `any()` — the natural consumers

Both take an **iterable** and return a `bool`, testing the *truthiness* of each element.
Both **short-circuit**: they stop at the first element that decides the answer.

| Function | Returns `True` when | Stops at first | Empty iterable |
| --- | --- | --- | --- |
| `all(it)` | **every** element is truthy | falsy element | `True` |
| `any(it)` | **at least one** is truthy | truthy element | `False` |

```python
all([True, True])          # True
all([True, False, True])   # False — stops at index 1, never reads index 2
all([])                    # True   <- "vacuously true", no counter-example exists

any([False, True])         # True  — stops at index 1
any([False, False])        # False
any([])                    # False  <- nothing found, because nothing was looked at
```

The empty cases are a classic trap: `all([])` being `True` means "no element
violates the rule". If an empty collection must be *rejected*, that has to be
an explicit, separate check.

**The idiomatic pairing** — a generator expression fed straight to `all()`:

```python
all(isinstance(item, (int, float)) for item in values)
```

This is why the generator form matters here: `all()` consumes one value at a
time and can bail out early, so building a whole intermediate list of booleans
with `[...]` would be pure waste.

### The `for` in there is not "a loop"

```python
result = True                        # manual: explicit loop, flag, break
for item in values:
    if not isinstance(item, (int, float)):
        result = False
        break

result = all(isinstance(item, (int, float)) for item in values)   # idiomatic
```

Both iterate. Only the first one *writes* the iteration: a flag to initialise,
a `break` to place, an inverted condition to get right. The comprehension form
delegates all three.

**Syntax detail** — when a generator expression is the *sole* argument of a
call, its parentheses are redundant:

```python
all((isinstance(x, int) for x in values))   # extra pair, needless
all(isinstance(x, int) for x in values)     # same thing, cleaner
sorted((x for x in values), reverse=True)   # here they ARE required — 2 arguments
```

---

## Multiple `for` clauses

Clauses read **left to right, outer to inner** — the same order as nested loops:

```python
[(x, y) for x in "ab" for y in (1, 2)]   # [('a',1), ('a',2), ('b',1), ('b',2)]

# equivalent to:
for x in "ab":
    for y in (1, 2):
        ...
```

Do not confuse with **nested comprehensions**, where a comprehension is the
*expression*:

```python
[[y for y in row] for row in matrix]     # produces a list of lists
```

---

## When *not* to use one

- The body needs a statement (`try`, assignment, `print`) — a comprehension
  holds an **expression** only.
- More than one `for` plus an `if` on a single line: readability wins, write
  the loop.
- The result is discarded — a comprehension whose only purpose is a side effect
  builds a list of `None` for nothing. Use a plain `for`.

---

## Aside: `isinstance` at runtime

Frequent companion of `all()`, with three facts worth knowing:

```python
isinstance(x, (int, float))    # OK — a tuple of types means "any of these"
isinstance(x, list[int])       # TypeError — parameterised generics are for
                               # static typing only, never runtime checks
isinstance(True, int)          # True — bool IS a subclass of int
```

Consequence of the second point: checking "a list of ints" is necessarily a
**two-step** job — is it a list, then does every element qualify. That second
step is exactly the `all()` + generator expression pattern above.

---

See also: [python_collections.md](python_collections.md) (list/tuple/dict/set),
[python_idioms.md](../05_style/python_idioms.md) (why "pythonic" favours these forms),
[python_keywords.md](../02_syntax_flow/python_keywords.md) (`in`, `for`).
