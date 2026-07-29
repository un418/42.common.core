# Custom exception classes

## The rule

Inherit from `Exception` (never `BaseException`), name the class in CamelCase with an
`Error` suffix, and keep the body simple — a docstring, and at most an `__init__` that
forwards to `super().__init__()`.

```python
class NoCheeseError(Exception):
    """Raised when there is no cheese in the fridge."""

    def __init__(self, message="No cheese to eat from the fridge."):
        super().__init__(message)
```

```python
>>> raise NoCheeseError
NoCheeseError: No cheese to eat from the fridge.
>>> raise NoCheeseError("The brie is gone!")
NoCheeseError: The brie is gone!
```

Why not `BaseException`: that root is reserved for the "system" exceptions that must
escape a normal `except Exception:` handler (`KeyboardInterrupt`, `SystemExit`,
`GeneratorExit`). A custom error caught alongside them would hide Ctrl-C.

## How the message actually works (PEP 352 contract)

`BaseException.__init__(*args)` stores everything it receives in `self.args`, and the
inherited `__str__` derives the display from it:

| `args` content | `str(e)` shows |
|---|---|
| `()` | `""` (empty line) |
| `("msg",)` | `msg` |
| `("msg", 42)` | `("msg", 42)` (the tuple) |

So `args` is the **only official channel for the message**. The old `.message`
attribute existed briefly in Python 2.5 and was removed by PEP 352 — storing the
message anywhere else fights the language design.

Consequence: a "default message" is nothing more than making sure
`super().__init__()` receives that message when the caller did not provide one.
Everything (`str`, `repr`, traceback display, pickling/copying) then works for free.

### Built-ins that give `args` a special meaning

I first read `raise MyError("...")` as "pass a string to override the default message".
It is more than that: the string is just the common case of a general mechanism, and
some built-ins use the tuple structurally.

