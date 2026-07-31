# Custom exception classes

Where the errors come from and how they are organized : [[python_exception]]. Catching and raising them : [[python_try_except_raise]].

- https://docs.python.org/3/tutorial/errors.html#user-defined-exceptions

## The rule

Inherit from `Exception`, name the class in CamelCase with an `Error` suffix, and keep the body simple : a docstring, and at most an `__init__` that forwards to `super().__init__()`.

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

## Q&A ?

### Why inherit from `Exception` and never from `BaseException` ?

Because `BaseException` is the root reserved for the **system** exceptions that must escape a normal `except Exception:` handler : `KeyboardInterrupt`, `SystemExit`, `GeneratorExit` (_cf._ the tree in [[python_exception]]).

If my error sits up there next to them, a caller who wants to catch my error has to write `except BaseException:` and ends up swallowing Ctrl-C too.

### Where does the message go when I write `raise MyError("Something")` ?

At the beginning I thought the string was stored in a `.message` attribute somewhere. In reality there is no such attribute : `BaseException.__init__(*args)` dumps **everything it receives** into `self.args`, and the inherited `__str__` derives the display from it.

| `args` content | `str(e)` shows |
|---|---|
| `()` | `""` (empty line) |
| `("msg",)` | `msg` |
| `("msg", 42)` | `("msg", 42)` (the tuple) |

- `args` is the **only official channel** for the message. The `.message` attribute existed briefly in Python 2.5 and was removed by PEP 352.
- So a "default message" is nothing more than making sure `super().__init__()` receives that message when the caller did not provide one. `str`, `repr`, the traceback display and pickling then all work for free.

### So `raise MyError("...")` just overrides the default message ?

That is the common case, not the mechanism. The string is only one possible `args` tuple, and some built-ins use that tuple **structurally** :

> Some built-in exceptions (like `OSError`) expect a certain number of arguments and assign a special meaning to the elements of this tuple, while others are usually called only with a single string giving an error message. — [docs, `BaseException.args`](https://docs.python.org/3/library/exceptions.html#BaseException.args)

`UnicodeDecodeError` takes **5** arguments `(encoding, object, start, end, reason)` and defines a `__str__` that assembles them into a sentence :

```python
>>> b"\x80abc".decode("utf-8")
UnicodeDecodeError: 'utf-8' codec can't decode byte 0x80 in position 0: invalid start byte
```

Rule of thumb : forward to `super().__init__()` the values that *define* the error, and let `__str__` build the sentence (_cf._ [`__str__` vs `__repr__`](https://www.geeksforgeeks.org/python/str-vs-repr-in-python/)).

### How do I attach extra data to my exception ?

Pass it positionally to `super().__init__()` **and** bind it as a named attribute, so handlers can read it without parsing the message :

```python
class HTTPError(Exception):
    def __init__(self, status_code, reason):
        super().__init__(status_code, reason)   # keeps args/__str__/__repr__ honest
        self.status_code = status_code
        self.reason = reason
```

### How do I build a message from the argument, like `ValueError` does ?

`ValueError` embeds the offending input in its message (`invalid literal for int() with base 10: 'abc'`). To get the same, the message has to be built **in the body of `__init__`**, at call time :

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

My first reflex was to write the default in the signature, `message: str = f"The {food} has gone off."`. It does not work : **defaults are evaluated once, at `def` time**, where `food` does not exist yet → `NameError` the moment the class is defined. Same mechanism as the mutable default argument trap (`def f(x=[])`) : signature evaluated at definition, body at each call.

- `None` : the sentinel for "the caller gave no message" ; test it with `is`, not `==`.
- `super().__init__(message)` : receives exactly **one** already-formatted string, so `str(e)` prints the bare sentence (see the `args` table above).
- `self.food` : the raw datum survives as an attribute, like `AttributeError.name` in the stdlib. The message itself lives **only** in `args`.
- `str | None` : requires Python 3.10+ ; below that, `typing.Optional[str]`.

### When do I write my own instead of using a built-in ?

Use a built-in (`ValueError`, `TypeError`, ...) whenever one fits. Write my own only for **domain errors** that callers must be able to catch *separately* from everything else.

And when I do, the stdlib and the big packages (`requests.RequestException`, the `OSError` family) all use the same shape : one base exception per domain, specific errors derived from it.

```python
class FridgeError(Exception): ...
class NoCheeseError(FridgeError): ...
class DoorStuckError(FridgeError): ...
```

- `except NoCheeseError:` : surgical, one failure mode.
- `except FridgeError:` : the whole family, because `except` matches subclasses.
- Order matters : subclass handlers **before** the base handler, otherwise the base catches everything first (_cf._ [[python_try_except_raise]]).

## Anti-patterns

```python
# BAD — super() called empty: args == (), print(e) shows a blank line,
# repr(e) is 'BrokenError()', copy/pickle break
class BrokenError(Exception):
    def __init__(self, message="oops"):
        super().__init__()
        self.message = message
```

- **`self.message` without feeding `args`** : invisible to `str(e)` and to the traceback.
- **f-string default in the signature** : `NameError` at class definition, never the per-call value.
- **Docstring as default message** (`super().__init__(msg or self.__doc__)`) : breaks under `python -OO`, where docstrings are stripped → `None`.
- **Reimplementing `__str__`** to carry the message : pointless in the simple case, the inherited one already does the right thing once `args` is correct.
- **Logic in the exception class** : exceptions are data carriers, behavior belongs in the code that raises and catches them.

## Defense-day one-liner

> The message lives in `args`, filled by `super().__init__()`. My default value on the `message` parameter means `raise MyError` still produces a proper message, and catching the base class catches the whole family because `except` matches subclasses.

## Reference

- https://peps.python.org/pep-0352/ — the `args`/`str()` contract, removal of `.message`
- https://docs.python.org/3/tutorial/errors.html#user-defined-exceptions
- https://docs.python.org/3/library/exceptions.html
- https://peps.python.org/pep-0008/#exception-names — naming convention
- [discuss.python.org — pythonic way of setting a default message](https://discuss.python.org/t/whats-the-pythonic-way-of-setting-default-message-on-custom-exception/92527)
- [Sean Hammond — Designing Python Exception Classes](https://www.seanh.cc/2019/06/20/python-custom-exception-classes/)
- *Python Cookbook* 3rd ed., recipe 14.8 "Creating Custom Exceptions"
