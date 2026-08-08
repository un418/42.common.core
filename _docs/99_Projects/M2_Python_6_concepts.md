# Python Module 06 — Concepts Guide (Modules, Packages & Imports)

> Subject: *The Codex — Mastering Python's Import Mysteries* (`_subjects/en.python_mod06.subject.pdf`, v2.0). Python ≥ 3.10, flake8 + mypy clean, **comprehensive** type annotations. Authorized imports: **only the modules and files you create in this project** — no stdlib at all. All builtins allowed except `eval()` / `exec()`. **Modifying `sys.path` is forbidden.**

---

## 0. The big picture — "an import is a name, a path, and a moment"

The four previous modules were about *writing* code. This one is about **where code lives and how Python finds it**. Every exercise is a one-line function returning a string — the logic is deliberately trivial so that the only thing under examination is the import statement above it.

| Part | Mystery | Question it answers |
| ---- | ------- | ------------------- |
| I — Alembic | **Modules, packages, `__init__.py`** | How does Python find a file, and what name do I get back? |
| II — Distillation | **Nested imports & re-export** | How does a package expose code that lives deeper inside it? |
| III — Transmutation | **Absolute vs relative** | Two paths to the same module — when do I use which? |
| IV — Kaboom | **Circular dependencies** | Why does A ↔ B explode, and how do I break the loop? |

### The import algorithm — the six steps to be able to recite

`import X` is not a compiler directive, it is a **statement executed at runtime**. What it does:

```
1. sys.modules cache hit?  ──yes──▶  bind the name, done.   ← why a module runs only ONCE
        │ no
2. Walk sys.meta_path finders → PathFinder scans sys.path entries in order.
3. Loader creates an empty module object.
4. Insert it into sys.modules  ◀── BEFORE executing it. This single fact explains Part IV.
5. Execute the module body top-to-bottom (defs, classes, top-level statements).
6. Bind a name in the importing namespace.
```

Two consequences carry the whole module:

- **Step 1** — importing the same module from ten files runs its top-level code once. Modules are effectively process-wide singletons.
- **Step 4 before step 5** — a module in `sys.modules` may be **partially initialized**: it exists, but its names do not all exist yet. That is a circular import.

### Where does `sys.path` come from, if you may not touch it?

| How you launch | `sys.path[0]` is |
| -------------- | ---------------- |
| `python3 ft_alembic_0.py` | the **directory of the script** |
| `python3 -m package.module` | the **current working directory** |
| REPL / `python3 -c` | the current working directory |

The whole project works because every `ft_*.py` sits at the repo root, so the root lands on `sys.path` and `elements`, `alchemy`, `alchemy.transmutation` all become importable. Nothing else is needed — which is exactly why the subject forbids editing `sys.path`: the tree is designed so you never have to.

### The tree, annotated by what it teaches

```
.
├── elements.py                    ← top-level module   (import elements)
├── alchemy/                       ← package
│   ├── __init__.py                ← the package's public interface
│   ├── elements.py                ← SAME basename as the root one, different module
│   ├── potions.py                 ← imports its siblings         (Part II)
│   ├── transmutation/             ← sub-package
│   │   ├── __init__.py
│   │   └── recipes.py             ← 1 absolute + 1 relative import (Part III)
│   └── grimoire/                  ← sub-package
│       ├── __init__.py
│       ├── light_spellbook.py ─┐  ← cycle BROKEN                  (Part IV)
│       ├── light_validator.py ─┘
│       ├── dark_spellbook.py  ─┐  ← cycle KEPT → must explode
│       └── dark_validator.py  ─┘
└── ft_*.py                        ← 13 driver scripts, one import style each
```

The twin `elements.py` is not an accident: it demonstrates that a module's identity is its **fully-qualified name** (`elements` vs `alchemy.elements`), not its filename. Both live in `sys.modules` simultaneously, with separate function objects.

---

## 1. Part I — MODULES, PACKAGES & THE `__init__.py` GATEWAY

### The concept

- A **module** is a single `.py` file. Importing it creates one module object whose attributes are its top-level names.
- A **package** is a directory Python can import. Importing it executes its `__init__.py`, and the package object gets a `__path__` telling the import system where to look for submodules.

