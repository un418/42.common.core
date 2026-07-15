# Conditions: guard clauses vs `if/elif/else`

## The starting point

`raise` and `return` are **terminal statements**: control leaves the function
immediately, nothing after them in that branch ever runs. So when every branch of an
`if/elif/else` chain ends in `raise` or `return`, the `elif`/`else` keywords are
redundant — the mutual exclusivity they express syntactically is already guaranteed by
the control flow itself. Redundant, not wrong.

```python
# Chain form — works, but the elif/else add nothing
if temp < 0:
    raise ValueError("too cold")
elif temp > 40:
    raise ValueError("too hot")
else:
    return temp
```

## The guard clause idiom

Stack the error checks as independent `if` statements that exit immediately, and let
the happy path sit flat at the function's base indentation, with no `else`:

```python
def register(age: int, name: str) -> str:
    if age < 18:
        raise ValueError("too young")
    if not name:
        raise ValueError("empty name")
    return f"{name} registered"      # happy path, unconditional
```

Each `if` reads like a bouncer at the door (hence "guard"): *fail this check and
you're out*. Once past all the guards, the reader knows **everything below runs with
valid data** — no need to mentally track which branch they are in.

## Why guards are considered more idiomatic

1. **"Flat is better than nested"** — literally in the Zen of Python (`import this`).
   The happy path stays at base indentation instead of being buried in an `else`.
2. **It scales.** With 2 validations the chain is perfectly readable. With 6 it becomes
   a ladder where the final `return` is visually just another rung. Guards stay flat
   no matter how many there are.
3. **It separates roles visually**: precondition block on top, business logic below.
   The `return` is no longer "the 3rd branch of a choice" but "the result of the
   function".
4. **Linters know the pattern**: pylint flags the chain form as `no-else-raise` (R1720)
   and `no-else-return` (R1705). flake8 alone says nothing — that's why it stays
   silent on the chain form.

## When `if/elif/else` is still the right tool

Not a hard rule. The chain is correct when the branches are true **alternatives** that
each produce something *without leaving the function* — then the chain expresses
"exactly one of these cases" and is the honest shape:

```python
if score >= 90:
    grade = "A"
elif score >= 75:
    grade = "B"
else:
    grade = "C"
print(grade)          # execution continues — elif/else carry real meaning here
```

Another defensible case: when the subject/spec literally reads as N cases ("too cold /
too hot / otherwise OK"), the chain mirrors the spec word for word. That's a style
choice, not an error — what matters at defense is being able to explain both shapes
and why you kept one.

Rule of thumb: **branches that exit → guards; branches that continue → chain.**

## Related: chained comparisons

For pure "in range" tests, Python lets comparisons chain like in math notation:

```python
if 0 <= temp <= 40:      # idiomatic "in range" test
    ...
```

This is the idiom when the two bounds share one outcome. When each bound needs its own
message (like two distinct `ValueError`s), two separate checks are justified — one
outcome per check.

## Defense-day one-liner

> `raise` leaves the function on the spot, so the `elif/else` after it can't ever be
> reached differently than a plain `if` — guards keep the error checks flat and the
> happy path unindented.

See also: [python_custom_exceptions.md](python_custom_exceptions.md) for what `raise`
does, [python_main_guard.md](python_main_guard.md) for file structure.
