# Data model: what "properties" a type can have

> In Python a *property* of a type is not a label — it's a **protocol**: a set of dunder
> methods the type implements. Duck typing, formalized. `collections.abc` and `numbers`
> are just two specialized views on the one reference: the **Data Model**.

---

## The built-in types, side by side

| | list | tuple | set | frozenset | dict | str |
| --- | --- | --- | --- | --- | --- | --- |
| Iterable | ✅ | ✅ | ✅ | ✅ | ✅ keys | ✅ |
| Sized | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Container (`in`) | ✅ O(n) | ✅ O(n) | ✅ O(1) | ✅ O(1) | ✅ O(1) keys | ✅ |
| Order guaranteed | ✅ | ✅ | ❌ | ❌ | ✅ 3.7+ | ✅ |
| Indexable | ✅ | ✅ | ❌ | ❌ | ❌ by key | ✅ |
| Sliceable | ✅ | ✅ | ❌ | ❌ | ❌ | ✅ |
| Reversible | ✅ | ✅ | ❌ | ❌ | ✅ 3.8+ | ✅ |
| Mutable | ✅ | ❌ | ✅ | ❌ | ✅ | ❌ |
| Hashable | ❌ | ✅¹ | ❌ | ✅ | ❌ | ✅ |
| Duplicates | ✅ | ✅ | ❌ | ❌ | ❌ keys | ✅ |
| ABC | `MutableSequence` | `Sequence` | `MutableSet` | `Set` | `MutableMapping` | `Sequence` |

¹ a tuple is hashable **only if all its elements are** — `hash((1, [2]))` raises `TypeError`.

### The invariant that ties it all together

> **Mutable ⇒ not hashable.** A hash must stay constant for the object's lifetime; a
> container you can mutate cannot promise that. Hence: no `list`/`set`/`dict` as a dict
> key or set element — use their frozen twin.

| Mutable | Frozen twin | Consequence |
| --- | --- | --- |
| `list` | `tuple` | tuple usable as dict key / set element |
| `set` | `frozenset` | frozenset usable as a set element (`set` of `set` is impossible) |
| `dict` | `MappingProxyType` | read-only view, still not hashable |
| `bytearray` | `bytes` | bytes hashable |

---

## The protocol families

| Family | Property | Dunder(s) | Have it |
| --- | --- | --- | --- |
| **Identity / value** | Equality | `__eq__`, `__ne__` | all |
| | Ordering | `__lt__` `__le__` `__gt__` `__ge__` | int, float, str, tuple, list |
| | Hashable | `__hash__` | int, str, tuple, frozenset |
| | Truthy / falsy | `__bool__`, fallback `__len__` | all |
| **Container** | Iterable | `__iter__` | list, tuple, set, dict, str |
| | Iterator | `__next__` (+ `__iter__`) | generators, `zip`, `enumerate`, file objects |
| | Sized | `__len__` | list, tuple, set, dict, str |
| | Container | `__contains__` | list, tuple, set, dict, str |
| | Reversible | `__reversed__` | list, tuple, str, dict (3.8+) |
| **Access** | Subscriptable | `__getitem__` | list, tuple, str, dict |
| | Mutable | `__setitem__`, `__delitem__` | list, dict, set (via methods) |
| **Numeric** | Numeric tower | `numbers.Integral` → `Real` → `Complex` | int, float, complex, `Fraction` |
| **Behaviour** | Callable | `__call__` | functions, classes, objects defining it |
| | Context manager | `__enter__`, `__exit__` | files, locks |
| | Descriptor | `__get__`, `__set__`, `__delete__` | `property`, methods |
| | Awaitable / async | `__await__`, `__aiter__`, `__anext__` | coroutines, async generators |
| **Representation** | Displayable | `__repr__`, `__str__`, `__format__` | all |
| **Serialization** | Copyable | `__copy__`, `__deepcopy__` | via `copy` |
| | Picklable | `__reduce__`, `__getstate__`/`__setstate__` | via `pickle` |
| | Buffer | buffer protocol | bytes, bytearray, memoryview |

**Reading rule** — no inheritance required. A class that defines `__len__` and
`__getitem__` *is* a sequence for every practical purpose, even without subclassing
anything. That's what "structural" means.

---

## `collections.abc` — the container properties, formalized

> **ABC = Abstract Base Class**: a class that cannot be instantiated and defines a
> *contract* (which methods a type must provide) instead of an implementation. Python's
> ABCs are **structural**: thanks to `__subclasshook__`, `isinstance(x, Iterable)` is
> `True` for anything defining `__iter__`, even with no inheritance link.

