# The `main()` + `__main__` guard pattern

## The rule

Every runnable script gets a `main()` function and a guard. Never put executable statements at module top level.

```python
#!/usr/bin/env python3


def do_work(value: int) -> int:
    return value * 2


def main() -> None:
    print(do_work(21))


if __name__ == "__main__":
    main()
```

## Why the guard exists

`import module` **executes the whole file top to bottom**. `def` and `class` statements just create the function/class objects — harmless. Everything else *runs*.

| Run mode | `__name__` value | Guarded block |
|---|---|---|
| `python3 file.py` | `"__main__"` | runs |
| `import file` | `"file"` | skipped |

So the guard is not an obstacle to imports — it is **exactly what makes a file safely importable** while staying directly runnable. One file, two roles.

## Why wrap the body in `main()` (not just inside the `if`)

Putting the code inside the `if` block already prevents it from running on import. The extra `main()` function buys three more things:

1. **No module-level globals.** Variables declared inside the `if` block are globals — visible to every function in the file, and importable by other modules. Inside `main()` they're locals, gone when it returns.
2. **The entry point is testable and callable.** Another module can `import file` then call `file.main()` deliberately.
3. **Type checking.** `mypy` checks function bodies; annotate `def main() -> None:` and the body gets checked. Code in a bare `if` block is checked too, but globals leak into inference and produce noisier errors.

## What must live inside `main()`

Anything with a **side effect** or that reads the **environment**:

- `print()` calls, tests, demos
- object creation (`rose = Plant(...)`)
- `sys.argv` parsing — at top level this runs at import time and reads the *importing* program's arguments
- file/network access

What stays at top level: `import` statements, `def`, `class`, and true constants (`MAX_HEIGHT = 300`).

## One `main()` per file — is that a problem?

No. Module namespaces keep them separate.

```python
import ft_plant_factory              # ft_plant_factory.main() — namespaced, safe
from ft_plant_factory import Plant   # explicit name, safe

from ft_plant_factory import *       # AVOID: pulls in main(), clobbers names
```

`import *` is the only thing that collides, and flake8 flags it (`F403`/`F401`). Don't use it.

## Import gotchas to know

- **Module name = file name**, minus `.py`, and it must be a valid Python identifier. `ft_plant_factory.py` → `import ft_plant_factory`. A file named `my-file.py` or `2ex.py` is not importable with a plain `import`.
- **Search path**: Python looks in the directory of the *executed* script, then in `sys.path`. Importing across sibling exercise folders (`ex3/` ← `ex2/`) does not work without packaging tricks. For 42 modules each exercise is self-contained anyway.
- **Import runs the module once.** Repeated `import x` reuses the cached module object from `sys.modules`; the file body does not re-execute.

## The anti-pattern

```python
# BAD — runs on import, leaks `result` as a global
result = do_work(21)
print(result)
```

```python
# GOOD
def main() -> None:
    result = do_work(21)
    print(result)


if __name__ == "__main__":
    main()
```

## Defense-day one-liner

> `__name__` is `"__main__"` only when the file is the program being executed. The guard separates reusable definitions from script code, so importing the file gives me the classes without running my tests.

See also: [python_module01_concepts.md](../../99_Projects/M2_Python_1_concepts.md) §2 (ex0) for the shebang and the exact questions asked at defense.
