# Syntax

The statement itself. Why the language has exceptions at all, and why they are typed:
[[python_exception]]. Why reaching for them first (EAFP) rather than checking before
(LBYL) is the Python default: [[python_idioms]].

```python
try:
    n = 0
    res = 100 / n
except ZeroDivisionError:
    print("You can't divide by zero!")    
except ValueError:
    print("Enter a valid number!")
else:
    print("Result is", res)
finally:
    print("Execution complete.")
```

**Explanation:**  
**try block attempts** division, **except blocks catch** specific errors, **else** block executes** only if no errors** occur, while **finally block always runs**, signaling end of execution.

- **try**: Runs the risky code that might cause an error.
- **except:** Catches and handles the error if one occurs.
- **else:** Executes only if no exception occurs in try.
- **finally**:Runs regardless of what happens useful for cleanup tasks like closing files.

# Catching Exceptions
### Specific Exceptions

```python
try:
    # This will cause ValueError
    x = int("str") 
    inv = 1 / x   # Inverse calculation
except ValueError:
    print("Not Valid!")
except ZeroDivisionError:
    print("Zero has no inverse!")
```

An `except C` matches if the exception is an instance of `C` **or of a subclass**, so
which class I name decides the granularity, and the clauses must go from the most
specific to the most general. The tree to pick from: [[python_exception]].

### Multiple Exceptions

We can catch multiple type of exception in a single `except` statement
```python
a = ["10", "twenty", 30]
try:
    # 'twenty' cannot be converted to int
    total = int(a[0]) + int(a[1])  
except (ValueError, TypeError) as e:
    print("Error", e)
except IndexError:
    print("Index out of range.")
```

`as e` binds the instance, so the handler can read what actually happened:
`e` for the message, `e.__class__.__name__` for the type name (_cf._
[[python_exception]]).

## Raise an Exception

### Syntax

 ```python
 raise ExceptionType("Error message")
 ```

Example:

```python
def set(age):
    if age < 0:
        raise ValueError("Age cannot be negative.")
    print(f"Age set to {age}")
try:
    set(-5)
except ValueError as e:
    print(e)
```

Two follow-ups on the choice of what to raise:

- a built-in fits most cases (`ValueError` = right type, wrong value; `TypeError` =
  wrong type of argument). Own class only for domain errors callers must catch
  *separately*, and then the `super().__init__()` contract applies: [[python_custom_exceptions]].
- when the operation actually succeeded and I only want to report something, the tool
  is a warning, not a `raise`: [[python_warnings]].

## Else Clause

else block is used with try-except and executes only when no exception occurs in the try block. If an exception is raised, the else block is skipped.

```python
def divide(a, b):
    try:
        result = a // b
    except ZeroDivisionError:
        print("Cannot divide by zero")
    else:
        print("Result:", result)
divide(10, 2)
divide(10, 0)
```

## Finally Keyword

finally block is always executed after the try and except blocks, whether an exception occurs or not. 
It is commonly used for cleanup tasks such as closing files or releasing resources.

```python
try:
    result = 10 // 0
    print(result)
except ZeroDivisionError:
    print("Cannot divide by zero")
finally:
    print("This block always executes")
```

### `finally` vs code placed after the try/except

This is the question I could not answer on defense day, and the block above is
exactly why: here both constructs behave the same, so the difference is invisible.

One sentence: **`finally` runs on every exit path out of the `try`; code placed
after the try/except only runs if the flow reaches it normally.**

| How the `try` is left | `finally` | code after the try/except |
|---|---|---|
| normal completion | runs | runs |
| exception caught, no `return` | runs | runs |
| **`return` inside the `try` or the `except`** | **runs** | **skipped** |
| **exception nobody catches** | **runs, before propagation resumes** | **never reached** |
| `break` / `continue` inside a loop | runs | skipped |

`finally` runs **while the exception is still propagating**, then the propagation
resumes. 
That is the whole point: cleanup is not something you hope to reach, it
is something the language guarantees.
A file handle left open, a lock never released or a valve left running are all the same bug, the cleanup line sitting on a path the flow abandoned.

```python
>>> def g():
...     try:
...         raise ValueError("boom")
...     except TypeError:
...         print("no match")
...     finally:
...         print("finally ran")
...     print("after: never reached")
...
>>> g()
finally ran
Traceback (most recent call last):
  ...
ValueError: boom
```

### Order of execution when `return` sits in the `except`

The trap is thinking the function returns and *then* the `finally` runs somehow
afterwards. What actually happens:

1. the return **value is evaluated** (right there, in the `except`);
2. the `return` is put **on hold**;
3. the `finally` block runs;
4. only then does the function actually return the value from step 1.

```python
>>> def log(x):
...     print(f"evaluating: {x}")
...     return x
...
>>> def f():
...     try:
...         raise ValueError("boom")
...     except ValueError:
...         print("except")
...         return log("return value")
...     finally:
...         print("finally")
...
>>> f()
except
evaluating: return value
finally
'return value'
```

`evaluating:` prints before `finally`, so the value is computed first; the
function hands it back last. Consequence: a `finally` that mutates the object
being returned still affects the caller, but rebinding the local variable does
not, the value is already captured.

### Anti-pattern: `return` inside `finally`

Because the pending `return` is only "on hold", a `return` written **in** the
`finally` overwrites it, and it also **swallows an exception in flight**:

```python
>>> def swallow():
...     try:
...         raise ValueError("boom")
...     finally:
...         return "swallowed"
...
>>> swallow()
'swallowed'
```

The `ValueError` is gone; no traceback, no trace of it anywhere. 
Same story with `break` and `continue` inside a `finally`. Keep `finally` for cleanup only, never for control flow (flake8-bugbear flags this as B012).

### Note: for files, `with` does this for me

`finally` is the manual form of the guarantee. A context manager (`with`) is the same
guarantee packaged into the object, which is why `with open(...)` never needs a
`close()` in a `finally` (_cf._ [[python_keywords]], § Context managers). I still write
`finally` by hand for anything that is not a context manager: a flag to reset, a valve
to shut, a state to restore.

# Related notes

- [[python_exception]] — the error model: hierarchy, why the type carries the meaning, propagation, the C return-code comparison.
- [[python_custom_exceptions]] — defining my own error classes, the `args` / `super().__init__()` contract.
- [[python_warnings]] — the non-fatal branch: emitted instead of raised, execution continues.
- [[python_idioms]] — EAFP vs LBYL, and when LBYL still wins.
- [[python_keywords]] — `try` / `except` / `finally` / `raise` / `assert` / `with` in the keyword table.
- [[M2_Python_2]] — the module where these were exercised, and the defense questions this note answers.

# Sources
- https://www.geeksforgeeks.org/python/python-try-except/
- https://www.geeksforgeeks.org/python/python-exception-handling/
- https://www.geeksforgeeks.org/python/errors-and-exceptions-in-python/
- https://www.geeksforgeeks.org/python/built-exceptions-python/
- https://www.geeksforgeeks.org/python/user-defined-exceptions-python-examples/
- https://www.geeksforgeeks.org/python/python-raise-keyword/
- https://docs.python.org/3.12/library/exceptions.html#exception-hierarchy
- https://docs.python.org/3/reference/compound_stmts.html#the-try-statement — the
  `finally` semantics: pending `return`/`break`/`continue` and discarded exceptions
- https://docs.python.org/3/tutorial/errors.html#defining-clean-up-actions