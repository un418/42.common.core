# Floats in Python

## Why `0.1 + 0.2 != 0.3`

A `float` is a **binary** fraction (IEEE-754 double). Just as `1/3` has no finite decimal form, `0.1`, `0.2`, `0.8` and `30.6` have **no finite binary form**. Python stores the nearest representable double, so a tiny error is baked in *before* any arithmetic happens.

```python
>>> 0.1 + 0.2 == 0.3
False
>>> 0.1 + 0.2
0.30000000000000004
```

Nothing is broken and nothing is Python-specific: C, Java and JS behave the same. **Never compare floats with `==`.**

## Three different problems, three different tools

Do not reach for the wrong one — this is the trap.

| Problem | Question | Tool |
|---|---|---|
| **Type** | is the value an `int` or a `float`? | arithmetic promotion (`x * 1.0`), or `float(x)` |
| **Precision** | has error accumulated in the stored value? | `round(x, n)` |
| **Formatting** | how does the value look on screen? | f-string spec: `f"{x:.1f}"` |

Key facts, each verified:

- `round(25, 1)` → `25` (an **int**). `round()` is **type-preserving** when `ndigits` is given; it does *not* convert. Only `round(2.7)` with `ndigits` omitted returns an `int`.
- `f"{x:.1f}"` fixes what the user **sees**. `round()` fixes what the object **is**.
- `mypy --strict` accepts an `int` where a `float` is annotated (PEP 484 numeric tower), so it will never catch a type drift on a `float` attribute.

## What `round()` actually does

It does **not** make the value exact — no binary float is exactly `30.6`. It snaps the value back to *the same double that the literal `30.6` produces*, which is why equality starts working again:

```python
>>> round(30.600000000000005, 1) == 30.6
True
```

So `round()` **re-normalises** and stops error from **accumulating** across iterations:

```python
h = 25.0
for _ in range(7): h = h + 0.8            # 30.600000000000005   != 30.6
for _ in range(7): h = round(h + 0.8, 1)  # 30.6                 == 30.6
```

Rule of thumb: **round where accumulation happens** (a loop, a `+=`, a `grow()`), not at every read. A format spec at display time cannot repair an accumulated state — it only hides it, and it hides it only on the lines that use a spec.

Corollary, easy to miss: rounding each step does **not** make derived computations exact. A subtraction reintroduces drift, so results of a calculation need their own rounding:

```python
>>> 30.6 - 25.0
5.600000000000001
```

## `round()` uses banker's rounding

Not "half up" — **half to even**:

```python
>>> round(0.5), round(1.5), round(2.5), round(3.5)
(0, 2, 2, 4)
```

Rationale: rounding `.5` always upwards biases sums upwards; rounding to the nearest even value cancels out statistically. And a classic:

```python
>>> round(2.675, 2)
2.67          # not 2.68 — because 2.675 is already not 2.675 in binary
```

## Comparing floats

Never `==`. Compare with a tolerance:

```python
abs(a - b) < 1e-9
```

(The stdlib has `math.isclose(a, b)`, which does this properly — not authorized in the Python modules, but know it exists.)

## Applied to `Plant` (P01)

- `_height` is annotated `float`. Passing `set_height(25)` stores an `int` — the annotation does not enforce anything, and `mypy` stays silent. Formatting in `show()` hides it.
- `show()` formats with `f"{self._height:.1f}cm"` → presentation belongs to the class that displays, not to the stored value. That is why the subject prints the same value as `25cm` in one line and `25.0cm` in another: two owners, two formats.
- `grow()` accumulates (`_height + grow_factor`, called repeatedly), so it rounds. It is the **only** place in `Plant` where accumulation happens.
- ex2's `Growth this week:` line rounds again, because it is a **subtraction** of two rounded values.

## Reference

- https://docs.python.org/3/tutorial/floatingpoint.html
- https://docs.python.org/3/library/functions.html#round
