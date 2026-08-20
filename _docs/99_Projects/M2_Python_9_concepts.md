# Python Module 09 — Concepts Guide (Pydantic: Models, Validation & Nested Structures)

> Subject: *Cosmic Data — Discover Pydantic Models & Validation* (`_subjects/en.python_mod09.subject.pdf`, v3.0). Python ≥ 3.10, flake8 + mypy clean, **comprehensive** type annotations, "exception handling should protect the data streams from corruption". **Pydantic 2.x, installed with `pip`, inside a virtual environment** — the module 08 workflow is now a prerequisite, not a topic. One directory per exercise (`ex0/`, `ex1/`, `ex2/`), each `Authorized: None` beyond Pydantic, the standard library, and the provided `data_generator.py` / `data_exporter.py` / `generated_data/`. The subject's own warning: *"Avoid deprecated decorators like `@validator` — use `@model_validator` for custom validation instead."*

---

## 0. The big picture — "the type hint stops being a comment"

Everything you have written since module 00 carried type annotations that **do nothing at runtime**. mypy reads them, the interpreter throws them away. Pydantic is the module where that flips: it *reads the annotations at runtime* and builds a validator from them. The same `crew_size: int` that used to be documentation becomes an executable rule.

That single sentence is the module. Everything else is which rules you can express, and where.

| Ex  | Layer                          | Question it answers                                               | The new tool                              |
| --- | ------------------------------ | ------------------------------------------------------------------ | ----------------------------------------- |
| ex0 | **Field-level validation**     | Is each value individually well-formed?                            | `BaseModel` + `Field(...)` constraints     |
| ex1 | **Model-level validation**     | Are the values *consistent with each other*?                       | `@model_validator(mode="after")` + `Enum`  |
| ex2 | **Structural validation**      | Does a tree of objects satisfy rules about the whole tree?         | nested models + `list[Model]`              |

### Where a rule belongs — the decision the whole module is graded on

```
      raw input (dict / JSON / CSV row)
                │
                ▼
   ┌────────────────────────────────┐
   │  1. per-field: type + coercion │  crew_size must be an int
   │     annotation                 │
   ├────────────────────────────────┤
   │  2. per-field: constraints     │  ...between 1 and 20        ← Field(ge=1, le=20)   ex0
   │     Field(...)                 │
   ├────────────────────────────────┤
   │  3. cross-field: the model     │  a long mission needs 50%   ← @model_validator      ex1/ex2
   │     as a whole                 │  experienced crew
   └────────────────────────────────┘
                │
                ▼
      a valid instance — or ValidationError, never a half-built object
```

**A rule about one value goes in `Field`. A rule that needs two values goes in a model validator.** Every requirement in the three exercises falls on one side of that line, and being able to sort them instantly is the single most useful thing to rehearse. `station_id: 3–10 characters` is `Field`. `physical contact reports must be verified` needs `contact_type` *and* `is_verified`, so it is a model validator. No exceptions in this subject.

### The guarantee that makes it worth it

A Pydantic model is a **parsing boundary**: on the far side of a successful construction, every field is the declared type and satisfies every constraint. You never write a defensive `if crew_size > 20` again, anywhere downstream, because a `SpaceStation` that violates it **cannot exist**. That is the argument to make at defense — Pydantic is not "checks I could have written by hand", it is *moving all the checks to one place so the rest of the program has none*.

---

## 1. Ex0 — BASEMODEL & FIELD CONSTRAINTS

### The concept

`BaseModel` is a class whose **class body is a schema**. Each annotated name becomes a field; the annotation is the type rule; the assigned value is either the default or a `Field(...)` carrying extra rules.

```python
from pydantic import BaseModel, Field


class Sample(BaseModel):
    code: str = Field(min_length=3, max_length=10)   # required + constrained
    ratio: float = Field(ge=0.0, le=100.0)           # required + bounded
    active: bool = True                              # optional, defaults to True
    note: str | None = Field(default=None, max_length=200)   # optional, nullable, bounded
```

Three things happen at **class creation**, not at instantiation: the annotations are collected, a validator is compiled for each field, and the whole thing is handed to `pydantic-core`, a Rust engine. Validation at runtime is therefore not a pile of Python `if`s — which is the honest answer to "why not just write the checks yourself?".

### `Field(...)` — the constraint vocabulary

