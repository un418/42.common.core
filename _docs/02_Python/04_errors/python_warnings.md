# Warnings — the `Warning` exception subclass

## What it is

`Warning` is a subclass of `Exception`, but it is not meant to signal errors: it signals
**non-blocking problems** through the `warnings` module. The operation *succeeded*, but
something is worth reporting — "this still works but stop using it", "this behavior will
change", "you probably forgot to close this file".

```text
BaseException
 └── Exception
      └── Warning
           ├── UserWarning
           ├── DeprecationWarning
           ├── PendingDeprecationWarning
           ├── FutureWarning
           ├── RuntimeWarning
           ├── ResourceWarning
           ├── SyntaxWarning
           ├── ImportWarning
           ├── UnicodeWarning
           ├── BytesWarning
           └── EncodingWarning        (3.10+)
```

## Warnings vs exceptions — the core difference

An exception is **raised**: it interrupts control flow and unwinds the stack until caught
(or crashes the program). A warning is **emitted** with `warnings.warn(...)`: the message
goes to stderr and **execution continues normally**.

```python
import warnings


def old_function() -> int:
    warnings.warn("use new_function() instead", DeprecationWarning, stacklevel=2)
    return 42


x = old_function()  # prints the warning; x is still 42
```

| | Exception | Warning |
|---|---|---|
| Verb | `raise` | `warnings.warn()` |
| Control flow | interrupted | continues |
| Who decides severity | the author (`raise` is final) | the *runner*, via filters |
| Repetition | happens every time | deduplicated per location by default |
| Visibility | always | some categories hidden by default |

Two behaviors with no exception equivalent:

- **User-filterable**: whoever runs the code decides what happens — ignore, print, or
  escalate to a real error (`python -W error`, `warnings.simplefilter("error")`,
  `PYTHONWARNINGS` env var).
- **Hidden by default**: `DeprecationWarning` (outside `__main__`),
  `PendingDeprecationWarning` and `ResourceWarning` are ignored unless configured — or
  under dev mode, `python -X dev`.

## Why is it an `Exception` subclass at all?

Precisely so filters can **escalate warnings into errors**. With `simplefilter("error")`
a `warnings.warn(...)` becomes a real `raise` — catchable with `try/except UserWarning`.
Widely used in CI to force projects to deal with their deprecations before they break.

```python
>>> import warnings
>>> warnings.simplefilter("error")
>>> warnings.warn("boom")
Traceback (most recent call last):
  ...
UserWarning: boom
```

## Categories and their use cases

| Category | Use case | Shown by default |
|---|---|---|
| `UserWarning` | default category of `warn()`; generic warning to users of your code | yes |
| `DeprecationWarning` | API going away — aimed at **developers** calling your code | only in `__main__` |
| `PendingDeprecationWarning` | deprecation planned but not yet active | no |
| `FutureWarning` | behavior change coming — aimed at **end users** (pandas uses it a lot) | yes |
| `RuntimeWarning` | dubious runtime behavior (numpy overflow, coroutine never awaited) | yes |
| `ResourceWarning` | resource never released (unclosed file/socket) | no (yes with `-X dev`) |
| `SyntaxWarning` | valid but dubious syntax (e.g. `is` with a literal) | yes |
| `EncodingWarning` | `open()` without an explicit `encoding=` (3.10+) | no |

The `DeprecationWarning` / `FutureWarning` split is about **audience**: the former targets
the developer importing the library (hidden from end users running an app), the latter
targets whoever runs the program and must see it.

## Practical details

- **`stacklevel=2`** makes the warning point at the *caller's* line instead of the
  `warn()` line itself — far more useful for whoever has to fix the call site.
- **Filter actions**: `"error"`, `"ignore"`, `"always"`, `"default"` (once per location),
  `"once"` (once total), `"module"` (once per module).
- **Scoped filtering** for tests or noisy libraries:

  ```python
  with warnings.catch_warnings():
      warnings.simplefilter("ignore", DeprecationWarning)
      noisy_call()
  ```

- **pytest** has `pytest.warns(DeprecationWarning)`, symmetric to `pytest.raises(...)`,
  to assert a warning is emitted.

## When to pick which

Raise an **exception** when the caller *must* react: the operation failed, the result
does not exist (the statement itself: [[python_try_except_raise]]). Emit a **warning**
when the operation succeeded but something should be reported — without breaking anyone's code, and leaving the final severity decision to
the person running it.

## Defense-day one-liner

> A `Warning` is an `Exception` subclass that is emitted, not raised: execution continues
> and the runner chooses via filters whether to ignore it, print it, or turn it into a
> real error.

## Reference

- https://docs.python.org/3/library/warnings.html
- https://docs.python.org/3/library/exceptions.html#warnings
