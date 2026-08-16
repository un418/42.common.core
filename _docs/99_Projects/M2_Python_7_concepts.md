# Python Module 07 — Concepts Guide (Design Patterns: Abstract Factory, Capabilities & Strategy)

> Subject: *DataDeck — Abstract Card Architecture* (`_subjects/en.python_mod07.subject.pdf`, v3.0). Python ≥ 3.10, flake8 + mypy clean, **comprehensive** type annotations, exceptions handled "gracefully to avoid crashes". Authorized imports: **`abc` and `typing` only** — plus all builtins (except `eval()` / `exec()`) and all standard types/collections. **External libraries forbidden.** An `__init__.py` is **MANDATORY** in every exercise folder, and every test script lives at the **repository root**.

---

## 0. The big picture — "who builds it, what it can do, how it fights"

Module 05 taught you the *tools* of abstraction (ABC, polymorphism, Protocol). Module 06 taught you where code *lives* (packages, `__init__.py`, re-export). Module 07 spends both at once: it is the first module where the grade is on **architecture**, not on logic. Every method returns a hard-coded string on purpose — so that the only thing under examination is the shape of the object graph.

| Ex  | Pattern                             | Question it answers                                                        |
| --- | ----------------------------------- | -------------------------------------------------------------------------- |
| ex0 | **Abstract Factory** (creational)   | How do I create a *family* of objects without ever naming their classes?    |
| ex1 | **Capabilities / mixins**           | How do I add behaviour to *some* classes without polluting the base class?  |
| ex2 | **Strategy** (behavioral)           | How do I let the *algorithm* vary independently of the object it acts on?   |

### The one thread running through all three

```
        battle.py / capacitor.py / tournament.py       ← the CLIENT, at repo root
                        │  knows only:  factories + strategies
                        ▼
        ┌───────────────────────────────────────────┐
        │  ex0 / ex1 / ex2  packages                │
        │  __init__.py exposes factories ONLY       │  ← the encapsulation rule
        │  concrete Creature classes stay inside    │
        └───────────────────────────────────────────┘
```

The subject repeats it twice: *"your package cannot expose concrete Creature directly, it must only expose factories."* That single sentence is module 06's `__init__.py` lesson turned into an architectural constraint. Everything else in the project exists to make that constraint useful.

### The three-layer object graph, by the end of ex2

```
CreatureFactory (ABC) ──create_base()──▶ Creature (ABC) ──▶ describe() / attack()
       │                                     ▲  ▲
       │ subclasses                          │  └── + HealCapability      (ex1)
       ▼                                     │      + TransformCapability
Flame / Aqua / Healing / Transform           │
                                             │
BattleStrategy (ABC) ──is_valid(creature)──▶─┘   act(creature) drives the fight (ex2)
```

Three abstractions, three independent axes of variation: **what exists** (creature), **how it is born** (factory), **how it behaves in combat** (strategy). Adding a fifth family touches zero existing code — that is the Open/Closed Principle, and it is the answer to "why bother with all this?".

---

## 1. Ex0 — ABSTRACT FACTORY

### The concept

> **Intent (GoF):** *provide an interface for creating families of related or dependent objects without specifying their concrete classes.*

Two **parallel hierarchies**: one of products, one of creators. The client holds the abstract creator, calls abstract methods on it, and receives abstract products. No concrete name ever appears in the client.

```python
import abc


class Product(abc.ABC):                       # the abstract PRODUCT
    @abc.abstractmethod
    def use(self) -> str: ...


class Factory(abc.ABC):                       # the abstract CREATOR
    @abc.abstractmethod
    def create_small(self) -> Product: ...    # note the return type: the ABSTRACT type
    @abc.abstractmethod
    def create_large(self) -> Product: ...


def client(factory: Factory) -> str:          # depends on abstractions only
    return factory.create_small().use()       # never writes ConcreteSmallA()
```

The **family** is the key word. `create_small()` and `create_large()` on the *same* factory instance are guaranteed to belong together — one concrete factory cannot hand you a mismatched pair. In this project the family axis is the **evolution line**: base + evolved for one creature type.

### Factory Method vs Abstract Factory vs "simple factory"

An evaluator will ask. Have the three separated:

| | What it is | Granularity |
| --- | --- | --- |
| **Simple factory** (not GoF) | one function/`if` chain returning a concrete class | one product, one decision point |
| **Factory Method** | *one* abstract method; subclasses decide which class to instantiate | one product per creator |
| **Abstract Factory** | an *object* grouping several factory methods | a **family** of products per creator |

An Abstract Factory is usually *implemented with* Factory Methods — that's why they look alike. The distinguishing question is: **does one creator produce several related products that must stay consistent with each other?** Here, yes: base and evolved of the same line.

### The Python honesty point — the best answer you can give at defense

In Java or C++ a class is not a value, so building an object you can pass around *just to call `new`* is the only way. **In Python, classes are first-class objects** — `create_base` could be a one-line `return Flameling()`, and a bare `dict[str, type[Creature]]` already covers most of what the pattern buys elsewhere.

