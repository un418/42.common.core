# Python Module 08 — Concepts Guide (Virtual Environments, Dependency Management & Configuration)

> Subject: *The Matrix — Welcome to the Real World of Data Engineering* (`_subjects/en.python_mod08.subject.pdf`, v3.1). Python ≥ 3.10, flake8 + mypy clean, **comprehensive** type annotations, "exception handling should protect the data streams from corruption". Authorized per exercise: ex0 → `sys`, `os`, `site`, `print()`; ex1 → `pandas`, `requests`, `matplotlib`, `numpy`, `sys`, `importlib`; ex2 → `os`, `sys`, `python-dotenv`, file operations. The subject's own last instruction: **"Test your programs in different environments (with/without virtual env, with/without dependencies)."**

---

## 0. The big picture — "where does my code live, what does it need, what does it know"

This is the first module where **nothing is graded on Python semantics**. Every exercise is about the *environment around* the interpreter: which Python is running, which packages it can see, and which configuration it reads. The code is thin on purpose — three scripts that mostly print facts about their own surroundings. What is being examined is whether you can explain the machinery those facts come from.

| Ex  | Layer                        | Question it answers                                                        | The one artifact                   |
| --- | ---------------------------- | -------------------------------------------------------------------------- | ---------------------------------- |
| ex0 | **Interpreter isolation**    | *Which* Python am I, and whose `site-packages` do I install into?          | the `matrix_env/` directory        |
| ex1 | **Dependency declaration**   | How does someone else rebuild my exact environment?                        | `requirements.txt` + `pyproject.toml` |
| ex2 | **Configuration injection**  | How does the code get secrets without containing them?                     | `.env` + `.env.example` + `.gitignore` |

### The three things that must never be hard-coded, and where each one goes

```
                       ┌─────────────────────────────┐
   the interpreter ───▶│  venv          (ex0)        │  not in git — rebuilt from scratch
                       ├─────────────────────────────┤
   the dependencies ──▶│  requirements.txt / lock    │  IN git — it is the recipe
                       │  pyproject.toml     (ex1)   │
                       ├─────────────────────────────┤
   the secrets ───────▶│  .env               (ex2)   │  NOT in git — .env.example is
                       │  environment variables      │  IN git, with fake values
                       └─────────────────────────────┘
                                    ▲
                          your code reads all three,
                          contains none of them
```

That column of "in git / not in git" is the whole module in one image, and it is the fastest way to answer the peer-review's *"the goal isn't just to make the code work; it's to understand the why behind these tools."* Each row separates **a thing that is rebuilt** from **the instructions to rebuild it**. Only the instructions are versioned.

### What the module is actually teaching: reproducibility

A program is reproducible when a stranger, on a different machine, gets the same behaviour from the same repository. The three enemies of that are: a different interpreter (ex0), different package versions (ex1), and different configuration (ex2). Say it that way at defense and you have framed all three exercises with one sentence.

---

## 1. Ex0 — VIRTUAL ENVIRONMENT

### The concept

A **virtual environment** is not a sandbox, not a container, and not a separate Python installation. It is a **directory with its own `site-packages` and its own `sys.prefix`**, containing a symlink (or small copy) of an existing interpreter and a `pyvenv.cfg` file pointing back to the real one. That is all. PEP 405 defines it, and `venv` in the standard library implements it.

```
matrix_env/
├── pyvenv.cfg              ← home = /usr/bin ; the pointer back to the base interpreter
├── bin/
│   ├── python -> /usr/bin/python3.11    ← a symlink, not a copy of Python
│   ├── pip
│   └── activate            ← a *shell* script: it edits PATH, nothing more
└── lib/python3.11/site-packages/        ← the entire point of the exercise
```

When `bin/python` starts, it finds `pyvenv.cfg` next to itself, sets `sys.prefix` to the venv and `sys.base_prefix` to the real installation, and puts the venv's `site-packages` on `sys.path` instead of the global one. **Isolation is `sys.path` manipulation, nothing deeper.** A venv gives you no process isolation, no filesystem isolation, no security boundary — that answer alone separates "I ran the command" from "I know what the command did".

### Detecting a venv — three methods, only one of them correct

| Method | What it really tests | Verdict |
| ------ | -------------------- | ------- |
| `sys.prefix != sys.base_prefix` | the interpreter's own idea of where it lives | ✅ **the canonical check** (PEP 405), works whether or not the venv was "activated" |
| `os.environ.get("VIRTUAL_ENV")` | whether the **activate script** was sourced in this shell | ⚠️ useful for the *name*, but false-negative on `matrix_env/bin/python script.py` |
| `hasattr(sys, "real_prefix")` | old `virtualenv` (< v20) only | ❌ legacy; `venv` never sets it |

