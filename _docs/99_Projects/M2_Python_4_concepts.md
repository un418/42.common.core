# Python Module 04 — Concepts Guide (File I/O & Streams)

> Subject: *Data Archivist — Digital Preservation in the Cyber Archives* (`_subjects/en.python_mod04.subject.pdf`)
> Python ≥ 3.10, flake8 + mypy clean, graceful exception handling, type hints on every function.

---

## 0. The big picture — "a file is a stream you open, use, and close"

The whole module is about **talking to things outside your program** — files on
disk and the three standard channels — through one abstraction: a **file object**
(a *stream*). The lifecycle is always the same three beats:

1. **open** a resource → you get a *file object* (a handle, **not** the contents)
2. **use** it — `.read()` / `.write()` / `.readline()`
3. **close** it — release the OS handle (or let `with` do it, ex3)

Two worries run through every exercise:

- **Failure is normal.** A file may not exist, be unreadable, or be a directory.
  Every `open()` can raise `OSError`; the module is graded on *never crashing* —
  wrap I/O in `try/except`.
- **Where does output go?** Normal results go to **stdout**, errors to **stderr**
  (ex2). They look identical in a terminal but are two different channels.

### The file lifecycle at a glance

| Step  | Read flow                          | Write flow                            |
| ----- | ---------------------------------- | ------------------------------------- |
| open  | `open(path)` / `open(path, "r")`   | `open(path, "w")`                     |
| use   | `f.read()` → whole file as `str`   | `f.write(text)` → chars to the file   |
| close | `f.close()` (ex0-2) or `with` (ex3)| same                                  |

### File modes you must be able to name

| Mode  | Meaning              | If the file exists  | If it is missing |
| ----- | -------------------- | ------------------- | ---------------- |
| `"r"` | read (default)       | read from the start | **error**        |
| `"w"` | write                | **truncate to 0**   | create it        |
| `"a"` | append               | write at the end    | create it        |
| `"x"` | exclusive create     | **error**           | create it        |

Ex1's hint *"create the file or replace it if it already exists"* is literally
the definition of **`"w"`**.

### Text mode & the type question

`open()` in text mode returns an `io.TextIOWrapper` — a **file object** that
yields `str`. That is the answer to ex0's understanding-check question, and it is
why `typing.IO` (`typing.IO[str]`) is the authorized hint type for a handle. A
file object is *not* a string: you must call `.read()` on it to get the contents.

---

## 1. Ex0 — READING a file (`open` / `read` / `close`)

### The concept

Recover a file named on the command line and print it like `cat`. Three steps:
`open()` the path → `f.read()` the contents → `f.close()`. `sys.argv[1]` is the
filename; `len(sys.argv)` guards the "no file given" usage case (same argv logic
as mod03 ex0). The new ideas are the **file object** returned by `open()` and the
fact that every step can fail.

```python
f = open(sys.argv[1])   # file object (a stream) — NOT the text
data = f.read()         # whole file as one str, trailing \n included
f.close()               # release the OS descriptor
```

### The subject's explicit question — know this cold

**Q: "What is the type of the data returned by `open()`?"**
It returns a **file object** (a *stream*), not a string and not the file's
contents. In text mode it is an `io.TextIOWrapper`; you then call `.read()` on it
to get the contents as a single `str`. For type hints the authorized name is
`typing.IO` (or `typing.IO[str]`). "It returns the file's text" is the classic
wrong answer at defense — it returns the **handle**.

### Reading the whole file — cat behaviour

- `f.read()` with no argument returns the **entire** file as one `str` (including
  the trailing newlines), which `print()` then displays like `cat`.
- The subject wants headers/footers around the content — plain `print()` calls
  before and after the dump.

### Handling failure — the three cases in the example

| Situation                             | Outcome                                  |
| ------------------------------------- | ---------------------------------------- |
| no argument given                     | `len(sys.argv)` check → usage line       |
| file doesn't exist (`foo`)            | `FileNotFoundError` — `[Errno 2]`        |
| no permission (`/etc/master.passwd`)  | `PermissionError` — `[Errno 13]`         |

Both `FileNotFoundError` and `PermissionError` are subclasses of **`OSError`**;
catching `OSError` handles both, and its `str()` already produces the
`[Errno N] ... : 'name'` text the example prints. Know the hierarchy so you can
justify catching the parent versus each child.

### Closing — and why

`f.close()` releases the OS file descriptor; leaving files open leaks
descriptors. The subject prints an explicit "closed" line so you *demonstrate*
you did it. (Ex3 replaces this manual step with `with`.)

---

## 2. Ex1 — WRITING a file (`"w"` mode, `write`, `input`)

### The concept

The same file object, opened for **writing**. `open(name, "w")`:

- **creates** the file if missing, **truncates** it to empty if it exists (the
  "create or replace" line),
- then `f.write(text)` writes a `str` — note `write()` does **not** append a
  newline, you include `\n` yourself.

Build on ex0's reader: *read → transform (add `#` at the end of each line) → show
→ optionally save*.

### Optional save — the empty-input branch

`input("Enter new file name (or empty): ")` returns a `str`:

- empty string → the user declined → print "Not saving" and stop.
- non-empty → `open(that_path, "w")`, write, confirm. This second `open()` can
  itself fail (bad path / permission) → same `try/except` discipline as ex0.

### `write()` vs `print()`

`print(x, file=f)` and `f.write(x)` both reach the file; this exercise's
authorized list names `io.write()`. `write()` takes a single `str`, returns the
number of characters written, and adds **no** `\n` and no `sep`. Be able to say
why you chose one over the other.