So why keep it?

1. **The family guarantee** — a dict of classes has no way to say "these two go together".
2. **Encapsulation of the concrete names** — the point of the subject's export rule.
3. **Room for creation logic** — a factory method can compute, cache, or configure; a raw class reference cannot.

Saying "this pattern is partly a workaround for languages where classes aren't values, and here is what still earns its place in Python" is the difference between reciting a pattern and understanding it.

### What the subject asks for, layer by layer

| Piece | Kind | Must have |
| ----- | ---- | --------- |
| `Creature` | ABC | attributes for **name** and **type**; `attack` **abstract**; `describe` **concrete** and generic (built from name + type) |
| `Flameling`, `Pyrodon`, `Aquabub`, `Torragon` | concrete | override `attack`, return an appropriate message |
| `CreatureFactory` | ABC | `create_base` + `create_evolved`, both abstract |
| `FlameFactory`, `AquaFactory` | concrete | one family each: base + evolved |

`describe` being **concrete in the base** is the code-reuse half of inheritance: written once, inherited by every creature, and it reads `self.name` / `self.type` which each subclass fills in. `attack` being **abstract** is the specialization half. That contrast is the whole reason the base class is an ABC rather than a plain class — and it is exactly the `output()` vs `validate()` split you already met in module 05.

Output shape to match (dual types exist — `Fire/Flying`):

```
Flameling is a Fire type Creature
Flameling uses Ember!
```

### "Cannot expose concrete Creature" — what that means in a language with no privacy

Python has **no private modules and no private classes**. Non-export is a *convention*, not an enforcement — module 06 already made you say this out loud. The tools available:

| Tool | Effect |
| ---- | ------ |
| **not re-exporting** in `__init__.py` | `ex0.Flameling` → `AttributeError`; the name is absent from the package surface |
| **`__all__`** | declares the public surface, drives `import *`, silences flake8 `F401` on re-exports |
| **leading `_`** on a module name (`_creatures.py`) | conventional "internal", excluded from `import *` |

But `from ex0.creatures import Flameling` still works if someone insists. **Be ready to admit that.** The correct framing: the package publishes a *contract*; a caller who bypasses it is on their own, and nothing in the client code does so.

### The annotation question this rule creates — decide it before defense

The client script must annotate the object a factory returns. If the package exposes no creature type at all, there is no name to write. Note that the subject forbids exposing **concrete** creatures — an abstract base is an *interface*, not a creature. Work out which of these you are doing, and why:

- publish the abstract type as part of the contract (the client codes against the interface — the usual reading);
- or keep everything internal and have the client rely only on what factories and strategies expose.

Either is defensible; not having noticed the tension is not.

### `battle.py` — what each function proves

| Function | Signature shape | What it demonstrates |
| -------- | --------------- | -------------------- |
| test-a-factory | takes **one** factory | the client is written against `CreatureFactory`; the same code drives Flame and Aqua |
| make-them-fight | takes **both** factories | two families interoperate through the shared `Creature` interface |

The first function being called twice with different factories, printing different creatures, *is* the demonstration. If you find yourself writing `if isinstance(factory, FlameFactory)`, the pattern has been defeated.

---

## 2. Ex1 — CAPABILITIES (mixins, multiple inheritance & the MRO)

### The concept

> *"Maybe one day, these capabilities will not only apply to Creature. So we want to keep them separate: capability abstract classes will not inherit from the Creature base class!"*

That is the **Interface Segregation Principle** stated in game terms: a class should not be forced to depend on methods it doesn't use. Putting `heal()` on `Creature` would give a healing method to every card that will never heal.

The alternative is a **mixin**: a small ABC declaring one capability, combined with the main base class at the point of use.

```python
class Storable(abc.ABC):                      # a capability — independent of any hierarchy
    @abc.abstractmethod
    def store(self) -> str: ...


class Widget(Base, Storable):                 # combine at the leaf
    ...
```

`Widget` **is a** `Base` and **is a** `Storable`. Two independent trees meeting only where they are used. Adding a third capability adds a class, not a rewrite.

### Mixin conventions worth respecting (and citing)

| Convention | Why |
| ---------- | --- |
| Narrow: one capability per mixin | recombinable; that's the entire point |
| Never instantiated alone | it is a fragment, not an object |
| Listed **before** the main base in the bases list, by convention | its methods win the MRO — see below |
| Named for a capability, often `-able` / `-Capability` / `-Mixin` | signals "fragment, not a parent" at a glance |

### The MRO — the mechanism you must be able to trace

Multiple inheritance means Python needs a deterministic order to search for an attribute. That order is the **MRO** (Method Resolution Order), computed by **C3 linearization** at class-creation time.

```python
class A: ...
class B(A): ...
class C(A): ...
class D(B, C): ...

D.__mro__          # D → B → C → A → object
```

The rules C3 enforces: a class always precedes its parents; the order of the bases list is preserved; and the result is consistent across the whole hierarchy. If no such order exists, the **class definition itself** fails with `TypeError: Cannot create a consistent method resolution order`.