> **Nuance the subject skips — worth raising yourself.** "`__init__.py` transforms a folder into a package" is Python 2 lore. Since **PEP 420 (3.3)**, a directory *without* `__init__.py` is still importable as a **namespace package**. What `__init__.py` really gives you is a **regular package**: a place to run initialization code and to define the package's public surface. Saying this at defense shows you understand the mechanism rather than the recipe.

### `import X` vs `from X import y` — what name gets bound

This is the distinction Part I drills six times. Both forms **fully execute** the target module; they differ only in the name left behind in your namespace.

```python
import mod                  # binds  mod          → call mod.func()
import pkg.sub              # binds  pkg (only!)  → call pkg.sub.func()
import pkg.sub as s         # binds  s            → call s.func()

from mod import func        # binds  func         → call func()
from pkg import sub         # binds  sub          → call sub.func()
from pkg.sub import func    # binds  func         → call func()
from mod import func as f   # binds  f            → call f()
```

The trap in the middle: `import pkg.sub` binds **`pkg`**, never `sub`. Writing `import alchemy.elements` then calling `elements.create_earth()` is a `NameError` — you must go through the full dotted path or use `as`.

| | `import X` | `from X import y` |
| --- | --- | --- |
| Bound name | the module/package object | the attribute itself |
| Call site | `X.y()` — origin visible | `y()` — shorter, origin lost |
| Name clashes | impossible, namespaced | likely (two `create_air`s) |
| Under a circular import | **survives** (see Part IV) | **fails** |
| Attribute looked up | at **call** time | at **import** time |

That last row is the single most useful fact in the module, and it is what Part IV cashes in.

### The six alembic scripts — requirement → mechanism

The subject dictates the structure for each; your job is to know *why* each one reaches its target.

| Script | Target | Structure imposed | Concept exercised |
| ------ | ------ | ----------------- | ----------------- |
| `ft_alembic_0` | root `elements.py` | `import ...` | top-level module, dotted access |
| `ft_alembic_1` | root `elements.py` | `from ... import ...` | direct name binding |
| `ft_alembic_2` | `alchemy/elements.py` | `import ...` | submodule via dotted path |
| `ft_alembic_3` | `alchemy/elements.py` | `from ... import ...` | reaching *into* a package |
| `ft_alembic_4` | `alchemy` itself | `import alchemy` | the **package interface** |
| `ft_alembic_5` | `alchemy` itself | `from alchemy import ...` | pulling a name off that interface |

0–3 talk to **files**. 4–5 talk to the **package**, and only see what `__init__.py` chose to publish.

### `__init__.py` as the package's public face

> *"`alchemy/__init__.py` will contain: anything useful to partially import the alchemy module."*

`import alchemy` executes `__init__.py` and nothing else. If that file re-exports a name from a submodule, the name becomes an attribute of the package; if it doesn't, the package has no such attribute. **Publishing is opt-in.** That is the whole design of ex4: `create_air` reachable as `alchemy.create_air`, `create_earth` not.

The generic shape of a re-export:

```python
# pkg/__init__.py
from .sub import public_thing          # relative: pkg is its own root
__all__ = ["public_thing"]             # declares the public surface
```

**Honesty point for the defense:** `create_earth` is *not* hidden, it is merely **not re-exported**. `alchemy.elements.create_earth()` still works once the submodule is loaded — and `__init__.py` importing from `.elements` loads it and attaches it to the package as a side effect. Python has **no private modules**: encapsulation at package level is a convention (`__all__`, a leading `_`), never an enforcement. Expect to be asked "so is it really inaccessible?" — the answer is no, and knowing that is the point.

### The two deliberate errors of `ft_alembic_4`

> *"The `create_earth()` function will not be exposed through the module interface and raise an exception when called. A mypy error will also raise, again, on purpose."*

| Where | What | Why |
| ----- | ---- | --- |
| Runtime | `AttributeError: module 'alchemy' has no attribute 'create_earth'` | attribute lookup on the package object fails |
| mypy | `Module has no attribute "create_earth"  [attr-defined]` | mypy reads `__init__.py` and knows the surface too |

Note the runtime message ends with `Did you mean: 'create_air'?` — CPython's suggestion machinery (3.10+) proving the two names sit side by side in the same namespace. Do **not** silence the mypy error with `# type: ignore`: the subject wants it visible.

### flake8 / mypy on `__init__.py` — the "usual conventions"

> *"You may face flake8 / mypy errors over your `__init__.py` file. Follow usual conventions in this situation."*

