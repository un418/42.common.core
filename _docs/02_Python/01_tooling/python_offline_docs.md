# Python docs offline — `pydoc`, `help()`, `dir()`

> The Python manual from the command line. It reads the **docstrings** of the modules and objects actually installed — so the doc matches *exactly* the version of the interpreter, with no network. Three tools, two jobs: `pydoc`/`help()` to *understand*, `dir()` to *inventory*.

---

## `pydoc` — the manual (`man`-style)

Descriptions + signatures. This is the readable doc.

```bash
# Full doc of the list type: every method, signature and docstring
python3 -m pydoc list

# A single method
python3 -m pydoc list.append

# Through a pager
python3 -m pydoc list | less

# A whole module
python3 -m pydoc os
python3 -m pydoc os.path.join
```

Bonus — a local web server with the whole doc browsable:

```bash
python3 -m pydoc -p 8080        # then http://localhost:8080
python3 -m pydoc -b             # opens the browser directly
```

> Note: `pydoc list` also works without `-m` if the `pydoc` script is on the PATH, but `python3 -m pydoc` is the reliable form (it uses the right interpreter).

---

## `help()` — the same manual, interactive

Inside a `python3` REPL, `help()` is the exact equivalent of `pydoc`:

```python
>>> help(list)          # full doc of the type
>>> help(list.append)   # a single method
>>> help(str)
>>> help()              # interactive mode: type "list" then Enter, "q" to quit
```

Same content as `pydoc` (both read the docstrings) — one from the shell, the other from the REPL.

---

## `dir()` — the raw inventory of names

No description: just **the list of attributes/methods**. Ideal for "which methods exist, quickly".

```python
>>> dir(list)                                   # everything, dunders included
['__add__', ..., 'append', 'clear', 'copy', 'count', 'extend', 'index',
 'insert', 'pop', 'remove', 'reverse', 'sort']

>>> [m for m in dir(list) if not m.startswith('_')]   # the "public" ones only
['append', 'clear', 'copy', 'count', 'extend', 'index', 'insert',
 'pop', 'remove', 'reverse', 'sort']
```

As a one-liner from the shell:

```bash
python3 -c "print([m for m in dir(list) if not m.startswith('_')])"
```

---

## Which one to pick

| Need                                     | Tool                      |
| ---------------------------------------- | ------------------------- |
| Understand what a method does            | `pydoc` / `help()`        |
| See the signature / the arguments        | `pydoc` / `help()`        |
| List the available methods, fast         | `dir()`                   |
| Browse the whole stdlib at leisure       | `pydoc -b` (web server)   |

## Defense-day one-liner

> `pydoc`/`help()` read the docstrings of the installed version: the doc is local and always up to date. `dir()` gives only the *names*, with no description — for the inventory, not for understanding.

---

See also: [dev_env.md](dev_env.md) (interpreter & tooling setup), [python_keywords.md](../02_syntax_flow/python_keywords.md).
