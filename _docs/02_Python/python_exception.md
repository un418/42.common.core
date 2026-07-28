- https://docs.python.org/3/tutorial/errors.html
# Basics

## Exception Hierarchy
- https://docs.python.org/3/library/exceptions.html#exception-hierarchy

```python
BaseException
 ├── BaseExceptionGroup
 ├── GeneratorExit
 ├── KeyboardInterrupt
 ├── SystemExit
 └── Exception
      ├── ArithmeticError
      │    ├── FloatingPointError
      │    ├── OverflowError
      │    └── ZeroDivisionError
      ├── AssertionError
      ├── AttributeError
      ├── BufferError
      ├── EOFError
      ├── ExceptionGroup [BaseExceptionGroup]
      ├── ImportError
      │    └── ModuleNotFoundError
      ├── LookupError
      │    ├── IndexError
      │    └── KeyError
      ├── MemoryError
      ├── NameError
      │    └── UnboundLocalError
      ├── OSError
      │    ├── BlockingIOError
      │    ├── ChildProcessError
      │    ├── ConnectionError
      │    │    ├── BrokenPipeError
      │    │    ├── ConnectionAbortedError
      │    │    ├── ConnectionRefusedError
      │    │    └── ConnectionResetError
      │    ├── FileExistsError
      │    ├── FileNotFoundError
      │    ├── InterruptedError
      │    ├── IsADirectoryError
      │    ├── NotADirectoryError
      │    ├── PermissionError
      │    ├── ProcessLookupError
      │    └── TimeoutError
      ├── ReferenceError
      ├── RuntimeError
      │    ├── NotImplementedError
      │    ├── PythonFinalizationError
      │    └── RecursionError
      ├── StopAsyncIteration
      ├── StopIteration
      ├── SyntaxError
      │    └── IndentationError
      │         └── TabError
      ├── SystemError
      ├── TypeError
      ├── ValueError
      │    └── UnicodeError
      │         ├── UnicodeDecodeError
      │         ├── UnicodeEncodeError
      │         └── UnicodeTranslateError
      └── Warning
           ├── BytesWarning
           ├── DeprecationWarning
           ├── EncodingWarning
           ├── FutureWarning
           ├── ImportWarning
           ├── PendingDeprecationWarning
           ├── ResourceWarning
           ├── RuntimeWarning 
           ├── SyntaxWarning
           ├── UnicodeWarning
           └── UserWarning
```

## Q&A ? 
### Why does Python have different types of errors?
Firstly there are two types of errors:
- **SyntaxError** : Detected **before the code runs** by the parser. The Python interpreter will not be able to transform the code into bytecode and will not run any line of the code.  
```python
>>> while True print('Hello world')
  File "<stdin>", line 1
    while True print('Hello world')
               ^^^^^
SyntaxError: invalid syntax
```

- **Exception** : the code syntax is correct, it executes and a problem happens **during the execution (runtime)**.
```python
>>> 10 * (1/0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
    10 * (1/0)
          ~^~
ZeroDivisionError: division by zero
```

### Why does Python have different types of exception?
Because the **type itself carries the meaning**. A single generic error would force me to read the message text to guess what went wrong ; here the class *is* the diagnostic (`FileNotFoundError` vs `PermissionError` vs `ValueError`).

Three reasons it is worth it :
- **Precision** : the type tells me exactly what failed, no message parsing needed.
- **Selective handling** : I catch only what I know how to handle and let the rest propagate. Best practice → catch the **narrowest** exception, not a blank `except Exception`.
- **Hierarchy** : exceptions are classes (_cf._ the tree at the top). A parent `except` also catches **all its subclasses**, so I choose the granularity.

```python
>>> try:
...     10 * (1 / 0)
... except ArithmeticError as e:          # parent of ZeroDivisionError
...     print(f"Caught {type(e).__name__}: {e}")
Caught ZeroDivisionError: division by zero
```
`ArithmeticError` catches `ZeroDivisionError` and `OverflowError` ; `LookupError` catches `IndexError` and `KeyError` the same way.

Underlying philosophy (PEP 20, the Zen — _cf._ [python_idioms.md](python_idioms.md)) :
> - Errors should never pass silently.
> - Explicit is better than implicit.

Typed, catchable exceptions are what make those two aphorisms enforceable : an error is loud by default, and silencing it is an explicit `except`.

## Why exceptions at all? — the C comparison