Three consequences that matter here:

1. **A diamond exists whether you designed one or not.** Both `Creature` and the capability ABCs inherit `abc.ABC` → `object`. C3 resolves it; `object` appears exactly once, at the end.
2. **The metaclass must be compatible.** Both sides use `ABCMeta`, so combining them is fine. Mixing a class whose metaclass is unrelated raises `TypeError: metaclass conflict` — worth knowing as the failure mode.
3. **`__init__` does not chain by itself.** With two bases that both want to initialize state, exactly one of them runs unless the chain cooperates. Which brings us to:

### `super()` is not "the parent" — it is "the next one in *my instance's* MRO"

```python
super().__init__(...)     # → the next class after me in type(self).__mro__
```

This is the single most misunderstood thing in the module. `super()` is resolved against the *instance's* MRO, not the defining class's parent — so the "next" class can be a sibling branch the defining class has never heard of. For every class in a diamond to run, each `__init__` must call `super().__init__()` and pass along what it doesn't consume (**cooperative multiple inheritance**). Skip that and one capability's state silently never initializes — a bug that shows up only in the attack output.

The state attribute the subject requires for `TransformCapability` is exactly the thing that goes missing when the chain is broken. Trace `SomeClass.__mro__` in a REPL and know which `__init__`s actually ran.

### What ex1 adds

| Piece | Inherits | Must declare |
| ----- | -------- | ------------ |
| `HealCapability` | ABC only — **not** `Creature` | `heal` abstract (a `target` parameter is optional) |
| `TransformCapability` | ABC only — **not** `Creature` | `transform` + `revert` abstract, and a **persistent state attribute** |
| `Sproutling`, `Bloomelle` | `Creature` + `HealCapability` | one family |
| `Shiftling`, `Morphagon` | `Creature` + `TransformCapability` | one family |
| `HealingCreatureFactory`, `TransformCreatureFactory` | `CreatureFactory` | one family each |

Same export rule: **factories only**. And ex1 must **build on the ex0 package** — a cross-package import between two top-level packages sitting side by side at the repo root, so absolute imports (module 06, Part III).

### The transform state — a State pattern in miniature

> *"An attribute is used to make the state persistent and it impacts the `attack` implementation of Creature with this capability."*

`attack()` must branch on that attribute: the transformed form attacks differently from the base form. Read the expected output carefully — `Shiftling attacks normally.` before transforming, `Shiftling performs a boosted strike!` after. Same method, same object, different result, because the object carries state.

