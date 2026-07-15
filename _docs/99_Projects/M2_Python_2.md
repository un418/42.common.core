Execption

- https://www.geeksforgeeks.org/python/python-try-except/
- https://www.geeksforgeeks.org/python/python-exception-handling/
- https://www.geeksforgeeks.org/python/errors-and-exceptions-in-python/
- https://www.geeksforgeeks.org/python/built-exceptions-python/
- https://www.geeksforgeeks.org/python/user-defined-exceptions-python-examples/
- https://docs.python.org/3.12/library/exceptions.html#exception-hierarchy
- https://www.geeksforgeeks.org/python/python-raise-keyword/
- https://www.geeksforgeeks.org/python/what-does-the-if-__name__-__main__-do/

## Best Practices
#### `main()` vs code directly in `if __name__ == "__main__":`

Putting code directly under the `if` works, but defining a `main()` function is the good practice as soon as there is any logic (loops, try/except, variables):

- **Variable scope**: code under the `if` runs at module level → all its variables become globals (risk of collision/shadowing). Inside `main()`, they stay local.
- **Testability / import**: `from module import main` makes the entry point callable; a raw code block is not.
- **Static analysis**: mypy/flake8 check the body of an annotated function (`-> None`) more strictly than module-level code.
- **Readability**: an `if __name__` reduced to two lines immediately signals that the file is executable and that the entry point is `main()`.

Rule of thumb: one or two trivial lines under the `if` = acceptable; any logic = `main()` function.

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

Why does Python have different types of errors?

How can you catch  multiple types of errors with a single try: only?

Note that you  can’t use type()

# ex3

- https://www.geeksforgeeks.org/python/python-difference-between-list-and-tuple/
-  https://peps.python.org/pep-0257/#multi-line-docstrings

### Q&A:

When should you create your own error types instead of using Python’s  built-in ones?

How does inheritance help organize different types of  errors?

# ex4

### Q&A:

Why is it important to clean up resources even when errors happen?  

How does the finally block help ensure cleanup always occurs?  