A re-export is, syntactically, an import that is never used in that file. The conventions:

| Complaint | Conventional fix |
| --------- | ---------------- |
| flake8 `F401 imported but unused` | list the name in `__all__` (pyflakes counts that as a use), or `# noqa: F401` on the line |
| mypy implicit re-export (only under `--strict`) | `from .sub import name as name`, or `__all__` |
| `E402 module level import not at top of file` | keep every import above other statements |

Preferring `__all__` over `# noqa` is the better answer: it silences the linter *and* documents the public API in one gesture.

---

## 2. Part II — NESTED IMPORTS, RE-EXPORT & ALIASES

### The concept

`alchemy/potions.py` needs the four elements, which live in **two different places**: `alchemy/elements.py` (earth, air) and the root `elements.py` (fire, water). One module, two very different reaches:

```
alchemy/potions.py
   ├─ sibling inside the same package   →  from .elements import ...   (relative)
   └─ module outside the package        →  import elements             (absolute, top-level)
```

That asymmetry is the exercise. The sibling is reachable relatively because it shares a parent package; the root module is not part of any package, so only an absolute name finds it — and only because the repo root is on `sys.path`.

**The shadowing trap:** inside `alchemy/potions.py`, `import elements` gets the **root** module, not the neighbour. Python 3 has no implicit relative imports (Python 2 did — PEP 328 removed them precisely because of this ambiguity). Two distinct modules named `elements` coexist in `sys.modules` under different keys.

### The two distillation scripts

| Script | Structure | What it proves |
| ------ | --------- | -------------- |
| `ft_distillation_0` | `from alchemy.potions import ...` | a module can be reached directly, whatever its depth |
| `ft_distillation_1` | `import alchemy` | the package can **surface** deep functions at top level |

### The `heal` alias — the point of ex1

> *"…then brew the original strength potion and the special `heal()` potion, which is a package alias of the healing potion. You will need to improve your `__init__.py`."*

```python
# pkg/__init__.py
from .deep.module import long_internal_name as short          # renamed on re-export
```

Two ideas in one line:

1. **Flattening** — a caller writes `alchemy.heal()` and never learns that the code lives in `alchemy/potions.py`. The package's public API is decoupled from its internal file layout, so you can move `potions.py` later without breaking a single caller. This is what a `__init__.py` is *for*.
2. **Aliasing** — `as` rebinds a name; it does not copy or wrap anything. `alchemy.heal` and `alchemy.potions.healing_potion` are the **same function object** (`is` returns `True`), reachable under two names.

Chain of execution to be able to narrate for `import alchemy` in `ft_distillation_1`: `alchemy/__init__.py` runs → it imports `.potions` → `potions.py` runs → which imports `.elements` and root `elements` → those run → control unwinds, and only then does `import alchemy` return. One statement, five module bodies executed, all cached for the rest of the process.

---

## 3. Part III — ABSOLUTE vs RELATIVE IMPORTS

### The concept

Same destination, two ways of naming it:

```python
from alchemy.transmutation.recipes import func   # ABSOLUTE: full path from a sys.path root
from .recipes import func                        # RELATIVE: from where I am now
from ..potions import func                       # RELATIVE: one package up
```

A relative import is resolved against the module's **`__package__`**, not against the filesystem and not against the current working directory. From `alchemy/transmutation/recipes.py` (`__package__ == "alchemy.transmutation"`):

| Written | Resolves to | |
| ------- | ----------- | - |
| `from . import x` | `alchemy.transmutation.x` | own package |
| `from .sibling import x` | `alchemy.transmutation.sibling` | own package |
| `from ..potions import x` | `alchemy.potions` | parent package |
| `from ...anything import x` | — | `ImportError: attempted relative import beyond top-level package` |

Leading dots count **packages**, not directories, and you can never climb above the top-level package — the root `elements.py` is unreachable relatively from inside `alchemy`, which forces the absolute form. The subject's requirement that `recipes.py` hold *at least one of each* is satisfied naturally by its two needs (an element and a potion).

### The subject's own question — prepare this answer

> *"When should an alchemist use absolute pathways vs relative pathways?"*

