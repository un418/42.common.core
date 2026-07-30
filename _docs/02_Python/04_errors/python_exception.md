# Exceptions — the error model

Why the language has exceptions and how they are organized. The statement that
catches and raises them is a separate note: [[python_try_except_raise]].

- https://docs.python.org/3/tutorial/errors.html

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

Corollary on the ordering of the clauses, and the rest of the statement (`else`,
`finally`, `raise`) : [[python_try_except_raise]].

Underlying philosophy (PEP 20, the Zen — _cf._ [python_idioms.md](../05_style/python_idioms.md)) :
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

## What typed exceptions make possible : EAFP

Everything above pays off in one idiom : Python leans **EAFP** (act, then catch) rather than **LBYL** (check first, then act). That style only works *because* of the two properties on this page — exceptions are **typed**, so I catch exactly `KeyError` and nothing else, and they **propagate**, so the failure cannot be silently dropped. Without the hierarchy, EAFP would mean catching everything blindly.

The two styles side by side, when LBYL still wins, and the defense one-liner : [python_idioms.md](../05_style/python_idioms.md).

## How to print the error type

```python
        try:
            garden_operations(op)
        except Exception as e:
            print(f"Caught {e.__class__.__name__}: {e}")
            print(f"Caught {type(e).__name__}: {e}")
```

- `e.__class__.__name__` : Allow to print the type of error
- `type(e).__name__` : Do the same via the type function

## Where the message lives

An exception is a class, so `raise MyError("...")` is a constructor call : the string
goes into `self.args`, and the inherited `__str__` reads it back. That contract (PEP 352),
what happens when `args` holds zero or several values, and the built-ins that give the
tuple a structural meaning : [python_custom_exceptions.md](python_custom_exceptions.md).
