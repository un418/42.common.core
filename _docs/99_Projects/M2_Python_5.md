# Concepts

> [!note] #to-move
> General theory, not module-specific — belongs in `02_Python/02_syntax_flow/python_abstract_classes.md` (to create). Covers the whole `# Concepts` block below. Move after the module 05 defense.

### Abstract Classes

> https://www.geeksforgeeks.org/python/abstract-classes-in-python/

In Python, an abstract class is **a class that cannot be instantiated** on its own and is **designed to be a blueprint** for other classes. Abstract classes allow us to **define methods that must be implemented by subclasses**, **ensuring a consistent interface** while still **allowing the subclasses to provide specific implementations**.


### When to Use Abstract Classes ?

Abstract classes are useful when you want to:
- Define a common interface for all subclasses (e.g., all animals must have a sound()).
- Enforce implementation of certain methods in child classes.
- Provide shared functionality (concrete methods) while still requiring subclasses to implement specific behavior.

### Interface (Terminology )

An interface is **the contract of a class** : the set of methods/attributes a caller can rely on, **without knowing the implementation**. It answers *"what can I call on this object ?"*, never *"how does it work ?"*.

|            | Interface (the *what*)          | Implementation (the *how*)  |
| ---------- | ------------------------------- | --------------------------- |
| Describes  | method names, args, return type | the body of the method      |
| Defined by | the abstract class              | each subclass               |
| Shared     | same for all subclasses         | different for each subclass |

```
        Processor          <- interface : ingest(), report()
        /        \
NumericProcessor  TextProcessor   <- implementations : same names, own bodies
```

Python has no `interface` keyword (unlike Java) : the interface is expressed with an **abstract class** whose abstract methods define the contract. Concretely, "ensuring a consistent interface" = *every subclass exposes the same callable methods*, so client code can use any of them interchangeably.
### Abstract Method

Force child class to implement the method. If not :
- `TypeError: Can't instantiate abstract class NumericProcessor without an implementation for abstract method 'ingest'`

# ex0
- https://stackoverflow.com/questions/152580/whats-the-canonical-way-to-check-for-type-in-python
	- https://www.geeksforgeeks.org/python/how-to-check-the-type-of-an-object-in-python/
- https://fr.wikipedia.org/wiki/Principe_de_substitution_de_Liskov
- https://www.geeksforgeeks.org/python/queue-in-python/
- https://www.geeksforgeeks.org/python/data-abstraction-in-python/
	- Good Schema
- https://www.geeksforgeeks.org/python/method-overriding-in-python/
- https://www.geeksforgeeks.org/python/python-__len__-magic-method/
- https://www.geeksforgeeks.org/python/bool-in-python/

> [!note] #to-move
> General theory — belongs in `02_Python/03_data_types/python_comprehensions.md`, which already states the rule and the list-vs-dict/set contrast but has **neither** the turn-by-turn cursor table nor the three idioms below. Merge, don't overwrite.

### Common mistake : mutating a list while iterating over it

The iterator keeps **its own cursor**, `pop(0)` shifts items underneath it → the two cross.

| turn | cursor | len | `item` received |
| ---- | ------ | --- | --------------- |
| 1    | 0      | 5   | idx 0           |
| 2    | 1      | 4   | idx 2 ⚠️ skipped |
| 3    | 2      | 3   | idx 4 ⚠️ skipped |
| 4    | 3      | 2   | `3 >= 2` → **stop** |

`n` turns become `ceil(n/2)` → early exit, the queue is never drained. `dict`/`set` raise `RuntimeError: ... changed size during iteration` ; lists **give no warning**.

```python
for item in queue:      # ❌ anti-pattern : iterate + mutate the same list
    use(queue.pop(0))

while queue:            # ✅ drain : condition on the container itself
    use(queue.pop(0))

for item in list(queue):  # ✅ mutate while needing the items : iterate a copy
    queue.remove(item)
```

> [!note] #to-move
> **Theory only** — invariance/covariance belongs in `02_Python/02_syntax_flow/python_typing.md` (to create). The verdict blockquote at the end is specific to `ingest` and the subject's wording, so it stays here. Split, don't move wholesale.

### `list` is invariant — the `ingest` signature
+ https://hackmd.io/pNiqam53RIiUe4eMVBccaA
+ https://dev.to/daniel1in/python-type-hint-contravariant-covariant-invariant-15lj

`list` allows writing, so accepting a wider element type would let the callee drop a `float` into the caller's `list[int]` → checkers demand an **exact** match. Read-only `Sequence` has no write op, hence is covariant. Only `list[int]` actually breaks: `int` is promoted to `float`, so `list[float]` ≡ `list[int | float]` and already covers mixed lists.

| passed to `ingest(data: int \| float \| list[int \| float])`        | mypy         |
| ------------------------------------------------------------------- | ------------ |
| literal `[1, 2, 3]` · variable `list[float]` · `list[int \| float]` | ✅            |
| variable `list[int]`                                                | ❌ invariance |

> **Kept `list[...]`**: aligned with the runtime `isinstance(data, list)`, and the subject says *"lists of both types"*. `Sequence` would silently accept tuples that validation rejects.


> [!note] #to-move
> `02_Python/02_syntax_flow/python_truthiness.md` **already covers both** dunders in full (lookup chain, falsy set, which one to define). Only the two links below are not there. Candidate for deletion rather than migration.

### __len__ magic method
- https://www.geeksforgeeks.org/python/python-__len__-magic-method/
- Fiche : [Truthiness — what `if obj:` really asks](../02_Python/02_syntax_flow/python_truthiness.md) — `bool()` → `__bool__` sinon `__len__ != 0` sinon `True` ; d'où `if not lst:` sur un conteneur vide, et le piège de la classe sans aucun des deux (toujours truthy).
### __bool__ magic method
- https://www.geeksforgeeks.org/python/bool-in-python/