| | Absolute | Relative |
| --- | --- | --- |
| Reads as | `from alchemy.potions import strength_potion` | `from ..potions import strength_potion` |
| Pros | unambiguous, greppable, works identically from anywhere, PEP 8's default recommendation | short, survives renaming the whole package, states "this is internal" |
| Cons | verbose; every intra-package line repeats the package name; renaming the package touches every file | meaningless outside a package; breaks if the file is run as a script; harder to trace when deeply nested |
| Use for | **anything crossing a package boundary**, and top-level modules | **siblings inside your own package** |

The one-sentence answer: *PEP 8 recommends absolute imports as the default; relative imports are acceptable — and arguably better — for intra-package references, because they keep the package relocatable.* Add the killer detail: **a relative import forbids running that file directly** (below), which is why entry points and scripts always use absolute imports.

### Why running the file directly explodes

```
$ python3 alchemy/transmutation/recipes.py
ImportError: attempted relative import with no known parent package
```

Run a file directly and Python sets `__name__ = "__main__"` and `__package__ = ""` — the module is not considered part of any package, so there is no anchor for the dots. The fixes:

- **`python3 -m alchemy.transmutation.recipes`** — the `-m` flag imports it *as* a package member, so `__package__` is set and relative imports resolve. (`__name__` is still `"__main__"`, so a main guard still fires.)
- Or keep entry points at the root, importing absolutely — which is exactly the shape the subject imposes with its 13 root-level `ft_*.py` scripts.

This is why `ft_transmutation_0` says "access `alchemy/transmutation/recipes.py` **directly**" and still means `import alchemy.transmutation.recipes` — reaching the file *through its package*, never by path.

### The three transmutation scripts — three depths of the same call

| Script | Reaches | What has to exist for it to work |
| ------ | ------- | -------------------------------- |
| `ft_transmutation_0` | `alchemy.transmutation.recipes` | nothing extra — the module is named in full |
| `ft_transmutation_1` | `alchemy.transmutation` | the sub-package's `__init__.py` must re-export the recipe |
| `ft_transmutation_2` | `alchemy` | the top `__init__.py` must surface it too — a **two-level** re-export chain |

Hence the subject's *"you may need to create and/or update a few extra files"*. The progression is the real lesson: the deeper the caller stays, the more each `__init__.py` has to lift upward. Each hop up is a deliberate API decision, not boilerplate.

Also worth knowing: importing `alchemy.transmutation.recipes` **always** executes `alchemy/__init__.py` first, then `alchemy/transmutation/__init__.py`, then the module. Parent packages are always initialized before their children — which is one of the easiest ways to create an accidental cycle in Part IV.

---

## 4. Part IV — CIRCULAR DEPENDENCIES

### The mechanism, step by step

The spellbook needs the validator's verdict; the validator needs the spellbook's ingredient list. A mutual dependency. Trace what the interpreter does with `from .dark_spellbook import dark_spell_record`:

```
① import dark_spellbook   → not in sys.modules
② create the module object, PUT IT IN sys.modules (still empty)
③ run its body:
      from .dark_validator import validate_ingredients
      ④ import dark_validator → create, register, run its body:
             from .dark_spellbook import dark_spell_allowed_ingredients
             ⑤ dark_spellbook IS in sys.modules  →  cache hit, no re-execution
             ⑥ getattr(dark_spellbook, "dark_spell_allowed_ingredients")
                → the body is still stuck at line 2, the name does not exist yet
                → ImportError: cannot import name ... from partially initialized
                  module ... (most likely due to a circular import)
```

The insight is step ⑤: there is **no infinite recursion**, because `sys.modules` was populated at step ② *before* the body ran. What you get instead is a half-built module — the "partially initialized" wording of the error. Python's own error message names the diagnosis for you.

### Why `import X` survives what `from X import y` cannot

| Form | When is the attribute resolved | Under a cycle |
| ---- | ------------------------------ | ------------- |
| `from X import y` | **at import time** — needs `y` to exist *now* | 💥 `ImportError` |
| `import X` … `X.y()` | **at call time** — module object is enough now | ✅ works, if the call happens after both modules finished loading |

`import X` only needs a reference to the (possibly empty) module object; the attribute lookup is deferred to the moment `X.y()` executes, by which time everything is complete. This is the same "bound at import time vs looked up at call time" distinction from Part I — the module is built so that you meet it twice.

### The ways to break a cycle — the defense question

> *"There are multiple ways to avoid circular dependencies; you pick one. Be prepared to explain the different approaches during the evaluation."*