Edge cases to have an answer for (the subject doesn't specify them; an evaluator may):

- `transform()` called twice in a row — idempotent, error, or double boost?
- `revert()` when not transformed — no-op or error?
- the invariant: after `transform()` then `revert()`, is the object *exactly* as it was?

### `capacitor.py` — the sequence is the specification

| Family | Sequence to print |
| ------ | ----------------- |
| healing (base, then evolved) | describe → attack → **heal** |
| transforming (base, then evolved) | describe → attack → **transform → attack again → revert** |

The second sequence attacks **twice on purpose**: it is the proof that state changed behaviour. That asymmetry between the two families is also the setup for ex2 — the whole reason a Strategy is needed.

---

## 3. Ex2 — STRATEGY

### The concept

> **Intent (GoF):** *define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from the clients that use it.*

The subject walks you into the problem first: healing creatures fight `attack → heal`, transforming ones fight `transform → attack → revert`. A tournament that knows both would be a growing `isinstance` cascade — the **type switch anti-pattern**, and the thing every pattern in this project exists to delete.

```python
class Strategy(abc.ABC):
    @abc.abstractmethod
    def is_valid(self, subject: object) -> bool: ...
    @abc.abstractmethod
    def act(self, subject: object) -> None: ...


def context(subject: object, strategy: Strategy) -> None:
    strategy.act(subject)          # one call site, N algorithms, zero branching
```

The **context** (here: the battle function) holds a strategy and delegates. The algorithm is now an object: passed around, swapped at runtime, tested alone.

### Why not just put `fight()` on the Creature?

The question to prepare, because it is the obvious objection. Both work; they differ in **which axis is allowed to vary**.

| | Method on the Creature | Strategy object |
| --- | --- | --- |
| Behaviour is chosen | at class-definition time | at **runtime**, per opponent entry |
| Same creature, two tactics | needs a new subclass | pass a different strategy |
| Adding a tactic | edits every creature class | adds one class |
| Combinations of N creatures × M tactics | N×M classes | N + M classes |
| Behaviour reusable across unrelated types | no | yes — `NormalStrategy` suits *any* creature |

Strategy is **composition over inheritance**: the tournament entry is a *pair*, and the subject makes that literal by asking for `(factory, strategy)` tuples. The same Flameling appears with `Normal` in one tournament and with `Aggressive` in another — with behaviour baked into the class, that experiment is impossible.

### The three strategies and their validity rules

| Strategy | Suitable for | Sequence |
| -------- | ------------ | -------- |
| `NormalStrategy` | **any** creature | attack |
| `AggressiveStrategy` | creatures with **transform** capability | transform → attack → revert |
| `DefensiveStrategy` | creatures with **healing** capability | attack → heal |

`is_valid` is a **runtime capability check** — and this is where ex1's separate capability classes pay off. Three ways to ask "can this creature do X?", each defensible:

| Approach | Mechanism | Trade-off |
| -------- | --------- | --------- |
| `isinstance(c, TransformCapability)` | **nominal** — checks the MRO | exact, cheap, mypy narrows the type afterwards; requires importing the capability class |
| `typing.Protocol` + `@runtime_checkable` | **structural** | zero coupling to the class; `isinstance` on a Protocol checks **method names only, never signatures** |
| `hasattr(c, "transform")` | duck typing | no import at all; silently true for anything with a same-named attribute |

Whichever you pick, know what the other two would have cost. And note that mypy *narrows* after an `isinstance` check — which is how `act` can call `transform()` on something typed as a plain creature without an error.

### The dedicated exception — and the tension to resolve

> *"If the `act` method is called with an invalid combination, a dedicated exception is raised with a clear message."*

"Dedicated" means **your own exception class**, not a bare `ValueError` (see [python_custom_exceptions.md](../02_Python/04_errors/python_custom_exceptions.md)). It must be catchable *specifically* — the tournament catches this and nothing else.

That sits against the general instruction *"your functions should handle exceptions gracefully to avoid crashes."* No contradiction, but say the resolution out loud: **the strategy raises, the tournament catches.** Raising is how a layer reports "you asked for something impossible"; catching is how the layer above turns it into a clean message instead of a traceback. Matching the example:

```
Battle error, aborting tournament: Invalid Creature 'Flameling' for this aggressive strategy
```

Note **where** that line appears in the expected output: *after* the two creatures have been described and after `now fight!`. So the failure surfaces when a strategy is asked to **act**, not during an upfront sweep of the roster — and it aborts the whole tournament, not just that battle. Reproduce that ordering.

Also note `is_valid` returns a bool and `act` raises: two different answers to the same question, for two different callers. That is deliberate — a caller that wants to *choose* asks `is_valid`; a caller that already committed gets an exception.

### `tournament.py` — round-robin

> *"makes each opponent fight once all other opponents"*

Every unordered pair, exactly once: **n(n−1)/2** battles. The example confirms it — 2 opponents → 1 battle, 3 opponents → 3 battles (A-B, A-C, B-C).

⚠️ **`itertools.combinations` is not authorized** (`abc` and `typing` only). Index arithmetic over the list is the intended route — and the standard shape for "each unordered pair once" is the second loop starting *after* the first index, not from zero.

Within a battle, each opponent acts **once**, in list order, each through its own strategy. The battle function's signature is the deliverable: it takes a **list of `(CreatureFactory, BattleStrategy)` tuples** and nothing else — every creature it fights is one it created itself, from a factory it was handed, and it never learns a concrete class name. Read that sentence again; it is the whole project in one function.

---

## 4. The pattern map — where these three sit

The GoF catalogue splits 23 patterns into three families. Knowing the *categories* is cheap and makes you sound fluent:

| Family | Answers | Examples | Met in |
| ------ | ------- | -------- | ------ |
| **Creational** | how objects are made | **Abstract Factory**, Factory Method, Builder, Singleton, Prototype | ex0 |
| **Structural** | how objects are composed | Adapter, Decorator, Facade, Composite, Proxy | — (mixins are a *language* technique, not a GoF pattern) |
| **Behavioral** | how objects collaborate | **Strategy**, Observer, Template Method, State, Command, Visitor | ex2 |

Neighbours worth being able to distinguish, because they look alike:

| Pattern | vs Strategy |
| ------- | ----------- |
| **State** | same structure (delegate to an object), different intent: State transitions **itself** between states; Strategy is chosen by the client and doesn't change. `TransformCapability` is State-flavoured. |
| **Template Method** | the base class fixes the *skeleton* and subclasses fill the steps — inheritance instead of composition; the algorithm can't be swapped at runtime. |
| **Command** | encapsulates a *request* to be queued/undone, not an interchangeable algorithm. |

And the running theme of the whole module, worth naming: **program to an interface, not an implementation** — the GoF's own first principle, and the reason the client scripts sit at the root importing nothing but factories and strategies.

---

## 5. Module-wide rules & traps

- **`__init__.py` is MANDATORY in each exercise folder** — `ex0/`, `ex1/`, `ex2/` are packages, not loose directories. This is stricter than module 06, where namespace packages were a talking point.
- **Test scripts at the repository root**: `battle.py`, `capacitor.py`, `tournament.py`. That is what puts the root on `sys.path` and makes `ex0`, `ex1`, `ex2` importable (module 06, and `sys.path` is still not something you touch).
- **ex1 builds on ex0; ex2 imports from both.** Cross-package absolute imports. Decide once whether ex1 re-exports ex0's factories or the client imports each package directly — and be consistent.
- **Only `abc` and `typing` may be imported.** No `itertools`, no `random`, no `dataclasses`, no `enum`. Annotations use builtin generics (`list[tuple[...]]`, `str | None`) — 3.10 syntax, no `typing.List`.
- **`F401 imported but unused` will fire in every `__init__.py`.** Prefer `__all__` over `# noqa`: it silences the linter *and* documents the exported surface, which is literally what the subject grades.
- **"Comprehensive type annotations"** — every parameter and every return, including `-> None` and `-> str`, in `__init__.py` too. Factory methods returning the abstract product type is the annotation that carries the design.
- **The output examples are the spec.** Blank lines between blocks, the leading-space continuation lines (` vs.`, ` fight!`, ` base:`, ` evolved:`), the exact abort message. Wording of the attack messages is yours; the *structure* is not.
- **Creature "type" is a string, and can be dual** (`Fire/Flying`). `type` is also a builtin — shadowing it as an attribute name is legal (`self.type`) but shadowing it as a *local variable* or parameter is the kind of thing flake8 won't catch and a reviewer will.
- **`__pycache__` must never be committed**, and every scenario must be verified **from a fresh clone** — a stale `.pyc` hides a file you forgot to `git add`, and this project has a lot of small files.
- **Defense warning, straight from the subject:** *"you may be asked to explain the design patterns explored in this project. Focus on understanding the concepts, not just the implementation."* Expect live edits: "add a fourth family", "add a capability", "make this creature usable with a different strategy". If the architecture is right, each is a few lines and no edit to existing classes. That is the demonstration.

---

## 6. Terminology — every term of the module, defined

Terms in **bold** are the ones an evaluator can legitimately ask you to define on the spot.

### 6.1 Design patterns — general vocabulary

| Term | Definition |
| ---- | ---------- |
| **Design pattern** | A named, reusable solution to a recurring design problem — a vocabulary, not a library. |
| **GoF** | *Gang of Four*: Gamma, Helm, Johnson & Vlissides, authors of the 1994 catalogue of 23 patterns. |
| **Creational / structural / behavioral** | The three GoF families: how objects are created, composed, and how they collaborate. |
| **Intent** | The one-sentence problem statement a pattern answers — the part to memorize, ahead of the structure. |
| **Participant / role** | A named slot in a pattern (creator, product, context, strategy) filled by one of your classes. |
| **Client** | The code that uses the pattern while depending only on its abstractions — here, the root scripts. |
| **Anti-pattern** | A common solution that makes things worse; here, the `isinstance` cascade in the caller. |
| **Program to an interface, not an implementation** | The GoF's first principle, and the sentence that summarizes this whole module. |
| **Boilerplate** | Structural code carrying no logic; patterns trade some boilerplate for flexibility — a trade to be able to defend. |

### 6.2 Creational — factories

| Term | Definition |
| ---- | ---------- |
| **Abstract Factory** | An object exposing several creation methods that produce a **consistent family** of related products. |
| **Factory Method** | A single abstract creation method whose subclasses decide which concrete class to instantiate. |
| **Simple factory** | A plain function or `if` chain returning a concrete class; not a GoF pattern. |
| **Product** | The object a factory returns; the *abstract product* is the type the client is written against. |
| **Concrete factory** | One implementation of the abstract factory, owning one family. |
| **Parallel hierarchies** | The products tree and the creators tree, mirroring each other — the structural signature of the pattern. |
| **Family of products** | Objects that must be used together and must not be mismatched — the guarantee a dict of classes cannot give. |
| **First-class class** | In Python a class is a value: it can be stored, passed and called — which is why factories are lighter here than in Java/C++. |
| **`type[Creature]`** | The annotation for "the class itself, not an instance" — the typing form behind class-as-value tricks. |

### 6.3 Inheritance, mixins & the MRO

| Term | Definition |
| ---- | ---------- |
| **Multiple inheritance** | A class with more than one base; Python allows it, most languages don't. |
| **Mixin** | A small class contributing one capability, designed to be combined rather than instantiated. |
| **Capability class** | This subject's name for a mixin ABC: `heal`, `transform`/`revert`, deliberately outside the main hierarchy. |
| **MRO** | *Method Resolution Order* — the linearized class list Python searches for an attribute (`Cls.__mro__`). |
| **C3 linearization** | The algorithm computing the MRO: a class before its parents, base order preserved, globally consistent. |
| **Diamond problem** | Two bases sharing an ancestor; C3 makes the shared ancestor appear exactly once. |
| **`super()`** | The **next class in the instance's MRO** — not "the parent"; the whole point of cooperative inheritance. |
| **Cooperative multiple inheritance** | Every `__init__` in the chain calling `super().__init__()` so no branch is skipped. |
| **Metaclass conflict** | `TypeError` when combining bases whose metaclasses are unrelated; `ABCMeta` on both sides avoids it here. |
| **Composition over inheritance** | Holding an object and delegating ("has a") instead of subclassing ("is a") — what Strategy applies. |
| **Interface Segregation Principle** | No class should be forced to depend on methods it doesn't use — the subject's stated reason for separate capabilities. |
| **Open/Closed Principle** | Open for extension, closed for modification: a new family adds classes, edits none. |
| **Liskov Substitution Principle** | A subtype must be usable wherever its base is — what makes the client's single loop safe. |

### 6.4 Behavioral — strategy

| Term | Definition |
| ---- | ---------- |
| **Strategy** | An interchangeable algorithm encapsulated in its own object, selected by the client at runtime. |
| **Context** | The object holding and invoking a strategy — here the battle function. |
| **Delegation** | Forwarding work to a held object instead of doing it inline; the mechanism under Strategy. |
| **Dependency injection** | Handing a component its collaborators from outside instead of letting it build them. |
| **Guard / precondition** | A check run before an operation — `is_valid` before `act`. |
| **Type switch** | The `if isinstance(...)` cascade Strategy removes from the caller. |
| **State pattern** | Same structure as Strategy, different intent: the object changes its own state — the transform flag's flavour. |
| **Template Method** | Skeleton in the base, steps in subclasses — the inheritance-based rival of Strategy. |
| **Round-robin** | Every participant meets every other exactly once: n(n−1)/2 pairings. |
| **Runtime capability check** | Asking an object at runtime whether it can do something: `isinstance`, `runtime_checkable` Protocol, or `hasattr`. |

### 6.5 Packaging & encapsulation

| Term | Definition |
| ---- | ---------- |
| **Package** | An importable directory; `__init__.py` makes it a *regular* package and defines what it publishes. |
| **`__init__.py`** | The package's public interface: a name is reachable as `pkg.name` only if this file binds it. |
| **Re-export** | Importing a name into `__init__.py` so it becomes part of the package surface. |
| **`__all__`** | The declared public surface: drives `import *`, documents the API, silences flake8 `F401`. |
| **Public API surface** | The set of names a package intends callers to use — here: **factories only**. |
| **Encapsulation by convention** | Python's only kind: leading `_`, absence from `__all__`, non-re-export. Never an enforcement. |
| **Non-export ≠ privacy** | A class left out of `__init__.py` is still reachable through its module — say this before you're asked. |
| **Absolute import** | A full dotted name from a `sys.path` root — what ex1 and ex2 use to reach ex0. |
| **Entry point** | The script actually launched: `battle.py`, `capacitor.py`, `tournament.py`, all at the repo root. |

### 6.6 Typing, errors & tooling

| Term | Definition |
| ---- | ---------- |
| **ABC / `abc.ABC`** | A class meant to be inherited, never instantiated; inheriting it installs `ABCMeta` and the enforcement. |
| **`@abc.abstractmethod`** | Declares a method every concrete subclass must implement; checked at **instantiation**, not at definition. |
| **Concrete method in an ABC** | Shared implementation inherited as-is — `describe()` here. |
| **Nominal vs structural subtyping** | "You inherit from it" (ABC) vs "you have the methods" (`typing.Protocol`, PEP 544). |
| **`@typing.runtime_checkable`** | Allows `isinstance()` on a Protocol — checks **method names only**, never signatures. |
| **Type narrowing** | mypy refining a variable's type inside an `isinstance` branch — what makes capability checks type-check. |
| **Custom exception** | Your own `Exception` subclass, catchable specifically — what "a dedicated exception" means. |
| **Raise vs handle** | The lower layer raises the precise failure; the upper layer catches it and prints a clean message. |
| **flake8 `F401`** | "Imported but unused" — fires on every re-export; fix with `__all__`. |
| **mypy** | Static checker required clean; type hints are **never** runtime validation. |

---

## 7. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **ABSTRACT FACTORY** | An object whose methods create a consistent **family** of related products, so the client never names a concrete class. |
| **FACTORY METHOD vs ABSTRACT FACTORY** | One creation method per creator vs a group of them covering a family; the second is usually built from the first. |
| **PARALLEL HIERARCHIES** | A tree of products mirrored by a tree of creators — the structural fingerprint of Abstract Factory. |
| **WHY FACTORIES ARE LIGHTER IN PYTHON** | Classes are first-class values, so the family guarantee and the hidden concrete names are what still earn the pattern. |
| **EXPOSE FACTORIES ONLY** | The package publishes creators, not creatures — `__init__.py` + `__all__` define the contract. |
| **NON-EXPORT ≠ PRIVACY** | Leaving a class out of `__init__.py` hides it from `pkg.Name`, never from `pkg.module.Name`. |
| **MIXIN / CAPABILITY** | A small ABC declaring one capability, combined at the leaf, deliberately outside the main hierarchy. |
| **INTERFACE SEGREGATION** | Don't force a class to carry methods it will never use — the subject's own reason for separate capability classes. |
| **MRO** | The C3-linearized order Python searches for an attribute; `Cls.__mro__` is the answer to every multiple-inheritance question. |
| **`super()`** | The next class in **the instance's** MRO, not "the parent" — which is why cooperative `__init__` chaining is required. |
| **PERSISTENT STATE CHANGES BEHAVIOUR** | The transform flag makes the same `attack()` return two different things — one object, two behaviours. |
| **STRATEGY** | An interchangeable algorithm as an object, chosen at runtime, so behaviour varies independently of the creature. |
| **STRATEGY vs METHOD ON THE OBJECT** | N+M classes and runtime swapping, versus N×M classes fixed at definition time. |
| **COMPOSITION OVER INHERITANCE** | Pair a creature with a strategy instead of subclassing a creature per tactic. |
| **`is_valid` vs `act`** | A bool for a caller that wants to choose; a dedicated exception for a caller that already committed. |
| **RUNTIME CAPABILITY CHECK** | `isinstance` against the capability ABC (nominal), a `runtime_checkable` Protocol (structural), or `hasattr` (duck). |
| **TYPE SWITCH** | The growing `isinstance` cascade in the caller — the anti-pattern all three exercises exist to delete. |
| **OPEN/CLOSED** | A fourth family or a third capability adds classes and edits none — the live-edit demo at defense. |
| **STATE vs STRATEGY** | Same shape, different intent: State transitions itself, Strategy is handed in by the client. |
| **ROUND-ROBIN** | Every unordered pair exactly once — n(n−1)/2 battles, and no `itertools` allowed. |

---

## 8. Worth reading — before and during

### 8.1 The books already on the shelf — `42.secret.repo/_books/`

Two of them cover this module almost exercise by exercise. Page numbers below are **printed book pages**; add the offset to jump straight to the right PDF page.

#### Fluent Python — Ramalho, 2nd ed. 2022 *(PDF page = book page **+ 30**)*

| Chapter | Book pp. | For |
| ------- | -------- | --- |
| **Ch 14 — Inheritance: For Better or for Worse** | **487–515** | **ex1 — the chapter of this module.** |
| ↳ The `super()` Function | 488 | why `super()` is not "the parent" |
| ↳ **Multiple Inheritance and Method Resolution Order** | **494** | C3, `__mro__`, diamond |
| ↳ **Mixin Classes** | **500** | exactly the capability classes |
| ↳ ABCs Are Mixins Too | 502 | why capability ABCs combine cleanly |
| ↳ Coping with Inheritance | 510–513 | *Favor Object Composition over Class Inheritance* (510), *Make Interfaces Explicit with ABCs* (511), *Use Explicit Mixins for Code Reuse* (511) — three headings that are the design rationale of ex1 and ex2 |
| **Ch 13 — Interfaces, Protocols, and ABCs** | **431–482** | **ex0's base classes + ex2's `is_valid`** |
| ↳ Two Kinds of Protocols / The Typing Map | 432–434 | the dynamic-vs-static map |
| ↳ **Goose Typing** | **442** | Ramalho's name for ABC-based `isinstance` — the nominal route for `is_valid` |
| ↳ Defining and Using an ABC / ABC Syntax Details | 451, 457 | the mechanics for `Creature` and `CreatureFactory` |
| ↳ Static Protocols → **Limitations of Runtime Protocol Checks** | 466, **471** | why `runtime_checkable` only checks *names*, never signatures |
| ↳ Best Practices for Protocol Design | 476 | if you go structural |
| **Ch 10 — Design Patterns with First-Class Functions** | **341–358** | **ex2 — read with care, see below** |
| ↳ **Classic Strategy** | **342–347** | the ABC version the subject requires |
| ↳ Function-Oriented Strategy → Finding Strategies in a Module | 347–352 | the Pythonic counter-argument |
| ↳ The Command Pattern | 355 | the neighbour pattern, for §4 |

> ⚠️ **Ch 10 will argue against the subject.** Ramalho's thesis is that in Python, first-class functions make a class-per-strategy mostly ceremony. The subject *mandates* the ABC form — so read **Classic Strategy** as the thing you must build, and the function-oriented sections as the objection to have ready. "I know Python lets me collapse this into functions; here's what the class form still buys, and here's what the subject is teaching" is a much stronger defense answer than not knowing the debate exists. Same trap in Ch 11, *Private and "Protected" Attributes in Python* (382) — the honest version of the "expose factories only" rule.

#### Effective Python — Slatkin, 3rd ed. 2024 *(PDF page = book page **+ 27**)*

Short items, 3–8 pages each. **Chapter 7 — Classes and Interfaces** (201–264) is the one.

| Item | Book p. | For |
| ---- | ------- | --- |
| **49 — Prefer Object-Oriented Polymorphism over Functions with `isinstance` Checks** | **205** | the anti-pattern all three exercises exist to delete; read it first |
| **54 — Consider Composing Functionality with Mix-in Classes** | **240** | ex1, straight to the point |
| **53 — Initialize Parent Classes with `super`** | **235** | ex1, cooperative `__init__` and the MRO — the bug that eats your transform state |
| **52 — Use `@classmethod` Polymorphism to Construct Objects Generically** | **230** | ex0: the Pythonic cousin of Abstract Factory, and the best "why not just do it this way?" material |
| 48 — Accept Functions Instead of Classes for Simple Interfaces | 201 | the counter-argument again; know it, don't apply it |
| 55 — Prefer Public Attributes over Private Ones | 245 | Python has no privacy — the export rule, honestly stated |
| 50 — Consider `functools.singledispatch`… | 210 | out of Authorized here, but a strong alternative to name at defense |
| **119 — Use Packages to Organize Modules and Provide Stable APIs** | **588** | `__init__.py`, `__all__`, a stable public surface: the "factories only" rule as an engineering practice |
| **121 — Define a Root Exception to Insulate Callers from APIs** | **595** | ex2's "dedicated exception" — why your own class beats a bare `ValueError` |
| 32 — Prefer Raising Exceptions to Returning `None` | 142 | the `is_valid`-returns-bool vs `act`-raises split |
| 122 — Know How to Break Circular Dependencies | 600 | P06 revision, still useful with ex1 → ex0 |

### 8.2 A reading order that fits the project

| When                               | Read                                                                                                                   |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| **Before writing anything** (~1 h) | Effective **Item 49** (205) → Fluent **Ch 13, Goose Typing** (442–458) → Effective **Item 52** (230)                   |
| **During ex0**                     | Fluent Ch 13, *Defining and Using an ABC* (451–460)                                                                    |
| **During ex1** ⭐                   | Fluent **Ch 14 in full** (487–515) + Effective **Items 53 & 54** (235, 240). This is the densest payoff in the module. |
| **During ex2**                     | Fluent **Ch 10, Classic Strategy** (342–347), then skim 347–352 for the objection + Effective **Item 121** (595)       |
| **Before the defense**             | Fluent Ch 14, *Coping with Inheritance* (510–513) — seven headings that answer "why did you build it this way?"        |

*(`C Programming — K. N. King` is also in `_books/`; nothing for this module.)*

### 8.3 From these notes (in order of usefulness)

| Doc | Why, for this project |
| --- | --- |
| [M2_Python_5_concepts.md](M2_Python_5_concepts.md) | **The direct prerequisite.** §1 (ABC, `@abstractmethod`, overriding), §5.1–5.3 (abstraction, dispatch, nominal vs structural). Re-read before starting ex0. |
| [M2_Python_6_concepts.md](M2_Python_6_concepts.md) | §1 (`__init__.py` as the public face), §2 (re-export & aliases), §5 (`F401`, `__all__`). This is what "expose factories only" is built on. |
| [python_classes.md](../02_Python/02_syntax_flow/python_classes.md) | Class body ordering, and Part B — visibility is only a convention. Directly relevant to the export rule. |
| [python_custom_exceptions.md](../02_Python/04_errors/python_custom_exceptions.md) | For ex2's "dedicated exception with a clear message": what to inherit from, where the message goes. |
| [python_data_model.md](../02_Python/03_data_types/python_data_model.md) | §"Checking a property at runtime" — the `isinstance` / Protocol / `hasattr` comparison behind `is_valid`. |
| [python_naming.md](../02_Python/05_style/python_naming.md) | F3, the `is_` / `has_` trap — the module hands you a method literally named `is_valid`. |

### 8.4 Official docs (short, worth the detour)

- [`abc` — Abstract Base Classes](https://docs.python.org/3/library/abc.html) — the API you'll actually use.
- [The Python 2.3 Method Resolution Order](https://docs.python.org/3/howto/mro.html) — the canonical C3 explanation, still the reference.
- [`typing.Protocol`](https://docs.python.org/3/library/typing.html#typing.Protocol) + [PEP 544](https://peps.python.org/pep-0544/) — if you go structural for `is_valid`.
- Raymond Hettinger, [*Python's `super()` Considered Super!*](https://rhettinger.wordpress.com/2011/05/26/super-considered-super/) — **the** article on cooperative multiple inheritance. If you read one external thing for ex1, read this.

### 8.5 Patterns (online, free)

- [python-patterns.guide](https://python-patterns.guide/) — Brandon Rhodes. Free, and unusually honest: it explains which GoF patterns are pointless in Python and why. The **Abstract Factory** and **Strategy** entries are exactly this project, and it is the best source for the "what does this pattern still buy me in Python?" answer an evaluator will dig for.
- [refactoring.guru — Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory) and [Strategy](https://refactoring.guru/design-patterns/strategy) — diagram-heavy, Python examples, five minutes each. Best for getting the *shape* into visual memory before writing anything.

### 8.6 Not on the shelf yet

- **Architecture Patterns with Python** — Percival & Gregory. Free at [cosmicpython.com](https://www.cosmicpython.com): dependency inversion and "program to an interface" at application scale. The natural sequel once this project clicks. Already listed in [python_reference_books.md](../02_Python/06_resources/python_reference_books.md).
- *Head First Design Patterns* (O'Reilly) — very visual, and its running example is Strategy. Java, but the diagrams carry over.
- *Design Patterns* (GoF, 1994) — the original catalogue. Reference material, not a read-through; useful for quoting an intent verbatim.

---
