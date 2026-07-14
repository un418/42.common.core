## Class

A class is a user-defined **template** for creating objects.
It bundles data and functions together, making it easier to manage and use them.
When we create a new class, we define a new type of object.
We can then **create multiple instances** of this object type.

- https://docs.python.org/3/tutorial/classes.html
- https://www.geeksforgeeks.org/python/python-classes-and-objects/
- https://www.geeksforgeeks.org/python/__init__-in-python/

## Object

An object is a specific **instance** of a class.
It holds its own set of data (instance variables) and can invoke methods defined by its class. Multiple objects can be created from same class, each with its own unique attributes.

## Initiate Object with __init__()

[__init__()](https://www.geeksforgeeks.org/python/__init__-in-python/) method acts as a constructor and is automatically executed when an object is created.
It is used to initialize the attributes of the object with the values provided at the time of object creation.

```python
class Dog:
    species = "Canine"  # Class attribute

    def __init__(self, name, age):
        self.name = name  # Instance attribute
        self.age = age  # Instance attribute

# Creating an object of the Dog class
dog1 = Dog("Buddy", 3)

print(dog1.name)
print(dog1.species)

```

## Increment / Decrement in Python

-
- https://www.geeksforgeeks.org/python/g-fact-21-increment-and-decrement-operators-in-python/

```python
#increment
i+=1
i=i+1
#decrement
i-=1
i=i-1
```

## ex4

- https://www.geeksforgeeks.org/python/input-validation-in-python/
- https://www.geeksforgeeks.org/python/encapsulation-in-python/
- https://www.geeksforgeeks.org/python/python-property-decorator-property/
- [Floats in Python](../02_Python/python_floats.md) — `round()` vs `:.1f` vs type promotion

### Why not `@property`, even though it is the pythonic way

**It is not authorized.** `property` is not a Python keyword (`'property' in keyword.kwlist`
is `False`), it is a builtin. The subject only exempts "fundamental language keywords such
as `class` and `def`".
Proof that builtin decorators must be listed: ex6 explicitly authorizes `staticmethod()` and `classmethod()`, which are the same kind of object. ex4 authorizes `print()`, `range()`, `round()` only.

**It also cannot produce the expected output.** In Python an assignment is a *statement*,
not an expression: `plant.height = -5` evaluates to nothing. A property setter therefore
has no way to return a status to the caller — its only outbound channel is `raise`.
But the subject's example needs the caller to react:

```
Rose: Error, height can't be negative   <- printed by the class
Height update rejected                  <- printed by main(), so main must KNOW it failed
```

Hence explicit `set_height()` / `set_age()` returning a bool. The subject is not being
old-fashioned, it is matching the behaviour it asks for.

### The pythonic version, for reference

Real-world Python starts with a plain public attribute and only converts it to a property
once validation is needed.
Thanks to the *uniform access principle*, `dog.age = 3` keeps
working, so no calling code breaks — this is why Java-style `get_x()`/`set_x()` written
"just in case" is an anti-pattern in Python.

```python
class Dog:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self.age = age          # goes through the setter below

    @property
    def age(self) -> int:       # getter: read as `dog.age`
        return self._age

    @age.setter
    def age(self, value: int) -> None:   # written as `dog.age = 5`
        if value < 0:
            raise ValueError("age can't be negative")
        self._age = value
```

Note `__init__` assigns `self.age`, not `self._age`: the constructor reuses the setter,
so validation lives in exactly one place. That single-source-of-truth idea *does* apply
to ex4, even with explicit methods.

The truly idiomatic error handling is `raise ValueError(...)`, caught by the caller with
`try`/`except`. The subject makes you print a message instead because exceptions come in
module 02 — what you write here is a pedagogical step, not the destination.

### Defense answer

> In idiomatic Python I would use `@property`, which keeps `plant.height = 25` on the
> caller side while still validating. Here the subject requires explicit accessors, and
> anyway a property setter cannot return anything — an assignment is a statement, so it
> can only raise. With plain methods I return a bool and let the caller decide.

## ex5
- https://www.geeksforgeeks.org/python/inheritance-in-python/

# ToDo

- [x] ex1 & ex2 : Try to use \_\_str\_\_() instead of show()
- [x] Redo the [quizz](https://www.geeksforgeeks.org/python/python-classes-and-objects/)
- [x] Uniformize usage of :1.f with print
- [x] Uniformize naming between exercices
- [x] Rewiew grow() implementation
- [x] ex6 - implem encapsulation for stats