The distinction between the first two is the best question in the exercise, and the reviewer's `python3 construct.py` vs `(matrix_env) $> python3 construct.py` test walks straight into it. **Activation is a convenience, not a mechanism**: `source bin/activate` prepends `matrix_env/bin` to `$PATH`, sets `VIRTUAL_ENV`, and rewrites the prompt. Running `matrix_env/bin/python` directly is *fully* inside the venv with none of those variables set. Decide which signal your program treats as authoritative, and be able to say why.

### The `sys` / `site` / `os` surface the exercise wants

| Need | Where it comes from | Note |
| ---- | ------------------- | ---- |
| which interpreter is running | `sys.executable` | absolute path to the binary — the "Current Python:" line |
| is this a venv | `sys.prefix` vs `sys.base_prefix` | see above |
| where the venv lives | `sys.prefix` | the "Environment Path:" line |
| its name | basename of `sys.prefix`, or `VIRTUAL_ENV` | a name is a directory name; there is no registry of venvs |
| where packages install | `site.getsitepackages()` / `sysconfig.get_paths()["purelib"]` | the global vs venv contrast the subject asks you to *show* |
| user-level packages | `site.getusersitepackages()`, `site.ENABLE_USER_SITE` | the third location most people forget exists |
| the import search order | `sys.path` | worth printing, worth being able to read out loud |

Reading `sys.path` top to bottom is a good live demo: script directory → `PYTHONPATH` → stdlib → `site-packages`. The reason a venv works is that the last entry changed; nothing else did.

### Why isolation matters — the answer that isn't "it's cleaner"

Three concrete failures, each worth one sentence at defense:

1. **Version conflicts.** Project A needs `pandas==1.5`, project B needs `pandas==2.1`. One global `site-packages` can hold exactly one of them. Two venvs hold both.
2. **Reproducibility.** A global environment accretes packages you installed and forgot. `pip freeze` from it lists your entire history, not your project's needs — and the next person cannot rebuild what you have.
3. **Not breaking the system.** On Linux and macOS, `/usr/bin/python3` belongs to the OS; `pip install --user` or `sudo pip` into it can break system tooling. Modern Python refuses outright: **PEP 668** makes distro interpreters "externally managed" and `pip` errors with `error: externally-managed-environment` — which is, in practice, the OS telling you to make a venv.

### The subject's own constraints, and what they imply

> *"Your program should work both inside and outside virtual environments, providing different outputs for each scenario."*

> *"Do not submit your virtual environnement in your repository. You must be able to create a new one during review if needed."*

The second is graded from a **fresh clone**: `matrix_env/` in `.gitignore`, and the reviewer must be able to recreate everything with `python3 -m venv` + one install command. A venv is also **not relocatable** — the paths in `bin/activate` and the shebangs of installed scripts are absolute, so a committed venv would be broken on any other machine anyway. That is a better reason to give than "it's big".

### Neighbours worth being able to place

| Tool | What it isolates | Relation to `venv` |
| ---- | ---------------- | ------------------ |
| **`venv`** | `site-packages` for one already-installed interpreter | stdlib since 3.3; the baseline |
| **`virtualenv`** | same, faster, supports older Pythons | third-party ancestor of `venv` |
| **`conda`** | packages **and** the interpreter **and** native libs | a package manager in its own right, not pip-based |
| **`pyenv`** | which Python *version* is on your PATH | orthogonal — often used *with* venv |
| **`pipx`** | one venv per installed CLI tool | how you should install `flake8`/`mypy` globally |
| **Docker** | the whole userland | a real isolation boundary; a venv is not |

---

## 2. Ex1 — DEPENDENCY MANAGEMENT (`pip` vs Poetry)

### The concept

A dependency is not "a package I installed". It is **a constraint you publish** so that an environment can be rebuilt. Two schools:

```
pip / requirements.txt                    Poetry / pyproject.toml + poetry.lock
──────────────────────                    ─────────────────────────────────────
a flat list of install commands           a declared project + a resolver
you pin (or don't) by hand                the resolver pins for you, into a lock file
`pip install -r` installs top to bottom   `poetry install` reproduces the lock exactly
no conflict detection worth the name      refuses to resolve an unsatisfiable set
your venv is wherever you made it         Poetry creates and owns the venv
```

### The comparison table to have memorized

