Execption

- https://www.geeksforgeeks.org/python/python-try-except/
- https://www.geeksforgeeks.org/python/python-exception-handling/
- https://www.geeksforgeeks.org/python/errors-and-exceptions-in-python/
- https://www.geeksforgeeks.org/python/built-exceptions-python/
- https://www.geeksforgeeks.org/python/user-defined-exceptions-python-examples/
- https://docs.python.org/3.12/library/exceptions.html#exception-hierarchy
- https://www.geeksforgeeks.org/python/python-raise-keyword/

## Best Practices
#### `main()` vs code directly in `if __name__ == "__main__":`

Putting code directly under the `if` works, but defining a `main()` function is the good practice as soon as there is any logic (loops, try/except, variables):

- **Variable scope**: code under the `if` runs at module level → all its variables become globals (risk of collision/shadowing). Inside `main()`, they stay local.
- **Testability / import**: `from module import main` makes the entry point callable; a raw code block is not.
- **Static analysis**: mypy/flake8 check the body of an annotated function (`-> None`) more strictly than module-level code.
- **Readability**: an `if __name__` reduced to two lines immediately signals that the file is executable and that the entry point is `main()`.

Rule of thumb: one or two trivial lines under the `if` = acceptable; any logic = `main()` function.
