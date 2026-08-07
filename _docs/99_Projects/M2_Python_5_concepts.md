# Python Module 05 — Concepts Guide (Abstraction & Polymorphism)

> Subject: *Code Nexus — Polymorphic Data Streams in the Digital Matrix* (`_subjects/en.python_mod5.subject.pdf`) Python ≥ 3.10, flake8 + mypy clean, **comprehensive** type annotations, exception handling that "protects the streams from corruption". Authorized imports: **`abc` and `typing` only** — plus all builtins and all standard types/collections.

---

## 0. The big picture — "one interface, many behaviours"

Module 03 gave you containers, module 04 gave you streams of bytes. This module is about **one caller driving many different implementations without knowing which one it holds**. Three ideas stack on top of each other, one per exercise:

| Ex  | Mechanism                     | Question it answers                                            |
| --- | ----------------------------- | -------------------------------------------------------------- |
| ex0 | **Abstract base class (ABC)** | How do I *force* every processor to expose the same interface? |
| ex1 | **Subtype polymorphism**      | How does one loop drive processors it has never heard of?      |
| ex2 | **Protocol / duck typing**    | How do I accept a plugin that doesn't inherit from me at all?  |

### The two flavours of "same interface" — the distinction of the module

| | **Nominal** (ex0-1) | **Structural** (ex2) |
| --- | --- | --- |
| Tool | `abc.ABC` + `@abstractmethod` | `typing.Protocol` |
| Rule | "you *are* a `DataProcessor` **because you inherit from it**" | "you *are* an `ExportPlugin` **because you have the method**" |
| Enforced | at **runtime** (instantiation fails) | at **type-check time** (mypy) |
| Coupling | plugin must import & subclass your base | plugin knows nothing about you |

Both give polymorphism. The subject deliberately makes you use **one of each** so you can compare them at defense — that comparison is the single most likely question of the whole module.

### The data flow to keep in your head

```
stream (list of Any)
   │  process_stream: ask each registered processor "validate(element)?"
   ▼
[ NumericProcessor ] [ TextProcessor ] [ LogProcessor ]     ← internal FIFO queues
   │  output() → (rank, str), oldest first, item removed
   ▼
output_pipeline(nb, plugin) → plugin.process_output([(rank, str), ...])   ← CSV / JSON
```

---

## 1. Ex0 — ABSTRACT CLASSES (`abc.ABC`, `@abstractmethod`, overriding)

### The concept

An **abstract base class** is a class that exists to be inherited from, never instantiated. It declares *what* subclasses must provide (abstract methods) and may also provide *shared* working code (concrete methods) — here `output()`.

```python
import abc


class Shape(abc.ABC):                 # inheriting ABC installs ABCMeta
    @abc.abstractmethod
    def area(self) -> float: ...      # no body: a contract, not an implementation

    def describe(self) -> str:        # concrete: inherited as-is by every subclass
        return f"area={self.area()}"  # calls the subclass version — see ex1


Shape()      # TypeError: Can't instantiate abstract class Shape
             # without an implementation for abstract method 'area'
```

The three facts to be able to state:

1. **`ABC` is just a class with `ABCMeta` as metaclass** — inheriting it is what activates the check. `@abstractmethod` alone on a plain class does nothing.
2. **The check happens at instantiation, not at definition.** A subclass that forgets one abstract method is a perfectly legal class object — it explodes only when someone calls it. That is a runtime guarantee, not a static one.
3. **An ABC can hold real code.** `output()` is written once in the base and inherited by all three specialized classes — that is the *code reuse* half of inheritance, while the abstract methods are the *specialization* half.

### The class hierarchy the subject asks for

```
          DataProcessor (ABC)
          ├── validate(self, data: Any) -> bool     @abstractmethod
          ├── ingest(self, data: Any) -> None       @abstractmethod
          └── output(self) -> tuple[int, str]       concrete, NOT overridden
                 ▲              ▲              ▲
    NumericProcessor      TextProcessor    LogProcessor
```

| Class               | Accepts                                                    | Stores                       |
| ------------------- | ---------------------------------------------------------- | ---------------------------- |
| `NumericProcessor`  | `int`, `float`, and lists of both (**mixed allowed**)       | converted to `str`, item by item |
| `TextProcessor`     | `str`, and lists of `str`                                   | as-is, item by item          |
| `LogProcessor`      | `dict[str, str]`, and lists of those                        | converted to `str`, item by item |