| | **pip + requirements.txt** | **Poetry + pyproject.toml** |
| --- | --- | --- |
| Declaration file | `requirements.txt` (plain lines) | `pyproject.toml` (`[project]` / `[tool.poetry]`) |
| Standard behind it | none — a convention | **PEP 518 / 517 / 621** |
| Direct vs transitive deps | **mixed together** after `pip freeze` | direct deps declared, transitive resolved |
| Lock file | none (needs `pip-tools`, `uv`, `pip freeze` discipline) | **`poetry.lock`**, with hashes |
| Dependency resolution | installs sequentially, last write wins | full SAT-style resolver, fails loudly on conflict |
| Version syntax | `==`, `>=`, `~=` | same, plus caret `^2.1` (compatible-release) |
| Dev/test deps | second file by convention (`requirements-dev.txt`) | **dependency groups**, one file |
| Environment creation | you run `python -m venv` yourself | `poetry install` / `poetry run` manage it |
| Also builds/publishes | no | yes (build backend + `poetry publish`) |
| Ubiquity | everywhere, zero install | must be installed first |

The one-line answer: **`pip` installs, Poetry *resolves and locks*.** `requirements.txt` describes what to install; `poetry.lock` describes an environment that is known to have worked, byte for byte.

### `~=` vs `^` vs `==` — a small table that makes you sound fluent

| Spec | Means | Allows |
| ---- | ----- | ------ |
| `==2.1.0` | exactly this | nothing else — reproducible, but you never get fixes |
| `>=2.1` | at least this | any future major version, including the breaking one |
| `~=2.1.0` | compatible release (PEP 440) | `2.1.*` — patch only |
| `^2.1.0` | Poetry's caret, semver-flavoured | `>=2.1.0, <3.0.0` — minor + patch |

`pip freeze` produces the first form for *everything*, direct and transitive alike — which is why a frozen file is a decent lock file and a terrible declaration file.

### Handling missing dependencies gracefully — the design question of the exercise

> *"Your program should detect which packages are available and provide helpful error messages if dependencies are missing."*

A top-level `import pandas` on a bare interpreter kills the program with a traceback before line 1 of your logic. Three ways to avoid that, with different trade-offs:

| Approach | Mechanism | Trade-off |
| -------- | --------- | --------- |
| `try: import pandas / except ImportError:` | catch at import time, set a flag or `None` | simple; the module object is now `Module \| None` for the type checker |
| `importlib.util.find_spec("pandas")` | **ask whether it is importable, without importing** | cleanest for a pure availability report; no side effects, no cost |
| `importlib.import_module("pandas")` | import by name at runtime | needed if you want the module only in the branch where it exists |

`importlib` is explicitly Authorized here, and that is a hint. For the versions line, the modern answer is **`importlib.metadata.version("pandas")`** — it reads the installed distribution metadata, so it works without importing the package and without relying on a `__version__` attribute that not every project defines.

> ⚠️ *distribution name ≠ import name.* `pip install python-dotenv` gives you `import dotenv`. `importlib.metadata.version()` takes the **distribution** name; `find_spec()` takes the **import** name. Getting this pair right in ex2 is a small, very visible detail.

### The flake8/mypy exemption — and the "mechanics" the subject dangles

> *"Exceptionnally, flake8 and mypy errors are allowed for this exercise, only for import errors. Nonetheless there is some mechanics and implementation to avoid those errors, if you are curious and want dig further."*

The tools you'd reach for, in increasing order of correctness — worth naming even if you take the exemption:

| Problem | Fix |
| ------- | --- |
| flake8 `F401 imported but unused` inside a `try:` | `__all__`, or restructure so the name is used |
| flake8 `E402 module level import not at top of file` | conditional imports pushed below other statements |
| mypy `import-not-found` / `import-untyped` | install the stubs (`pandas-stubs`, `types-requests`), or `ignore_missing_imports` in config |
| the module is `None` when absent | `if TYPE_CHECKING: import pandas` for the annotation, guard the runtime use |
| a targeted silence | `# type: ignore[import-not-found]` — narrow, on the one line |

Knowing that `TYPE_CHECKING` exists (a constant that is `False` at runtime, `True` for the type checker, so the import happens only for mypy) is the single most impressive thing you can say in this exercise.

### numpy / pandas / matplotlib — the minimum you should be able to justify

The subject is emphatic: **"It must be the source of your dataset — not hardcoded lists or `range()`."** So the data comes from something like a numpy random generator or `linspace`, not from a literal.

| Library | Its one job | The concept behind it |
| ------- | ----------- | --------------------- |
| **numpy** | the `ndarray`: fixed dtype, contiguous memory | **vectorization** — the loop runs in C, not in Python |
| **pandas** | `DataFrame`: labelled columns over numpy arrays | indexing, grouping, aggregation on tabular data |
| **matplotlib** | figures and axes | the figure is an object you build then save |
| **requests** | HTTP | **optional here** — the subject's own note says the `requests` line only appears if you actually fetch |