| Target | Argument | Means |
| ------ | -------- | ----- |
| `str` | `min_length` / `max_length` | length bounds |
| `str` | `pattern` | a regex the whole value must match |
| numbers | `gt` / `ge` / `lt` / `le` | strict / inclusive bounds |
| numbers | `multiple_of`, `allow_inf_nan` | divisibility; whether `inf`/`nan` pass |
| collections | `min_length` / `max_length` | number of items (ex2's `1–12` crew) |
| any | `default` / `default_factory` | the value, or a callable for mutable defaults |
| any | `strict` | disable coercion for this field only |
| docs | `description`, `examples`, `alias` | metadata; feeds the generated JSON Schema |

Two styles exist and both are correct; v2 documentation leans toward the second:

```python
code: str = Field(min_length=3, max_length=10)                        # classic
code: Annotated[str, Field(min_length=3, max_length=10)]              # v2-preferred, composable
```

`Annotated` keeps the *type* and the *constraints* separable, which matters as soon as you want to reuse `StationId` in two models. Pick one, use it consistently, and be able to say why.

> **Required vs optional — the trap.** `x: int` is required. `x: int = 0` is optional. `x: int | None` **is still required** — it may be `None`, but it must be *provided*. `x: int | None = None` is the optional-and-nullable one. The subject's `notes: Optional string` needs the last form; the difference between rows two and three of that list is a classic defense question.

### Coercion — the subject asks about it directly

> *"Think About: How does Pydantic's automatic type conversion work? What happens when you pass a string timestamp to a datetime field?"*

Pydantic v2 validates in **smart mode** by default: it accepts an input whose type is not the declared one when the conversion is unambiguous and lossless.

| Declared | Input | Result | Why |
| -------- | ----- | ------ | --- |
| `int` | `"42"` | `42` | lossless string→int |
| `int` | `"42.5"` / `"abc"` | ❌ `ValidationError` | not an integer |
| `int` | `42.0` | `42` | no fractional part |
| `int` | `42.5` | ❌ | would lose information |
| `float` | `42` | `42.0` | widening |
| `bool` | `"yes"`, `"true"`, `1` | `True` | a fixed accepted set — **not** Python truthiness |
| `bool` | `"maybe"` | ❌ | not in the set |
| `datetime` | `"2024-03-01T12:00:00Z"` | `datetime(...)` | **ISO 8601 parsing** — the subject's question |
| `datetime` | `1709294400` | `datetime(...)` | int/float read as a Unix timestamp |
| `Enum` | `"radio"` | `ContactType.RADIO` | looked up **by value** |

Note the contrast with plain Python: `bool("False")` is `True`, but Pydantic rejects `"False"`-adjacent junk and accepts only a known vocabulary. That is the difference between a cast and a *parse*.

The counterpart is **strict mode**, available at three scopes: `Field(strict=True)`, `model_config = ConfigDict(strict=True)`, or the `StrictInt` / `StrictStr` aliases. Knowing that lax is the default and that strict exists — and having an opinion on which suits ingesting CSV — is the full answer to the Think About box.

### `ValidationError` — reading it, and printing the one line the subject wants

Pydantic never raises `ValueError` at you and never half-builds an object. It collects **every** failure and raises one `ValidationError` at the end.

```python
try:
    SpaceStation(**bad_data)
except ValidationError as exc:
    for err in exc.errors():
        print(err["loc"], err["type"], err["msg"])
```

| Key | Contents |
| --- | -------- |
| `loc` | a **tuple** locating the failure: `("crew_size",)`, or `("crew", 0, "age")` in ex2 |
| `type` | machine-readable code: `less_than_equal`, `string_too_short`, `int_parsing`, `missing` |
| `msg` | the human sentence — this is what the subject's expected output prints |
| `input` | the offending value |

The standard v2 messages, worth recognising on sight because the subject reproduces one verbatim:

| Constraint | Message |
| ---------- | ------- |
| `le=20` | `Input should be less than or equal to 20` |
| `ge=1` | `Input should be greater than or equal to 1` |
| `min_length=3` | `String should have at least 3 characters` |
| `max_length=200` | `String should have at most 200 characters` |
| wrong type | `Input should be a valid integer` |
| absent | `Field required` |

The expected output shows exactly `Input should be less than or equal to 20` — one line, no traceback, no `loc` prefix. That means reaching into `errors()` and taking `msg`, not printing `str(exc)` (which is a multi-line report with a header and a URL). **Match the shape.** And note that "Expected validation error:" is the subject's own framing: the failure is a *demonstration*, so it must be caught and displayed calmly, never allowed to terminate the program.

### The ex0 requirement map

| Subject requirement | Where it goes |
| ------------------- | ------------- |
| `station_id`: String, 3–10 characters | annotation `str` + length constraints |
| `name`: String, 1–50 characters | same |
| `crew_size`: Integer, 1–20 people | annotation `int` + inclusive bounds |
| `power_level` / `oxygen_level`: Float, 0.0–100.0 | annotation `float` + inclusive bounds |
| `last_maintenance`: DateTime field | `datetime` — coercion does the parsing for you |
| `is_operational`: Boolean, defaults to True | annotation + a plain default; **no `Field` needed** |
| `notes`: Optional string, max 200 characters | nullable **with** a default, plus a length bound |
| `main()`: valid instance, then an invalid one | construct, print, then a guarded construction |

---

## 2. Ex1 — MODEL VALIDATORS & ENUMS

### The concept

A field validator sees one value. A **model validator** sees the whole object, so it is where rules involving *two or more fields* live. Pydantic v2 offers it in three modes:

| Mode | Receives | Returns | Use it for |
| ---- | -------- | ------- | ---------- |
| `mode="before"` | the **raw input** (usually a `dict`), as a `classmethod` | the (possibly rewritten) input | normalising or renaming keys before any typing happens |
| `mode="after"` | the **constructed model instance** (`self`) | **`self`** | cross-field business rules — what this subject wants |
| `mode="wrap"` | input + a handler to call | the model | intercepting both sides; rarely needed |

```python
from pydantic import BaseModel, model_validator


class Sample(BaseModel):
    kind: str
    verified: bool

    @model_validator(mode="after")
    def check_consistency(self) -> "Sample":
        if self.kind == "strict" and not self.verified:
            raise ValueError("strict records must be verified")
        return self          # ← forgetting this is the #1 bug in this exercise
```

> *"The `@model_validator` decorator allows you to validate the entire model after all fields have been validated. Remember to return self at the end of your validator function."*

The subject says it because a validator returning `None` makes Pydantic hand you `None` in place of your model, and the failure surfaces far from its cause. mypy catches it if — and only if — you annotate the return type. That is a genuinely good reason to annotate here.

### The three rules of writing a validator

1. **Raise `ValueError`, never `ValidationError`.** Pydantic catches your `ValueError` (or `AssertionError`) and folds it into the single `ValidationError` it raises to the caller, with the right `loc` attached. Constructing a `ValidationError` yourself is not the API.
2. **`mode="after"` runs only if every field already validated.** If `signal_strength` failed its bounds check, your cross-field rule never executes — and it doesn't need to defend against a missing attribute.
3. **It is a method on the instance, not a `classmethod`** in `after` mode (`before` is the opposite). Getting these backwards is the second most common error.

### `@field_validator` — the neighbour you should be able to name

The subject only requires `@model_validator`, but "why not the other one?" is a fair question:

| | `@field_validator("x")` | `@model_validator(mode="after")` |
| --- | --- | --- |
| Sees | one field's value | the whole instance |
| Runs | during that field's validation | after **all** fields are done |
| For | a rule expressible about a single value | a rule relating several values |
| Is a | `classmethod` | instance method |

`Contact ID must start with "AC"` is genuinely a single-field rule — a `@field_validator`, or even a `pattern=r"^AC"` in `Field`, would express it more precisely. The subject groups it with the others; note the nuance, implement what is asked, and say at defense that you noticed. *(There are three ways to express that rule: regex constraint, field validator, model validator. Being able to rank them is worth more than picking the "right" one.)*

### Enums — and the formatting trap

```python
from enum import Enum


class ContactType(str, Enum):
    RADIO = "radio"
    VISUAL = "visual"
```

Inheriting `str` alongside `Enum` makes members usable as strings and JSON-serialisable. Pydantic validates by **value**: input `"radio"` becomes `ContactType.RADIO`; `"morse"` raises with `Input should be 'radio', 'visual', 'physical' or 'telepathic'`.

> ⚠️ **Printing an enum is version-dependent.** For `class C(str, Enum)`, `f"{C.RADIO}"` yields `radio` on Python 3.10 but `ContactType.RADIO` on 3.11+, because 3.11 changed `Enum.__format__` for mixin enums. The expected output is `Type: radio`. Three safe routes: print `.value` explicitly, use `enum.StrEnum` (3.11+ only, and the subject allows 3.10), or set `model_config = ConfigDict(use_enum_values=True)` so the model stores the raw string instead of the member. **Verify your output on the interpreter the reviewer will use** — this is exactly the kind of drift that a fresh-clone run on another machine exposes.

`use_enum_values=True` has a real cost worth knowing: the field's runtime value becomes `str`, so you lose the enum type in comparisons and in mypy. Explicit `.value` at the print site keeps the type where it belongs.

### The ex1 rule map

| Subject rule | Kind | Fields involved |
| ------------ | ---- | --------------- |
| Contact ID must start with `"AC"` | single-field (implemented in the model validator) | `contact_id` |
| Physical contact reports must be verified | **cross-field** | `contact_type` + `is_verified` |
| Telepathic contact requires at least 3 witnesses | **cross-field** | `contact_type` + `witness_count` |
| Strong signals (> 7.0) should include received messages | **cross-field** | `signal_strength` + `message_received` |
| Every field bound (lengths, 0.0–10.0, 1–1440, 1–100, ≤ 500) | field-level | `Field` constraints |

Note `should` in the fourth rule versus `must` in the others. Decide whether it raises or merely warns, and be ready to justify the reading you chose — that is a real design call, not a typo to ignore.

### One validator or several?

Four rules in one `@model_validator` function means the first failure hides the other three, and the function grows an `if` per rule. Several small validators each raise independently and read like the specification. Pydantic runs `after` validators **in definition order**. Either structure passes; the multi-validator version is easier to defend and much easier to extend live during the review.

---

## 3. Ex2 — NESTED MODELS

### The concept

A field annotated with another `BaseModel` is validated by that model. A field annotated `list[CrewMember]` validates every element. Composition needs no new API — **the type hint is the whole mechanism**.

```python
class Mission(BaseModel):
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
```

Passing a list of plain dicts works: each dict is validated into a `CrewMember`. This is what makes Pydantic a *parser* for JSON and CSV data — an arbitrarily deep untyped structure goes in, a typed object graph comes out, in one call.

### What happens when a child fails — the subject's own question

> *"Think About: How does Pydantic handle validation of nested models? What happens when a CrewMember fails validation within a SpaceMission?"*

The answer has four parts, and it is the best-value thing to rehearse in this exercise:

1. **Depth-first.** Children are fully validated before the parent's fields are considered complete.
2. **Errors accumulate.** One `ValidationError` is raised for the whole tree, listing every failure — not the first one.
3. **`loc` becomes a path.** A bad age on the second crew member reports `("crew", 1, "age")`. That tuple is the feature: it tells you *where* in the structure, not just *what*.
4. **The parent's `mode="after"` validator never runs.** No `Mission` instance exists to hand it. So your "at least one Commander or Captain" rule can assume every `CrewMember` in `self.crew` is valid — no defensive checks needed inside it.

```
Mission(**data)
   │
   ├── crew[0] → CrewMember  ✅
   ├── crew[1] → CrewMember  ❌ age=15   → error at loc ("crew", 1, "age")
   ├── crew[2] → CrewMember  ❌ rank="pilot" → error at loc ("crew", 2, "rank")
   │
   └── ✗ model_validator(mode="after") is never reached
          one ValidationError, two entries
```

### Rules that quantify over a collection

The mission rules are a step up from ex1: they are not about *a* value, they are about a **set** of values.

| Subject rule | The shape of the check | Idiom |
| ------------ | ---------------------- | ----- |
| Mission ID must start with `"M"` | single field | prefix test |
| Must have at least one Commander or Captain | **existential** over the crew | `any(...)` over `self.crew` |
| Long missions (> 365 days) need 50% experienced crew (5+ years) | **conditional + counting** | a guard on `duration_days`, then a count over `self.crew` and a ratio |
| All crew members must be active | **universal** | `all(...)` over `self.crew` |

Three quantifier flavours — *exists*, *for all*, *counts at least half* — and a rule that only applies under a condition. Naming them that way in the defense ("this one is existential, this one is universal") reads as design vocabulary rather than improvisation. And a detail worth deciding deliberately: `50%` of an odd-sized crew — does 2 of 5 pass? Round, floor, or compare `2 * experienced >= len(crew)` to dodge float division entirely. Have an answer.

### Two behaviours that surprise people

- **Mutation is not validated.** `mission.duration_days = 99999` succeeds silently: validation happens at construction. `model_config = ConfigDict(validate_assignment=True)` changes that; `frozen=True` forbids mutation outright. Knowing the default is *no re-validation* is a strong point at defense.
- **An already-built model passed as a child is not re-validated** by default (`revalidate_instances="never"`). Pydantic trusts a `CrewMember` instance because constructing it already proved it valid — but if you mutated it in between, the parent will not catch it. This is the same fact as the previous bullet, seen from the other side.

### `model_config` — the knobs worth knowing

| Setting | Effect | Why you'd want it here |
| ------- | ------ | ---------------------- |
| `extra="forbid"` | unknown keys raise instead of being dropped | catches typos in input data; the default silently **ignores** them |
| `frozen=True` | immutable + hashable instances | a validated record shouldn't drift |
| `validate_assignment=True` | re-validate on attribute set | closes the mutation hole above |
| `str_strip_whitespace=True` | trim strings before validating | CSV ingestion hygiene |
| `use_enum_values=True` | store the raw value, not the member | the printing trap from ex1 — with a type cost |

`extra="ignore"` being the **default** is worth internalising: by default, a misspelled key in your input data disappears without a word.

### The output surface

`model_dump()` (dict), `model_dump_json()` (JSON string), `model_validate(obj)` and `model_validate_json(s)` (the constructors for untrusted input), `model_json_schema()` (the generated JSON Schema), `model_copy()`. The v1 names — `.dict()`, `.json()`, `.parse_obj()`, `@validator`, `@root_validator` — are deprecated and emit warnings; using one is the most visible way to show you followed a v1 tutorial, which the subject explicitly warns against.

---

## 4. The validation pipeline — the order of everything

Worth being able to draw. Most "why didn't my validator run?" questions are answered by reading this top to bottom.

| Step | What runs | Notes |
| ---- | --------- | ----- |
| 0 | class body is read, validators compiled | **at import time**, once |
| 1 | `@model_validator(mode="before")` | sees the raw dict; nothing is typed yet |
| 2 | per-field type coercion | smart mode unless `strict` |
| 3 | per-field `Field(...)` constraints | bounds, lengths, patterns |
| 4 | `@field_validator(..., mode="after")` | one field at a time, in field order |
| 5 | **nested models** validated the same way, recursively | errors carry a `loc` path |
| 6 | `@model_validator(mode="after")` | in definition order; only if 1–5 all passed |
| 7 | the instance exists | every invariant now holds, forever (absent mutation) |

Defaults are **not** validated at all unless `validate_default=True` — a default of `-5` on a `ge=0` field sails straight through. It is a favourite trick question.

---

## 5. Module-wide rules & traps

- **Pydantic 2.x only, installed with `pip`, inside a venv.** Module 08's workflow is now infrastructure. `pip show pydantic` at the start of the review settles it in one line, and a `requirements.txt` makes the reviewer's setup one command.
- **Never `@validator` or `@root_validator`.** They are v1, deprecated, and named in the subject as the thing not to do. Same for `.dict()`, `.json()`, `parse_obj()`.
- **`return self`** at the end of every `mode="after"` validator. Annotate the return type so mypy enforces it for you.
- **Raise `ValueError` inside validators**, and let Pydantic package it. Your `main()` catches `ValidationError` — one `except`, one clean message, no traceback.
- **Every demonstration must survive its own failure.** Each exercise deliberately constructs an invalid object; that construction is inside a `try`. "No unexpected termination" applies to the exercise's own examples.
- **flake8 + mypy clean, comprehensive annotations.** Pydantic ships a **mypy plugin** — worth enabling, since without it mypy is imprecise about generated `__init__` signatures. `main() -> None` is still an annotation.
- **Optional means nullable, not absent.** `str | None` without a default is a *required* field. Re-read every "Optional" line in the subject with that in mind.
- **`extra` defaults to `ignore`** — unknown input keys vanish silently. Decide whether that is what you want for data arriving from a generator script.
- **Enum printing differs between 3.10 and 3.11+.** Print `.value` and the question disappears.
- **Constraints on floats are exact comparisons.** `power_level: 0.0–100.0` with `le=100.0` and an input of `100.00000000000001` fails — as it should. Don't chase it with rounding inside a validator.
- **The generated data is a gift, and a test.** `data_generator.py`, `data_exporter.py`, and `generated_data/` exist so the reviewer can feed you data you did not choose. Run your models against all of it before the defense — that is where the missing-key and wrong-type paths actually get exercised.
- **`__pycache__`, the venv, and generated exports stay out of git**, and every scenario is verified **from a fresh clone**.
- **What the module is really testing:** you can already write every one of these checks by hand. The grade is on knowing *which layer* each rule belongs to and *why the boundary exists* — not on the rules themselves.

---

## 6. Terminology — every term of the module, defined

Terms in **bold** are the ones an evaluator can legitimately ask you to define on the spot.

### 6.1 Validation, generally

| Term | Definition |
| ---- | ---------- |
| **Validation** | Checking that data satisfies a set of rules before the program relies on it. |
| **Parsing vs validating** | Parsing turns untyped input into a typed object (and rejects what can't be); validating only says yes/no. Pydantic parses. |
| **Parse, don't validate** | The design principle: encode the guarantee in the type, so downstream code cannot receive invalid data. |
| **Parsing boundary** | The one place in a program where untrusted input becomes trusted objects — the model. |
| **Invariant** | A property that holds for every instance of a type, by construction. |
| **Fail fast** | Rejecting bad data at the boundary rather than crashing deep in business logic. |
| **Schema** | The machine-readable description of a data shape; Pydantic can emit JSON Schema from a model. |
| **Coercion** | Converting a compatible input to the declared type (`"42"` → `42`). |
| **Lax vs strict mode** | v2's two coercion policies; **lax (smart) is the default**, strict accepts only the exact type. |
| **Type narrowing** | What a validated model gives the type checker: after construction, the field *is* the declared type. |

### 6.2 Pydantic API

| Term | Definition |
| ---- | ---------- |
| **`BaseModel`** | The base class whose annotated class body becomes a validated schema. |
| **Field** | One annotated name in a model; the annotation is the type rule. |
| **`Field(...)`** | The per-field configuration object: constraints, default, alias, description. |
| **`Annotated[T, Field(...)]`** | The v2-preferred way to attach constraints while keeping the type reusable. |
| **`default_factory`** | A callable producing the default — required for mutable defaults like `list`. |
| **`model_validator`** | The whole-model hook, in `before` / `after` / `wrap` modes. |
| **`field_validator`** | The single-field hook; a `classmethod`, running during that field's validation. |
| **`mode="before"` vs `"after"`** | Raw input before typing, versus the constructed instance after every field validated. |
| **`return self`** | Mandatory at the end of an `after` model validator — its return value *is* the model. |
| **`ValidationError`** | The single exception Pydantic raises, carrying **all** failures at once. |
| **`.errors()`** | The structured list of failures: `loc`, `type`, `msg`, `input`. |
| **`loc`** | The tuple locating a failure inside a nested structure: `("crew", 1, "age")`. |
| **`model_config` / `ConfigDict`** | Per-model settings: `extra`, `frozen`, `strict`, `validate_assignment`, `use_enum_values`. |
| **`extra`** | What to do with unknown input keys: `ignore` (**default**), `forbid`, `allow`. |
| **`validate_assignment`** | Re-run validation when an attribute is set; **off** by default. |
| **`validate_default`** | Validate default values too; **off** by default. |
| **`frozen`** | Immutable and hashable instances. |
| **`model_dump` / `model_dump_json`** | Serialise to dict / JSON — the v2 names for v1's `.dict()` / `.json()`. |
| **`model_validate` / `model_validate_json`** | Construct from an arbitrary object / a JSON string. |
| **`model_json_schema`** | Emit the JSON Schema derived from the model. |
| **`pydantic-core`** | The Rust validation engine v2 compiles models down to. |
| **v1 vs v2** | `@validator`/`@root_validator`/`.dict()` are v1 and deprecated; this subject is v2-only. |
| **Pydantic mypy plugin** | Teaches mypy the generated `__init__` signature and the config semantics. |

### 6.3 Types & structure

| Term | Definition |
| ---- | ---------- |
| **`Enum`** | A fixed set of named constants; Pydantic validates membership **by value**. |
| **`str, Enum` mixin** | Members usable as strings; note the 3.11 change to `__format__`. |
| **`StrEnum`** | 3.11+ stdlib enum whose `str()` is the value — cleaner, but not available on 3.10. |
| **`use_enum_values`** | Store the raw value instead of the member; convenient for printing, lossy for typing. |
| **Optional vs nullable** | `x: T \| None` is nullable but **required**; a default is what makes it optional. |
| **Nested model** | A field annotated with another `BaseModel`; validated recursively, no extra API. |
| **`list[Model]`** | A homogeneous collection validated element by element, with indices in the error `loc`. |
| **Depth-first validation** | Children fully validated before the parent's model validator can run. |
| **`revalidate_instances`** | Whether an already-built model passed as a child is checked again; **`"never"`** by default. |
| **ISO 8601** | The datetime string format Pydantic parses into `datetime`. |
| **Aware vs naive datetime** | With or without a timezone; `AwareDatetime` / `NaiveDatetime` let you require one. |
| **Existential / universal rule** | "at least one crew member is a captain" / "all crew members are active" — `any` / `all`. |

---

## 7. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **PYDANTIC IN ONE SENTENCE** | It reads your type annotations at runtime and compiles them into a validator, so the hint stops being a comment. |
| **PARSE, DON'T VALIDATE** | Move every check to the boundary so that an invalid object cannot exist downstream. |
| **`BaseModel`** | A class whose annotated body is a schema; validation happens at construction, in Rust. |
| **FIELD VS MODEL VALIDATOR** | A rule about one value goes in `Field`; a rule needing two values goes in `@model_validator`. |
| **`mode="before"` VS `"after"`** | The raw dict before any typing, versus the finished instance after every field validated. |
| **`return self`** | An `after` validator's return value *is* the model — omit it and you get `None`. |
| **RAISE `ValueError`** | Validators raise plain `ValueError`; Pydantic folds it into the one `ValidationError`. |
| **SMART / LAX COERCION** | Unambiguous conversions are accepted by default (`"42"` → `42`, ISO string → `datetime`); `strict=True` turns it off. |
| **`bool` IS NOT TRUTHINESS** | Pydantic accepts a fixed vocabulary of boolean inputs and rejects the rest — unlike `bool("False")`. |
| **`ValidationError` COLLECTS** | Every failure in one exception, each with a `loc`, a `type`, and a message. |
| **`loc` IS A PATH** | `("crew", 1, "age")` tells you where in the structure, not just what went wrong. |
| **OPTIONAL ≠ NULLABLE** | `str \| None` is required-but-nullable; only a default makes a field optional. |
| **DEFAULTS AREN'T VALIDATED** | Unless `validate_default=True` — a default may legally violate its own constraints. |
| **MUTATION ISN'T VALIDATED** | Validation runs at construction; `validate_assignment=True` or `frozen=True` if you need more. |
| **`extra` DEFAULTS TO IGNORE** | Unknown input keys are silently dropped until you set `extra="forbid"`. |
| **NESTED = JUST A TYPE HINT** | `list[CrewMember]` is the entire mechanism; validation recurses depth-first. |
| **A CHILD FAILURE SHORT-CIRCUITS THE PARENT** | If any crew member is invalid, the mission's `after` validator never runs. |
| **ENUM VALIDATES BY VALUE** | `"radio"` becomes the member; anything else lists the accepted values in the error. |
| **ENUM PRINTING IS VERSION-DEPENDENT** | 3.11 changed mixin-enum formatting — print `.value` and stop worrying. |
| **v1 VS v2** | `@validator`, `.dict()`, `parse_obj` are v1; this project is `@model_validator`, `model_dump`, `model_validate`. |
| **WHY NOT HAND-WRITTEN `if`s** | One declarative place, all errors at once, a JSON Schema for free, and a Rust core doing the work. |

---

## 8. Worth reading — before and during

### 8.1 The books already on the shelf — `42.secret.repo/_books/`

Pydantic is third-party, so neither book teaches it directly — but both explain the *idea* it implements, and Ramalho names Pydantic exactly where you'd expect.

#### Fluent Python — Ramalho, 2nd ed. 2022 *(PDF page = book page **+ 30**)*

| Chapter / section | Book pp. | For |
| ----------------- | -------- | --- |
| **Ch 5 — Data Class Builders** | **163–196** | **The chapter to read first.** `namedtuple`, `typing.NamedTuple`, `@dataclass` — the three things Pydantic is compared against. |
| ↳ Overview of Data Class Builders / Main Features | 164, 167 | the feature-by-feature comparison table you want in your head at defense |
| ↳ **Type Hints 101 → No Runtime Effect** | **173** | *the* paragraph of this module: annotations do nothing at runtime — **which is precisely what Pydantic changes** |
| ↳ The Meaning of Variable Annotations | 175 | how a class body's annotations become inspectable metadata — the mechanism Pydantic exploits |
| ↳ Field Options / Post-init Processing | 180, 183 | `default_factory` and `__post_init__`, the dataclass ancestors of `Field()` and `model_validator` |
| ↳ **Data Class as a Code Smell** | **190** | the honest counterweight: when a bag of validated fields is the wrong design |
| **Ch 8 — Type Hints in Functions** | **253–298** | gradual typing, `Optional`/`Union`, generic collections — the vocabulary the annotations use |
| **Ch 15 — More About Type Hints** | 519–555 | |
| ↳ **TypedDict** | **526** | Ramalho: for runtime checking of JSON-like structures, *"check out the pydantic package"* |
| ↳ TypedDict caveat | **534** | *"TypedDict is absolutely not a replacement for data validation at runtime. For that, use pydantic."* — quote it |
| ↳ **Reading Type Hints at Runtime → Problems with Annotations at Runtime** | **537–540** | how a library reads annotations at runtime, and why Pydantic's maintainers fought PEP 563. This is the deepest "how does it work?" answer available to you. |

#### Effective Python — Slatkin, 3rd ed. 2024 *(PDF page = book page **+ 27**)*

| Item | Book p. | For |
| ---- | ------- | --- |
| **51 — Prefer `dataclasses` for Defining Lightweight Classes** | **217** | the stdlib alternative, and the page that names `attrs` and `pydantic` as the community answers |
| 56 — Prefer `dataclasses` for Creating Immutable Objects | 250 | the `frozen=True` idea, one layer down |
| **81 — `assert` Internal Assumptions and `raise` Missed Expectations** | **404** | the distinction behind every validator: an assertion is for your bugs, an exception is for bad input |
| 32 — Prefer Raising Exceptions to Returning `None` | 142 | why validators raise instead of returning a flag |
| **121 — Define a Root Exception to Insulate Callers from APIs** | **595** | how to wrap `ValidationError` if you ever want your own boundary type |
| 85 — Beware of Catching the `Exception` Class | 416 | catch `ValidationError`, not everything |
| 124 — Consider Static Analysis via `typing` to Obviate Bugs | 613 | the mypy side, and where the Pydantic plugin fits |
| 29 — Compose Classes Instead of Deeply Nesting Dictionaries, Lists, and Tuples | 127 | the argument for ex2's nested models, made without Pydantic |
| 117 — Use Virtual Environments | 576 | module 08 revision, now a hard prerequisite |

### 8.2 A reading order that fits the project

| When | Read |
| ---- | ---- |
| **Before writing anything** (~1 h) | Fluent **Ch 5 up to p. 179** (data class builders + *No Runtime Effect*) → the Pydantic docs' *Models* page |
| **During ex0** | Pydantic docs *Fields* + *Conversion Table*; Effective **Item 51** (217) |
| **During ex1** | Pydantic docs *Validators* (the `before`/`after` table) + stdlib `enum` docs |
| **During ex2** | Pydantic docs *Models → Nested models* and *Error handling*; Effective **Item 29** (127) |
| **Before the defense** ⭐ | Fluent **pp. 534 and 537–540** — "why not TypedDict?" and "how does it read hints at runtime?" are the two questions that separate a pass from an outstanding |

### 8.3 From these notes (in order of usefulness)

| Doc | Why, for this project |
| --- | --- |
| [python_classes.md](../02_Python/02_syntax_flow/python_classes.md) | Class body ordering and attribute declaration — a `BaseModel` body is a class body with new meaning. |
| [python_custom_exceptions.md](../02_Python/04_errors/python_custom_exceptions.md) | What to raise inside a validator, and when your own exception type is warranted on top of `ValidationError`. |
| [python_try_except_raise.md](../02_Python/04_errors/python_try_except_raise.md) | The shape of the `try` around each deliberate failure demonstration. |
| [M2_Python_8_concepts.md](M2_Python_8_concepts.md) | venv + `requirements.txt` — the prerequisite this module now assumes silently. |
| [M2_Python_5_concepts.md](M2_Python_5_concepts.md) | Nominal vs structural typing, ABCs and Protocols — the typing vocabulary Pydantic sits on top of. |
| [python_data_model.md](../02_Python/03_data_types/python_data_model.md) | How a class is built and what a class body can be made to mean. |
| [python_naming.md](../02_Python/05_style/python_naming.md) | Field names *are* the public API of a model, and they end up in the JSON Schema. |

### 8.4 Official docs (the ones that actually answer questions)

- [Pydantic — Models](https://docs.pydantic.dev/latest/concepts/models/) — start here; the nested-models section is ex2 in five minutes.
- [Pydantic — Fields](https://docs.pydantic.dev/latest/concepts/fields/) — the full `Field()` argument list, and the `Annotated` style.
- [Pydantic — Validators](https://docs.pydantic.dev/latest/concepts/validators/) — the `before`/`after`/`wrap` table; the page ex1 is built from.
- [Pydantic — Conversion Table](https://docs.pydantic.dev/latest/concepts/conversion_table/) — **exactly which coercions are allowed in lax and strict mode**. The single best page for the ex0 Think About box.
- [Pydantic — Error Handling](https://docs.pydantic.dev/latest/errors/errors/) and the [error-message reference](https://docs.pydantic.dev/latest/errors/validation_errors/) — where `Input should be less than or equal to 20` comes from.
- [Pydantic — Migration guide (v1 → v2)](https://docs.pydantic.dev/latest/migration/) — read the rename table once so you recognise v1 code in a tutorial and don't copy it.
- [`enum`](https://docs.python.org/3/library/enum.html) — and the 3.11 *What's New* note on `__format__` for mixin enums.

### 8.5 Worth the detour

- Alexis King, [*Parse, don't validate*](https://lexi-lambda.github.io/blog/2019/11/05/parse-don-t-validate/) — the essay behind the whole module. Not Python, and it does not matter: the idea is that a successfully parsed value carries its guarantee in its type. Fifteen minutes, and it will give you the framing that makes the defense easy.
- [The Twelve-Factor App](https://12factor.net/) — module 08 revision, and the reason validated configuration objects are the natural next step.
- [FastAPI](https://fastapi.tiangolo.com/) — where Pydantic actually gets used: request bodies are models, and the OpenAPI docs are `model_json_schema()`. Skimming the tutorial's first page is the fastest way to see *why* this library exists.

### 8.6 Not on the shelf yet

- **Robust Python** — Patrick Viafore (O'Reilly). The book-length version of "encode your constraints in types". Chapters on user-defined types and runtime checking map directly onto this module.
- **Architecture Patterns with Python** — Percival & Gregory, free at [cosmicpython.com](https://www.cosmicpython.com). Where validated models sit in a real application: at the edge, never in the middle.

---
