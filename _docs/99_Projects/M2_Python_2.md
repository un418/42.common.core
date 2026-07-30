Execption

Concept notes for this module: [[python_exception]] (the model and the hierarchy),
[[python_try_except_raise]] (the statement, `else`, `finally`, `raise`),
[[python_custom_exceptions]] (own error classes), [[python_warnings]] (the non-fatal
branch).

- https://www.geeksforgeeks.org/python/python-try-except/
- https://www.geeksforgeeks.org/python/python-exception-handling/
- https://www.geeksforgeeks.org/python/errors-and-exceptions-in-python/
- https://www.geeksforgeeks.org/python/built-exceptions-python/
- https://www.geeksforgeeks.org/python/user-defined-exceptions-python-examples/
- https://docs.python.org/3.12/library/exceptions.html#exception-hierarchy
- https://www.geeksforgeeks.org/python/python-raise-keyword/
- https://www.geeksforgeeks.org/python/what-does-the-if-__name__-__main__-do/


> [!note] #to-move
> General theory — belongs in `02_Python/02_syntax_flow/python_main_guard.md`, which has
> three of the four arguments below but **not** "readability", and **not** the rule of
> thumb at the end (1-2 trivial lines under the `if` = fine, any logic = `main()`).
> Merge those two in rather than duplicating the section.

## Best Practices
#### `main()` vs code directly in `if __name__ == "__main__":`

Putting code directly under the `if` works, but defining a `main()` function is the good practice as soon as there is any logic (loops, try/except, variables):

- **Variable scope**: code under the `if` runs at module level → all its variables become globals (risk of collision/shadowing). Inside `main()`, they stay local.
- **Testability / import**: `from module import main` makes the entry point callable; a raw code block is not.
- **Static analysis**: mypy/flake8 check the body of an annotated function (`-> None`) more strictly than module-level code.
- **Readability**: an `if __name__` reduced to two lines immediately signals that the file is executable and that the entry point is `main()`.

Rule of thumb: one or two trivial lines under the `if` = acceptable; any logic = `main()` function.

> [!note] #to-move
> Tooling, not module-specific — belongs in `02_Python/01_tooling/dev_env.md` next to the
> other mypy/flake8 material. The ex2 mention is just the example, keep it as such.

#### Ignore a mypy error on a single line

When an error is intentional (e.g. ex2 requires keeping faulty code that raises a TypeError), silence mypy on that line only, with the specific error code:

```python
_ = "abc" + 5  # type: ignore[operator]
```

- The error code is the one mypy prints between brackets at the end of the message (`[operator]`, `[assignment]`, ...).
- Targeted form `# type: ignore[code]` > bare `# type: ignore`: only that error code is ignored, anything else on the line is still checked.
- The comment must be on the faulty line itself (not above), two spaces before `#` for flake8, and it counts toward the line-length limit (E501).
- Runtime is unchanged: it is just a comment for the type checker, the exception still fires.
- Wider tools exist (`# mypy: ignore-errors` at top of file, per-module config overrides) but the line-level ignore is the right calibre for a single deliberate error.

# ex2

- https://www.geeksforgeeks.org/python/conditional-statements-in-python/
- https://www.geeksforgeeks.org/python/python-docstrings/

### Q&A:

_cf._ [[python_exception]], [[python_try_except_raise]] § Multiple Exceptions

Why does Python have different types of errors?

How can you catch  multiple types of errors with a single try: only?

Note that you  can’t use type()

# ex3

- https://www.geeksforgeeks.org/python/python-difference-between-list-and-tuple/
-  https://peps.python.org/pep-0257/#multi-line-docstrings

### Q&A:

_cf._ [[python_custom_exceptions]]

When should you create your own error types instead of using Python’s  built-in ones?

How does inheritance help organize different types of  errors?

# ex4

### Q&A:

_cf._ [[python_try_except_raise]] § Finally Keyword (the two sub-sections: `finally`
vs code placed after the try/except, and the order when `return` sits in the `except`)

Why is it important to clean up resources even when errors happen?  

How does the finally block help ensure cleanup always occurs?  