"Keeping each item separated" is the key phrase: ingesting a 5-element list must leave **5 retrievable pieces**, not one blob — `output()` hands them back one at a time.

### OVERRIDING — and the signature question

**Overriding** = a subclass defines a method with the same name as its parent; the subclass version wins for instances of that subclass. Python has **no overloading**: two `def`s with the same name in one class means the second silently replaces the first (`typing.overload` exists but only talks to the type checker, never changes runtime behaviour).

The subject splits the two abstract methods on purpose:

- **`validate` keeps the base signature** (`data: Any`) in every subclass — it must accept *anything* precisely because its job is to answer "is this mine?" about data of unknown type.
- **`ingest` narrows** to the types each subclass really handles, e.g. `int | float | list[int | float]` (3.10 union syntax, no `typing.Union` needed).

Narrowing a parameter type in a subclass normally **violates the Liskov Substitution Principle** and mypy flags it (`[override]`): a caller holding a `DataProcessor` could legally pass a `str`. It passes here **only because the base declares `Any`**, and mypy treats `Any` as compatible in both directions. Be able to say that out loud — "the base uses `Any`, which is why the narrowed override type-checks" — it is exactly the kind of thing a good evaluator digs into.

### The deliberate mypy warning

> *"Test at least one invalid data item with the `ingest` method without prior validation, and check that it raises an exception. This will leave you with a mypy warning, on purpose."*

The warning is on the **call site**, not the class: passing `"foo"` to a `NumericProcessor.ingest` whose annotation says numbers is an `arg-type` error. It is wanted — it proves the annotations are doing their job. The lesson: **type hints are not runtime validation**. mypy complains; Python still runs the call; so `ingest` must defend itself with a `raise` (`Got exception: Improper numeric data` in the example). Do **not** silence it with `# type: ignore` unless you can justify why — the subject asks for the warning to exist.

### `output()` — a FIFO queue with a persistent rank

```
output(self) -> tuple[int, str]
```

Two things come back in the tuple:

- the **oldest** stored piece (First-In-First-Out), which is then **removed**;
- its **processing rank** *within that processor* — assigned at ingest time, starting at 0 and **never reset**.

Trace it from the ex2 example: after 4 numeric items (ranks 0-3) three are consumed; the next batch of 7 continues at rank 4; the JSON export then prints `item_3, item_4, item_5…`. So the rank travels **with** the piece of data and the counter is monotonic per processor — it doubles as the "total processed" figure in ex1's statistics. Design consequence: storing bare strings is not enough, the rank has to be recoverable when the item is popped.

Edge case to have an answer for: `output()` on an **empty** processor — return something, raise, or guard from the caller? Pick one and be consistent, the pipeline in ex2 hits it (asking for 5 items when only 4 remain).

### Exceptions

Only `abc` and `typing` may be imported, but **classes are free** — so a custom exception class (module 02 territory) is available if you want typed failures, and built-ins (`TypeError` for a wrong type, `ValueError` for a wrong value) are always allowed. Know why you chose yours. Whatever you raise, the caller must be able to catch it without catching everything else.

---

## 2. Ex1 — SUBTYPE POLYMORPHISM (one loop, many processors)

### The concept

**Polymorphism** = the same call expression executes different code depending on the runtime type of the object. Python resolves `obj.method()` by looking through `type(obj).__mro__` **at call time** — nothing is decided at compile time, which is why `DataStream` can drive a processor class that did not exist when it was written.

```python
for proc in self.processors:      # list[DataProcessor] — static type
    if proc.validate(element):    # runs NumericProcessor.validate, or Text…, or Log…
        proc.ingest(element)
```

That loop is the whole exercise's idea: `DataStream` only ever speaks the **`DataProcessor` interface** (`validate` / `ingest` / `output`), and the ABC of ex0 is what guarantees those three names exist on every registered object.

### The three methods to build

| Method                                          | Role                                                                |
| ----------------------------------------------- | ------------------------------------------------------------------- |
| `register_processor(self, proc: DataProcessor)`  | add a processor to the stream — note the **base-class** annotation   |
| `process_stream(self, stream: list[typing.Any])` | route each element to a processor that validates it; print an error if none does |
| `print_processors_stats(self)`                   | per-processor `total processed` + `remaining`, or the "no processor" line |

`register_processor` annotating its parameter as `DataProcessor` (not a union of the three concrete classes) *is* the polymorphism, expressed in the type system.

