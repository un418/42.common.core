# Collections: list, tuple, dict, set

## Lists

> To write.

## Tuples

> To write.

## Dictionaries

### `in` tests keys only, never values

```python
d = {"a": 1, "b": 2}
"a" in d   # True  — "a" is a key
1 in d     # False — 1 is a value, not a key
```

To test values explicitly: `1 in d.values()`. To test both: `1 in d or 1 in d.values()`
(the first half is redundant with `in d.keys()`, since `in d` already means that).

Not just a syntax distinction — a complexity one:

| Test | Complexity | Why |
| --- | --- | --- |
| `key in d` | O(1) | hash lookup, same as `key in d.keys()` |
| `value in d.values()` | O(n) | linear scan — values aren't hashed/indexed |

See [python_keywords.md](../02_syntax_flow/python_keywords.md) for `in` as a general keyword (also
drives `for` loops, tests list/set/tuple membership too).

### `.keys()` returns a view, not a list

```python
d = {"apple": 5, "banana": 3}
k = d.keys()
k            # dict_keys(['apple', 'banana'])
type(k)      # <class 'dict_keys'>
```

- **Live view, not a snapshot** — mutating `d` after the call updates `k` automatically,
  no need to call `.keys()` again.
- **Iterable**, usable directly in `for key in d.keys():` (or just `for key in d:`) —
  no need to convert it for iteration.
- **Not indexable** — `d.keys()[0]` raises `TypeError`.
- **`list(d.keys())`** converts it to a real, indexable, "frozen" (snapshot-at-call-time)
  list — also changes the repr from `dict_keys([...])` to `[...]`, useful for clean
  display (e.g. `print(list(inventory.keys()))`).

### `.update()` — every accepted syntax

`d.update(...)` mutates `d` in place and always returns `None`. It accepts one
positional argument (of several possible shapes), keyword arguments, or both:

```python
d = {"a": 1, "b": 2}

d.update({"b": 20, "c": 3})        # 1. another dict — merges/overwrites keys
d.update(b=20, c=3)                # 2. keyword arguments — same effect
d.update([("b", 20), ("c", 3)])    # 3. iterable of (key, value) pairs (tuples/lists)
d.update(zip(["b", "c"], [20, 3])) # 4. any iterable of 2-length iterables — zip() included
d.update({"c": 3}, b=20)           # 5. positional dict + kwargs — kwargs applied after,
                                   #    so kwargs win on key conflicts
d.update()                         # 6. no argument — no-op
```

Existing keys are overwritten, new keys are added — nothing is ever removed.

**Alternative (Python ≥ 3.9): merge operators**

```python
d |= {"b": 20, "c": 3}        # in-place merge, equivalent to d.update(...)
merged = d | {"c": 3}         # new dict, d itself untouched (update() has no non-mutating form)
```

**Link with `d[key] = val`**

| | `d[key] = val` | `d.update(...)` |
|---|---|---|
| Keys touched | exactly one | one or many at once |
| Source | a single value | a dict, kwargs, or an iterable of pairs |
| Use case | set/overwrite a single known key | merge in a batch of key/value pairs |

`d.update({"b": 20})` is functionally equivalent to `d["b"] = 20` for a single key —
`.update()` is really `[key] = val` generalized to many keys in one call.

## Sets

> To write.

## Building these collections

Which brackets build which type, eager vs lazy, `all()`/`any()`, the empty-iterable
traps: [python_comprehensions.md](python_comprehensions.md).