> Some built-in exceptions (like `OSError`) expect a certain number of arguments and
> assign a special meaning to the elements of this tuple, while others are usually
> called only with a single string giving an error message.
> — [docs, `BaseException.args`](https://docs.python.org/3/library/exceptions.html#BaseException.args)

`UnicodeDecodeError` is the clearest example: it takes **5** arguments
`(encoding, object, start, end, reason)` and defines a `__str__` that assembles them
into a readable sentence:

```python
>>> b"\x80abc".decode("utf-8")
UnicodeDecodeError: 'utf-8' codec can't decode byte 0x80 in position 0: invalid start byte
```

So the rule of thumb: forward to `super().__init__()` the values that *define* the
error, and let `__str__` do the sentence (_cf._
[`__str__` vs `__repr__`](https://www.geeksforgeeks.org/python/str-vs-repr-in-python/)).

## Extra attributes: forward them too

When an error carries context, keep the contract by passing the same data positionally
to `super().__init__()` **and** binding named attributes for handlers:

```python
class HTTPError(Exception):
    def __init__(self, status_code, reason):
        super().__init__(status_code, reason)   # keeps args/__str__/__repr__ honest
        self.status_code = status_code
        self.reason = reason
```

## Contextual default message (ValueError-style)

`ValueError` embeds the offending input in its message
(`invalid literal for int() with base 10: 'abc'`). To get the same from a custom
exception, build the message **in the body of `__init__`** — at call time:

```python
class RottenFoodError(Exception):
    """Raised when a food in the fridge has gone off."""

    def __init__(self, food: str, message: str | None = None):
        if message is None:
            message = f"The {food} has gone off."
        super().__init__(message)
        self.food = food
```

```python
>>> raise RottenFoodError("milk")
RottenFoodError: The milk has gone off.
>>> raise RottenFoodError("milk", "The milk walked away by itself.")
RottenFoodError: The milk walked away by itself.
```

- The default **cannot** live in the signature: `message: str = f"The {food} ..."` is
  evaluated once, at `def` time, where `food` does not exist → `NameError` the moment
  the class is defined. Same mechanism as the mutable-default-argument trap
  (`def f(x=[])`): signature evaluated at definition, body at each call.
- `None` is the sentinel for "caller gave no message"; test it with `is`, not `==`.
- `super().__init__(message)` receives exactly **one** already-formatted string, so
  `str(e)` prints the bare sentence (see the args table above). Contrast with
  `HTTPError` just above, which forwards two raw values and accepts the tuple display.
- The raw datum survives as an attribute (`self.food`) so handlers read it without
  parsing the message — like `AttributeError.name` in the stdlib. The message itself
  lives **only** in `args`.
- `str | None` in annotations requires Python 3.10+; below that, `typing.Optional[str]`.

## One base class per domain

The standard library and big packages (`requests.RequestException`, `OSError` family)
all use the same shape: one base exception for the domain, specific errors derived
from it.

```python
class FridgeError(Exception): ...
class NoCheeseError(FridgeError): ...
class DoorStuckError(FridgeError): ...
```

- `except NoCheeseError:` → surgical, one failure mode.
- `except FridgeError:` → the whole family, because `except` matches subclasses.
- Order matters: subclass handlers **before** the base handler, otherwise the base
  catches everything first.

This is the answer to "when custom instead of built-in?": use a built-in
(`ValueError`, `TypeError`, ...) when it fits; create your own only for
domain/business errors that callers must be able to catch *separately* from
everything else.

## Anti-patterns

```python
# BAD — super() called empty: args == (), print(e) shows a blank line,
# repr(e) is 'BrokenError()', copy/pickle break
class BrokenError(Exception):
    def __init__(self, message="oops"):
        super().__init__()
        self.message = message
```

- **f-string default in the signature** (`message: str = f"The {food} is bad"`) —
  defaults are evaluated once at `def` time, where the other parameters don't exist:
  `NameError` when the class is defined, never the per-call value.
- **`self.message` without feeding `args`** — invisible to `str(e)` and the traceback
  (see above). Common enough that flake8-bugbear has a rule request for it (#421).
- **Docstring as default message** (`super().__init__(msg or self.__doc__)`) — breaks
  under `python -OO` (docstrings stripped → `None`), and mixes documentation with
  behavior. Write the literal string.
- **Reimplementing `__str__`** to carry the message — pointless in the simple case;
  the inherited one already does the right thing once `args` is correct.
- **Logic in the exception class** — exceptions are data carriers; behavior belongs in
  the code that raises/catches them.

## Defense-day one-liner

> The message lives in `args`, filled by `super().__init__()`. My default value on the
> `message` parameter means `raise MyError` still produces a proper message, and
> catching the base class catches the whole family because `except` matches
> subclasses.

## Sources (by authority)

- [PEP 352 – Required Superclass for Exceptions](https://peps.python.org/pep-0352/) —
  Brett Cannon & Guido van Rossum; the `args`/`str()` contract, removal of `.message`.
- [Official tutorial § User-defined Exceptions](https://docs.python.org/3/tutorial/errors.html#user-defined-exceptions)
  and [Built-in Exceptions](https://docs.python.org/3/library/exceptions.html) —
  derive from `Exception`, keep it simple, `Error` suffix.
- [PEP 8 § Exception Names](https://peps.python.org/pep-0008/#exception-names) —
  naming convention.
- [discuss.python.org — pythonic way of setting a default message](https://discuss.python.org/t/whats-the-pythonic-way-of-setting-default-message-on-custom-exception/92527)
  — the exact question, on the official forum; conclusion = the pattern above.
- David Beazley & Brian K. Jones, *Python Cookbook* 3rd ed.,
  [recipe 14.8 "Creating Custom Exceptions"](https://www.oreilly.com/library/view/python-cookbook-3rd/9781449357337/ch14.html)
  — always forward args to `super().__init__()`.
- Sean Hammond, [*Designing Python Exception Classes*](https://www.seanh.cc/2019/06/20/python-custom-exception-classes/)
  — deep dive into what breaks (`args`, `__str__`, `__repr__`) when you deviate.
- MIT OCW 6.0001,
  [Lecture 7 — Testing, Debugging, Exceptions, Assertions](https://ocw.mit.edu/courses/6-0001-introduction-to-computer-science-and-programming-in-python-fall-2016/resources/lecture-7-testing-debugging-exceptions-and-assertions/)
  — academic backup on try/except/raise/assert (light on custom subclasses).