Before Python, the dominant model (C) is **return codes** : every function returns a status code, and it is the caller's job to check it. The problems with that model :

- **Silent failure** : if I **forget** to check the code, the program **keeps running** with invalid data — the crash lands later, far from its cause. Debug hell.
- **Entangled code** : the "happy path" and the error handling are mixed together — an `if (err) return ...` after every single call.
- **Return slot is stolen** : the return value is used up by the status code, so the real result has to travel through an out-parameter.

```c
/* C : check by hand, every time */
FILE *f = fopen("tank.txt", "r");
if (f == NULL) {                 // forget this line -> undefined behaviour later
    perror("fopen");
    return -1;
}
```

Python builds exceptions **into the language** to fix exactly these :

1. **Impossible to ignore by accident** : if nobody catches it, the exception **propagates** up to the top of the interpreter and **stops** the program with a traceback. The error cannot pass unnoticed (_cf._ Zen : *Errors should never pass silently*).
2. **Happy path stays clean** : the normal logic lives in the `try`, the error handling is grouped in the `except`.
3. **Automatic propagation** : a deep function can raise, a caller 5 frames up handles it, the frames in between do nothing.
4. **Rich context** : an exception carries a type, a message and a full **traceback** — the error points near its cause.

```python
# Python : open either works or it raises — no status code to forget
try:
    f = open("tank.txt")
except FileNotFoundError as e:
    print(f"Caught {type(e).__name__}: {e}")
```

> Note : exceptions are not universally superior. Low-level / critical code (kernels, embedded) still prefers return codes ; Rust's `Result` is a modern middle ground. It's a trade-off, not a dogma.

- _cf._ [Why I Prefer Exceptions to Error Values — CedarDB](https://cedardb.com/blog/exceptions_vs_errors/)
- _cf._ [The History of Python — Python's Design Philosophy](http://python-history.blogspot.com/2009/01/pythons-design-philosophy.html)

## EAFP vs LBYL (brief)

Two error-handling styles. Python leans **EAFP** : I try the operation and catch the failure, instead of testing everything first (**LBYL**).

```python
# LBYL — Look Before You Leap : check first, then act
if "fertilizer" in tank:
    dose = tank["fertilizer"]

# EAFP — Easier to Ask Forgiveness than Permission : try, then catch
try:
    dose = tank["fertilizer"]
except KeyError:
    ...
```

Why EAFP : the access *is* the test (no double work), and there is no test/act gap where the state can change in between (race condition). It only works because exceptions are typed and propagate — so I catch exactly `KeyError` and nothing else.

Full trade-off (when LBYL still wins, the defense one-liner) : [python_idioms.md](python_idioms.md).

# How to print Error Type ? 

```python
        try:
            garden_operations(op)
        except Exception as e:
            print(f"Caught {e.__class__.__name__}: {e}")
            print(f"Caught {type(e).__name__}: {e}")
```

- `e.__class__.__name__` : Allow to print the type of error
- `type(e).__name__` : Do the same via the type function


# Error args

At the beginning I thought that an exception can have a string as parameter and that it allows to override the default error message.
In reality it is more complex and powerful than that.
```python
print("Testing WaterError...")
try:
    raise WaterError("Not enough water in the tank!")
except WaterError as e:
    print(f"Caught {e.__class__.__name__}: {e}")
print()
```


Exceptions are classes (that usually use inheritance)
  The constructor of the top level [BaseException](https://docs.python.org/fr/3.14/library/exceptions.html#OSError) accepts `args` and it can be super useful to enrich the error message that they return. (_cf._ : [\__str__ dunder method concept ](https://www.geeksforgeeks.org/python/str-vs-repr-in-python/))


- From :  https://docs.python.org/fr/3.14/library/exceptions.html#BaseException.args 
 >  Some built-in exceptions (like [`OSError`](https://docs.python.org/3/library/exceptions.html#OSError "OSError")) expect a certain number of arguments and assign a special meaning to the elements of this tuple, while others are usually called only with a single string giving an error message.
  
- Another good example with [`UnicodeDecodeError`](https://docs.python.org/3/library/exceptions.html#UnicodeError) that accepts
>  **5 arguments** : `(encoding, object, start, end, reason)`, and a  `__str__` that builds a more comprehensible sentence :
 >  ```
 >'utf-8' codec can't decode byte 0x80 in position 0: invalid start byte
 > ```
