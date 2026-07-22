# Naming — judgment layer

> PEP 8 = *mechanics* (`snake_case`, no builtin shadowing) → [python_idioms.md](python_idioms.md).
> Here = *judgment*: the name is syntactically fine, but is it **good**?

---

## At a glance

**Functions** — a name is a *contract*

| #   | Rule                                     | Smell → Fix                                        |
| --- | ---------------------------------------- | -------------------------------------------------- |
| F1  | **Verb** first: a function *does*        | `summary_report()` that prints → `print_summary()` |
| F2  | Verb family = **return type**            | `check_` → `None` · `parse_` → value               |
| F3  | `is_` / `has_` = **pure predicate**      | raises, or returns only `False` → not a predicate  |
| F4  | Name the **behavior**, not the mechanism | `str_to_int` that also validates → under-promises  |

**Variables** — a name is a *label on a value*

| # | Rule | Smell → Fix |
| --- | --- | --- |
| V1 | Name the **role**, not the type | `lst`, `d`, `splitted_str` → `scores`, `fields` |
| V2 | Compound: **head noun last** | `count_items` → `item_count` |
| V3 | Reuse vocabulary **already in the file** | var `most` next to `print("most abundant")` |

**Both**

| #   | Rule                                 | Smell → Fix                               |
| --- | ------------------------------------ | ----------------------------------------- |
| B1  | **One concept, one name** everywhere | `inventory` here / `inv` there → pick one |
| B2  | Line too long? Fix the **structure** | shrink the ternary, keep the good name    |

---

# Part A — Functions

## F1 · Verb = does · Noun = is

A function name is a **verb phrase**. A noun-only name promises a value and
hides the action.

| ✗ Bad               | Reads as                     | ✓ Better                       |
| ------------------- | ---------------------------- | ------------------------------ |
| `summary_report()`  | *a* summary report (a value) | `print_summary()`              |
| `duplicate_check()` | *a* check (a value)          | `check_duplicate()`            |
| `data()`            | *the* data                   | `load_data()` / `fetch_data()` |

## F2 · The verb family *is* the return type

| Prefix                  | Contract                                       | Returns   |
| ----------------------- | ---------------------------------------------- | --------- |
| `check_…`               | validates an invariant, **raises** if violated | `None`    |
| `parse_…`               | validates **and** transforms untrusted input   | the value |
| `print_…` / `display_…` | side-effecting output                          | `None`    |
| `get_…` / `compute_…`   | pure lookup / computation                      | the value |

> A function that validates **and** converts is misfiled as `validate_…` —
> it returns a value, so it's a `parse_`.

Goal: **the signature alone tells the contract**, no need to read the body.

```
command  →  does something    →  side effect     →  returns None
query    →  answers something →  no side effect  →  returns a value
```

Never both (Command-Query Separation). `check_` / `parse_` is exactly this
split applied file-wide.

## F3 · The `is_` / `has_` trap

`is_`/`has_` promises a **pure predicate**: `True`/`False`, no side effect,
never raises for the "false" case.

```python
def is_duplicate(key: str, seen: dict[str, int]) -> bool:
    if key in seen:
        raise ValueError(f"duplicate '{key}'")   # ✗ True path never returns
    return False                                 # ✗ only value ever returned
```

→ callers write `if not is_duplicate(...)`, testing a boolean that **never
varies**. A command pretending to be a query.

| Fix | Shape |
| --- | --- |
| Real predicate | returns the bool both ways, never raises; caller decides |
| Real validator | rename `check_not_duplicate`, `-> None`, raise is the only signal |

Never leave a `bool` function that returns only one of its two values.

## F4 · Behavior, not mechanism

`str_to_int` promises a generic conversion. If the body also rejects
negatives and builds a domain-specific error, the name **under-promises** →
name it for what it guarantees, not for the operation it happens to use.

---

# Part B — Variables

## V1 · Role, not type or mechanism

| ✗ Bad | Why | ✓ Better |
| --- | --- | --- |
| `splitted_str` | names the operation | `fields`, `parts` |
| `k`, `v` | names the dict type-slot | `name`, `age` |
| `d`, `lst`, `obj` | names the container type | `scores`, `players` |
| `tmp`, `val`, `data` | adds nothing the type hint didn't | what it *represents* |

**Test** → *Could I drop this name into an unrelated file without it lying?*
If no, it's named after the mechanism.

> Short names (`i`, `e`, `p1`) stay defensible in **short scopes**. The cost
> of a terse name grows with the length of the scope it lives in.

## V2 · Head noun last

English compounds put **what the thing is** at the end.

| Name | Parses as | Verdict |
| --- | --- | --- |
| `item_count` | a *count* (of items) | ✓ variable |
| `count_items` | "count the items" — verb phrase | ✓ function, ✗ variable |
| `total_price` | a *price* (that is total) | ✓ — `total` is an adjective, not a verb |

**Test** → *Does the last word say what the value fundamentally is?*
This is also what separates a variable from a function: same words, order
flipped.

## V3 · Vocabulary already in the file

Output strings and comments are free, already-correct vocabulary. A variable
named `most` sitting two lines above `print("most abundant: ...")` is a
signal to adopt the fuller name.

> ⚠️ **Bulk-rename trap**: renaming a variable also rewrites the word inside
> **string literals** when the old name is a normal English word.
> `most` → `most_abundant` turns `"Item most abundant"` into
> `"Item most_abundant abundant"`.
> Type checkers can't see this — only diffing actual program output catches it.

---

# Part C — Both

## B1 · One concept, one name

The costliest defect *and* the most invisible — the author holds the mapping
in their head, the reader rebuilds it function by function.

Check at every **call boundary**:

```
caller says      item  ──►  parameter says  key      ✗ mismatch
function's own error message says "item"             ✗ tells on itself
```

## B2 · Line length = structure problem

Name doesn't fit in 79 chars? Look at the **structure** first.

```python
best = x if score > table[best] else best     # ✗ name repeated 3× ; else = no-op
```

```python
if score > table[best_candidate]:             # ✓ 1× + 1× ; no-op gone
    best_candidate = x
```

- A ternary repeating the name **triples** the cost of every character.
- `x = a if cond else x` — the `else` branch is a self-assignment, i.e. "do
  nothing" written as an assignment.

Shorten the name only as a **last resort**, and keep a pair symmetric
(matching lengths) rather than trimming one side.

---

See also: [python_idioms.md](python_idioms.md) (PEP 8 mechanics, EAFP/LBYL, Zen).