```
Hashable   Iterable   Sized   Container      Callable
              |         |        |
            Iterator    +--------+---------+
              |                  |
          Generator          Collection
                          /      |      \
                     Sequence   Set    Mapping
                        |        |        |
             MutableSequence  MutableSet  MutableMapping
```

| ABC | Requires | Grants (mixin methods) |
| --- | --- | --- |
| `Iterable` | `__iter__` | — |
| `Sized` | `__len__` | — |
| `Container` | `__contains__` | — |
| `Collection` | the three above | — |
| `Sequence` | `__getitem__`, `__len__` | `__contains__`, `__iter__`, `__reversed__`, `index`, `count` |
| `Set` | `__contains__`, `__iter__`, `__len__` | `&` `\|` `-` `^`, `<` `<=` `>` `>=`, `isdisjoint` |
| `Mapping` | `__getitem__`, `__iter__`, `__len__` | `get`, `keys`, `items`, `values`, `__eq__` |

⚠ **There is no `Ordered` ABC.** Insertion order is a *documented guarantee* for list,
tuple, str and dict (3.7+), not a runtime-testable protocol. Say "guaranteed by the
language", not "it's an ABC".

---

## Focus: `set` vs `frozenset`

Same protocol (`Set`), one differs only by mutability — and mutability costs the hash.

| | `set` | `frozenset` |
| --- | --- | --- |
| Literal | `{1, 2}` — empty is `set()` | `frozenset()` only, no literal |
| Mutating methods | `add` `remove` `discard` `pop` `clear` `update` | none |
| In-place operators | `\|=` `&=` `-=` `^=` | ❌ |
| Algebra operators | `\|` `&` `-` `^` | ✅ same |
| Inclusion tests | `<` `<=` `>` `>=` `==` `isdisjoint` | ✅ same |
| Hashable | ❌ | ✅ |
| Can be a set element / dict key | ❌ | ✅ |

Shared traits worth stating out loud:

- **No index, no slice, no `reversed()`** — a hash table has no positions to address.
- **Iteration order is arbitrary and unstable across runs** for `str` elements: CPython
  randomizes string hashing per process (`PYTHONHASHSEED`). Never rely on set order.
- **Elements must be hashable** — a set of tuples is fine, a set of lists raises
  `TypeError: unhashable type: 'list'`.
- **Empty set prints `set()`, not `{}`** — `{}` was already the empty dict, and `repr`
  must stay unambiguous.
- **Operators vs methods**: `a & b` demands two sets; `a.intersection(b)` accepts any
  iterable.

---

## Checking a property at runtime

`dir()` and `help()` will **not** tell you "list is Mutable". The ABCs use
`__subclasshook__`, so they don't show up in the MRO — you have to *ask*:

```python
>>> import collections.abc as abc
>>> isinstance([], abc.MutableSequence)   # True
>>> isinstance((), abc.Hashable)          # True
>>> isinstance([], abc.Hashable)          # False
>>> issubclass(dict, abc.Mapping)         # True
```

Or probe the protocol directly — closer to how Python actually decides:

```python
>>> hasattr([], "__iter__")     # True
>>> hasattr(set(), "__getitem__")  # False — that's why s[0] fails
```

Offline manual for the whole hierarchy (see
[python_offline_docs.md](../01_tooling/python_offline_docs.md)):

```bash
python3 -m pydoc collections.abc     # every ABC + its abstract methods
python3 -m pydoc numbers             # the numeric tower
python3 -m pydoc set                 # a concrete type, method by method
```

---

## Reference

| Doc | Covers |
| --- | --- |
| [Data model](https://docs.python.org/3/reference/datamodel.html) | **the** source — every dunder, object customization |
| [collections.abc](https://docs.python.org/3/library/collections.abc.html) | the container ABC hierarchy |
| [numbers](https://docs.python.org/3/library/numbers.html) | the numeric tower |
| [Built-in types](https://docs.python.org/3/library/stdtypes.html) | concrete behaviour per category |
| [Glossary](https://docs.python.org/3/glossary.html) | short official definitions (hashable, iterable, sequence…) |
| [PEP 544](https://peps.python.org/pep-0544/) | `typing.Protocol` — structural typing for mypy |

See also: [python_collections.md](python_collections.md),
[python_truthiness.md](../02_syntax_flow/python_truthiness.md),
[python_comprehensions.md](python_comprehensions.md).