Two practical traps, both of which have failed reviews before:

- **Headless plotting.** `matplotlib` picks an interactive backend by default; on a machine with no display, importing `pyplot` can fail or block. `matplotlib.use("Agg")` **before** importing `pyplot` forces the file-only backend. The output spec ends at "Results saved to: matrix_analysis.png" — no window is expected to open, and no window is expected to *block the program either*, which the "no uncontrolled termination" rule cares about.
- **Generated artifacts in git.** `matrix_analysis.png` is *output*, like `__pycache__` and `matrix_env/`. Decide deliberately whether it is committed; the defensible answer is no.

---

## 3. Ex2 — ENVIRONMENT CONFIGURATION (`.env`, secrets, dev vs prod)

### The concept

**Configuration is everything that differs between deployments of the same code**: the database URL, the API key, the log level. The rule it comes from is *config in the environment*, factor III of the **Twelve-Factor App** — and its test is a good one to quote: *could this repository be made public right now without leaking anything?*

An **environment variable** is a string-to-string map the OS hands to a process at exec time, inherited by children. In Python it is `os.environ` — a live mapping of the *current process*, and edits to it affect only this process and anything it spawns afterwards. **You can never set an environment variable in your parent shell from Python**; that is why `activate` is a shell script and not a Python one, and it is a satisfying thing to be able to explain.

### The precedence chain — the mechanism the reviewer will test

The subject's own three test scenarios *are* the precedence ladder:

```
  MATRIX_MODE=production python3 oracle.py     ← real environment variable   (highest)
                    │
                    ▼   load_dotenv() does NOT overwrite what is already set
              .env file                        ← developer's local values
                    │
                    ▼
        your default in the code                ← os.environ.get(key, default)  (lowest)
```

`python-dotenv`'s `load_dotenv()` **defaults to `override=False`**: it only fills in names that are *absent* from `os.environ`. That single default is what makes `MATRIX_MODE=production python3 oracle.py` win over the `.env` file, and it is the most likely "explain this line" question in the exercise. Know that `override=True` exists and that using it would break the third test.

### Reading configuration safely

| Need | Idiom | Note |
| ---- | ----- | ---- |
| optional with a default | `os.environ.get("LOG_LEVEL", "INFO")` | returns `str \| None` without the default — mypy will make you handle it |
| required | `os.environ["API_KEY"]` → `KeyError`, or an explicit check + your own error | "proper error handling for missing configuration" means *your* message, not a traceback |
| a number | `int(os.environ.get("PORT", "8000"))` | **everything from the environment is a string**; the conversion can raise `ValueError` |
| a boolean | compare against a set of accepted strings | `bool("False")` is **`True`** — the classic bug |
| a secret | read it, **never print it** | mask to a prefix, or print only "Authenticated" like the subject's sample output |

Note what the subject's expected output does *not* contain: no URL, no key. It prints `Database: Connected to local instance` and `API Access: Authenticated`. **Status, not value.** Mirroring that is a free point.

### Dev vs prod — you choose the difference, but it must be visible

> *"You are free to implement whatever you choose to showcase difference in development/production. But it must be visible in the output when testing your program."*

Pick one or two axes and make them observable. Realistic ones: log verbosity (`DEBUG` vs `WARNING`), how much of the config is echoed, whether missing values are tolerated (defaults in dev) or **fatal** (fail-fast in prod), whether a fake/local endpoint is used. The strongest choice is **fail-fast in production**: a missing `API_KEY` warns in dev and refuses to start in prod. It shows you understand that the *validation policy* is itself configuration-dependent.

### `.env`, `.env.example`, `.gitignore` — three files, three roles

| File | In git? | Contains | Role |
| ---- | ------- | -------- | ---- |
| `.env` | ❌ **never** | the real values | the developer's local, private configuration |
| `.env.example` | ✅ yes | the **keys**, with empty or obviously fake values | documentation of the required configuration surface |
| `.gitignore` | ✅ yes | the `.env` line | the enforcement of the first row |

> *"Never commit real secrets to version control! Your .env file should be in .gitignore. You must be able to explain why."*

The subject is explicitly asking for the explanation, so have the full version: **git history is permanent and distributed.** A secret committed once lives in every clone, in every fork, in the reflog, and in any CI cache — deleting the file in a later commit removes nothing. Rewriting history (`filter-repo`, BFG) breaks every clone and still doesn't reach forks or the GitHub API cache. Public repositories are scraped for keys within *minutes*. Therefore: the only remedy for a leaked secret is **rotation** — invalidate it and issue a new one. Prevention is `.gitignore` plus `.env.example`; a leaked key is a revoked key, not a reverted commit.