### Statistics — two different counters

```
Numeric Processor: total 8 items processed, remaining 5 on processor
```

- **total** = cumulative, never decreases — the same counter that produces the rank in ex0.
- **remaining** = current queue length, drops as `output()` is consumed.

The empty case has its own line (`No processor found, no data`), printed before any registration.

### Routing nuances worth anticipating

- **First match wins.** Registration order matters as soon as two processors could both accept an element. Deciding "first that validates" vs "check they are mutually exclusive" is a design choice you should be able to defend.
- **The empty list `[]`.** If validation is "every element is of my type", an empty list passes for *all three* processors (`all([])` is `True`) and contributes zero items. Decide whether that is acceptable.
- **`isinstance(True, int)` is `True`.** `bool` is a subclass of `int`, so a naive numeric check swallows `True`/`False`. Classic trap — know it even if you choose to allow it.
- **Nested structure.** The subject's stream contains lists *of* dicts and lists *of* numbers, so validation has to look **inside** the container, not just at its outer type.
- **Unroutable elements** are reported, not crashed on: `DataStream error - Can't process element in stream: <element>`.

### The subject's explicit question — know this cold

> *"How does polymorphism allow the `DataStream` to handle different data types in the stream without knowing their specific implementations? What are the benefits of this design approach?"*

The shape of a strong answer: `DataStream` depends on the **abstraction**, not the concretions — it calls `validate`/`ingest` and Python dispatches to the real class at runtime. Benefits to name: no `if isinstance(...)` chain to maintain; adding a fourth processor requires **zero** changes to `DataStream` (**Open/Closed Principle**); each processor's rules stay in one place (single responsibility); and each is independently testable. The contrast to draw is the type-switch version of the same loop, which grows with every new type.

---

## 3. Ex2 — PROTOCOLS & DUCK TYPING (the plugin system)

### The concept

**Duck typing**: "if it walks like a duck and quacks like a duck, it's a duck" — Python only cares that the object *has* the method you call, never what it inherits from. A **`typing.Protocol`** is that idea made checkable: it declares a required shape, and any class with a matching method is a subtype **without inheriting anything** (*structural subtyping*, PEP 544).

```python
import typing


class Greeter(typing.Protocol):
    def greet(self, name: str) -> None: ...   # required shape, no implementation


class Cowboy:                     # inherits NOTHING — never heard of Greeter
    def greet(self, name: str) -> None:
        print(f"Howdy {name}")


def welcome(g: Greeter) -> None:  # mypy accepts Cowboy() here
    g.greet("Nexus")
```

Contrast with ex0 in one line: **ABC = "prove your ancestry", Protocol = "show me your shape"**. That is the sentence to have ready.

### Protocol details that come up at defense

- A Protocol body holds **signatures only** — `...` or a docstring as body.
- `isinstance(x, Greeter)` raises `TypeError` **unless** the protocol is decorated `@typing.runtime_checkable` — and even then it checks only *method names*, not signatures. If you reach for `isinstance` here, know that limitation.
- Instantiating the protocol itself is meaningless; it is a static description.
- Protocols are the reason a plugin author can write an exporter **without importing your code at all** — the decoupling argument for a plugin system.

### The pipeline method

```
output_pipeline(self, nb: int, plugin: ExportPlugin) -> None
```

Reading the subject's example carefully tells you the semantics:

- called **after** `process_stream`;
- consumes **up to** `nb` items from **each** registered processor via `output()` (Text had only 4 left when 5 were asked → 4 exported, 0 remaining — so it stops early instead of raising);
- hands each processor's harvest to the plugin as **one** `list[tuple[int, str]]` — the example prints one `CSV Output:` / `JSON Output:` block **per processor**, so the plugin is called once per processor, not once per item;
- the tuple type is exactly `DataProcessor.output`'s return type — that is why the subject spells out "matches the return value of the `output` method".

### The two export plugins

Hand-built strings — **no `csv` / `json` import is authorized**, and the subject says so explicitly.

| Plugin   | Uses the tuple's… | Shape from the example                                        |
| -------- | ----------------- | -------------------------------------------------------------- |
| **CSV**  | value only        | `3.14,-1,2.71` — values joined by `,` on one line               |
| **JSON** | rank **and** value | `{"item_3": "42", "item_4": "21"}` — `item_<rank>` as key, values quoted |

The rank is what makes the two formats differ in information content: CSV drops it, JSON promotes it to the key. Note that both plugins receive the *same* list — that is the point of a plugin system.

