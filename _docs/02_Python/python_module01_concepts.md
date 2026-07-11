# Python Module 01 — Concepts Guide (OOP)


## 1. Ex0 — Program structure & `if __name__ == "__main__":`

### The concept

Every Python file has a built-in variable `__name__`:

- When the file is **executed directly** (`python3 file.py`), Python sets
  `__name__ = "__main__"`.
- When the file is **imported** from another file (`import file`), Python sets
  `__name__ = "file"` (the module's name) — and **executes the whole file top to
  bottom** during the import.

So `if __name__ == "__main__":` guards code so it only runs on direct execution,
never on import. It marks the program's **entry point**.

### Understanding check — expect these exact questions

**Q: "What could happen if you remove the `if __name__ == "__main__":` line?"**
The program still works when run directly, but if anyone imports the file, all the
top-level code (prints, tests, object creation) runs immediately as a side effect of
the import. You lose control over *when* the code executes.

**Q: "When would this code NOT run?"**
When the file is imported as a module instead of executed directly — `__name__` is then
the module name, not `"__main__"`, so the guarded block is skipped.

**Q: "Why is this pattern important?"**
It separates *reusable definitions* (classes, functions) from *executable script code*.
It's the foundation for imports (an upcoming project): your classes can be imported
elsewhere without triggering your test code.

### The shebang — you WILL be asked to live-edit this

The subject warns: *"The evaluation will ask you to update your script live to use this
shebang."* Know it cold:

```python
#!/usr/bin/env python3
```

- It must be the **very first line** of the file.
- It tells the OS which interpreter to use when the file is executed **as a program**
  (`./ft_garden_intro.py`) instead of via `python3 ft_garden_intro.py`.
- `/usr/bin/env python3` finds `python3` in the user's `PATH` (portable), versus
  hard-coding a path like `/usr/bin/python3`.
- The file also needs the execute permission: `chmod +x ft_garden_intro.py`.
- Without a shebang, `./file.py` fails (or is run by the shell); `python3 file.py`
  works either way because you named the interpreter yourself.

The eval sheet asks to launch the program **with and without a shebang** — practice both.

---

## 2. Ex1 — CLASSES (data organization)

### The concept

A **class** is a blueprint/model that describes what data (attributes) and behavior
(methods) a kind of object has. An **object** (or **instance**) is one concrete thing
built from that blueprint.

```python
class Plant:            # blueprint (PascalCase)
    ...

rose = Plant()          # instantiation: creating an instance
rose.name = "Rose"      # attribute: data attached to THIS instance
```

Vocabulary you must use correctly at defense:

- **Class definition**: the `class Plant:` block.
- **Instantiation**: calling the class like a function (`Plant()`) to create an object.
- **Attribute**: a variable attached to an instance (`self.name`).
- **Instance**: one object created from the class; each instance holds its own data.

### Why a class instead of separate variables?

With plain variables, 3 plants × 3 properties = 9 unrelated variables (`rose_name`,
`rose_height`, …). It doesn't scale, and nothing groups the data. A class bundles the
data of *one* plant together, and the same model works for 3 or 3000 plants. This is
the "what challenges might arise with more plants?" question from the subject.

Ex1 also requires a `show()` method in the class to display a plant — one place that
knows how to print a plant, reused everywhere.

---

## 3. Ex2 — METHODS (behavior & state changes)

### The concept

A **method** is a function defined *inside* a class. It represents an **action the
object can perform**, and it can read/modify the object's own data through `self`.

```python
class Plant:
    def grow(self) -> None:
        self._height += self._growth_rate
```

### `self` — be ready to explain it

`self` is the instance the method was called on. `rose.grow()` is equivalent to
`Plant.grow(rose)`: Python passes the object as the first parameter automatically.
That's how the same method can act on different objects.

### Key points the evaluator verifies

- **Method definition within a class** (indented under `class`, first param `self`).
- **Method calls on instances**: `rose.grow()`, not `grow(rose)`.
- **State changes are persistent**: after `grow()`, the new height is stored in the
  object — calling `show()` later reflects it. State lives in the instance, not in
  the method.
- **Multiple calls accumulate**: 7 days of growth = 7 calls, each building on the
  previous state.
- The subject hints that *different plants can evolve differently* — e.g. a per-plant
  growth rate attribute that `grow()` uses, so behavior is data-driven.

---

## 4. Ex3 — INITIALIZATION with `__init__`

### The concept

`__init__` is the **initializer** (commonly called the constructor). Python calls it
automatically when you instantiate the class, so the object is created *and* filled
with its initial data in one step:

```python
class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self._name = name
        self._height = height
        self._age = age

oak = Plant("Oak", 200.0, 365)   # ready to use immediately
```

### What to be able to explain

- **What `__init__` does and why it's needed**: without it, you create an empty object
  then assign attributes one by one from outside — error-prone (forgotten attribute →
  `AttributeError` later) and repetitive. With it, every object is **guaranteed to be
  ready to use immediately after construction**.
- **Parameter passing during object creation**: arguments given to `Plant(...)` go to
  `__init__` after `self`.
- **Multiple objects, different initial values**: each call creates an independent
  instance with its own state (ex3 requires ≥ 5 different plants).
- `__init__` returns `None` (annotate it `-> None`); the *instantiation expression*
  returns the new object. `__init__` doesn't create the object — it initializes an
  object that already exists (creation is `__new__`'s job; nice bonus point if asked).

The ex3 output must reuse `show()` **unchanged** — a sign your class design was right.

---

## 5. Ex4 — ENCAPSULATION (data protection)

### The concept

**Encapsulation** = bundling data with the methods that operate on it, and
**restricting direct access** to the data so the class controls every read and write.
Purpose: protect data integrity — invalid states (negative height/age) become
impossible to reach through the public interface.

### The `_` protected convention — NOT name mangling

The subject explicitly requires the **"protected" convention, not mangling**:

| Prefix | Meaning | Enforced? |
|---|---|---|
| `name` | public | — |
| `_name` | **protected by convention**: "internal, don't touch from outside" | No — it's a social contract between developers |
| `__name` | **name mangling**: Python renames it to `_ClassName__name` | Sort of — makes accidental access/override harder. **Not what's asked here** |

Be ready to say it out loud: *Python has no real `private`. The single underscore is a
convention that signals "access this only through the class's methods". It still works
if you access it directly, but you're breaking the contract.*

### Getters and setters

Controlled access goes through methods:

- `get_height()`, `get_age()` — safe **read** access.
- `set_height(value)`, `set_age(value)` — **write** access with **validation before
  storing**: negative values are rejected, an error message is printed **from the
  class**, and the data is left **unchanged** (or the plant is created with default
  values if the invalid value came in at construction time).

### Test scenarios the evaluator runs

- Valid updates work; invalid updates are rejected **with a message** and state is
  untouched afterwards (the example shows `Current state:` still valid at the end).
- Invalid values at `__init__` time are also caught (eval sheet: *"during
  initialization or in later updates"*).
- No crash on invalid input — reject, print, continue.

---

## 6. Ex5 — INHERITANCE (specialized types)

### The concept

**Inheritance** lets a class (child / derived) reuse and extend another class (parent /
base). The child automatically gets all attributes and methods of the parent, and adds
or replaces what makes it special.

```python
class Flower(Plant):                      # Flower IS-A Plant
    def __init__(self, name: str, height: float, age: int, color: str) -> None:
        super().__init__(name, height, age)   # let Plant set up the common part
        self._color = color
```

The point: **code reuse** — common features (name, height, age, grow, age, show) live
once in `Plant`; each subclass only adds its own delta. The subject insists: *avoid
duplicating common plant code across specialized types*.

### The class hierarchy required

```
Plant  (base: name, height, age, grow(), age(), show(), getters/setters)
├── Flower     + color, bloom()
├── Tree       + trunk_diameter, produce_shade()
└── Vegetable  + harvest_season, nutritional_value (starts at 0,
               grows when age()/grow() are called → method override)
```

### `super()` — must be able to explain it

`super()` returns a proxy to the **parent class**, letting you call the parent's
version of a method from the child. Two required uses:

- `super().__init__(...)` inside the child's `__init__`: initialize the inherited
  attributes without re-writing that code.
- `super().show()` inside an overridden `show()`: print the common part, then append
  the specialized lines (color, trunk diameter, …).

### Method overriding

Defining a method with the **same name** in the child **replaces** the parent's version
for instances of the child. Python looks the method up on the instance's class first,
then walks up the parent chain (the **MRO**, Method Resolution Order — good keyword to
drop at defense). The eval sheet requires at least `show()` overridden, either by
calling `super().show()` and adding lines, or by fully re-implementing it.

`Vegetable` also overrides `grow()`/`age()` to increase `nutritional_value`, calling
`super().grow()` / `super().age()` so the base behavior still happens.

### Overriding vs overloading (classic trap question)

- **Overriding**: same signature redefined in a subclass → runtime polymorphism. Exists
  in Python.
- **Overloading**: several methods with the same name but different parameter lists.
  Python does **not** support it (the last `def` wins); you use default arguments or
  `*args` instead.

---

## 7. Ex6 — ADVANCED OOP (Garden Analytics)

This exercise combines five concepts. The eval sheet says the evaluator will ask you to
**explain each one you implemented** — and discuss *when to use which*.

### 7.1 Instance methods vs class methods vs static methods vs functions

| Kind                    | First param | Receives         | Typical use                                                                         | Called as                          |
| ----------------------- | ----------- | ---------------- | ----------------------------------------------------------------------------------- | ---------------------------------- |
| **Instance method**     | `self`      | the instance     | read/change *this object's* state (`grow()`)                                        | `obj.method()`                     |
| **Class method**        | `cls`       | the class itself | **alternative constructors** / behavior about the class as a whole                  | `Class.method()` or `obj.method()` |
| **Static method**       | none        | nothing implicit | utility logically tied to the class but needing neither instance nor class state    | `Class.method()`                   |
| **Non-member function** | —           | nothing          | operations that don't belong to any class, or that operate *across* several classes | `func(obj)`                        |

```python
class Plant:
    @staticmethod
    def is_older_than_a_year(age: int) -> bool:      # required by ex6
        return age > 365

    @classmethod
    def anonymous(cls) -> "Plant":                    # required by ex6
        return cls("Unknown plant", 0.0, 0)           # alternative constructor
```

Both `@decorator` syntax and the explicit call form
(`is_older = staticmethod(is_older)`) are accepted — know that both exist.

**"When to use each type of method?"** (Advanced concepts discussion — prepare this
answer):

- Needs the object's data → **instance method**.
- Creates or describes instances without having one yet (factory, "anonymous plant"),
  or must behave correctly through inheritance (`cls` is the *actual* subclass, so
  `Flower.anonymous()` would build a `Flower`) → **class method**.
- Pure helper about the domain, no state at all (checking whether an age exceeds a
  year) → **static method**: it groups the function under the class's namespace for
  discoverability.
- Works generically on objects from the outside, spans multiple classes, or is a
  program-level utility → **plain function**.

### 7.1b What the decorators actually do (technical / performance)

**No compilation effect.** A decorator is runtime syntactic sugar, executed **once**
when the class block is defined:

```python
class Fruit:
    @classmethod
    def from_string(cls, raw): ...

# strictly equivalent to:
class Fruit:
    def from_string(cls, raw): ...
    from_string = classmethod(from_string)
```

`classmethod` and `staticmethod` are built-in classes that **wrap the function in a
wrapper object** stored in the class dict (`Fruit.__dict__`). The function's body and
bytecode are untouched — only the *type of the stored object* changes.

**The real mechanism: the descriptor protocol.** The difference plays out at
**attribute access** (`obj.method`). If the object found on the class defines
`__get__`, Python calls it to produce what you actually get back:

- plain function → `__get__` returns a **bound method** (remembers the instance,
  injects `self`);
- `classmethod` → `__get__` binds to the **class** (injects `cls`, whether accessed
  via the instance or the class);
- `staticmethod` → `__get__` returns the **raw function**, no binding, nothing
  injected.

Visible in the REPL:

```python
>>> Fruit.__dict__["from_string"]
<classmethod object at 0x...>            # wrapper object in the class dict
>>> f.describe
<bound method Fruit.describe of ...>     # result of __get__ on a plain function
>>> f.is_valid_name
<function Fruit.is_valid_name at 0x...>  # staticmethod → raw function, not bound
```

**Performance**: negligible.

- The decorator itself costs one call at class definition — zero cost per call.
- At call time the only difference is the binding step; a staticmethod skips bound
  method creation (nanoseconds), and CPython optimizes `obj.method()` aggressively
  anyway (specialized opcodes since 3.7, improved in 3.11+).

So the choice is **never** about performance — it expresses intent to the reader and
to mypy: which implicit first argument the method receives (`self`, `cls`, or none).

One-sentence defense answer: *the decorators wrap the function in an object whose
`__get__` changes what gets auto-injected as first argument at attribute access —
they don't modify the function itself, and the cost is paid once at class definition.*

### 7.2 Nested classes (class within a class)

A class defined inside another class:

```python
class Plant:
    class Stats:                 # nested class
        def __init__(self) -> None:
            self._grow_calls = 0
            ...
```

Each `Plant` creates its own `Stats` instance (e.g. in `__init__`:
`self._stats = Plant.Stats()`), which encapsulates the counters (grow/age/show call
counts) plus a display method. The outer class's methods increment the counters.

**"Benefits of nested classes?"** (prepare this answer):

- **Namespacing / signaling ownership**: `Stats` only makes sense in the context of a
  `Plant`; nesting states that relationship in the code itself.
- **Encapsulation of a helper component**: the statistics system is an internal detail
  of `Plant`, not a top-level concept of the program.
- Honest nuance worth saying: Python nested classes are mostly *organizational* — the
  inner class gets no special access to the outer instance (unlike Java inner classes).

**Nested class override through inheritance** (explicitly on the eval sheet): a
subclass can define its **own nested class with the same name**, replacing the parent's
version for that subclass — e.g. `Tree.Stats` extends/overrides `Plant.Stats` to add
the `produce_shade()` counter. For the override to take effect, the attribute lookup
must go through the actual class (e.g. instantiate via `self.Stats()` /
`type(self).Stats()` rather than hard-coding `Plant.Stats()` — that lookup respects
inheritance the same way method lookup does).

### 7.3 Inheritance chains (A → B → C)

Required chain: `Plant → Flower → Seed`. `Seed` inherits from `Flower` (which inherits
from `Plant`), adds a seed count once bloomed, and improves `show()` accordingly.

- Each level's `__init__`/`show()` calls `super()` so the whole chain runs:
  `Seed.show()` → `Flower.show()` → `Plant.show()`.
- **"Explain the inheritance chain design choices"** (prepare): each level adds exactly
  one layer of specialization; a Seed *is a* Flower *is a* Plant, so anything that
  works on a Plant (like the standalone stats function) works on a Seed for free —
  that's **polymorphism**. Deep chains have costs too (rigidity), which is why you keep
  them short and meaningful.

### 7.4 The standalone statistics function (required, and specifically tested)

One function, **outside any class**, that displays statistics **for any kind of
plant**:

- Takes a `Plant` (type-hinted as such) as parameter.
- Calls the display method of the plant's nested stats class.
- Works for `Flower`, `Tree`, `Seed`, anonymous plants… because they are all `Plant`s
  — this demonstrates **polymorphism**: same call, behavior adapted to the actual type
  (a Tree's stats also show shade calls).

This is the "non-member function" checkbox *and* the polymorphism proof in one.

### 7.5 Forward references — why `-> "Plant"` has quotes

The classmethod in 7.1 annotates its return type as the class it lives in. Written
without quotes, it crashes at import time:

```python
class Plant:
    @classmethod
    def anonymous(cls) -> Plant:      # NameError: name 'Plant' is not defined
        ...
```

**Why**: Python executes a `class` block line by line and binds the name `Plant` only
**after the whole block finishes**. But annotations in a `def` signature are ordinary
expressions, **evaluated immediately at definition time** — so line by line, `Plant`
doesn't exist yet when the annotation is evaluated. A class can't name itself in its
own annotations (naively).

**The fix — a forward reference (PEP 484)**: write the annotation as a **string**
containing the type name:

```python
    @classmethod
    def anonymous(cls) -> "Plant":    # string → never evaluated at runtime
        ...
```

Who reads that string:

- **mypy** parses it as code — `"Plant"` and `Plant` are strictly equivalent to the
  type checker, no checking is lost.
- **The runtime** stores it as-is in `__annotations__` and never evaluates it
  spontaneously (tools that need the real type later use `typing.get_type_hints()`,
  which resolves strings once the class exists).
- **flake8** knows the pattern — no more F821.

**Trap this teaches**: mypy said `Success` on the unquoted version while the program
crashed on launch — mypy analyzes statically without executing anything. *mypy clean ≠
code that runs.*

Typical use cases: a class referencing itself (this one), two mutually-referencing
classes, referencing a class defined further down the file.

Alternatives to know:

- `from __future__ import annotations` (PEP 563) at the top of the file makes **all**
  annotations lazy strings automatically — same effect, file-wide instead of local.
- `typing.Self` is purpose-built for "returns an instance of the current class" but is
  **Python 3.11+** — grading targets 3.10, so stick to the string form.

One-sentence defense answer: *annotations are evaluated at definition time, but the
class binds to its name only at the end of its `class` block, so we defer evaluation by
using a string that mypy knows how to read.*

---

## 8. Concept cheat-sheet (uppercase words from the eval sheet)

| Eval keyword                    | One-sentence definition to say out loud                                                                                                                 |
| ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **CLASS**                       | A blueprint describing the attributes and behaviors shared by all objects of one kind.                                                                  |
| **METHODS**                     | Functions defined in a class that act on an instance through `self`, changing or reading its state.                                                     |
| **`__init__` / INITIALIZATION** | The method Python calls automatically at instantiation so every object starts complete and valid.                                                       |
| **ENCAPSULATION**               | Keeping data internal (`_attr` convention) and forcing access through methods that validate, so invalid states can't happen.                            |
| **INHERITANCE**                 | A child class reuses a parent's attributes/methods and adds or overrides only what's special — code reuse plus specialization.                          |
| **ADVANCED OOP**                | Nested classes, A→B→C chains, `@classmethod`/`@staticmethod` vs instance methods vs plain functions, and overriding nested classes through inheritance. |
| **super()**                     | Proxy to the parent class, used to run the parent's version of a method (esp. `__init__`, `show()`) from the child.                                     |
| **Polymorphism**                | Code written against the base type (`Plant`) works with any subclass; each object responds with its own overridden behavior.                            |

---