Two follow-ups worth having ready: `.env` is **not encrypted** — it is plain text, protected only by file permissions, which is why real deployments use a secret manager (Vault, AWS Secrets Manager, the platform's own env vars) and `.env` is a *development* convenience. And a `.env` is **not** a shell script: `python-dotenv` parses `KEY=value` lines itself, which is exactly why the subject forbids writing your own parser — it wants you to learn the ecosystem tool, not to reimplement quoting rules.

---

## 4. The reproducibility map — one command per layer

Worth being able to draw on the whiteboard: the exact sequence a stranger runs on a fresh clone, and which file feeds each step.

| Step | Command | Reads | Produces |
| ---- | ------- | ----- | -------- |
| 1. isolate | `python3 -m venv matrix_env` | — | `matrix_env/` (gitignored) |
| 2. enter | `source matrix_env/bin/activate` | — | a modified `$PATH` in **this shell only** |
| 3. install | `pip install -r requirements.txt` | `requirements.txt` | populated `site-packages` |
| 3′. or | `poetry install` | `pyproject.toml` + `poetry.lock` | its own venv, populated exactly |
| 4. configure | `cp .env.example .env` then edit | `.env.example` | `.env` (gitignored) |
| 5. run | `python3 oracle.py` | `.env` + `os.environ` | output |

Everything in the "reads" column is committed. Everything in the "produces" column is not. That is the module.

---

## 5. Module-wide rules & traps

- **Test from a fresh clone, in all four states**: no venv / venv, no deps / deps. The subject makes this an explicit General Instruction, and every exercise has a "without" branch that only that test exercises.
- **Never commit**: `matrix_env/` (or any venv name), `.env`, `__pycache__/`, `.mypy_cache/`, generated `.png`s. One `.gitignore` at the root, checked with `git check-ignore -v <path>` and `git add -An` before you commit — not by eye.
- **`.env.example` must actually list every key the program reads** — `MATRIX_MODE`, `DATABASE_URL`, `API_KEY`, `LOG_LEVEL`, `ZION_ENDPOINT`. It is the only documentation of your configuration surface, and the reviewer's `cp .env.example .env` path goes through it.
- **`requirements.txt` appears in two exercises** (ex1 and ex2) with different contents — ex2's needs `python-dotenv`. They are per-directory files; don't let one drift into being a copy of the other.
- **Comprehensive type annotations** — every parameter, every return, including `-> None`. `os.environ.get()` returns `str | None`: mypy will force you to handle the `None`, and that is the tool doing its job, not an obstacle.
- **"Exception handling should protect the data streams from corruption"** — in this module that means: a missing package, a missing `.env`, a missing key, and an unparseable value each produce a clear message and a controlled exit, never a traceback.
- **No uncontrolled termination.** A blocking `plt.show()`, an unhandled `KeyError`, or a network call with no timeout are all the same failure in the reviewer's eyes.
- **Do not hard-code paths.** `sys.prefix`, `sys.executable`, and `os.path` produce them; a literal `/usr/bin/python3.11` in your source is the exact mistake the exercise exists to prevent.
- **Poetry may not be installed on the review machine.** You are asked to demonstrate the *difference* between pip and Poetry, and `pyproject.toml` must be present and valid — but plan for a defense where only the pip path can actually be executed, and be ready to walk through the Poetry side from the file.
- **Defense warning, straight from the subject:** you will be asked for *"your ability to explain these concepts to other learners."* This module is graded almost entirely on explanation. If you can only demonstrate, you have done half of it.

---

## 6. Terminology — every term of the module, defined

Terms in **bold** are the ones an evaluator can legitimately ask you to define on the spot.

### 6.1 Interpreter & isolation

| Term | Definition |
| ---- | ---------- |
| **Virtual environment** | A directory with its own `site-packages` and `pyvenv.cfg`, using an existing interpreter through a symlink. |
| **PEP 405** | The specification that defines venvs, `pyvenv.cfg`, and the `sys.prefix` / `sys.base_prefix` split. |
| **`sys.prefix`** | The root of the environment the interpreter considers itself installed in — the venv, when in one. |
| **`sys.base_prefix`** | The root of the *underlying* installation; equal to `sys.prefix` outside a venv. |
| **`sys.executable`** | Absolute path of the running interpreter binary. |
| **`pyvenv.cfg`** | The marker file at the venv root whose `home =` line points back to the base interpreter. |
| **Activation** | Sourcing `bin/activate`: prepends the venv's `bin` to `$PATH` and sets `VIRTUAL_ENV`. A convenience, not the mechanism. |
| **`VIRTUAL_ENV`** | The env var set by activation — present only if activated, so never the primary detection method. |
| **`site-packages`** | The directory third-party packages install into; each venv has its own. |
| **`site` module** | Imported at startup; wires `site-packages` into `sys.path`. `getsitepackages()`, `getusersitepackages()`. |
| **`sys.path`** | The ordered list of directories `import` searches. Isolation is a change to this list. |
| **User site** | The per-user package directory (`pip install --user`), a third location beside global and venv. |
| **System Python** | The interpreter shipped with the OS; PEP 668 marks it **externally managed** so pip refuses to write to it. |
| **`pyenv` / `conda` / `pipx` / Docker** | Version switching / full env + interpreter / one venv per CLI tool / OS-level isolation. |
| **Relocatable** | A venv is **not**: its scripts contain absolute paths, so it cannot be copied to another machine. |

### 6.2 Packaging & dependencies

| Term | Definition |
| ---- | ---------- |
| **Package vs distribution** | What you `import` vs what you `pip install`; the two names need not match (`dotenv` vs `python-dotenv`). |
| **PyPI** | The Python Package Index — the default source `pip` downloads from. |
| **`pip`** | The installer: resolves little, installs what it is told, in order. |
| **`requirements.txt`** | A plain list of requirement specifiers; a convention, not a standard. |
| **`pip freeze`** | Dumps every installed distribution pinned with `==` — direct and transitive, indistinguishable. |
| **Direct vs transitive dependency** | What you asked for vs what your dependencies dragged in. |
| **Version specifier (PEP 440)** | `==`, `>=`, `~=` (compatible release) and the ordering rules behind them. |
| **Caret `^`** | Poetry's semver range: `^2.1.0` means `>=2.1.0,<3.0.0`. Not PEP 440. |
| **Pinning** | Fixing an exact version, for reproducibility, at the cost of never receiving fixes. |
| **Lock file** | The full resolved graph with exact versions and hashes — `poetry.lock`. Committed; never hand-edited. |
| **Dependency resolution** | Finding one version of every package satisfying all constraints at once; can be unsatisfiable. |
| **Dependency hell / diamond** | Two dependencies requiring incompatible versions of a third. |
| **`pyproject.toml`** | The standard project file (**PEP 518** build requirements, **PEP 621** metadata) — config for tools too. |
| **Build backend (PEP 517)** | The component that turns a source tree into a wheel: setuptools, poetry-core, hatchling, flit. |
| **Wheel vs sdist** | A prebuilt archive that just unpacks vs a source distribution that must be built. |
| **Poetry** | Declares, resolves, locks, creates the venv, and builds/publishes — a project manager, not just an installer. |
| **Dependency group** | Poetry's dev/test/docs sets in one file, replacing `requirements-dev.txt`. |
| **`importlib.metadata`** | Stdlib access to installed-distribution metadata: `version("pandas")` without importing pandas. |
| **`importlib.util.find_spec`** | Answers "is this importable?" without importing or executing it. |
| **`ImportError` / `ModuleNotFoundError`** | The subclass relationship matters: catch the former to cover both. |
| **`TYPE_CHECKING`** | `False` at runtime, `True` for type checkers — lets you import a name for annotations only. |

### 6.3 Configuration & secrets

| Term | Definition |
| ---- | ---------- |
| **Environment variable** | A string→string pair given to a process at exec and inherited by its children. |
| **`os.environ`** | Python's live view of them; mutations affect this process and future children only, never the parent shell. |
| **`os.getenv` / `os.environ.get`** | Read with a default; the value is **always** a `str` or `None`. |
| **`.env` file** | A plain-text `KEY=value` file, loaded by a library. Not encrypted, not a shell script, never committed. |
| **`python-dotenv`** | The library that parses `.env` and injects it into `os.environ`; `load_dotenv(override=False)` by default. |
| **Precedence / override** | Real env vars beat `.env`, which beats in-code defaults — the behaviour the reviewer tests directly. |
| **`.env.example`** | The committed template listing required keys with fake values; documents the configuration surface. |
| **Twelve-Factor App, factor III** | *Store config in the environment* — the doctrine this whole exercise implements. |
| **Secret** | A credential whose disclosure is the incident: API key, DB password, token. |
| **Secret rotation** | Invalidating and reissuing a credential — the **only** real remedy after a leak. |
| **Secret manager** | Vault, AWS Secrets Manager, the platform's env-var store — what replaces `.env` outside development. |
| **Fail-fast** | Refusing to start when required configuration is absent; typically enabled in production, not in dev. |
| **Configuration validation** | Checking presence, type, and range of config at startup rather than at first use. |
| **Masking** | Printing status or a truncated prefix instead of the value; note the subject's own output does exactly this. |
| **`.gitignore`** | Path patterns git refuses to stage — verified with `git check-ignore -v`, not by eye. |

---

## 7. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **VIRTUAL ENVIRONMENT** | A directory with its own `site-packages` and a symlinked interpreter — isolation is a change to `sys.path`, nothing deeper. |
| **HOW TO DETECT ONE** | `sys.prefix != sys.base_prefix`; `VIRTUAL_ENV` only tells you whether someone *activated* it. |
| **ACTIVATION** | A shell script that edits `$PATH` — running `venv/bin/python` directly is just as "inside". |
| **`pyvenv.cfg`** | The marker file whose `home =` line is the pointer back to the base interpreter. |
| **WHY ISOLATE** | Conflicting versions, reproducibility, and not writing into an OS-managed interpreter (PEP 668). |
| **A VENV IS NOT A SANDBOX** | No process, filesystem, or security isolation — that is Docker's job, not `venv`'s. |
| **NEVER COMMIT THE VENV** | It is regenerated output, and its absolute paths make it unusable on any other machine. |
| **pip VS POETRY** | pip installs a list; Poetry *resolves* a graph and *locks* it — declaration versus reproduction. |
| **LOCK FILE** | The exact resolved graph with hashes, committed, never hand-edited — what makes a build repeatable. |
| **`pip freeze` IS NOT A DECLARATION** | It pins everything, direct and transitive alike, with no record of what you actually asked for. |
| **`pyproject.toml`** | The standardized project file (PEP 518/517/621) — metadata, dependencies, and tool config in one place. |
| **GRACEFUL MISSING DEPENDENCY** | `find_spec` or a guarded import, then a helpful message — never a traceback before line 1. |
| **`importlib.metadata.version()`** | Reads the installed distribution's version without importing the package. |
| **DISTRIBUTION NAME ≠ IMPORT NAME** | `pip install python-dotenv` → `import dotenv`; the two APIs want different ones. |
| **ENVIRONMENT VARIABLE** | A string handed to the process at exec; `os.environ` edits never reach the parent shell. |
| **EVERYTHING IS A STRING** | Config must be parsed and validated — and `bool("False")` is `True`. |
| **PRECEDENCE** | Real env var > `.env` > in-code default, because `load_dotenv()` defaults to `override=False`. |
| **`.env` VS `.env.example`** | Real values, gitignored, versus the committed key list that documents them. |
| **WHY `.env` IS GITIGNORED** | Git history is permanent and distributed; the only fix for a leaked secret is rotation. |
| **TWELVE-FACTOR CONFIG** | Config lives in the environment, so the same artifact runs in dev and prod unchanged. |
| **DEV VS PROD** | Same code, different configuration — and typically tolerant defaults in dev, fail-fast in prod. |
| **REPRODUCIBILITY** | A stranger, from a fresh clone, gets the same behaviour: same interpreter, same versions, same config. |

---

## 8. Worth reading — before and during

### 8.1 The books already on the shelf — `42.secret.repo/_books/`

This module is the one the books cover *least* — it is ecosystem, not language — but the Collaboration chapter of Slatkin is dead on target.

#### Effective Python — Slatkin, 3rd ed. 2024 *(PDF page = book page **+ 27**)*

| Item | Book p. | For |
| ---- | ------- | --- |
| **117 — Use Virtual Environments for Isolated and Reproducible Dependencies** | **576** | **ex0 and ex1 in one item.** `venv`, `pip freeze`, transitive dependency conflicts, reproducing an environment elsewhere. Read this first. |
| 116 — Know Where to Find Community-Built Modules | 575 | PyPI and `pip` in two pages; the context for Item 117 |
| **120 — Consider Module-Scoped Code to Configure Deployment Environments** | **593** | **ex2, exactly**: how a program adapts itself to dev vs prod without changing code |
| 119 — Use Packages to Organize Modules and Provide Stable APIs | 588 | P06 revision; the `__init__.py` / `__all__` half of packaging |
| 124 — Consider Static Analysis via typing to Obviate Bugs | 613 | the mypy configuration knobs behind the ex1 exemption |
| 121 — Define a Root Exception to Insulate Callers from APIs | 595 | your own configuration error class for ex2's "proper error handling" |
| 91 — Avoid `exec` and `eval` Unless You're Building a Developer Tool | 445 | why a `.env` is parsed, never executed |
| 80 — Take Advantage of Each Block in try/except/else/finally | 399 | the shape of the guarded-import and missing-config handlers |
| 98 — Lazy-Load Modules with Dynamic Imports to Reduce Startup Time | 478 | the other legitimate reason to import inside a function |
| 125 — Prefer Open Source Projects for Bundling Python Programs | 621 | where this all leads: shipping the thing you built |

#### Fluent Python — Ramalho, 2nd ed. 2022 *(PDF page = book page **+ 30**)*

Ramalho stays away from packaging almost entirely. Nothing in it is required for this module; the closest useful page is the discussion of imports and module objects in Ch 21 if you want depth on `importlib`.

### 8.2 A reading order that fits the project

| When | Read |
| ---- | ---- |
| **Before writing anything** (~30 min) | Effective **Item 117** (576), then skim **Item 116** (575) |
| **During ex0** | the `venv` docs and **PEP 405** — the `sys.prefix` / `sys.base_prefix` paragraph is the whole exercise |
| **During ex1** | the packaging guide's *Tool recommendations* + Poetry's *Basic usage*; Effective **Item 124** (613) if you attempt the clean-mypy route |
| **During ex2** | The Twelve-Factor App, factor III + Effective **Item 120** (593) |
| **Before the defense** | re-read your own `.gitignore` and `.env.example`, and rehearse the "why is a leaked secret rotated, not reverted?" answer |

### 8.3 From these notes (in order of usefulness)

| Doc | Why, for this project |
| --- | --- |
| [dev_env.md](../02_Python/01_tooling/dev_env.md) | Your own environment notes — the interpreter, flake8, mypy, pipx. The direct prerequisite; update it as this module teaches you things. |
| [M2_Python_6_concepts.md](M2_Python_6_concepts.md) | §1–2 on `__init__.py`, packages and imports. Module 06 was *packages inside a project*; module 08 is *packages arriving from outside it*. |
| [python_custom_exceptions.md](../02_Python/04_errors/python_custom_exceptions.md) | For a dedicated configuration error in ex2 rather than a bare `KeyError`. |
| [python_try_except_raise.md](../02_Python/04_errors/python_try_except_raise.md) | The guarded-import pattern and how narrow an `except` should be. |
| [Git.md](../05_Others/Git.md) | `.gitignore`, and why history rewriting is not a remedy for a committed secret. |
| [shell_101.md](../05_Others/shell_101.md) | `export`, `$PATH`, and why `source` exists — the mechanics under `activate`. |

### 8.4 Official docs (short, worth the detour)

- [`venv` — Creation of virtual environments](https://docs.python.org/3/library/venv.html) — read the "How venvs work" section; it is three paragraphs and answers most of ex0.
- [PEP 405 — Python Virtual Environments](https://peps.python.org/pep-0405/) — the source of the `sys.prefix` / `sys.base_prefix` rule.
- [PEP 668 — Externally managed environments](https://peps.python.org/pep-0668/) — why your system pip now refuses to install; a great thing to be able to explain.
- [`sys`](https://docs.python.org/3/library/sys.html) and [`site`](https://docs.python.org/3/library/site.html) — the two modules ex0 is built from.
- [`importlib.metadata`](https://docs.python.org/3/library/importlib.metadata.html) — `version()`, `distributions()`, `packages_distributions()`.
- [PEP 621 — Storing project metadata in pyproject.toml](https://peps.python.org/pep-0621/) — the standard Poetry now targets.

### 8.5 Ecosystem guides (online, free)

- [The Python Packaging User Guide](https://packaging.python.org/) — the official one. Its [Tool recommendations](https://packaging.python.org/en/latest/guides/tool-recommendations/) page is the neutral ground for the pip-vs-Poetry question, and citing it beats citing a blog.
- [Poetry — Basic usage](https://python-poetry.org/docs/basic-usage/) and [Dependency specification](https://python-poetry.org/docs/dependency-specification/) — where the caret operator is defined.
- [The Twelve-Factor App — III. Config](https://12factor.net/config) — one page, and it is the entire argument of ex2. Read it before you write `oracle.py`.
- [`python-dotenv` README](https://github.com/theskumar/python-dotenv) — short; the `override` parameter is the part that matters.
- [Brett Cannon, *Why you should use `python -m pip`*](https://snarky.ca/why-you-should-use-python-m-pip/) — a two-minute read that explains which pip you are actually running, and pairs perfectly with ex0's "which Python am I?" theme.

### 8.6 Not on the shelf yet

- **Publishing Python Packages** — Dane Hillard (Manning). The full lifecycle: `pyproject.toml`, build backends, versioning, publishing. The natural sequel to ex1.
- **uv** ([docs](https://docs.astral.sh/uv/)) — not required here, but it is where the ecosystem is heading: a single Rust tool covering venv creation, resolution, locking and installation. Naming it as "the third answer" to the pip-vs-Poetry question shows you follow the ecosystem, not just the subject.

---