Two honest caveats to raise before an evaluator does: hand-rolled JSON is **fragile** (a value containing `"` or `\` produces invalid JSON — real code escapes, or uses the `json` module), and everything is a string by then because `output()` returns `str`, so JSON numbers come out quoted (`"42"`, as in the subject's own example).

---

## 4. Module-wide rules & traps

- **Imports: `abc` and `typing` only.** No `json`, no `csv`, no `dataclasses`, no `collections.deque` — the FIFO is built from a standard list.
- **Python ≥ 3.10** → `int | float` unions, `list[str]` / `tuple[int, str]` builtin generics. No `typing.List` / `typing.Union` needed.
- **"Comprehensive type annotations", checked with mypy** — every parameter, every return (`-> None` included), on methods as well as functions. The *only* expected mypy complaint is the deliberate ex0 one.
- **flake8-clean**: 79 columns, blank-line rules around classes/methods.
- **Exception handling protects the streams**: invalid data raises inside `ingest`, unroutable elements are reported by `DataStream`, and nothing crashes the script. Catch specific exceptions, never bare `except`.
- **Each exercise builds on the previous file** — ex1 is ex0 + `DataStream`, ex2 is ex1 + protocol and plugins, each as its own self-contained file in `ex0/`, `ex1/`, `ex2/`. Copy forward, don't import across directories.
- **Every file is runnable**: `python3 data_processor.py` must print the demo scenario, so each exercise needs its own test scenario under a main guard (see [python_main_guard.md](../02_Python/02_syntax_flow/python_main_guard.md)).
- **Output text is yours**, structure is the subject's: keep the sections, statistics lines and error lines recognizable.
- Defense warning from the subject: you may be asked to **extend the system live** — "add a fourth processor type", "add an XML plugin". If your design is right that is a new class and one `register_processor` call, with **no edit** to `DataStream`. Rehearse it.

---

## 5. Terminology — every term of the module, defined

Grouped by theme. Terms in **bold** are the ones an evaluator can legitimately ask you to define on the spot.

### 5.1 Classes & abstraction

| Term | Definition |
| ---- | ---------- |
| **Class** | A template describing state (attributes) and behaviour (methods); calling it produces an instance. |
| **Instance / object** | One concrete value built from a class, with its own attribute values. |
| **Instantiation** | The act of calling a class (`NumericProcessor()`) — the moment Python checks that no abstract method is left unimplemented. |
| **Base class / superclass / parent** | The class being inherited from (`DataProcessor`). |
| **Subclass / derived class / child** | The class that inherits (`TextProcessor`); it *is a* `DataProcessor`. |
| **Inheritance** | Reusing a base class's attributes and concrete methods, while adding or replacing behaviour. |
| **Composition** | The alternative to inheritance: holding another object as an attribute and delegating to it ("has a" instead of "is a"). |
| **Abstract class (ABC)** | A class meant to be inherited, never instantiated; it declares an interface and may carry shared concrete code. |
| **Abstract method** | A method declared with `@abc.abstractmethod` and no real body — a contract every concrete subclass must fulfil. |
| **Concrete method** | A fully implemented method in the ABC, inherited as-is by subclasses (here `output()`). |
| **`abc.ABC`** | The helper base class whose only job is to set `ABCMeta` as metaclass — inheriting it is what activates the enforcement. |
| **`ABCMeta`** | The metaclass that performs the "are all abstract methods implemented?" check at instantiation time. |
| **Metaclass** | The class of a class — it controls how classes are created and how their instances are built. |
| **Interface** | The set of method names and signatures a caller relies on, independent of any implementation behind them. |
| **Contract** | The promise attached to an interface: what the caller may pass, what it gets back, what may be raised. |
| **Implementation** | The concrete code fulfilling a contract; several implementations can share one interface. |

### 5.2 Polymorphism & method dispatch

| Term | Definition |
| ---- | ---------- |
| **Polymorphism** | One call expression producing different behaviour depending on the object it acts on. |
| **Subtype polymorphism** | The flavour used in ex1: any subtype of `DataProcessor` can stand in wherever the base type is expected. |
| **Ad-hoc polymorphism** | Behaviour chosen by argument types (overloading in other languages) — absent at runtime in Python. |
| **Parametric polymorphism** | Code written once for any element type (generics, `list[T]`) — what `list[typing.Any]` gestures at. |
| **Dynamic dispatch / late binding** | Resolving `obj.method` at **call time** by walking `type(obj).__mro__` — the reason `DataStream` needs no knowledge of its processors. |
| **MRO** | Method Resolution Order — the linearized list of classes Python searches for an attribute. |
| **Overriding** | Redefining an inherited method in a subclass; the subclass version is the one dispatched. |
| **Overloading** | Same name, several signatures — **does not exist** in Python at runtime: the last `def` wins. |
| **`typing.overload`** | Declares several signatures for the type checker only; the runtime behaviour is unchanged. |
| **`super()`** | Explicitly calls the next implementation in the MRO — how an override extends rather than replaces. |
| **LSP (Liskov Substitution Principle)** | A subclass must be usable anywhere its base is; narrowing a parameter type breaks it. |
| **Covariance / contravariance** | Return types may narrow (covariant), parameter types may only widen (contravariant) — the formal reason `ingest`'s narrowing is unsound, and why `Any` in the base is the escape hatch. |

### 5.3 Typing — nominal vs structural

| Term | Definition |
| ---- | ---------- |
| **Type annotation / type hint** | A declaration of the expected type; **never enforced at runtime**, only read by tools like mypy. |
| **Static check** | Verification done before running (mypy) — catches contradictions in annotations. |
| **Runtime check** | Verification done while running (`isinstance`, a `raise` inside `ingest`) — the only thing that actually protects the data. |
| **Nominal subtyping** | "You are a `DataProcessor` **because you inherit from it**" — what the ABC of ex0 enforces. |
| **Structural subtyping** | "You are an `ExportPlugin` **because you have the methods**" — what `typing.Protocol` describes (PEP 544). |
| **Duck typing** | The dynamic version of the same idea: Python only cares that the attribute exists when you call it. |
| **`typing.Protocol`** | A class declaring a required shape (signatures only); matching classes conform without inheriting anything. |
| **`@typing.runtime_checkable`** | Decorator allowing `isinstance()` on a Protocol — it verifies **method names only**, never signatures. |
| **`typing.Any`** | "Type unknown, checks off" — compatible with every type in both directions, which is what lets the overrides narrow. |
| **Union type (`int \| float`)** | "One of these types"; 3.10 syntax replacing `typing.Union[int, float]`. |
| **Builtin generics (`list[str]`, `tuple[int, str]`)** | Parameterized standard collections, usable directly since 3.9 — no `typing.List` needed. |
| **`isinstance()`** | Runtime type test; remember `isinstance(True, int)` is `True` because `bool` subclasses `int`. |
| **mypy** | The static type checker the subject requires you to run clean — except for the one deliberate ex0 warning. |
| **`arg-type` / `override`** | The two mypy error codes of this module: passing a wrong argument type, and an override incompatible with its base. |
| **`# type: ignore`** | Silences a mypy error on one line — to be justified, and *not* to be used on the deliberate warning. |
| **flake8** | The style linter (79 columns, blank lines, unused names) that must also pass clean. |

### 5.4 Design principles & architecture

| Term | Definition |
| ---- | ---------- |
| **Open/Closed Principle** | Open for extension, closed for modification — a fourth processor must require zero edit to `DataStream`. |
| **Single Responsibility Principle** | One class, one reason to change: each processor owns its own validation rules. |
| **Dependency inversion / program to an interface** | High-level code depends on the abstraction (`DataProcessor`), not on the concrete classes. |
| **Coupling / decoupling** | How much one component must know about another; a Protocol drops it to zero — the plugin never imports your code. |
| **Plugin architecture** | Extending a system with components it never imports, by agreeing only on an interface. |
| **Registration** | Handing an implementation to the system at runtime (`register_processor`) instead of hard-coding it. |
| **Type switch / `isinstance` chain** | The anti-pattern polymorphism replaces: a growing `if isinstance(...)` cascade in the caller. |
| **EAFP vs LBYL** | "Easier to Ask Forgiveness" (try/except) vs "Look Before You Leap" (`validate()` then `ingest()`) — this module uses LBYL for routing and EAFP as the safety net. |

### 5.5 The module's own vocabulary

| Term | Definition |
| ---- | ---------- |
| **Stream** | The `list[Any]` of heterogeneous elements handed to `process_stream`. |
| **Element / item** | One entry of the stream; a list-shaped element yields several stored items. |
| **Processor** | An object implementing the `DataProcessor` interface, owning one data type and one queue. |
| **`validate`** | "Is this element mine?" — accepts `Any`, returns `bool`, never stores anything. |
| **`ingest`** | Stores an element, item by item, and **raises** if the data is not the type it handles. |
| **`output`** | Pops the oldest stored item and returns `(rank, value)`. |
| **FIFO queue** | First-In-First-Out storage: the first item ingested is the first one returned. |
| **Enqueue / dequeue** | Adding at the back (ingest) and removing from the front (output). |
| **Processing rank** | The per-processor counter assigned at ingest, starting at 0, **never reset**, carried with the item. |
| **Total processed** | The cumulative ingest count — the same counter as the rank, never decreasing. |
| **Remaining** | The current queue length, which drops as `output()` is consumed. |
| **Pipeline** | `output_pipeline`: harvest up to `nb` items from each processor and hand each harvest to the plugin. |
| **Export plugin** | A class matching the `ExportPlugin` protocol, turning `list[tuple[int, str]]` into a formatted string. |
| **Serialization** | Turning in-memory data into a textual format (CSV, JSON) that can be stored or transmitted. |
| **CSV / JSON** | The two target formats, hand-built here — the `csv` and `json` modules are **not** authorized. |
| **Escaping** | Protecting the format's special characters (`"`, `\`) in a value — the known weakness of hand-rolled JSON. |

### 5.6 Errors & exceptions

| Term | Definition |
| ---- | ---------- |
| **Exception** | An object signalling an abnormal situation, propagating up the call stack until caught. |
| **`raise`** | Emits an exception — how `ingest` refuses invalid data. |
| **`try` / `except`** | Catches a specific exception type; a bare `except:` swallows everything and is forbidden here. |
| **Custom exception class** | A class inheriting `Exception`, giving the caller a precise type to catch. |
| **Exception hierarchy** | Exceptions are classes, so `except Exception` catches all subclasses — precision matters. |
| **`TypeError` / `ValueError`** | Wrong type vs right type but unusable value — the built-in pair to choose between. |
| **Graceful degradation** | Reporting an unroutable element and carrying on, instead of crashing the whole stream. |

---

## 6. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **ABSTRACT CLASS / ABC** | A class that declares an interface and cannot be instantiated — inherit `abc.ABC` to get the enforcement. |
| **`@abstractmethod`** | Marks a method subclasses *must* implement; a missing one makes instantiation raise `TypeError`. |
| **INTERFACE** | The set of method names and signatures a caller relies on, independent of any implementation behind them. |
| **INHERITANCE** | A subclass reuses the base's attributes and concrete methods while adding or replacing behaviour. |
| **OVERRIDING** | Redefining an inherited method in a subclass; the subclass version is the one dispatched at runtime. |
| **OVERLOADING** | Same name, several signatures — **does not exist** in Python at runtime; `typing.overload` only informs the type checker. |
| **POLYMORPHISM (subtype)** | One call expression running different code depending on the object's runtime type. |
| **DYNAMIC DISPATCH** | The runtime lookup of `obj.method` through `type(obj).__mro__` — why the base class needn't know its subclasses. |
| **MRO** | Method Resolution Order — the linearized list of classes Python searches for an attribute. |
| **LISKOV SUBSTITUTION (LSP)** | A subclass must be usable anywhere its base is; narrowing a parameter type breaks it, which is why the base declares `Any`. |
| **DUCK TYPING** | Compatibility judged by the methods an object actually has, not by what it inherits from. |
| **`typing.Protocol`** | A declared shape giving *structural* subtyping — a class matches by having the methods, with no inheritance. |
| **NOMINAL vs STRUCTURAL** | ABC checks ancestry (nominal, at runtime); Protocol checks shape (structural, at type-check time). |
| **`@runtime_checkable`** | Lets `isinstance()` work on a Protocol — method **names** only, signatures are not verified. |
| **`typing.Any`** | The "any type, checks disabled" hint — compatible with everything in both directions, which is what lets overrides narrow. |
| **PLUGIN ARCHITECTURE** | Extending a system with components it never imports, by agreeing only on an interface. |
| **OPEN/CLOSED PRINCIPLE** | Open for extension, closed for modification — a new processor or plugin should require zero edits to `DataStream`. |
| **FIFO** | First-In-First-Out — `output()` returns the oldest stored item and removes it. |
| **PROCESSING RANK** | The per-processor counter assigned at ingest, never reset, carried with the item and reused as the "total processed" figure. |

---
