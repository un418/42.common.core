# Python Module 10 — Concepts Guide (Functional Programming: Lambdas, Higher-Order Functions, Closures, `functools` & Decorators)

> Subject: *FuncMage — Master the Ancient Arts of Functional Programming* (`_subjects/en.python_mod10.subject.pdf`, v3.2). Eval sheet: `42.secret.repo/P10/Intra Projects Python Module 10 Edit.pdf`. Python ≥ 3.10, flake8 clean, **type hints for all function signatures and return types** (docstrings explicitly *not* required). Authorized: `typing`, `itertools`, `collections.abc` for `Callable`, all builtins, standard library as needed; `functools` and `operator` **only where an exercise lists them**. **Forbidden: external libraries, file I/O, `eval`/`exec`, and global variables.** Five exercises, one file each, `ex0/` … `ex4/`.

---

## 0. The big picture — "the function is the data"

Every previous module treated functions as *places where code lives*. This one treats them as **values**: sortable keys, arguments, return values, dictionary entries, things you wrap. The foreword states it outright — *"functions are first-class citizens in Python, meaning they can be passed around, stored in variables, and transformed just like any other data."*

The five exercises are one idea stepped up five times.

| Ex  | Concept                        | Question it answers                                                     | The mechanism |
| --- | ------------------------------ | ------------------------------------------------------------------------ | ------------- |
| ex0 | **Lambda**                     | How do I write a function where an expression is expected?               | anonymous function objects |
| ex1 | **Higher-order functions**     | How do I take a function in and hand a new one back?                     | functions as parameters and return values |
| ex2 | **Closures & lexical scoping** | How does a returned function *remember* where it was born?               | free variables captured in cells |
| ex3 | **`functools` / `operator`**   | Which of these patterns are already in the standard library?             | `reduce`, `partial`, `lru_cache`, `singledispatch` |
| ex4 | **Decorators**                 | How do I change a function's behaviour without editing it?               | a higher-order function + `@` syntax |

### The dependency chain — why the order is not negotiable

```
   ex0  a function is a VALUE               sorted(key=<function>)
     │
     ▼
   ex1  a function can RETURN a function    def amplify(spell) -> Callable
     │        │
     │        └── the returned function needs to remember `spell`…
     ▼
   ex2  …that memory is a CLOSURE           free variable in a cell, nonlocal to rebind
     │
     ├──▶ ex3  functools = closures + HOFs, already written and optimized
     │
     └──▶ ex4  a DECORATOR is exactly ex1 + ex2 + @ syntax
                  ┌──────────────────────────────────────┐
                  │  @deco  ⟺  func = deco(func)         │
                  └──────────────────────────────────────┘
```

**A decorator is not a new concept.** It is a higher-order function (ex1) that returns a closure (ex2), with one line of syntax on top. If you can say that sentence and then draw the arrow from ex1 through ex2 to ex4, you have explained the module. The eval sheet's *Code Quality and Understanding* section asks for exactly these five explanations, in this order.

### The one caveat: Python is not a functional language

It is a language with functional *features*. `map`/`filter` exist, but comprehensions are the idiomatic replacement; `reduce` was demoted out of builtins in Python 3; lambdas are deliberately crippled. This subject makes you use the functional forms **so that you understand them**, and it is worth being able to say where you would actually reach for them in production and where you would not. Knowing the objection is stronger than not knowing it exists.

---

## 1. Ex0 — LAMBDA (`lambda_spells.py`)

### The concept

`lambda` is an **expression that evaluates to a function object**. `def` is a **statement that binds a function object to a name**. Same kind of object — `lambda` just has no name and fits where only an expression is allowed.

```python
add = lambda a, b: a + b          # ⚠️ legal, but flake8 E731 — this is what def is for
sorted(items, key=lambda x: x["power"])   # ✅ the only place a lambda earns its keep
```

| | `lambda` | `def` |
| --- | --- | --- |
| Is a | expression | statement |
| Body | **exactly one expression**, implicitly returned | any block of statements |
| Statements allowed | none — no `if`/`for`/`try`/`return`/assignment | all |
| Type annotations | **impossible** on parameters or return | required by this subject |
| `__name__` | `"<lambda>"` | the real name — matters in tracebacks |
| Docstring | none | yes |
| Typical use | passed inline as an argument | everything else |

### The trap the subject sets

> *"You must use lambda expressions for all transformations. Do not use the 'def' keyword to create named functions for simple operations."*

…while flake8 enforces **E731 `do not assign a lambda expression, use a def`**. Both are satisfiable at once, and noticing how is the point: **a lambda should be passed, never bound to a name.** The four required `artifact_sorter` / `power_filter` / `spell_transformer` / `mage_stats` are `def`s — they are the module's API, they carry annotations, they are not "simple operations". The lambdas live *inside* them, as arguments to `sorted`, `filter`, `map`, `max`, `min`.

### The builtins in play

| Builtin | Returns | Watch out |
| ------- | ------- | --------- |
| `sorted(it, key=…, reverse=True)` | a **new list** | key is called **once per element**, not per comparison; the sort is **stable** |
| `filter(pred, it)` | a **lazy iterator** | `list(...)` it, or the reviewer sees `<filter object at 0x…>` |
| `map(func, it)` | a **lazy iterator** | same |
| `max(it, key=…)` / `min(it, key=…)` | **the element**, not the key value | `ValueError` on an empty iterable unless `default=` is given |
| `sum`, `len`, `round` | — | see the rounding note below |

Two details worth having ready:

- **`max(mages, key=lambda m: m["power"])` returns the mage**, so the power level is one attribute access away. If you want the value directly you'd map first — and mapping first loses *which* mage it was. Know which one each of your functions needs.
- **`round()` is not schoolbook rounding.** It is round-half-to-even (banker's rounding), and it operates on binary floats: `round(2.675, 2)` gives `2.67`. For an average of integers this is harmless, but be able to say *why* it happens if the reviewer's generated data lands on a tie.

### `sorted` vs `list.sort`, and the key you were not allowed to use

`sorted` returns a new list; `list.sort()` sorts in place and returns `None`. Returning the result of `.sort()` is a `None`-shaped bug, and "return the sorted list" in the subject points at `sorted`.

`operator.itemgetter("power")` is the faster, clearer alternative to `lambda a: a["power"]` — and it is **not authorized in ex0** (it arrives in ex3). Mention it at defense as the thing you would write outside the exercise; it shows the constraint was a choice, not a limit.

### Understanding check — the subject's own

> *"How do lambda expressions make code more concise? When should you use lambda vs. regular function definitions?"*

The short answer that lands: **a lambda is worth it when naming the function would be noise** — a one-expression key, predicate, or transformation used exactly once, at the site where it is read. The moment it needs a name, a second line, an annotation, or a docstring, `def` is not a heavier tool, it is the correct one.

---

## 2. Ex1 — HIGHER-ORDER FUNCTIONS (`higher_magic.py`)

### The concept

A **higher-order function** takes a function as an argument, returns a function, or both. It is possible because functions are **first-class objects**: created at runtime, bound to names, stored in containers, passed, returned, given attributes.

```python
def double_it(f):                  # takes a function
    def wrapper(*args):            # …returns a new one
        return f(*args) * 2
    return wrapper
```

The four required functions cover all the shapes:

| Function | Takes | Returns | Pattern |
| -------- | ----- | ------- | ------- |
| `spell_combiner(s1, s2)` | two functions | one function → tuple of both results | **fan-out / parallel combination** |
| `power_amplifier(spell, n)` | function + data | one function with the **same signature** | **argument transformation** |
| `conditional_caster(cond, spell)` | two functions | one function, guarded | **predicate + action**, `"Spell fizzled"` on refusal |
| `spell_sequence(spells)` | a list of functions | one function → list of results | **fan-out over a collection** |

Every one of them returns a function that references a parameter of the enclosing call — which means **every one of them is already a closure**. Ex2 only names the thing you built here.

### The contract, and why it matters

> *"Every spell in your grimoire follows the same contract: `def spell(target: str, power: int) -> str`"*

A shared signature is what makes these combinators possible at all — `spell_combiner` can call both spells with the same arguments only because every spell accepts the same arguments. That is the same "program to an interface" idea as module 07, expressed with functions instead of ABCs. Naming that parallel out loud is a strong defense move; a `Spell` type alias makes it visible in the code:

```python
from collections.abc import Callable

Spell = Callable[[str, int], str]     # the contract, written down once
```

`power_amplifier` is the one that tests whether you understood the contract: it *"returns a function with the same signature as the original spell"* — so the returned object must still be `(target, power) -> str`, and the multiplication happens to `power` **on the way in**, not to the result string on the way out.

### `Callable` — the subject asks explicitly

> *"From which package is it recommended to use `Callable`? What is the purpose of `callable()`?"*

Two different things with almost the same name:

| | `Callable` | `callable()` |
| --- | --- | --- |
| What | a **typing** construct | a **builtin function** |
| From | **`collections.abc`** (since 3.9 / PEP 585) — *not* `typing.Callable`, which is deprecated | nowhere, it's a builtin |
| Used for | annotations: `Callable[[str, int], str]` | a runtime check: does this object have `__call__`? |
| At runtime | erased — annotations do nothing | actually executes |

`Callable[[str, int], str]` reads "takes a `str` and an `int`, returns a `str`". A bare `Callable` means `Callable[..., Any]` — it type-checks nothing. The subject's own signatures use the bare form for brevity; parameterising them is strictly better and the subject rewards understanding over transcription.

`callable(x)` is the runtime counterpart: `True` for functions, lambdas, classes, `functools.partial` objects, and any instance whose class defines `__call__`. It answers "can I put parentheses after this?" — useful for validating a `condition` argument before calling it.

### Understanding check — the subject's own

> *"How do higher-order functions enable code reuse and composition? What makes functions 'first-class citizens' in Python?"*

For the second half, don't recite the definition — **demonstrate** it: a function has `__name__`, `__doc__`, `__code__`, can be given arbitrary attributes, can sit in a dict as a value, and `def` is itself just a binding operation. Showing `spells = {"fire": fireball}` and calling `spells["fire"](...)` is the two-second proof.

---

## 3. Ex2 — CLOSURES & LEXICAL SCOPING (`scope_mysteries.py`)

### The concept

A **closure** is a function plus the environment it was defined in. When an inner function references a name from its enclosing function, Python does not copy the value — it keeps the enclosing scope's **cell** alive, and the inner function holds a reference to it.

```python
def make_counter():
    count = 0                 # a free variable, seen from the inner function
    def tick() -> int:
        nonlocal count        # "rebind the ENCLOSING count, don't create a local one"
        count += 1
        return count
    return tick               # make_counter has returned — but `count` is still alive
```

The machinery is inspectable, and showing it during the review is worth more than describing it:

```python
tick.__code__.co_freevars     # ('count',)   ← which names were captured
tick.__closure__              # (<cell at 0x…: int object at 0x…>,)
tick.__closure__[0].cell_contents   # the current value
```

**Every call to `make_counter()` creates a fresh cell.** That is why two counters are independent — the eval sheet checks exactly this (*"Create multiple counters and verify they maintain separate state"*), and the one-sentence answer is "each call to the factory builds a new frame, so each closure captures a different cell".

### LEGB — the lookup order

```
   L ocal        names bound in this function
   E nclosing    the frames of lexically enclosing functions   ← where closures live
   G lobal       module level
   B uiltins     print, len, …
```

**Lexical (static) scoping** means the chain is determined by *where the code is written*, not by who called it. Python decides at **compile time** whether a name is local, free, or global — that is why `count += 1` without `nonlocal` raises `UnboundLocalError` rather than reading the outer value: the assignment made `count` local for the whole function body, including the read on its right-hand side.

### `global` vs `nonlocal` — the subject asks, and the eval sheet enforces

> *"Why is `global` forbidden, but `nonlocal` allowed? What are the key differences?"*

| | `global x` | `nonlocal x` |
| --- | --- | --- |
| Rebinds a name in | the **module** namespace | the **nearest enclosing function** scope |
| Requires the name to pre-exist | no — it can create it | **yes**, or it is a `SyntaxError` |
| Scope of the effect | the entire program | the one closure |
| Testability | shared mutable state, order-dependent, unresettable | state is per-instance and dies with the closure |

The reason the subject bans one and requires the other: **both mutate state, but only one of them keeps the state private.** A `global` counter is shared by every caller, cannot be created twice, and leaks between tests. A closure counter is created fresh per call, invisible from outside, and garbage-collected when dropped. That is encapsulation *without a class* — which is why the eval sheet also demands *"no class definitions"* in this exercise. `memory_vault()` is the proof: two functions, `store` and `recall`, sharing one private dict through their common enclosing scope. **A closure is an object with one method; an object is a closure with many.**

### The late-binding trap

The single most-asked closure question in any interview:

```python
fns = [lambda: i for i in range(3)]
[f() for f in fns]        # [2, 2, 2]  ← not [0, 1, 2]
```

The cell is captured, **not the value** — all three lambdas share the same `i`, read at call time, long after the loop finished. The fix is to force capture at definition time with a default argument (`lambda i=i: i`) or a factory function. Nothing in the exercise requires it, and being able to explain it anyway is exactly the kind of thing the *Understanding* section rewards.

### The four functions, and what each proves

| Function | Proves |
| -------- | ------ |
| `mage_counter()` | rebinding a free variable requires `nonlocal`; separate calls → separate state |
| `spell_accumulator(initial_power)` | the **parameter itself** is captured — a factory argument becomes persistent state |
| `enchantment_factory(type)` | a closure over a value that is never rebound — read-only capture needs no `nonlocal` |
| `memory_vault()` | **two** closures over **one** shared scope — the encapsulation punchline |

Note the third one carefully: mutating a captured mutable object (`d[k] = v`) is **not** rebinding, so `memory_vault` needs no `nonlocal` at all, while `mage_counter` does. Getting asked "why does one need `nonlocal` and the other doesn't?" is likely, and the answer is *rebinding a name versus mutating an object*.

---

## 4. Ex3 — `functools` & `operator` (`functools_artifacts.py`)

### The concept

Everything in ex1 and ex2 was hand-rolled. `functools` is the standard library's collection of the same patterns, written once, correctly, and fast. The exercise is a tour of four of them.

### `reduce` — fold a sequence into one value

```python
functools.reduce(operator.add, [1, 2, 3])        # ((1+2)+3) = 6
functools.reduce(operator.add, [], 0)            # 0  — the initializer saves you
functools.reduce(operator.add, [])               # TypeError: reduce() of empty iterable
                                                 #            with no initial value
```

> Eval sheet: *"What happens if you call reduce on an empty list without an initializer?"*

`TypeError`, and that is precisely why the subject specifies *"If spells is empty, return 0"* — either short-circuit before reducing, or pass an initial value. Note the second option is only *correct* for `add`; the identity element differs per operation (`0` for add, `1` for multiply), and for `max`/`min` there is no identity at all. That asymmetry is the interesting half of the exercise.

`operator` supplies `add`, `mul`, `sub`, `truediv`, `itemgetter`, `attrgetter` — function versions of the syntax operators. It has **no `max`/`min`**, because those are already builtins.

> Eval sheet: *"Ask the learner to explain how are handled 'min' and 'max'. Do you know other solutions?"*

Three answers, in increasing quality: a `lambda a, b: a if a > b else b` passed to `reduce`; the **builtin `max` used as the two-argument reducer** (`reduce(max, spells)` — `max` is itself a binary function, which is the neat one); or simply `max(spells)`, since reducing is what `max` already does. Have all three, and say which you'd ship.

### `partial` — freeze arguments

`functools.partial(f, *args, **kwargs)` returns a **callable object** (not a function) with some arguments pre-supplied.

```python
fire = functools.partial(enchant, power=50, element="fire")
fire(target="sword")          # enchant(power=50, element="fire", target="sword")
```

| Detail | Consequence |
| ------ | ----------- |
| `type(fire) is functools.partial` | **the eval sheet checks this literally** — a lambda wrapper fails the test |
| positional args are frozen from the left | they cannot be overridden later |
| keyword args are defaults | a later call **can** override them |
| `fire.func`, `fire.args`, `fire.keywords` | introspectable, unlike a lambda's captured cell |
| `callable(fire)` | `True` — a `partial` is not a function but is callable |

> Eval sheet: *"Does `partial_enchanter()` use `functools.partial` to create specialized functions (not lambdas wrapping calls)?"* … *"Verify `type(result['fire_enchant']) is functools.partial`"*

That check is the exercise's whole point. `lambda target: enchant(50, "fire", target)` does the same job and is *not* the same object — it is opaque, unpicklable, and reports `<lambda>` in a traceback. This is Effective Python's Item 39 (*Prefer `functools.partial` over lambda expressions for glue functions*), and citing it by name is free credit.

### `lru_cache` — memoization

```python
@functools.lru_cache(maxsize=None)      # or @functools.cache (3.9+), the same thing
def fib(n: int) -> int:
    return n if n < 2 else fib(n - 1) + fib(n - 2)
```

| Fact | Why it matters |
| ---- | -------------- |
| Naive recursive fib is **O(2ⁿ)**; memoized it is **O(n)** | the measurable point of the exercise |
| The recursive call must go through the **decorated** name | calling an inner undecorated helper caches nothing |
| Arguments must be **hashable** | a `list` argument raises `TypeError` |
| `fib.cache_info()` → `CacheInfo(hits, misses, maxsize, currsize)` | the eval sheet checks `hits > 0` after `fib(10)` then `fib(5)` |
| `fib.cache_clear()`, `fib.__wrapped__` | reset, and the original undecorated function |
| `maxsize=None` never evicts | on a long-lived process or a method, that is a memory leak |

> Eval sheet: *"What is the difference between memoization and simply storing results in a global dict?"*

The full answer: a global dict is a global variable (**forbidden here**), shared across every caller, never bounded, never evicted, has no thread-safety, no statistics, no reset, and must be keyed by hand — while `lru_cache` keeps the cache in the function's own closure, bounds it with an **LRU eviction policy**, is thread-safe, and gives you `cache_info()`. Same idea, and every difference is on the engineering side.

### `singledispatch` — polymorphism without classes

```python
@functools.singledispatch
def cast(spell) -> str:            # the fallback: unknown type
    return "Unknown spell type"

@cast.register
def _(spell: int) -> str: ...      # dispatch is read from the ANNOTATION
```

Dispatch is on the runtime type of the **first argument**, resolved through that type's MRO. Three consequences that make good questions:

- **`bool` is a subclass of `int`**, so `cast(True)` reaches the `int` handler unless `bool` is registered explicitly.
- **`float` is not an `int`** and has no numeric-tower fallback here — an unregistered `float` lands on the base function. The eval sheet says *"Try also with a float"*, so this is being checked on purpose.
- Registration for a **subclass** wins over its base, by MRO — the same linearization you learned in module 07.

It is the functional-style counterpart to module 07's polymorphism: instead of `Creature.attack()` overridden per subclass, one function with per-type implementations attached from outside. Effective Python Item 50 compares the two directly, and being able to say *"this is `isinstance`-dispatch made extensible, and it's the alternative to the ABC design of P07"* connects two modules in one sentence.

---

## 5. Ex4 — DECORATORS & `staticmethod` (`decorator_mastery.py`)

### The concept

A decorator is a callable that takes a function and returns a replacement. The `@` is pure syntax:

```python
@spell_timer
def fireball(...): ...

# is EXACTLY
def fireball(...): ...
fireball = spell_timer(fireball)
```

Two facts that answer most decorator questions:

1. **Decorators run at definition time**, when the module is imported — not when the function is called. `@` is executed once; the wrapper is executed every call.
2. **Stacked decorators apply bottom-up**, and therefore *wrap* outermost-last: `@a` over `@b` over `def f` gives `a(b(f))`.

### `functools.wraps` — required, and worth explaining

Without it, the decorated function is a liar:

```python
def deco(func):
    @functools.wraps(func)          # ← copies __name__, __qualname__, __doc__,
    def wrapper(*args, **kwargs):   #   __module__, __dict__; sets __wrapped__
        return func(*args, **kwargs)
    return wrapper
```

| Without `wraps` | With `wraps` |
| --------------- | ------------ |
| `f.__name__` is `"wrapper"` | the real name |
| the docstring is gone | preserved |
| `help(f)` and tracebacks are useless | correct |
| `inspect.signature(f)` shows `(*args, **kwargs)` | follows `__wrapped__` to the real signature |

This bites in ex4 directly: `spell_timer` must print `"Casting function_name..."`, and the name it has access to is `func.__name__` — the *original*, because the wrapper closed over `func`. But any *other* decorator stacked on top would see `wrapper` unless you used `wraps`. The eval sheet checks its presence explicitly; the interesting part is being able to say what breaks without it.

### The three-level shape of a parameterized decorator

`spell_timer` takes a function. `power_validator(min_power)` and `retry_spell(max_attempts)` take **arguments** — so they are **decorator factories**, and need one more level:

```
def factory(config):              ← level 1: takes the decorator's ARGUMENT
    def decorator(func):          ← level 2: takes the FUNCTION  (this is the decorator)
        @functools.wraps(func)
        def wrapper(*a, **kw):    ← level 3: takes the CALL's arguments
            ...
        return wrapper
    return decorator
```

`@power_validator(10)` **calls** `power_validator(10)` first, then applies the returned decorator. The parentheses are the tell: `@spell_timer` has none, `@power_validator(10)` does. Being able to name what each of the three levels receives is the single best-value thing to rehearse for this exercise — and note that levels 2 and 3 are closures over levels 1 and 2, so this is ex1 and ex2 stacked, exactly as promised.

### The trap in `power_validator` — the real design problem of ex4

The subject applies the *same* decorator in two places:

```
@power_validator(10)
def some_spell(target: str, power: int) -> str      # power is args[1]

class MageGuild:
    @power_validator(10)
    def cast_spell(self, spell_name: str, power: int) -> str    # power is args[2] — self shifted it
```

A wrapper that reaches for a fixed positional index works in one case and silently misreads the other; and either can be called with `power=` as a keyword, which puts it in `**kwargs` instead of `*args`. Decide how the wrapper locates the power value and make that decision explicit — by position, by keyword, or by inspecting the signature. This is the one genuinely non-obvious piece of design in the module, and the eval sheet tests both call sites (*"Does `cast_spell` use `power_validator` with `min_power=10`?"* plus *"Test `power_validator` with valid and invalid power levels"*). Work it out before the defense rather than during it.

### `retry_spell` — read the expected output as a specification

```
Spell failed, retrying... (attempt 1/3)
Spell failed, retrying... (attempt 2/3)
Spell casting failed after 3 attempts
```

Three attempts, **two** retry messages. The message is printed *after a failure when another attempt remains*; the third failure produces the final message instead. An off-by-one here is the most likely visible defect in the exercise. Two more decisions to make deliberately: which exceptions are caught (bare `except Exception`, or a narrower set), and whether a successful attempt returns immediately — the subject says *"if one attempt succeeds, return its result normally"*, so yes.

### `staticmethod` — the last concept

| | instance method | `@classmethod` | `@staticmethod` |
| --- | --- | --- | --- |
| First parameter | `self` | `cls` | **none** |
| Needs an instance | yes | no | no |
| Can read instance state | yes | no | no |
| Can read/return the class | via `type(self)` | yes — the alternate-constructor pattern | no |
| Why use it | behaviour tied to one object | factories, class-level polymorphism | **a function that belongs in the class's namespace and needs nothing from it** |

`validate_mage_name` is the textbook case: a pure predicate on a string, conceptually part of `MageGuild`, needing neither the instance nor the class. Callable as `MageGuild.validate_mage_name("Alex")` *and* as `guild.validate_mage_name("Alex")` — the eval sheet checks the first (*"Verify staticmethod works without instance"*).

Under the hood, `staticmethod` is itself a decorator returning a descriptor that skips the binding step ordinary functions go through — which is the honest answer to "how does it work?", and a nice callback to the data-model material. Since Python 3.10, `staticmethod` objects are also directly callable, so the old "you can't call it from inside the class body" caveat no longer applies.

`"at least 3 characters and contains only letters/spaces"` — the builtins to reach for are `str.isalpha()` (note: **`" ".isalpha()` is `False`**, so a naive `name.isalpha()` rejects every name with a space) plus a length check. It is a small trap and it is in the expected output: `True`, then `False`.

### Understanding check — the subject's own

> *"How do decorators enable separation of concerns? What's the difference between `@staticmethod` and regular instance methods?"*

For the first: timing, validation, and retrying are **cross-cutting concerns** — they are not what `fireball` is about, and without decorators each of them would be copy-pasted into every function that needs them. A decorator lets the function contain only its own logic and the policy live in one reusable place. Naming the three concerns of ex4 (measurement, precondition, fault tolerance) and pointing out that none of them belongs in a spell is the answer.

---

## 6. The evaluator's own questions — consolidated

From `Intra Projects Python Module 10 Edit.pdf`. These are the checks that appear verbatim on the scale, so rehearse them literally.

| Where | The question or check |
| ----- | --------------------- |
| Preliminaries | *"Ensure the learner avoided Global variables and File I/O operations."* |
| Preliminaries | *"Ensure all dependencies are installed via proper package management in a virtual environment."* (module 08 carries over) |
| ex0 | *"Verify that lambda expressions are used appropriately (not `def` functions for simple operations)."* |
| ex1 | *"Verify that functions are treated as first-class citizens (passed as arguments, returned from functions)."* |
| ex2 | *"Verify there is no use of 'global' keyword, and no class definitions."* |
| ex2 | *"Store 3 values, recall all 3, recall 1 missing key. Ask reviewee to explain what happens."* |
| ex3 | *"What happens if you call reduce on an empty list without an initializer?"* |
| ex3 | *"What is the difference between memoization and simply storing results in a global dict?"* |
| ex3 | *"How are handled 'min' and 'max'? Do you know other solutions?"* |
| ex3 | `type(result['fire_enchant']) is functools.partial` — and `cache_info()` with `hits > 0` after `fib(10)` then `fib(5)` |
| ex3 | *"Check single dispatch handles different types appropriately. Try also with a float."* |
| ex4 | *"Check that `functools.wraps` is used to preserve function metadata."* |
| Quality | *"Can the learner explain the difference between lambda and def functions?"* |
| Quality | *"Can the learner explain what makes functions 'first-class citizens'?"* |
| Quality | *"Does the learner understand how closures capture lexical scope?"* |
| Quality | *"Can the learner explain the benefits of functools utilities?"* |
| Quality | *"Does the learner understand how decorators transform functions?"* |
| Quality | *"Are type hints REQUIRED for all functions and methods (parameters and return values)?"* — **yes**; *"Docstrings are NOT required for this module."* |

Note what the scale does **not** mention: mypy. The subject asks for type hints on all signatures; the scale checks flake8 only. Running mypy anyway costs nothing and catches the `Callable` sloppiness.

---

## 7. Module-wide rules & traps

- **No global variables. No file I/O. No `eval`/`exec`. No external libraries.** All four are in the Forbidden list and the first two are checked in the Preliminaries — a single module-level mutable is a flag, not a remark.
- **No classes in ex2.** The eval sheet says so explicitly; the whole point is state without a class. (ex4 has the only class in the module.)
- **`Callable` comes from `collections.abc`**, not `typing` — the subject states it and then asks about it. `typing.Callable` is deprecated since 3.9.
- **Type hints on every signature and return**, including the nested `wrapper` functions inside decorators. Annotating a decorator honestly is genuinely awkward — `Callable[..., Any]` is the pragmatic floor, `ParamSpec` (3.10+) is the precise answer if you want to go further.
- **flake8 E731** — never `name = lambda …`. Pass lambdas, don't bind them.
- **`map` and `filter` are lazy.** Every function that "returns a list" must actually materialise one.
- **`sorted` returns; `list.sort` mutates and returns `None`.**
- **`reduce` on an empty iterable without an initializer raises**, and the identity element differs per operation.
- **`lru_cache` needs hashable arguments**, and the recursion must go through the decorated name to benefit.
- **`functools.wraps` on every wrapper**, including the ones inside decorator factories.
- **Each exercise's Authorized list is narrower than the module's.** `functools`/`operator` are ex3's; `functools.wraps` and `staticmethod` are ex4's; ex0 gets six builtins and nothing else. Do not let an ex3 import drift into ex0.
- **`time.sleep` is offered for simulation** — keep the durations small. A defense that takes 30 seconds to print four lines is its own kind of failure, and the timer only needs to show three decimals of something.
- **`data_generator.py` is part of the review.** The scale says *"Using `data_generator.py` in attachments to generate sample data"* for four of the five exercises: your functions will be run against data you did not write. Test with it beforehand — empty lists, ties, missing keys, a `float` for the dispatcher.
- **No unexpected termination.** `max()` on an empty list, an unhandled `KeyError` in the vault, an unregistered dispatch type — each of these is one `ValueError` away from ending the review.
- **Verify from a fresh clone**, `__pycache__` never committed.
- **Defense framing, from the subject:** *"During peer-review, you may be asked to explain functional programming concepts, demonstrate how closures work, or show how decorators transform functions. Focus on understanding the concepts, not just the implementation."* Followed immediately by *"Avoid over-engineering."* Both halves are graded.

---

## 8. Terminology — every term of the module, defined

Terms in **bold** are the ones an evaluator can legitimately ask you to define on the spot.

### 8.1 Functional programming, generally

| Term | Definition |
| ---- | ---------- |
| **First-class function** | A function that can be created at runtime, named, stored, passed, and returned like any other value. |
| **Higher-order function** | A function that takes and/or returns a function. |
| **Pure function** | Same inputs → same output, no side effects; what "functional purity" in the subject refers to. |
| **Side effect** | Any observable change outside the return value: printing, mutating, writing a file. |
| **Referential transparency** | A pure call can be replaced by its result — the property memoization depends on. |
| **Immutability** | Not rebinding or mutating shared state; the reason `global` is forbidden here. |
| **Composition** | Building a new function by combining existing ones. |
| **Combinator** | A function whose only job is to combine other functions — all four of ex1. |
| **Declarative vs imperative** | Saying *what* (`map`, `filter`, `reduce`) versus *how* (an explicit loop). |
| **Lazy evaluation** | Producing values on demand; why `map`/`filter` return iterators, not lists. |
| **Fold / reduce** | Collapsing a sequence into one value with a binary function. |
| **Identity element** | The value that leaves a fold unchanged: `0` for add, `1` for multiply; `max` has none. |
| **Predicate** | A function returning a bool, used to filter or guard. |
| **Cross-cutting concern** | Behaviour (timing, validation, retry) orthogonal to what a function is *for* — decorator territory. |

### 8.2 Lambdas & callables

| Term | Definition |
| ---- | ---------- |
| **Lambda** | An expression evaluating to an anonymous function whose body is a single expression. |
| **Anonymous function** | A function object with no name binding; `__name__` is `"<lambda>"`. |
| **flake8 E731** | *Do not assign a lambda expression, use a def* — the rule that shapes ex0's style. |
| **`key` function** | A one-argument function computing the sort/comparison value; called once per element. |
| **Stable sort** | Equal elements keep their original relative order; Python's Timsort is stable. |
| **`callable()`** | Builtin answering "does this object define `__call__`?" |
| **`Callable[[X], Y]`** | The **annotation** form, imported from `collections.abc`; bare `Callable` means `Callable[..., Any]`. |
| **Type alias** | `Spell = Callable[[str, int], str]` — naming a contract so it appears in every signature. |
| **`__call__`** | The dunder that makes an instance callable; why a `partial` object is callable without being a function. |

### 8.3 Scope & closures

| Term | Definition |
| ---- | ---------- |
| **Closure** | A function together with the enclosing-scope variables it captured. |
| **Free variable** | A name used in a function but bound in an enclosing one; listed in `__code__.co_freevars`. |
| **Cell** | The container holding a captured variable, shared between the closure and its enclosing frame. |
| **`__closure__`** | The tuple of cells attached to a closure; `cell_contents` reads one. |
| **Lexical / static scoping** | Name resolution follows where the code is *written*, decided at compile time. |
| **LEGB** | Local → Enclosing → Global → Builtins, the lookup order. |
| **`nonlocal`** | Declares that an assignment rebinds a name in the nearest enclosing function scope. |
| **`global`** | Declares that an assignment rebinds a module-level name; **forbidden in this project**. |
| **`UnboundLocalError`** | Reading a name that an assignment elsewhere in the function made local. |
| **Rebinding vs mutating** | `x = …` needs `nonlocal`; `d[k] = …` does not — the object is the same one. |
| **Late binding** | A closure reads its cell at **call** time, not definition time — `[lambda: i for i in range(3)]`. |
| **Function factory** | A function whose job is to build and return configured functions. |
| **Encapsulation via closure** | Private state reachable only through the functions that captured it — an object without a class. |

### 8.4 `functools` & `operator`

| Term | Definition |
| ---- | ---------- |
| **`functools.reduce`** | Fold a sequence with a binary function; demoted from builtins in Python 3. |
| **Initializer** | `reduce`'s third argument; without it an empty iterable raises `TypeError`. |
| **`operator` module** | Function forms of the operators: `add`, `mul`, `itemgetter`, `attrgetter`. |
| **`functools.partial`** | A callable object with some arguments pre-bound; introspectable via `.func`, `.args`, `.keywords`. |
| **Partial application** | Fixing some arguments of a function to obtain one of smaller arity. |
| **Currying** | The related idea of turning an n-argument function into a chain of one-argument ones. |
| **Memoization** | Caching results keyed by arguments; valid only for pure, hashable-argument functions. |
| **`lru_cache` / `cache`** | Bounded LRU memoization / the unbounded shorthand (3.9+). |
| **`cache_info()`** | `CacheInfo(hits, misses, maxsize, currsize)` — the proof the cache is working. |
| **LRU eviction** | Least-recently-used entries are discarded when `maxsize` is reached. |
| **`singledispatch`** | Generic function dispatching on the runtime type of its first argument, resolved by MRO. |
| **`.register`** | Attaches a type-specific implementation, read from the parameter's annotation. |
| **Generic function** | One name, several implementations chosen by argument type — the functional face of polymorphism. |

### 8.5 Decorators & methods

| Term | Definition |
| ---- | ---------- |
| **Decorator** | A callable taking a function and returning a replacement; `@d` is `f = d(f)`. |
| **Wrapper** | The inner function a decorator returns, closing over the original. |
| **Decorator factory** | A function returning a decorator, so the decorator can take arguments — three nested levels. |
| **`functools.wraps`** | Copies `__name__`, `__qualname__`, `__doc__`, `__module__`, `__dict__` and sets `__wrapped__`. |
| **`__wrapped__`** | The reference back to the undecorated function; how `inspect.signature` sees through a wrapper. |
| **Definition-time execution** | Decorators run at import, once; the wrapper runs per call. |
| **Stacking order** | Applied bottom-up: `@a` above `@b` yields `a(b(f))`. |
| **`*args` / `**kwargs`** | The signature that lets a wrapper forward any call unchanged. |
| **`ParamSpec` (3.10+)** | The typing tool that lets a decorator's annotation preserve the wrapped signature. |
| **`@staticmethod`** | A function in a class's namespace taking neither `self` nor `cls`; callable on class or instance. |
| **`@classmethod`** | Receives the class as `cls`; the alternate-constructor pattern. |
| **Descriptor** | The protocol behind method binding; `staticmethod` is the descriptor that opts out of it. |
| **`time.perf_counter`** | The monotonic high-resolution clock to measure durations with — not `time.time()`. |

---

## 9. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **FIRST-CLASS FUNCTION** | A function is a value: it can be named, stored, passed, returned, and given attributes like any object. |
| **LAMBDA VS DEF** | Same object, different syntax — an expression with one expression inside, versus a statement with a name, annotations, and a body. |
| **WHEN A LAMBDA IS RIGHT** | When it is passed inline and naming it would be noise; the moment it needs a name, flake8 E731 is telling you to use `def`. |
| **HIGHER-ORDER FUNCTION** | A function that takes a function, returns a function, or both. |
| **`Callable` VS `callable()`** | An annotation from `collections.abc` versus a runtime builtin asking whether `()` can follow. |
| **MAP/FILTER ARE LAZY** | They return iterators; nothing runs until you consume them. |
| **`sorted` VS `.sort()`** | Returns a new list versus mutates in place and returns `None`. |
| **CLOSURE** | A function plus the cells holding the enclosing-scope variables it captured. |
| **LEXICAL SCOPING** | Names resolve by where the code is written, decided at compile time — LEGB. |
| **`nonlocal` VS `global`** | Rebinds the nearest enclosing function's name versus the module's; only the first keeps state private. |
| **WHY CLOSURES BEAT GLOBALS** | Fresh state per call, invisible from outside, garbage-collected — encapsulation without a class. |
| **REBINDING VS MUTATING** | `x = …` needs `nonlocal`; `d[k] = …` does not, because the object never changed identity. |
| **LATE BINDING** | A closure reads its cell when *called*, so all the lambdas from one loop see the final value. |
| **`reduce`** | Fold a sequence into one value; empty without an initializer is a `TypeError`. |
| **IDENTITY ELEMENT** | The safe initializer: `0` for add, `1` for multiply, and none exists for `max`. |
| **`partial` VS LAMBDA** | A real, introspectable object with `.func`/`.args` versus an opaque closure named `<lambda>`. |
| **MEMOIZATION** | Cache results of a pure function by its arguments; `lru_cache` adds bounding, eviction, thread-safety and stats over a hand-rolled dict. |
| **`cache_info()`** | `hits/misses/maxsize/currsize` — the one-line proof the cache is doing work. |
| **`singledispatch`** | One function, per-type implementations chosen by the first argument's MRO — `isinstance` dispatch made extensible. |
| **`bool` IS AN `int`** | So `singledispatch` sends `True` to the `int` handler unless you register `bool`. |
| **DECORATOR** | A higher-order function returning a closure, plus `@` syntax: `@d` is exactly `f = d(f)`. |
| **DECORATOR FACTORY** | Three levels: the argument, the function, the call — because `@d(10)` calls `d(10)` first. |
| **`functools.wraps`** | Restores the wrapped function's identity; without it, tracebacks, `help()` and signatures all lie. |
| **DECORATORS RUN AT IMPORT** | The `@` executes once at definition; only the wrapper runs per call. |
| **SEPARATION OF CONCERNS** | Timing, validation and retry are not what a spell is about — a decorator keeps each in one reusable place. |
| **`@staticmethod`** | A function living in a class's namespace that needs neither the instance nor the class. |

---

## 10. Worth reading — before and during

### 10.1 The books already on the shelf — `42.secret.repo/_books/`

This is the module the shelf covers best. **Fluent Python chapters 7 and 9 are, almost literally, ex0–ex4.**

#### Fluent Python — Ramalho, 2nd ed. 2022 *(PDF page = book page **+ 30**)*

| Chapter / section | Book pp. | For |
| ----------------- | -------- | --- |
| **Ch 7 — Functions as First-Class Objects** | **231–250** | **ex0 and ex1, entirely.** Twenty pages, and the best money in the module. |
| ↳ Treating a Function Like an Object | 232 | the literal answer to "what makes functions first-class?" |
| ↳ **Higher-Order Functions** | **234** | ex1's definition, with the sorting-key example |
| ↳ Modern Replacements for map, filter, and reduce | 235 | the counter-argument: comprehensions. Know it, then follow the subject. |
| ↳ **Anonymous Functions** | **236** | lambda's limits and Ramalho's "lambda refactoring recipe" |
| ↳ The Nine Flavors of Callable Objects | 237 | why `callable()` is broader than "is it a function" |
| ↳ **The `operator` Module** | **243** | ex3: `itemgetter`, `attrgetter`, and the arithmetic functions |
| ↳ **Freezing Arguments with `functools.partial`** | **247** | ex3, exactly |
| **Ch 9 — Decorators and Closures** | **303–336** | **ex2, ex3 and ex4 in one chapter.** The densest payoff of the module. |
| ↳ Decorators 101 / **When Python Executes Decorators** | 304, **306** | the `f = d(f)` identity, and import-time execution |
| ↳ **Variable Scope Rules → Closures → The `nonlocal` Declaration** | **308–316** | ex2, start to finish, including `UnboundLocalError` and the cells |
| ↳ Implementing a Simple Decorator / How It Works | 317, 318 | the `clock` decorator — essentially ex4's `spell_timer` |
| ↳ **Memoization with `functools.cache` / Using `lru_cache`** | **320, 323** | ex3, with the fibonacci example the subject reuses |
| ↳ **Single Dispatch Generic Functions** | **324** | ex3's `singledispatch`, with the MRO caveats |
| ↳ **Parameterized Decorators → The Parameterized Clock Decorator** | **329, 332** | ex4's three-level factory, written out |
| ↳ A Class-Based Clock Decorator | 335 | the alternative shape, for the "could you do it another way?" question |
| **Ch 10 — Design Patterns with First-Class Functions** | 341–358 | P07 revision from the other side: patterns dissolved by first-class functions |
| Ch 8 — Type Hints in Functions → **Callable** | **291** | annotating higher-order functions properly |

#### Effective Python — Slatkin, 3rd ed. 2024 *(PDF page = book page **+ 27**)*

| Item | Book p. | For |
| ---- | ------- | --- |
| **33 — Know How Closures Interact with Variable Scope and `nonlocal`** | **145** | **ex2, the whole exercise, in six pages.** Read it first. |
| **38 — Define Function Decorators with `functools.wraps`** | **166** | ex4; the "without wraps everything lies" demonstration |
| **39 — Prefer `functools.partial` over lambda Expressions for Glue Functions** | **169** | ex3 — and the exact reason the eval sheet checks `type(...) is functools.partial` |
| **50 — Consider `functools.singledispatch` for Functional-Style Programming Instead of Object-Oriented Polymorphism** | **210** | ex3, and the bridge back to P07's ABCs |
| 48 — Accept Functions Instead of Classes for Simple Interfaces | 201 | ex1's design argument, stated as a rule |
| 40 — Use Comprehensions Instead of `map` and `filter` | 173 | the objection to ex0's style; have the answer ready, don't apply it |
| **100 — Sort by Complex Criteria Using the `key` Parameter** | **493** | ex0's `artifact_sorter`, including multi-key and `reverse` |
| 101 — Know the Difference Between `sort` and `sorted` | 499 | the `None`-returning trap |
| 34 / 37 — Variable Positional Arguments / Keyword-Only and Positional-Only | 150, 161 | `*args`/`**kwargs` in wrappers, and the `power_validator` positional problem |
| 30 — Know That Function Arguments Can Be Mutated | 135 | why memoizing a function with mutable arguments is a trap |
| 66 — Prefer Class Decorators over Metaclasses for Composable Class Extensions | 310 | where decorators go next |
| 93 — Optimize Performance-Critical Code Using `timeit` Microbenchmarks | 453 | how to *actually* show `lru_cache` is faster, if the reviewer asks |
| 24 — Consider `itertools` for Working with Iterators and Generators | 102 | `itertools` is Authorized module-wide; this is the map of it |

### 10.2 A reading order that fits the project

| When | Read |
| ---- | ---- |
| **Before writing anything** (~1 h) | Fluent **Ch 7, pp. 231–243** — first-class objects, HOFs, lambdas. It covers ex0 and ex1 before you type a line. |
| **During ex0** | Effective **Item 100** (493) + Fluent *Anonymous Functions* (236) |
| **During ex1** | Fluent *Higher-Order Functions* (234) + Ch 8 *Callable* (291); Effective **Item 48** (201) |
| **During ex2** ⭐ | Effective **Item 33** (145) then Fluent **pp. 308–316**. Two readings of the same material from different angles — this is the exercise where that pays. |
| **During ex3** | Fluent **pp. 320–328** (cache, lru_cache, singledispatch) + *partial* (247); Effective **Items 39 & 50** (169, 210) |
| **During ex4** | Fluent **pp. 317–335** (simple decorator → parameterized → class-based); Effective **Item 38** (166) |
| **Before the defense** | Fluent *When Python Executes Decorators* (306) and the late-binding passage in *Closures* (311). Those two produce the questions people actually fail on. |

### 10.3 From these notes (in order of usefulness)

| Doc | Why, for this project |
| --- | --- |
| [python_functions.md](../02_Python/02_syntax_flow/python_functions.md) | **The direct prerequisite.** Parameters, defaults, `*args`/`**kwargs`, return semantics — re-read before ex1. |
| [python_keywords.md](../02_Python/02_syntax_flow/python_keywords.md) | `lambda`, `nonlocal`, `global` — the three keywords the module is built on and the one it forbids. |
| [M2_Python_7_concepts.md](M2_Python_7_concepts.md) | §3 (Strategy) and §4 (the pattern map). Ex3's `singledispatch` and ex1's combinators are the same problems solved without classes — the strongest cross-module answer you can give. |
| [python_comprehensions.md](../02_Python/03_data_types/python_comprehensions.md) | The idiomatic alternative to `map`/`filter`; you need it to explain *why* the subject bans it here. |
| [python_data_model.md](../02_Python/03_data_types/python_data_model.md) | `__call__`, descriptors, and what "callable" really means — the layer under `staticmethod`. |
| [python_idioms.md](../02_Python/05_style/python_idioms.md) | Where the functional forms are and aren't idiomatic Python. |
| [python_naming.md](../02_Python/05_style/python_naming.md) | Naming factories and wrappers — `make_`, `_factory`, and why `wrapper` should never survive `wraps`. |
| [M2_Python_8_concepts.md](M2_Python_8_concepts.md) | The venv the eval sheet's Preliminaries still checks for. |

### 10.4 Official docs (short, worth the detour)

- [`functools`](https://docs.python.org/3/library/functools.html) — read the whole page; it is short and it is ex3's specification. `reduce`, `partial`, `lru_cache`, `cache`, `wraps`, `singledispatch`, `singledispatchmethod`.
- [`operator`](https://docs.python.org/3/library/operator.html) — skim the table; note there is no `max`/`min`.
- [Python HOWTO — *Functional Programming*](https://docs.python.org/3/howto/functional.html) — the official tour: iterators, generators, lambdas, `functools`, `itertools`. One sitting, and it frames the entire module.
- [Execution model — *Naming and binding*](https://docs.python.org/3/reference/executionmodel.html#naming-and-binding) — the formal definition of free variables, `nonlocal` and `global`. Dry, and the definitive answer to the ex2 question box.
- [PEP 318 — Decorators for Functions and Methods](https://peps.python.org/pep-0318/) — why the `@` syntax exists at all; the rationale section is the good part.
- [PEP 443 — Single-dispatch generic functions](https://peps.python.org/pep-0443/) — the design rationale behind `singledispatch`.
- [PEP 612 — `ParamSpec`](https://peps.python.org/pep-0612/) — if you want your decorators to type-check precisely rather than settling for `Callable[..., Any]`.

### 10.5 Worth the detour

- Guido van Rossum, [*Origins of Python's Functional Features*](https://python-history.blogspot.com/2009/04/origins-of-pythons-functional-features.html) — why `lambda`, `map` and `filter` exist, from the person who reluctantly added them and later tried to remove them. Three minutes, and it is the best possible framing for "Python is not a functional language" at defense.
- [`itertools` recipes](https://docs.python.org/3/library/itertools.html#itertools-recipes) — `itertools` is Authorized module-wide and barely used by the subject; the recipes section is where the functional idioms live.
- Brandon Rhodes, [python-patterns.guide](https://python-patterns.guide/) — the *Decorator* and *Strategy* entries, for how first-class functions dissolve half the GoF catalogue. Pairs with P07.

### 10.6 Not on the shelf yet

- **Functional Programming in Python** — David Mertz (O'Reilly, free short report). Sixty pages on exactly this material, with a clear-eyed section on where Python's functional style stops paying.
- *Structure and Interpretation of Computer Programs* — the closure/environment-model chapters are the deepest version of ex2 there is, and free online. Scheme, and it does not matter.

---