Have all of these ready, with the trade-off:

| # | Approach | How | Trade-off |
| - | -------- | --- | --------- |
| 1 | **Deferred / function-local import** | move the `from .other import x` **inside** the function that needs it | runs at call time, so the cycle never exists at import time; costs a `sys.modules` dict lookup per call (negligible), and hides a dependency from the top of the file |
| 2 | **Module-object import** | `import pkg.other` at the top, `pkg.other.x()` inside the function | keeps the import visible at the top; relies on the deferred-attribute rule above |
| 3 | **Dependency inversion** | stop importing: make the caller **pass** what is needed as an argument | the cleanest fix — the cycle disappears from the design, not just from the import list; changes the function signature |
| 4 | **Extract the shared piece** | move what both modules need into a third, dependency-free module | textbook fix for a real codebase; turns A↔B into A→C←B; here it fights the file layout the subject imposes |
| 5 | **Reorder within the file** | define the needed name *above* the import that triggers the cycle | ⚠️ works only for one entry order — import the other module first and it breaks again. Fragile; know it as a trap, not a solution |
| 6 | **`if TYPE_CHECKING:`** | import only for annotations, never at runtime | the standard real-world fix for *type-only* cycles — **but it needs `from typing import TYPE_CHECKING`, which this project's import rule forbids.** Mention it as knowledge, don't use it |

The meta-answer that scores best: **a circular import is a design smell before it is a technical problem.** It says two modules share a responsibility that belongs in one place, or that the dependency should point one way only. Options 1, 2 and 5 hide the cycle; 3 and 4 remove it.

### Building the one that must explode

`ft_kaboom_1` requires the *opposite* skill: keeping the cycle intact so the traceback appears. The recipe is simply the two conditions the light version avoids — both modules importing **names** (`from .x import y`) from each other, **at module level**. Match the subject's traceback: it must fail at *import* time, before any function is called, and the last line must be the `ImportError` naming the partially initialized module.

Two details from the subject's own output:

- Its traceback shows `from .dark_validator import validate_ingredients` — i.e. the *validator* function kept its name while the spellbook functions gained the `dark_` prefix. Two modules may hold same-named functions without conflict; only the exported spellbook names needed to differ. The printed example is the reference to match.
- `ImportError` is the base class; `ModuleNotFoundError` (raised when the module doesn't exist at all) is a subclass of it. Different failure, different cause — don't confuse them at defense.

The functional side is trivially small on purpose: an allowed-ingredient list, a case-insensitive membership check (`ingredients.lower()` against the allowed words), a `VALID` / `INVALID` verdict, and a recorded/rejected sentence. The grading weight is entirely on the import graph.

---

## 5. Module-wide rules & traps

- **Imports: only your own project files.** No `sys`, no `os`, no `typing`, no `importlib`. Annotations must therefore use builtin generics (`list[str]`, `str | None`) — available since 3.9/3.10 anyway.
- **`sys.path` is untouchable**, and you cannot import `sys` to touch it. The tree is designed so the root scripts put the root on the path for free.
- **Builtins allowed except `eval()` and `exec()`** — and `__import__()` / dynamic imports are against the spirit of the exercise even where not spelled out.
- **Python ≥ 3.10, flake8-clean (79 columns), mypy-clean** — with the single deliberate `attr-defined` error in `ft_alembic_4`.
- **"Comprehensive type annotations"**: every parameter and every return, including `-> str` and `-> None`, in `__init__.py` too if it defines anything.
- **All functions return strings and stay simple.** Resist adding logic — the subject says so twice. A complicated function is wasted effort here and dilutes the demo.
- **`E402`** (`module level import not at top of file`) is the flake8 code that bites when you start moving imports around in Part IV. A *function-local* import is exempt — E402 only inspects module level.
- **Each `ft_*.py` prints a header** (`=== Alembic 0 ===`) then a line naming the structure used, then the result. Keep the shape recognizable; the wording is yours.
- **Two scripts must fail on purpose** (`ft_alembic_4`, `ft_kaboom_1`) — catching the exception or not is your call, but be able to justify it. Uncaught reproduces the subject's traceback exactly; caught proves you know what is raised.
- **Verify from a fresh clone, run from the repo root.** Every path assumption in the project depends on the working directory and on `.pyc` caches not hiding a missing file — `__pycache__` must never be committed.
- Defense warning from the subject: *"you may be asked to explain import mechanisms, demonstrate different import styles, or modify your alchemical laboratory."* Rehearse live edits — "make `create_earth` reachable from `alchemy`", "make this relative import absolute", "break this cycle a second way".

---

## 6. Terminology — every term of the module, defined

Terms in **bold** are ones an evaluator can legitimately ask you to define on the spot.

### 6.1 Modules & packages

| Term | Definition |
| ---- | ---------- |
| **Module** | A single `.py` file; importing it produces one module object whose attributes are its top-level names. |
| **Package** | A directory Python can import; it has a `__path__` and may contain submodules and sub-packages. |
| **Regular package** | A package directory containing `__init__.py`, which runs on first import. |
| **Namespace package** | PEP 420 (3.3+): an importable directory **without** `__init__.py`, splittable across several `sys.path` entries. |
| **Sub-package** | A package nested inside another (`alchemy.transmutation`). |
| **Submodule** | A module inside a package (`alchemy.elements`). |
| **`__init__.py`** | The package's initialization file and public interface: what it binds becomes an attribute of the package. |
| **Fully-qualified name** | The dotted identity of a module (`alchemy.elements`) — what makes it distinct from a same-named file elsewhere. |
| **Script vs module** | A file run as `__main__` vs a file imported by another; the same file can be both. |
| **Entry point** | The script actually launched — here the 13 `ft_*.py` at the repo root. |

### 6.2 The import statement

| Term | Definition |
| ---- | ---------- |
| **`import X`** | Executes X and binds the **module object** under the name `X`. |
| **`import X.Y`** | Executes X then X.Y, and binds **`X` only** — access via `X.Y`. |
| **`from X import y`** | Executes X, then binds the **attribute** `y` (which may be a name or a submodule). |
| **`as` / aliasing** | Rebinds an imported object under another name; same object, second name, no copy. |
| **Re-export** | Importing a name in `__init__.py` so it becomes part of the package's public surface. |
| **Star import (`from X import *`)** | Binds every public name (or exactly `__all__`); flagged by flake8 `F403`/`F405` and best avoided. |
| **`__all__`** | The list of names a module publishes: controls `import *`, documents the API, and silences `F401` on re-exports. |
| **Shadowing** | A name hiding another (root `elements` vs `alchemy.elements`); resolved by the fully-qualified name. |
| **Public / private by convention** | A leading `_` marks internals; Python enforces nothing — non-export is not protection. |

### 6.3 The import machinery

| Term | Definition |
| ---- | ---------- |
| **`sys.modules`** | The cache of already-imported modules; a hit short-circuits the whole import, which is why bodies run once. |
| **`sys.path`** | The ordered list of directories searched for top-level modules; `sys.path[0]` is the script's directory. |
| **Finder / loader** | The components that locate a module and then create and execute it (`sys.meta_path`, `PathFinder`). |
| **Module object** | The runtime value of a module: a namespace, plus dunders like `__name__`, `__file__`, `__package__`. |
| **Binding** | The final step of an import: attaching a name in the importing namespace. |
| **Partially initialized module** | A module registered in `sys.modules` whose body has not finished executing — the state behind circular-import errors. |
| **Idempotence of imports** | Re-importing is a cache lookup, not a re-execution; module-level side effects happen exactly once. |
| **`__pycache__` / `.pyc`** | Cached bytecode; never committed, never a substitute for a missing source file. |

### 6.4 Absolute vs relative

| Term | Definition |
| ---- | ---------- |
| **Absolute import** | Naming a module from a `sys.path` root (`alchemy.potions`); PEP 8's default recommendation. |
| **Relative import** | Naming a module relative to the current package with leading dots (`.sibling`, `..parent`). |
| **`__package__`** | The package a module belongs to — the anchor every relative import is resolved against. |
| **`__name__`** | The module's name, or `"__main__"` when it is the file being run. |
| **`__main__` / main guard** | `if __name__ == "__main__":` — code that runs only when the file is executed, not when imported. |
| **`-m` flag** | Runs a module *as part of its package*, so `__package__` is set and relative imports work. |
| **Implicit relative import** | Python 2's "look next to me first" rule, removed by PEP 328 — why `import elements` inside `alchemy/` gets the **root** module. |
| **Package-relative depth** | Dots count packages, not directories; you cannot climb above the top-level package. |

### 6.5 Circular imports

| Term | Definition |
| ---- | ---------- |
| **Circular dependency** | Two or more modules that (transitively) import each other. |
| **Import-time vs call-time resolution** | `from X import y` needs `y` to exist *now*; `X.y` inside a function needs it only when called. |
| **Deferred / lazy import** | An import placed inside a function so it executes after module loading is complete. |
| **Dependency inversion** | Removing an import by passing the needed value in as an argument instead of fetching it. |
| **Dependency graph** | The directed graph of "who imports whom"; a healthy one is acyclic. |
| **Coupling** | How much one module must know about another; a cycle is maximal coupling. |
| **`TYPE_CHECKING`** | A `typing` flag, false at runtime, used to import purely for annotations — standard cycle fix, **not usable here**. |

### 6.6 Errors & tooling

| Term | Definition |
| ---- | ---------- |
| **`ImportError`** | Raised when an import fails for any reason other than the module being absent. |
| **`ModuleNotFoundError`** | Subclass of `ImportError`: the module itself could not be found on `sys.path`. |
| **`cannot import name … from partially initialized module`** | The circular-import signature; Python even appends the likely cause. |
| **`attempted relative import with no known parent package`** | A relative import in a file run directly as a script. |
| **`attempted relative import beyond top-level package`** | Too many leading dots. |
| **`AttributeError` on a module** | The name exists somewhere in the package but was never re-exported — the `ft_alembic_4` case. |
| **flake8 `F401` / `E402` / `F403`** | Unused import / import not at top of file / star import: the three codes this project provokes. |
| **mypy `attr-defined`** | "Module has no attribute X" — the deliberate error of `ft_alembic_4`. |
| **`# noqa` / `# type: ignore`** | Per-line silencers, to be justified — and *not* to be used on the deliberate errors. |

---

## 7. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **MODULE** | A `.py` file, loaded once per process into a single module object. |
| **PACKAGE** | An importable directory; `__init__.py` makes it a *regular* package and defines what it publishes. |
| **`__init__.py`** | The package's initialization and public interface — a name is reachable as `pkg.name` only if this file binds it. |
| **NAMESPACE PACKAGE** | A package without `__init__.py`, importable since PEP 420 — so the folder→package framing is Python 2 lore. |
| **`import X` vs `from X import y`** | The first binds the module and resolves attributes at **call** time; the second binds the attribute at **import** time. |
| **`sys.modules`** | The import cache: a hit skips execution entirely, which is why a module's top-level code runs exactly once. |
| **`sys.path`** | The search path for top-level modules; `sys.path[0]` is the running script's directory — untouchable in this project. |
| **RE-EXPORT** | Importing a name in `__init__.py` to lift it to package level, decoupling the public API from the file layout. |
| **ALIAS (`as`)** | A second name for the *same* object — `alchemy.heal is alchemy.potions.healing_potion`. |
| **`__all__`** | The declared public surface: drives `import *`, documents the API, and silences flake8 `F401` on re-exports. |
| **ABSOLUTE IMPORT** | A full dotted name from a `sys.path` root — unambiguous, greppable, PEP 8's default. |
| **RELATIVE IMPORT** | A dotted name anchored on `__package__` — good for siblings, and it forbids running that file directly. |
| **`__package__` / `__name__`** | The anchor for relative imports, and the module's own name (`"__main__"` when run directly). |
| **`python3 -m pkg.mod`** | Runs a module as a package member so relative imports resolve — the fix for "no known parent package". |
| **PARTIALLY INITIALIZED MODULE** | A module in `sys.modules` whose body is still running — registered at step 4, executed at step 5. |
| **CIRCULAR IMPORT** | Modules importing each other; it fails only when a **name** is needed before its module finished loading. |
| **BREAKING A CYCLE** | Defer the import into a function, import the module instead of the name, invert the dependency, or extract a shared third module. |
| **DEPENDENCY INVERSION** | Pass the value in instead of importing it — the fix that removes the cycle from the design, not just from the imports. |
| **`ImportError` vs `ModuleNotFoundError`** | The module exists but the name/import failed, vs the module was never found — the second is a subclass of the first. |
| **NON-EXPORT ≠ PRIVACY** | Leaving a function out of `__init__.py` hides it from `pkg.name`, never from `pkg.submodule.name`. |

---