---

## 3. Ex2 — STREAMS (stdin / stdout / stderr)

### The concept

A running program is born with **three already-open file objects**:

| Stream        | fd | Purpose                   | Default target |
| ------------- | -- | ------------------------- | -------------- |
| `sys.stdin`   | 0  | input                     | keyboard       |
| `sys.stdout`  | 1  | normal output             | terminal       |
| `sys.stderr`  | 2  | error / diagnostic output | terminal       |

They are the same kind of file object `open()` gives you — you can `.write()`,
`.readline()`, `.flush()` them directly.

### The two required changes

1. **Errors → stderr.** `print("...", file=sys.stderr)` (or `sys.stderr.write(...)`)
   sends the `[STDERR] ...` lines to channel 2. Why it matters: stdout can be
   piped/redirected to a file while errors still reach the screen — separating
   the two is standard Unix hygiene.
2. **Input without `input()`.** Read a line yourself with `sys.stdin.readline()`.
   The difference to know: `input()` strips the trailing `\n` and raises
   `EOFError` at end of input; `readline()` **keeps** the `\n` (so you
   `.rstrip()`) and returns `""` at EOF. That contrast is the concept being
   tested.

### Buffering & `flush()`

Output is **buffered** — Python may hold text before actually writing it.
`sys.stdout.flush()` forces it out now. It matters when you interleave stdout and
stderr (ordering) or prompt without a trailing newline. `stderr` is typically
unbuffered, `stdout` line-buffered to a terminal — say this if asked why the
order looks off under redirection.

---

## 4. Ex3 — CONTEXT MANAGERS (`with`)

### The concept

`with open(path) as f:` opens the file and **guarantees** `f.close()` runs when
the block ends — normally *or* via an exception. It is the Pythonic replacement
for the manual `try/finally: f.close()` pattern.

```python
with open(path) as f:      # __enter__  → binds f
    data = f.read()
# __exit__ ran here: the file is closed even if read() raised
```

- **Introduced here on purpose** — the General Rules say you must **not** use
  `with` before ex3. Expect to explain *why* it is safer than a manual close.
- Under the hood: `with` calls the object's `__enter__` / `__exit__`; `__exit__`
  runs on the way out whatever happens — that is the leak-proofing.

### The function contract to build

`secure_archive(filename, action=?, content=?)` returns a **tuple** `(bool, str)`:

- `(True, <file contents>)` or `(True, "Content successfully written...")` on success,
- `(False, "<error message>")` on failure — the message is the caught
  exception's `str()`.

Concepts folded in: **optional parameters** (default action = read; optional
content for write), returning a **tuple** as a *(success, payload)* pair (the
same idiom you met in mod03), and doing *all* the I/O inside the `with` so a
failure still returns cleanly instead of crashing. The subject says the
**structure** of this function is reviewed at defense — be ready to walk it.

---

## 5. Module-wide rules & traps

- **Python ≥ 3.10**, flake8-clean, **type hints on every function** (checked with
  mypy) — including `-> None` on procedures and `typing.IO` for file handles.
- **Graceful exceptions** — no bad path or user input may crash a script. Wrap
  every `open()`/read/write; catch the **specific** exception (`OSError` /
  `FileNotFoundError` / `PermissionError`), not a bare `except`.
- **`with` only from ex3.** Using it earlier breaks the exercise's intent — ex0-2
  do manual `open` / `close`.
- **Authorized lists are per-exercise and progressive**: `input()` appears only
  in ex1; `sys.stdin/stdout/stderr` only in ex2; ex3 drops back to just
  `open / read / write / print` (plus `with`). Re-read each exercise header.
- **Allowed types**: `str, int, float, list, dict, set, tuple` and all their
  methods — from the Common Instructions preamble.
- **Output is customizable** — messages may be reworded "to reflect your
  understanding" as long as the essential info (filename, error, status) is
  preserved; the *structure* of the examples must stay.

---

## 6. Concept cheat-sheet (one-sentence definitions)

| Keyword | One-sentence definition to say out loud |
| ------- | ---------------------------------------- |
| **FILE OBJECT / STREAM** | The handle `open()` returns — an object you read/write/close, *not* the file's contents. |
| **`open()`** | Opens a path in a given mode and returns a text (or binary) file object; can raise `OSError`. |
| **MODE** | The second `open()` argument — `r` read, `w` write+truncate, `a` append, `x` exclusive-create. |
| **`read()`** | Returns the file's remaining contents as one `str` (the whole file if no size is given). |
| **`readline()`** | Returns the next line **including** its `\n`; returns `""` at end of file. |
| **`write()`** | Writes one `str` to the stream and returns the character count; adds no newline. |
| **`close()`** | Releases the OS file descriptor; skipped when a `with` block does it for you. |
| **STDIN / STDOUT / STDERR** | The three always-open streams (fd 0/1/2): input, normal output, error output. |
| **BUFFERING / `flush()`** | Output may be held before being written; `flush()` forces it out now. |
| **CONTEXT MANAGER / `with`** | An object with `__enter__`/`__exit__` that guarantees cleanup (file close) on block exit, even on error. |
| **`typing.IO`** | The type-hint name for a file object (`IO[str]` in text mode). |
| **`OSError`** | Base class for file-system errors; `FileNotFoundError` (`[Errno 2]`) and `PermissionError` (`[Errno 13]`) are subclasses. |
| **EOF** | End of input; `readline()` returns `""`, `input()` raises `EOFError`. |
| **TRUNCATE** | What `"w"` does to an existing file — empties it to length 0 before writing. |

---
