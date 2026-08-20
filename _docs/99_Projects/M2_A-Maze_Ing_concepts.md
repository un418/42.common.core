# A-Maze-ing — Concepts Guide (Graphs, Randomness, Bitmasks & Packaging)

> Subject: *A-Maze-ing — This is the way* (`_subjects/en.A-Maze-ing.subject.pdf`, v2.2). Python ≥ 3.10, flake8 clean, mypy clean with `--warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs` (and `--strict` recommended), type hints on parameters / returns / variables, PEP 257 docstrings, exceptions handled *gracefully* (a crash during the review = non-functional), context managers for every resource, a `Makefile` with `install / run / debug / clean / lint`. **This subject has no `Authorized` allow-list** — after seven modules of `abc`-and-`typing`-only, the entire standard library is on the table (`random`, `collections`, `enum`, `dataclasses`, `argparse`, `curses`, `pathlib`…). Group project, and the deliverable is not just a program: a reusable `mazegen-*` package, a `LICENSE.md`, and a `README.md` that justifies your choices.

---

## 0. The big picture — "structure from chaos"

Every Python module so far graded one thing at a time: syntax, data structures, files, ABCs, packages, patterns. This project grades **a whole product**: an algorithm you chose and can defend, an encoding you must respect to the bit, a validation pass, a renderer, a distributable library, a licence, and a team.

The one sentence that organizes everything:

> **A maze is a graph.** Cells are vertices, missing walls are edges. Generating a maze = building a random connected subgraph of the grid. Solving it = a shortest-path search. Everything else is encoding, constraint-checking and presentation.

```
config.txt ──▶ [ parse + validate ] ──▶ Config(width, height, entry, exit, perfect, seed, …)
                                              │
                                              ▼
                            [ MazeGenerator ] ── seeded RNG ──▶ carve passages
                                              │
                                              ▼
                                       grid of cells
                                              │
        ┌──────────────────┬──────────────────┼──────────────────┬───────────────────┐
        ▼                  ▼                  ▼                  ▼                   ▼
  [ "42" stamp ]   [ braiding / loops ]  [ validation ]     [ solver: BFS ]     [ renderer ]
  fully closed      Pac-Man mode only     coherence          shortest path       ASCII + ANSI
  cells                                   connectivity       as N/E/S/W          + interaction
                                          corridors ≤ 2
        │                                       │                  │                  │
        └───────────────────▶ [ writer: hex grid + entry + exit + path ] ◀────────────┘
                                              │
                                              ▼
                                          maze.txt
```

### What each chapter of the subject is really asking

| Subject chapter | What it actually tests | Section here |
| --- | --- | --- |
| IV.2 Usage | CLI hygiene, one argument, never crash | §9 |
| IV.3 Config file format | Parsing a mini-format + validating every value | §9 |
| IV.4 Maze Requirements | Graph theory: spanning tree vs braided graph, invariants | §1–§4, §7 |
| IV.4 (seed) | Reproducible pseudo-randomness | §5 |
| IV.5 Output File Format | Bit manipulation, hexadecimal, exact byte-level layout | §6, §10 |
| IV.5 (shortest path) | BFS on an unweighted graph | §8 |
| V Visual representation | Terminal rendering, ANSI, input handling, restoring state | §11 |
| VI Code reusability | API design, separation of library/application, packaging, licensing | §12–§14 |
| VII Readme | Being able to *justify* every choice above | §16 |
| VIII Bonuses | Braiding to zero dead-ends, multiple algorithms, animation | §3, §4 |

### The duality to have in your head from minute one

```
        the maze (what you draw)              the graph (what you compute on)

        ┌───┬───────┐                          ●   ●───●
        │   │       │                          │   │
        ├───┼   ╷   ┤            ⇄             ●───●   ●
        │       │   │                              │   │
        └───────┴───┘                          ●───●   ●

        cell            = vertex
        missing wall    = edge
        wall            = no edge
        corridor        = path
        perfect maze    = spanning tree
        loop / cycle    = extra edge beyond the tree
        dead-end        = leaf (degree 1)
```

Once this mapping is fluent, every requirement in chapter IV.4 becomes a one-line graph statement — and that is exactly how you should say it at the defense.

---

## 1. THE GRID AS A GRAPH

### The concept

A **grid graph** of `W × H` cells: each cell `(x, y)` is a vertex, and each pair of orthogonally adjacent cells is a *potential* edge — the wall between them may be present (no edge) or removed (edge).

| Quantity | Formula | For 20 × 15 |
| --- | --- | --- |
| Vertices `V` (cells) | `W · H` | 300 |
| Potential interior edges `E_max` | `H(W−1) + W(H−1) = 2WH − W − H` | 565 |
| Edges of a perfect maze | `V − 1` | 299 |
| Interior walls kept in a perfect maze | `E_max − (V − 1)` | 266 |
| Border walls (always closed) | `2(W + H)` | 70 |

### Coordinates — decide the convention once, write it in the README

The config says `ENTRY=0,0` and `EXIT=19,14` for a 20×15 maze: `x` is the **column** (0 → W−1), `y` is the **row** (0 → H−1), and rows are written top to bottom. So `y` grows **southward**, which fixes your four deltas:

| Direction | Delta `(dx, dy)` | Opposite |
| --- | --- | --- |
| N | `(0, −1)` | S |
| E | `(+1, 0)` | W |
| S | `(0, +1)` | N |
| W | `(−1, 0)` | E |

Getting this backwards is the single most common source of "my path letters are mirrored" bugs, and it silently contradicts your renderer.

### Choosing the internal representation

| Representation | Type | Strength | Weakness |
| --- | --- | --- | --- |
| **Wall bitmask per cell** | `list[list[int]]` | maps 1:1 to the output file; O(1) "is there a wall here?" | the same wall is stored **twice** — it can disagree with itself |
| **Set of passages** | `set[tuple[Coord, Coord]]` with a normalized pair order | coherence is *impossible to break*: one wall, one entry | needs a conversion pass to produce the hex grid |
| **Two boolean grids** (V-walls, H-walls) | `list[list[bool]] × 2` | each wall stored once, still array-indexed | two structures to keep in your head |
| **Disjoint-set forest** | parent array | connectivity in near-O(1) | says nothing about walls; a companion structure, not a replacement |

There is no single right answer, but there is a right *discipline*: **one source of truth**. If you store the bitmask twice, every wall change must go through one helper that toggles both sides — never `grid[y][x] |= E` written by hand in five places. That helper is the answer to "how do you guarantee coherence?".

### The Python trap this project will hit you with

```python
grid = [[0] * width] * height      # ✗ height references to THE SAME row
grid[0][0] = 1                     # → column 0 of every row is now 1

grid = [[0] * width for _ in range(height)]   # ✓ one fresh list per row
```

`*` on a list copies **references**, not rows. This is *Fluent Python*, Ch 2, "Building Lists of Lists" (p. 51) — and it will look like a maze-generation bug for an hour.

---

## 2. PERFECT MAZE = SPANNING TREE

### The concept

| Term              | Definition                                                                                     |
| ----------------- | ---------------------------------------------------------------------------------------------- |
| **Connected**     | there is a path between any two vertices                                                       |
| **Acyclic**       | no cycle: no way to return to a vertex without reusing an edge                                 |
| **Tree**          | connected + acyclic ⇒ exactly `V − 1` edges, and **exactly one** path between any two vertices |
| **Spanning tree** | a tree that touches *every* vertex of the graph                                                |
| **Perfect maze**  | a maze whose passage graph is a spanning tree of the grid graph                                |

`PERFECT=True` is therefore not a vague aesthetic; it is a precise statement with three equivalent formulations, and being able to switch between them is the defense answer:

1. exactly one path between entry and exit (the subject's wording),
2. no loops at all, anywhere,
3. `V − 1` passages and full connectivity.

Any two of {connected, acyclic, `V−1` edges} imply the third — which gives you a **cheap validation**: count your carved passages. If it isn't exactly `V − 1`, the maze is not perfect and no traversal is needed to know it.

### Three consequences worth stating out loud

- **The "shortest path" is the only path.** In perfect mode, BFS and DFS return the same route. You still implement BFS, because the default mode needs it.
- **A perfect maze always has dead-ends.** A tree with at least 2 vertices has at least 2 leaves. So "perfect" and the "no dead-end at all" bonus are mathematically incompatible — that is why the bonus targets the *default* mode only. Say this at the defense; it proves you understand the tree, not just the code.
- **A perfect maze can never contain a 2×2 open area**, because four mutually connected cells form a cycle. So the "no corridor wider than 2 cells" rule costs you nothing in perfect mode, and everything in Pac-Man mode (§4, §7).

---

## 3. GENERATION ALGORITHMS

### The concept

Every classic algorithm builds a spanning tree; they differ only in **which edge they pick next**, and that choice produces a visible **texture** (also called *bias*, or *river* — how long and winding the corridors are). "Which algorithm did you choose and why?" is a mandatory README section, so you must be able to describe at least three and defend one.

| Algorithm | The idea in one line | Texture | Dead-ends | Extra memory |
| --- | --- | --- | --- | --- |
| **Recursive backtracker** (randomized DFS) | walk to a random unvisited neighbour, carving as you go; when stuck, back up to the last cell that still has one | long, winding corridors, few junctions | few, long | O(V) stack |
| **Randomized Prim** | keep the set of walls touching the visited region; pick one at random; carve if it reaches a new cell | short, bushy, many junctions | many, short | O(V) frontier |
| **Randomized Kruskal** | shuffle all interior walls; remove a wall only when it joins two *different* components (union-find) | even, very branchy | many | union-find + O(E) list |
| **Aldous-Broder** | random walk over the whole grid, carve on the first visit of each cell | **unbiased** (every spanning tree equally likely) | mixed | O(V) |
| **Wilson** | loop-erased random walks added one path at a time | **unbiased**, nicer runtime than Aldous-Broder | mixed | O(V) |
| **Eller** | row by row, merging sets left to right, guaranteeing vertical links | slightly horizontal | mixed | **O(W)** — independent of height |
| **Binary tree / Sidewinder** | for each cell, carve north or east at random | strong diagonal bias, two fully open borders | many | O(1) |

### The unification that pays for itself — "Growing Tree"

Keep a list of active cells. Repeat: **pick one cell from the list** (by some rule), carve to a random unvisited neighbour and add it; if there is none, remove the cell from the list.

| Pick rule | Behaves like |
| --- | --- |
| newest (last added) | recursive backtracker |
| random | Prim-like |
| oldest (first added) | BFS-like, very uniform |
| mix (e.g. 50 % newest / 50 % random) | tunable texture |

One implementation, a swappable pick rule, and the *"support multiple maze generation algorithms"* bonus costs a few lines instead of a second module. It is also a textbook use of the Strategy pattern you learned in module 07 — a link an evaluator will enjoy.

### The Python-specific trap: recursion

The "recursive backtracker" is named after its textbook form, but Python's default recursion limit is **1000 frames**. A 40×40 maze has 1600 cells and a corridor can visit most of them, so a truly recursive implementation raises `RecursionError` on a maze that is not even large. **Write it iteratively with an explicit stack** (a `list` used as LIFO, or `collections.deque`). Raising `sys.setrecursionlimit()` is the wrong answer, and saying *why* it is the wrong answer (you are trading a clean exception for a C-level stack overflow) is a good one.

### Complexity, so you can answer the question in one line

Generation is `O(V)` amortized for backtracker/Prim/Eller, `O(E log E)` for Kruskal if you sort (or `O(E · α(V))` if you shuffle and use union-find), and Aldous-Broder is `O(V³)`-ish in the worst case — elegant but slow. On a few thousand cells none of this matters; being able to say it does.

---

## 4. THE PAC-MAN BOARD — BRAIDING, LOOPS & DEAD-ENDS

### The concept

`PERFECT=False` is the **default**, and it is *not* "a perfect maze plus a bit of noise". The subject is explicit: a perfect maze with one wall removed is **not acceptable**. It asks for a *playable board*, and each of its four bullets is a graph property:

| Subject requirement | Graph statement | How you check it |
| --- | --- | --- |
| every corridor reachable, board fillable with pac-gums | the passage graph is **connected** | flood fill from any cell reaches all of them |
| at least two independent routes (loops) | **circuit rank** `E − V + 1 ≥ 2`, i.e. `E ≥ V + 1` | count carved passages |
| four corners + centre are open corridors | those five vertices have degree ≥ 1 and are not walled off | direct test after generation |
| dead-ends stay rare, zero is the bonus | number of **leaves** (degree-1 vertices) is small / null | count degrees |

### Circuit rank — the number to know

For a connected graph, the number of **independent cycles** is `E − V + 1` (the *circuit rank*, or cyclomatic number). A spanning tree has `E = V − 1` → rank 0. Removing one extra wall → rank 1 → a single loop, explicitly rejected by the subject. So your target is **at least `V + 1` passages**, and in practice comfortably more.

### Braiding

**Braiding** = removing dead-ends by opening one more wall at each leaf cell. Each removal adds an edge, so it adds a cycle. A **fully braided** maze has zero dead-ends, which is the bonus (`maze_analyzer.py --max-dead-ends 0`).

The approach, at the level you should be able to explain:

1. find every cell with exactly one open side (a leaf),
2. open one of its remaining walls — preferring a neighbour that is *also* a dead-end kills two leaves with one wall,
3. never open a border wall, and re-check the corridor-width rule afterwards, because braiding is exactly what creates 2×2 and then 3×3 open blocks (§7),
4. repeat until the leaf count reaches your target.

```
   before braiding (tree)              after braiding (rank ≥ 2)

   ●───●───●   ●                       ●───●───●───●
       │       │                           │   │   │
   ●   ●   ●───●        ──▶              ●───●   ●───●
   │   │   │                             │   │   │
   ●───●   ●   ●                         ●───●───●───●
     leaves everywhere                    no leaf left, several routes
```

### The tension to design for, not to discover late

The two modes share one generator but pull in opposite directions: perfect mode *forbids* every cycle, playable mode *requires* several and dislikes leaves. The clean shape is **one spanning-tree generator + one optional post-processing pass** (braiding) driven by the `PERFECT` flag — not two unrelated code paths. That single design decision is worth a paragraph in the README.

---

## 5. RANDOMNESS & REPRODUCIBILITY (THE SEED)

### The concept

`random` gives you a **PRNG** — pseudo-random: a deterministic function of an internal state. Seeding fixes that state, so the same seed replays the same sequence, which is what makes *"randomly generated, but reproducibility via a seed is required"* satisfiable at all.

| Term | Meaning |
| --- | --- |
| **PRNG** | deterministic algorithm producing a statistically random-looking stream |
| **Seed** | the initial state; same seed + same code + same call order ⇒ same output |
| **Mersenne Twister** | the MT19937 generator behind Python's `random`; huge period, well distributed, **not cryptographically secure** |
| **`random.Random`** | an *instance* of the generator, with its own independent state |
| **`secrets`** | the CSPRNG module, for tokens and keys — the right answer to "why not use `random` for passwords?" |

### The design choice for a reusable library

```python
import random

class MazeGenerator:
    def __init__(self, width: int, height: int, seed: int | None = None) -> None:
        self._rng = random.Random(seed)      # ✓ private state, no global side effect
        ...
```

Module-level `random.seed(42)` mutates a **global** shared with every other library in the process — acceptable in a script, wrong in a package meant to be imported by someone else's game. One instance per generator also means two generators in the same program never interfere. Expect the question: *"what happens if the Pac-Man project also calls `random`?"*

### Reproducibility is a contract you can accidentally break

| Trap | Why it breaks the seed | Fix |
| --- | --- | --- |
| iterating a `set` to pick a neighbour | set order is an implementation detail; for `str` elements it also varies per run (`PYTHONHASHSEED`) | build a `list`, sort it, then let the RNG choose |
| `random.sample(some_set, k)` | deprecated since 3.9, **removed in 3.11** for sets | `random.sample(sorted(s), k)` |
| using `dict` order from a dict you built in a non-deterministic order | insertion order is preserved — but only as deterministic as the insertions | control the insertion order |
| changing the *number* of RNG calls between two versions | every later draw shifts | keep the call sequence stable, or document that the seed is version-bound |

### What to do when no seed is given

Draw one yourself (e.g. from `random.randrange`), use it, and **print it / write it in the output or the config**. Otherwise a beautiful maze produced during the demo can never be shown again — and an evaluator asking "can you regenerate exactly this one?" is a fair question.

---

## 6. WALL ENCODING — BITMASK & HEXADECIMAL

### The concept

One cell, four walls, four bits, one hexadecimal digit — because 4 bits is exactly one hex digit (`0`–`F`).

```
        bit    3     2     1     0          value
               W     S     E     N
               8     4     2     1

        1 = wall CLOSED          0 = wall OPEN

        0xF = 1111 = fully closed cell (the "42" pattern)
        0x0 = 0000 = fully open cell (forbidden in practice: it is a 4-way junction)
        0x3 = 0011 = N + E closed, S + W open      ← the subject's example
        0xA = 1010 = W + E closed, N + S open      ← a vertical corridor
```

| Operation | Expression | Note |
| --- | --- | --- |
| close a wall | `mask \|= N` | bitwise OR — idempotent |
| open a wall | `mask &= ~N` | AND with the complement |
| test a wall | `if mask & N:` | non-zero = closed; **never** `== 1` |
| toggle | `mask ^= N` | XOR |
| opposite direction | `((d << 2) \| (d >> 2)) & 0xF` | with N=1,E=2,S=4,W=8 this maps N↔S and E↔W in one expression |
| render | `f"{mask:X}"` | one uppercase hex digit, no padding needed since `mask ≤ 15` |
| parse back | `int(ch, 16)` | for your own tests and for re-reading an output file |

### `enum.IntFlag` — available here, and a strong touch

The standard library is fully authorized in this project, so the magic numbers can disappear:

```python
from enum import IntFlag

class Wall(IntFlag):
    N = 1
    E = 2
    S = 4
    W = 8
```

Members are real `int`s, so `mask & Wall.N`, `mask | Wall.E` and `f"{int(mask):X}"` all still work, while `repr()` prints `Wall.N|E` — which makes debugging a wall bug enormously faster. mypy understands it. The cost is nearly zero; the readability gain in the renderer and the validator is large.

### The coherence invariant, written as an equation

> *"each neighbouring cell must have the same wall if any"*

```
        bool(grid[y][x]   & E)  ==  bool(grid[y][x+1] & W)          for every x < W−1
        bool(grid[y][x]   & S)  ==  bool(grid[y+1][x] & N)          for every y < H−1
```

Two comparisons per cell pair, each wall visited once (check only E and S and you cover the whole grid without duplicates). This is precisely what the provided `maze_analyzer.py` verifies first, so make it a function of your own and call it before writing the file.

---

## 7. VALIDATION — THE INVARIANTS AND HOW TO CHECK THEM

### The concept

The subject lists five structural requirements. Each maps to one check, and together they form the acceptance test you should be able to run yourself before ever touching the analyzer.

| # | Requirement (IV.4) | Check | Cost |
| --- | --- | --- | --- |
| 1 | entry and exit exist, differ, are inside bounds | validate at config-parse time, before generating anything | O(1) |
| 2 | walls on the external borders | row 0 has N closed, row H−1 has S, column 0 has W, column W−1 has E | O(W+H) |
| 3 | shared walls agree | the two equations of §6 | O(V) |
| 4 | full connectivity, no isolated cell (except the "42") | flood fill (BFS/DFS) from entry; count reached cells | O(V+E) |
| 5 | no corridor wider than 2 cells | slide a 3×3 window; the block is illegal if **all 12 interior walls** are open | O(V) |

### Reading requirement 5 correctly

"Corridors can't be wider than 2 cells. You can have 2×3 or 3×2 open areas, but never 3×3." So a 2×2 or 2×3 open block is legal — only a fully open 3×3 block is not. The test is local: for each top-left cell of a 3×3 window, check the 6 horizontal and 6 vertical interior passages; if every one of them is open, you have a room. This only ever triggers after braiding (§4), which is exactly when to run it.

### The "42" pattern — the subtle one

The maze must show a visible **42** drawn by *fully closed cells* (`0xF`). Three consequences that people discover too late:

- **Closing a cell means closing its neighbours' facing walls too**, or the coherence check fails immediately. A "42" cell is a hole punched out of the graph, and the hole has two sides.
- **It removes vertices from the graph.** The connectivity requirement explicitly exempts the "42" cells, but *everything else* must remain connected around them — so the safest order is: reserve the glyph cells **before** generating, and generate the maze on the remaining cells. Stamping the glyph after generation can cut the maze in two.
- **Small mazes can't fit it.** The subject allows omitting it then, but **requires an error message on the console**. That is a graded behaviour, not a detail: it needs a minimum-size rule you can state (glyph width/height + margin) and a message.

Storing the glyph as a small list of strings (`"#..#.###"` style) mapped onto cell coordinates keeps it readable, centrable, and easy to resize.

### Testing invariants is where pytest pays off

Not graded, not submitted — but four properties are trivially testable and will save the defense: coherence holds, connectivity holds, `PERFECT=True` gives exactly `V−1` passages, and the same seed twice gives byte-identical output files.

---

## 8. SOLVING — BFS & THE SHORTEST PATH

### The concept

The passage graph is **unweighted** (every step costs 1). On an unweighted graph, **breadth-first search visits vertices in order of increasing distance from the source**, so the first time BFS reaches the exit, it has reached it by a shortest route. That single sentence is the whole justification, and it is what to say when asked "why BFS?".

```
   BFS wavefront from the entry            frontier expands one ring at a time
                                           ⇒ first arrival = fewest steps
        0 1 2 3 4
        1 2 3 . 5
        2 3 . 5 6                          DFS would also reach the exit —
        3 . 5 6 7                          but by *a* path, not the shortest.
```

| Piece | Role | Standard tool |
| --- | --- | --- |
| queue | cells to expand, FIFO | `collections.deque` — `popleft()` is O(1), `list.pop(0)` is O(n) |
| visited | never enqueue a cell twice | `set[Coord]` |
| parent map | `child → parent`, the only thing you need to rebuild the route | `dict[Coord, Coord]` |
| reconstruction | walk back from the exit to the entry, then reverse | `list.reverse()` or `[::-1]` |
| letters | each consecutive delta → `N`/`E`/`S`/`W` | one dict `(dx, dy) → letter` |

Complexity `O(V + E)`, and in a grid `E ≤ 2V`, so it is linear in the number of cells. Memory is `O(V)`.

### Neighbours must be *passages*, not adjacent cells

The one bug everyone writes: expanding to `(x+1, y)` without first testing that the east wall is open. In graph terms you would be walking through walls. Have one function `neighbours(cell) -> list[Coord]` that returns only cells reachable through an open wall, and let both the solver **and** the connectivity check use it — one definition, two consumers, no drift.

### The alternatives, and why you don't need them

| Algorithm | When it wins | Here |
| --- | --- | --- |
| **DFS** | just needs *some* path, or exploring deep structures | returns a path, not the shortest — insufficient in braided mode |
| **Dijkstra** | edges have different costs | all costs are 1 ⇒ it degenerates into BFS with a useless heap |
| **A\*** | large graphs, good heuristic available (Manhattan distance) | works, needs `heapq`; a fine bonus, never a requirement |
| **Bidirectional BFS** | very large graphs | overkill at these sizes |

Free side-effect worth knowing: a BFS from the entry gives the **distance to every cell**, not just the exit. That is a colour-gradient rendering for free, and it identifies the farthest cell — useful if you ever let the program choose entry/exit itself.

---

## 9. THE CONFIG FILE — PARSING & GRACEFUL FAILURE

### The format

```
# comments start with a hash and are ignored
WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=True
```

Six mandatory keys, one `KEY=VALUE` per line, `#` comments ignored, extra keys allowed (`SEED`, `ALGORITHM`, `DISPLAY`…). A **default config file must live in the repository**, and its complete structure must be documented in the README.

### The parsing checklist

1. read with a context manager, explicit `encoding="utf-8"`,
2. strip each line; skip empty lines and lines starting with `#`,
3. split on the **first** `=` only (`str.split("=", 1)` or `str.partition("=")`) — an output path could contain one,
4. normalize the key (strip, upper), strip the value,
5. reject unknown-but-suspicious input as you see fit, but **never** silently ignore a malformed line,
6. verify all six mandatory keys are present *after* the loop,
7. convert and validate types, then validate relationships (entry ≠ exit, both inside `W × H`).

### Every value needs a rule

| Key | Rule | Failure to handle |
| --- | --- | --- |
| `WIDTH` / `HEIGHT` | integer, ≥ a sensible minimum, ≤ a sane maximum | `"abc"`, `"-5"`, `"0"`, `"20.0"`, `"1e9"` |
| `ENTRY` / `EXIT` | `x,y`, both integers, inside bounds, and **different from each other** | `"0"`, `"0,0,0"`, `"a,b"`, `"99,99"` |
| `OUTPUT_FILE` | non-empty; the directory must be writable | unwritable path, existing directory |
| `PERFECT` | an explicit string→bool mapping | **`bool("False")` is `True`** — the classic trap |
| `SEED` (optional) | integer, or absent | non-numeric |

### "Must never crash unexpectedly" — what that means concretely

```
        main()
          └─ try:  parse → generate → validate → write → render
             except MazeError as err:      ← your own hierarchy
                 print(f"error: {err}", file=sys.stderr)
                 sys.exit(1)
```

- Define **one root exception** for the project (`MazeError`) and derive `ConfigError`, `GenerationError`… Callers of your library then catch one class. (*Effective Python*, Item 121.)
- Chain with `raise ConfigError(...) from err` so the original cause survives in the traceback you keep for yourself.
- Catch **at the top level only**, print a clear message to **stderr**, exit non-zero. A traceback reaching the evaluator's terminal is the failure the subject describes.
- A bare `except:` is flake8 `E722`, and `except Exception: pass` is worse than a crash — it hides the bug and produces a wrong maze.
- The realistic evaluator moves are all filesystem ones: file missing (`FileNotFoundError`), path is a directory (`IsADirectoryError`), no read permission (`PermissionError`), binary file (`UnicodeDecodeError`), no argument at all, two arguments. Test the six.

---

## 10. THE OUTPUT FILE

### The exact layout

```
        1F5A7…            ┐
        3C2E9…            │  H lines, W hexadecimal digits each, row by row
        …                 ┘
                          ←  one empty line
        0,0               ←  entry coordinates
        19,14             ←  exit coordinates
        SSEESSWWSS…       ←  the shortest path, letters N / E / S / W only
```

Every line ends with `\n`, **including the last one**. The blank line is part of the format, not decoration.

### The details that decide a moulinette pass

| Point | Do |
| --- | --- |
| digits | uppercase hex, one per cell, no separators (`f"{mask:X}"`) |
| line endings | text mode writes `\n` as-is on macOS/Linux; be explicit with `newline="\n"` if you want it guaranteed everywhere |
| encoding | pass `encoding="utf-8"` rather than relying on the platform default (*Fluent Python*, "Beware of Encoding Defaults", p. 134) |
| coordinates | same `x,y` form as the config, no spaces |
| path | letters only, no separators, entry→exit order |
| resource | `with open(...) as f:` — the general rules mandate context managers |

### The provided analyzer is your moulinette

`maze_analyzer.py` ships with the subject: given an output file it verifies wall coherence and reports whether the maze is *perfect* or a *playable board*, with `--max-dead-ends 0` for the braided bonus. Run it on both modes, with several seeds and sizes, **before** the defense — and mention in the README that you did.

---

## 11. VISUAL REPRESENTATION & INTERACTION

### The rendering grid

A `W × H` maze of cells becomes a character grid of `(2W + 1) × (2H + 1)`: walls live on the odd coordinates, cells on the even ones.

```
        col →   0   1   2   3   4      (2W+1 characters)
        row 0   ┌───┬───────┐
            1   │   │       │          odd row / odd col  = junction
            2   ├───┼───╴   ┤          odd row / even col = horizontal wall segment
            3   │       │   │          even row / odd col = vertical wall segment
            4   └───────┴───┘          even row / even col = the cell itself
```

Each **junction** character is determined by which of its four wall segments exist — 16 combinations, so a 16-entry lookup table indexed by a 4-bit mask (the same trick as §6) turns the renderer into a table lookup instead of an `if` forest:

| Segments present | Char | | Segments present | Char |
| --- | --- | --- | --- | --- |
| N+E+S+W | `┼` | | N+S | `│` |
| N+E+S | `├` | | E+W | `─` |
| E+S+W | `┬` | | N+E | `└` |
| N+S+W | `┤` | | N+W | `┘` |
| N+E+W | `┴` | | E+S | `┌` |
| S+W | `┐` | | one arm only | `╵ ╶ ╷ ╴` |

Double the horizontal step (`───` instead of `─`) to compensate for character cells being taller than wide — that is why the subject's screenshots look square.

### Colour — ANSI escape sequences

| Effect | Sequence |
| --- | --- |
| reset | `\033[0m` |
| bold | `\033[1m` |
| 8 basic colours | `\033[31m` … `\033[37m` (foreground), `\033[41m`… (background) |
| 256 colours | `\033[38;5;{0-255}m` |
| true colour | `\033[38;2;{r};{g};{b}m` |
| clear screen + home | `\033[2J\033[H` |

Always emit a reset after a coloured run, or the user's shell prompt stays purple after your program exits — a small thing that reads as sloppiness during a defense.

### Interaction — the required four

The subject demands at minimum: **regenerate**, **show/hide the shortest path**, **change wall colours**, and optionally colour the "42". Two implementation routes:

| Route | How | Trade-off |
| --- | --- | --- |
| `input()` loop | print the maze, read a command, redraw | trivial, portable, needs Enter after each key; entirely acceptable |
| raw single keypress | `curses`, or `termios` + `tty.setcbreak` | real-time feel, arrow keys; **you must restore the terminal** |

If you go raw, restoration is not optional: wrap it in `try/finally` or a context manager (`curses.wrapper` does it for you). A crash that leaves the terminal without echo is exactly the "resources properly managed" rule from chapter III, applied to the tty.

Also worth a line of defense: `shutil.get_terminal_size()` lets you warn instead of vomiting a wrapped maze when the terminal is too narrow.

### About MLX

The subject allows MiniLibX as an alternative, but MLX is a C library: using it from Python means `ctypes` bindings or a compiled extension, for a project whose grade lies elsewhere. Choosing terminal ASCII is a legitimate, defendable engineering decision — say *why* (portability, zero dependency, the pip package stays pure-Python `py3-none-any`), don't say "it was easier".

---

## 12. THE REUSABLE MODULE — API DESIGN

### The concept

> *"You must implement the maze generation as a unique class inside a standalone module that can be imported in a future project."*

This is the chapter that decides whether the project is *good* or merely *working*, and it is the direct continuation of modules 06 and 07: a package publishes a **stable public surface**, and everything else is free to change.

### The separation of concerns to enforce

```
        a_maze_ing.py            ← the APPLICATION: argv, config file, printing, rendering, exit codes
              │  imports
              ▼
        mazegen.py               ← the LIBRARY: pure computation, no I/O, no print, no sys.exit
              MazeGenerator
```

| The library must **not** | Because |
| --- | --- |
| read the config file | its caller may have the parameters from a GUI, a test, or a game level |
| `print()` | a game engine decides what appears on screen (the "42 too small" message belongs to the app, or to a returned status/`warnings.warn`) |
| call `sys.exit()` | a library that kills the process cannot be reused; raise an exception instead |
| depend on the terminal | the future project may be graphical |

Everything the application needs must be reachable through the API — that is what makes the sentence *"what part of your code is reusable, and how"* answerable in the README.

### The public surface checklist

| Element | Why the evaluator will look for it |
| --- | --- |
| constructor with `width`, `height`, `seed`, `perfect` (and entry/exit or a default) | *"pass custom parameters (e.g. size, seed)"* is required documentation |
| a `generate()` (or generation in `__init__`, decided once) | the basic example in the README |
| an accessor for the **structure** | required — and the subject notes it need not be the file format |
| an accessor for **at least one solution** | required |
| an export to the hex/file representation | keeps the app thin |
| `__version__`, `__all__` | a package with a declared surface |
| type aliases (`Coord = tuple[int, int]`) | readable signatures under `mypy --strict` |
| PEP 257 docstrings on the class and every public method | mandated by chapter III, and it *is* the documentation |

### Two small things that make it a real library

- **Return copies, not internals.** Handing back your live `list[list[int]]` lets a caller corrupt the generator's state from the outside; a shallow copy of a nested list is still shared (*Fluent Python*, "Copies Are Shallow by Default", p. 208) — copy each row, or return an immutable view.
- **Validate constructor arguments and raise your own exception.** The app validates the config file; the library validates its own arguments, because its next caller is not your app.

The required documentation (instantiate, pass parameters, read the structure, read a solution, with a runnable example) must appear **both** in the module's docstrings and in the root `README.md`.

---

## 13. PACKAGING — sdist, WHEEL & `pyproject.toml`

### The vocabulary that gets confused

| Term | What it is |
| --- | --- |
| **Module** | one `.py` file |
| **Import package** | a directory with `__init__.py` — what `import x` gives you (module 06) |
| **Distribution package** | the *archive* you ship: what pip installs, named `mazegen-1.0.0…` |
| **sdist** (`.tar.gz`) | a source distribution: your sources + metadata; pip must *build* it at install time |
| **wheel** (`.whl`) | a built distribution: a zip archive installed by unpacking — no build step, no arbitrary code executed |
| **Build backend** | the tool that turns sources into those archives (`setuptools`, `hatchling`, `flit`…) |
| **Build frontend** | what you invoke: `python -m build`, or `pip` |

### Wheel filename anatomy — the subject's `mazegen-*` requirement

```
        mazegen  -  1.0.0  -  py3  -  none  -  any  .whl
           │          │        │       │       │
           │          │        │       │       └── platform tag: any OS
           │          │        │       └────────── ABI tag: no compiled extension
           │          │        └────────────────── Python tag: any Python 3
           │          └─────────────────────────── version (PEP 440)
           └────────────────────────────────────── distribution name
```

**Naming trap:** in wheel filenames, `-` separates fields, so a distribution named `maze-gen` is written `maze_gen-1.0.0-…whl` and no longer matches the required `mazegen-*`. Name the distribution `mazegen`, plainly.

### A minimal `pyproject.toml` for a single-module package

```toml
[build-system]
requires = ["setuptools>=68"]
build-backend = "setuptools.build_meta"

[project]
name = "mazegen"
version = "1.0.0"
description = "Reusable maze generator"
requires-python = ">=3.10"
readme = "README.md"
license = { file = "LICENSE.md" }     # newer setuptools also accept: license = "MIT"

[tool.setuptools]
py-modules = ["mazegen"]              # a single .py file, not a package directory
```

The relevant PEPs, worth naming: **517/518** (build backends and `pyproject.toml`), **621** (the `[project]` metadata table), **440** (version numbers), **427** (the wheel format).

### Build, install, verify — the sequence you will be asked to redo live

```
python -m venv .venv && . .venv/bin/activate
pip install build
python -m build                      # → dist/mazegen-1.0.0.tar.gz + …-py3-none-any.whl
pip install dist/mazegen-1.0.0-py3-none-any.whl
python -c "import mazegen; print(mazegen.__version__)"
```

The evaluation explicitly asks you to **rebuild the package from your sources in a virtualenv**, so everything needed to build must be committed (`pyproject.toml`, the module, `README.md`, `LICENSE.md`) — and nothing needed must live only on your machine.

### The `.gitignore` inversion

Build artefacts are normally ignored — but this subject **requires the built `.whl` or `.tar.gz` at the root of the repository**. So `dist/`, `*.whl` and `*.tar.gz` patterns in your `.gitignore` will silently swallow the deliverable. Check it with `git check-ignore -v <file>` and `git add -An` before the defense; a package that exists locally and not in the clone is the most expensive kind of mistake in this project.

---

## 14. LICENSING

### Why the subject makes this an exercise

Your generator is meant to be **reused by a later project**, possibly by other people. Without a licence, default copyright applies: *all rights reserved* — nobody may legally reuse or redistribute it, however public the repository is. Writing `LICENSE.md` is therefore a functional requirement, not paperwork.

| Licence | Family | Obligations for the reuser | Notable |
| --- | --- | --- | --- |
| **MIT** | permissive | keep the copyright notice + licence text | shortest, most common, zero friction — the natural default here |
| **BSD-2/3-Clause** | permissive | same, plus (3-clause) no endorsement using your name | equivalent to MIT in practice |
| **Apache-2.0** | permissive | notice + state changes | adds an explicit **patent grant**; longer, more "corporate" |
| **MPL-2.0** | weak copyleft | modified *files* must stay MPL | file-level, mixes fine with other code |
| **GPL-3.0** | strong copyleft | the whole derived work must be GPL | allowed, but it **forces** the downstream game to be GPL too |
| **AGPL-3.0** | strong copyleft | extends copyleft to network use | actively hostile to reuse here |
| *no licence* | — | none possible | ✗ fails the subject's requirement |

### The checklist

- `LICENSE.md` at the **root**, containing the full text, the year, and **all team members** as copyright holders.
- The licence must *explicitly allow reuse and distribution* — that is the subject's own criterion, and it disqualifies "all rights reserved" and custom hand-written terms.
- Declare it in `pyproject.toml` so it travels inside the wheel metadata.
- Be ready to justify the choice in one sentence: *"permissive, so the Pac-Man project can reuse it without inheriting any obligation"* is enough — and know what you would have chosen instead, and why.
- <https://choosealicense.com/> is the standard 30-second reference (already in your links).

---

## 15. Project-wide rules & traps

- **Fixed filename: `a_maze_ing.py`**, run as `python3 a_maze_ing.py config.txt`, exactly one argument. Check `len(sys.argv)` and fail cleanly on 0 or 2+ arguments.
- **Python ≥ 3.10**, so `int | None`, `list[tuple[int, int]]` and `match` are available — no `typing.List`, no `Optional[...]` needed.
- **`flake8 .` and the full `mypy` flag line must be clean** — and the Makefile's `lint` rule is what the evaluator runs. `lint-strict` (`mypy . --strict`) is optional but is the version that catches the untyped `**kwargs` and the `Any` leaks.
- **The Makefile is graded**: `install`, `run`, `debug` (via `pdb`), `clean` (`__pycache__`, `.mypy_cache`), `lint`, optional `lint-strict`. Mark them `.PHONY` — none of them produces a file of that name.
- **No `Authorized` restriction in this subject.** The whole standard library is fair game — but every import you add is something you must be able to justify, and a pure-standard-library project builds a `py3-none-any` wheel with zero dependencies, which is worth keeping.
- **Type hints on variables too**, not just signatures — the general rules say "parameters, return types, **and variables where applicable**". `grid: list[list[int]] = []` is the kind of annotation `--disallow-untyped-defs` won't force but a reviewer will notice.
- **Docstrings PEP 257 on every function and class**, in one consistent style (Google or NumPy — pick one, don't mix). For the reusable module they *are* the deliverable documentation.
- **Never crash**: one root exception, one top-level handler, message on stderr, non-zero exit. Verify with a missing file, a directory, an empty config, a config with a missing key, a negative size, entry == exit.
- **Everything must work from a fresh clone.** Build the wheel, run the default config, run the analyzer — in a clean directory, in a fresh virtualenv. This project has more root-level deliverables than any before it (`a_maze_ing.py`, the module, the wheel, `pyproject.toml`, `LICENSE.md`, `README.md`, the default config, `.gitignore`, `Makefile`); one forgotten `git add` is a failed defense.
- **The README is a graded artefact**, with an imposed first line (*This project has been created as part of the 42 curriculum by <login1>, <login2>…*, in italics) and imposed sections: Description, Instructions, Resources (**including how AI was used, for which tasks and which parts**), plus the project-specific list in §16.
- **Group project mechanics count**: the README must describe roles, the planning and how it evolved, what worked and what did not, and the tools used. Agree early on the internal structure (§12) — the library/application split is what lets two people work without collisions.
- **A live modification may be asked at the defense**: add a config key, change a rendering detail, store one more piece of data. Code with obvious seams (a config dataclass, a table-driven renderer, a strategy-selected algorithm) makes that a two-minute edit instead of a rewrite.

---

## 16. The defense question bank

The README chapter is, almost literally, the list of questions you will be asked. Prepare the *shape* of each answer.

| Question | What a strong answer contains |
| --- | --- |
| "Explain your config file format." | the six mandatory keys, your extra keys, how comments and whitespace are handled, and **what happens for each malformed input** |
| "Which generation algorithm did you choose, and why?" | the name, the one-line mechanism, its texture/bias, at least one alternative you rejected **and the reason** (bias, memory, recursion depth, complexity) |
| "Why is your maze perfect / playable?" | the graph statement: spanning tree, `V−1` edges, circuit rank ≥ 2, leaf count — not "because the analyzer says so" |
| "How do you guarantee wall coherence?" | the single source of truth, plus the two-equation check |
| "Show me the same maze twice." | the seed, the `random.Random` instance, and where the seed is recorded |
| "Why BFS?" | unweighted graph ⇒ first arrival is a shortest arrival; what DFS would return instead |
| "What is reusable, and how?" | the library/application boundary, the public API, the `pip install` of your own wheel |
| "Rebuild your package." | venv → `pip install build` → `python -m build` → install → import, from a fresh clone |
| "Why this licence?" | permissive vs copyleft, and the consequence for the downstream project |
| "Add feature X." | done in a few lines, in the right layer, still `flake8`/`mypy` clean |
| "Who did what?" | roles, branches, review process, what you would organize differently |

---

## 17. Terminology — every term of the project, defined

### 17.1 Graph theory

| Term | Definition |
| --- | --- |
| **Graph** | a set of vertices and a set of edges connecting them. |
| **Grid graph** | the graph of a `W × H` lattice where each cell is adjacent to its 4 orthogonal neighbours. |
| **Degree** | the number of edges at a vertex — here, the number of *open* sides of a cell. |
| **Path** | a sequence of vertices joined by edges; in a maze, a corridor. |
| **Cycle / loop** | a path returning to its start without reusing an edge. |
| **Connected** | every vertex is reachable from every other. |
| **Component** | a maximal connected subgraph; a valid maze has exactly one (plus the "42" holes). |
| **Tree** | a connected acyclic graph: `V − 1` edges, exactly one path between any two vertices. |
| **Leaf** | a degree-1 vertex — a **dead-end**. |
| **Spanning tree** | a tree covering every vertex of the graph — the formal definition of a perfect maze. |
| **Circuit rank** | `E − V + 1`: the number of independent cycles; 0 for a tree, ≥ 2 required by the Pac-Man mode. |
| **Flood fill** | traversal from a seed vertex covering its whole component — the connectivity check. |

### 17.2 Maze vocabulary

| Term | Definition |
| --- | --- |
| **Perfect maze** | exactly one path between any two cells; no loops. |
| **Braided maze** | a maze whose dead-ends have been removed by opening extra walls, creating loops. |
| **Braiding** | that removal process; a *full braid* has zero dead-ends. |
| **Dead-end** | a cell with a single opening. |
| **Texture / bias** | the visual signature an algorithm leaves (corridor length, branching, diagonal artefacts). |
| **River** | the tendency to produce long winding corridors — high for the backtracker, low for Prim. |
| **Room / open area** | a block of mutually connected cells; forbidden here beyond 2 cells wide (no 3×3). |
| **The "42" pattern** | a glyph drawn by fully closed (`0xF`) cells, exempted from the connectivity rule. |
| **Entry / exit** | two distinct in-bounds cells; the endpoints of the required shortest path. |

### 17.3 Algorithms & data structures

| Term | Definition |
| --- | --- |
| **BFS** | breadth-first search: explores by distance rings using a FIFO queue; shortest paths on unweighted graphs. |
| **DFS** | depth-first search: goes as deep as possible, backtracks; finds *a* path, not the shortest. |
| **Recursive backtracker** | randomized DFS carving as it walks — the classic generator; implement it iteratively. |
| **Randomized Prim** | grows the maze from a random frontier of walls. |
| **Randomized Kruskal** | shuffles all walls and removes those joining two distinct components. |
| **Union-find / DSU** | disjoint-set forest with union by rank and path compression; near-constant `α(n)` per operation. |
| **Aldous-Broder / Wilson** | random-walk generators producing a **uniform** spanning tree. |
| **Eller's algorithm** | row-by-row generation with `O(W)` memory. |
| **Growing Tree** | the family that reproduces backtracker/Prim/BFS-like textures by changing one pick rule. |
| **`deque`** | double-ended queue with O(1) `append`/`popleft` — the BFS queue. |
| **`heapq`** | binary heap; the priority queue behind Dijkstra/A\*. |
| **Manhattan distance** | `\|Δx\| + \|Δy\|`; the admissible heuristic for A\* on a grid. |
| **Amortized / `O(α(n))`** | cost per operation averaged over a sequence; `α` is the inverse Ackermann function — constant for any real input. |

### 17.4 Randomness

| Term | Definition |
| --- | --- |
| **PRNG** | pseudo-random generator: deterministic given its state. |
| **Seed** | the initial state; the reproducibility handle the subject requires. |
| **Mersenne Twister** | MT19937, the algorithm behind `random`; excellent statistically, **not** cryptographic. |
| **`random.Random`** | an independent generator instance — the right choice inside a library. |
| **CSPRNG / `secrets`** | the cryptographically secure alternative, for keys and tokens. |
| **`PYTHONHASHSEED`** | environment variable randomizing `str` hashing per run — the reason set iteration order is not reproducible. |

### 17.5 Bits & encoding

| Term | Definition |
| --- | --- |
| **Bitmask / flags** | packing several booleans into the bits of one integer. |
| **Bitwise OR / AND / XOR / NOT** | `\|` sets, `&` tests, `^` toggles, `~` complements. |
| **LSB / MSB** | least / most significant bit; here bit 0 (LSB) is North. |
| **Hexadecimal** | base 16; one hex digit ⇔ exactly 4 bits ⇔ one cell's walls. |
| **`f"{x:X}"`** | format an int as uppercase hex; `int(s, 16)` parses it back. |
| **`enum.IntFlag`** | a stdlib enum whose members are ints and combine with bitwise operators. |
| **Invariant** | a property that must hold at all times — here, the two shared-wall equations. |

### 17.6 Files, config & errors

| Term | Definition |
| --- | --- |
| **Context manager** | the `with` protocol guaranteeing cleanup; mandatory for files here. |
| **`KEY=VALUE`** | the line format of the config; split on the **first** `=` only. |
| **Validation** | checking types, ranges *and* relationships (entry ≠ exit, in bounds). |
| **Root exception** | one project-level exception class others derive from, so callers catch one thing. |
| **Exception chaining** | `raise X(...) from err` — keeps the original cause. |
| **stderr / exit code** | where errors go, and how a shell knows you failed (non-zero). |
| **Graceful failure** | a clear message instead of a traceback; the subject's explicit pass/fail criterion. |

### 17.7 Terminal & rendering

| Term | Definition |
| --- | --- |
| **ASCII / box-drawing rendering** | drawing the maze on a `(2W+1) × (2H+1)` character grid. |
| **ANSI escape sequence** | `\033[…m` codes controlling colour, style and cursor. |
| **256-colour / true colour** | `\033[38;5;n m` and `\033[38;2;r;g;b m`. |
| **`curses`** | the stdlib terminal-UI library; `wrapper()` restores the terminal for you. |
| **`termios` / `tty` cbreak mode** | reading a single keypress without Enter — must be restored in a `finally`. |
| **MiniLibX (MLX)** | 42's C graphics library; usable only through a binding from Python. |

### 17.8 Packaging & licensing

| Term | Definition |
| --- | --- |
| **Distribution package** | the shippable archive (`mazegen-1.0.0…`), as opposed to the import package. |
| **sdist / wheel** | source archive requiring a build vs pre-built archive installed by unpacking. |
| **`py3-none-any`** | the tags of a pure-Python wheel: any Python 3, no ABI, any platform. |
| **Build backend / frontend** | `setuptools.build_meta` vs `python -m build`. |
| **`pyproject.toml`** | the single declarative metadata + build-config file (PEP 517/518/621). |
| **PEP 440** | the version-numbering scheme (`1.0.0`, `1.0.0rc1`, `1.0.0.post1`). |
| **Virtual environment** | an isolated interpreter + site-packages (`python -m venv`), where you build and test the install. |
| **Copyright vs licence** | copyright is automatic and restrictive; a licence is the permission you grant on top of it. |
| **Permissive / copyleft** | keep the notice and do what you want, vs derived works must keep the same licence. |
| **SPDX identifier** | the standard short name of a licence (`MIT`, `Apache-2.0`, `GPL-3.0-or-later`). |

### 17.9 Tooling & team

| Term | Definition |
| --- | --- |
| **flake8** | style + basic error linter (PEP 8, unused imports, bare excepts). |
| **mypy** | static type checker; `--strict` turns on every optional check at once. |
| **pdb** | the built-in debugger, behind the Makefile's `debug` rule. |
| **`.PHONY`** | Make declaration for targets that are commands, not files. |
| **pytest / unittest** | the test frameworks — not graded, but the cheapest insurance for the invariants. |
| **`maze_analyzer.py`** | the analysis script shipped with the subject: coherence, perfect vs playable, `--max-dead-ends`. |

---

## 18. Concept cheat-sheet (one-sentence definitions)

| Keyword | One sentence to say out loud |
| --- | --- |
| **MAZE = GRAPH** | Cells are vertices, missing walls are edges; every requirement of chapter IV.4 is a graph property. |
| **PERFECT = SPANNING TREE** | Connected + acyclic + exactly `V−1` passages ⇒ exactly one path between any two cells. |
| **DEAD-END = LEAF** | A degree-1 vertex; a tree always has some, which is why "perfect" and "no dead-end" are incompatible. |
| **CIRCUIT RANK** | `E − V + 1` independent loops: 0 in perfect mode, ≥ 2 for a playable board. |
| **BRAIDING** | Opening one extra wall at each dead-end; a full braid reaches zero dead-ends — the bonus. |
| **TEXTURE / BIAS** | The visual signature of an algorithm: long winding corridors (backtracker) vs short bushy ones (Prim). |
| **GROWING TREE** | One loop whose pick rule reproduces several algorithms — the cheapest route to the multi-algorithm bonus. |
| **ITERATIVE, NOT RECURSIVE** | Python stops at ~1000 frames; the backtracker carries its own stack. |
| **SEEDED RNG** | `random.Random(seed)` in the object, never the global `random.seed()`, so reuse never surprises the caller. |
| **REPRODUCIBILITY IS FRAGILE** | Set iteration order and an extra RNG call both silently break "same seed, same maze". |
| **WALL BITMASK** | N=1, E=2, S=4, W=8; 1 means closed; one cell = one hex digit; `0xF` = fully closed. |
| **COHERENCE INVARIANT** | `cell.E` closed ⇔ `east neighbour.W` closed — the first thing the analyzer checks. |
| **SINGLE SOURCE OF TRUTH** | One helper toggles both sides of a wall, so the two copies can never disagree. |
| **NO 3×3 OPEN BLOCK** | Corridors ≤ 2 cells wide; only braiding can violate it, so re-check after braiding. |
| **THE "42" IS A HOLE** | Fully closed cells remove vertices; reserve them before generating or you split the maze. |
| **BFS = SHORTEST** | On an unweighted graph the first arrival is a shortest arrival; DFS returns *a* path only. |
| **PARENT MAP** | `child → parent` plus a reversal is all a path reconstruction needs. |
| **NEIGHBOURS = PASSAGES** | One function returning only cells reachable through an open wall, shared by the solver and the validator. |
| **NEVER CRASH** | One root exception, one top-level handler, message on stderr, non-zero exit — a traceback is a failed defense. |
| **`bool("False") is True`** | Config values are strings; booleans need an explicit mapping. |
| **LIBRARY ≠ APPLICATION** | The generator computes and raises; the app reads, prints and exits. |
| **RETURN COPIES** | Handing out the internal grid lets a caller corrupt your generator; a shallow copy of a nested list is not enough. |
| **sdist vs WHEEL** | Source archive that must be built vs pre-built archive that is merely unpacked. |
| **`py3-none-any`** | Pure Python, no ABI, any platform — the tags your wheel should carry. |
| **NAME NORMALIZATION** | `-` in a distribution name becomes `_` in the wheel filename, and stops matching `mazegen-*`. |
| **NO LICENCE = NO REUSE** | Default copyright forbids everything; the licence is what makes the next project legal. |
| **PERMISSIVE vs COPYLEFT** | MIT lets the downstream game choose its own terms; GPL imposes yours on it. |

---

## 19. Worth reading — before and during

### 19.1 The books on the shelf — `42.secret.repo/_books/`

Page numbers below are **printed book pages**; add the offset to jump to the right PDF page.

#### Fluent Python — Ramalho, 2nd ed. 2022 *(PDF page = book page **+ 30**)*

| Chapter / section | Book pp. | For |
| --- | --- | --- |
| **Ch 2 — An Array of Sequences** | **21–71** | the grid: lists of lists, slicing, sequence idioms |
| ↳ **Building Lists of Lists** | **51** | the `[[0] * w] * h` aliasing trap — read this *before* writing the grid |
| ↳ **Deques and Other Queues** | **67** | `collections.deque`, the BFS queue and the iterative backtracker's stack |
| **Ch 3 — Dictionaries and Sets** | **77–113** | `visited` sets, the parent map, set operations for the frontier |
| ↳ Practical Consequences of How Sets Work | 107 | **why iterating a set breaks reproducibility** |
| **Ch 6 — Object References, Mutability, and Recycling** | **201–224** | the library boundary |
| ↳ **Copies Are Shallow by Default** | **208** | returning the grid to a caller without handing over your internals |
| ↳ Function Parameters as References / Mutable Defaults | 213–216 | the classic `def f(cells=[])` bug, in a project full of grids |
| **Ch 4 — Unicode Text Versus Bytes** | **117–158** | the output file |
| ↳ Handling Text Files / **Beware of Encoding Defaults** | 131, **134** | why `encoding="utf-8"` is not optional |
| **Ch 5 — Data Class Builders** | **163–196** | a `Config` / `Coord` that mypy likes |
| ↳ Typed Named Tuples / More About `@dataclass` | 172, 179 | `NamedTuple` for coordinates, `@dataclass` for the config |
| **Ch 8 — Type Hints in Functions** | **253–298** | the graded typing pass |
| ↳ Making Mypy More Strict / Generic Collections / Tuple Types | 257, 271, 274 | `list[list[int]]`, `tuple[int, int]`, `--strict` |
| Ch 10 — *Classic Strategy* | 342–347 | swapping generation algorithms cleanly (module 07 revisited) |
| Ch 11 — A Pythonic Object | 363–395 | `__repr__` / `__str__` / `__format__` on `MazeGenerator` |
| Ch 18 — `with`, `match`, and `else` Blocks | 657 | context managers, incl. writing your own for the terminal mode |

#### Effective Python — Slatkin, 3rd ed. 2024 *(PDF page = book page **+ 27**)*

Short items, 3–8 pages each. Two chapters carry this project: **Ch 12 — Data Structures and Algorithms** (493) and **Ch 14 — Collaboration** (575).

| Item | Book p. | For |
| --- | --- | --- |
| **103 — Prefer `deque` for Producer–Consumer Queues** | **504** | the BFS queue; why `list.pop(0)` is O(n) |
| **104 — Know How to Use `heapq` for Priority Queues** | **509** | only if you go A\* |
| **29 — Compose Classes Instead of Deeply Nesting Dictionaries, Lists, and Tuples** | **127** | the moment `dict[tuple, list[tuple]]` appears, read this |
| **51 — Prefer `dataclasses` for Defining Lightweight Classes** | **217** | the parsed config object |
| **121 — Define a Root Exception to Insulate Callers from APIs** | **595** | `MazeError` — exactly this project's error strategy |
| 32 — Prefer Raising Exceptions to Returning `None` | 142 | the library never returns `None` to signal failure |
| **80 — Take Advantage of Each Block in `try`/`except`/`else`/`finally`** | **399** | the top-level handler, and restoring the terminal |
| 82 — Consider `contextlib` and `with` for Reusable `try`/`finally` | 408 | a context manager for raw terminal mode |
| 83 / 85 — Short `try` Blocks / Beware of Catching the `Exception` Class | 412, 416 | "never crash" without swallowing your own bugs |
| **117 — Use Virtual Environments for Isolated and Reproducible Dependencies** | **576** | the venv the evaluator will ask you to build in |
| **118 — Write Docstrings for Every Function, Class, and Module** | **582** | PEP 257, and the module documentation is a deliverable |
| **119 — Use Packages to Organize Modules and Provide Stable APIs** | **588** | `__all__`, a stable public surface — the reusability chapter |
| **125 — Prefer Open Source Projects for Bundling Python Programs** | **621** | the packaging landscape around your wheel |
| 124 — Consider Static Analysis via `typing` to Obviate Bugs | 613 | what `mypy --strict` is actually buying you |
| 114 — Consider Interactive Debugging with `pdb` | 565 | the Makefile's `debug` rule |
| 92 — Profile Before Optimizing | 448 | before "optimizing" a generator that runs in 3 ms |
| 12 — Understand the Difference Between `repr` and `str` | 58 | debugging grids and masks |
| 108 / 109 — `TestCase` Subclasses / Integration Tests | 533, 541 | the invariant tests of §7 |

### 19.2 A reading order that fits the project

| When | Read |
| --- | --- |
| **Before writing anything** (~45 min) | Fluent **Ch 2, Building Lists of Lists** (51) + **Deques** (67) → Effective **Item 29** (127) → Effective **Item 121** (595) |
| **While choosing the algorithm** | Jamis Buck's series (below) — one page per algorithm, with animations |
| **While writing the solver** | Red Blob Games, *Introduction to A\**, the BFS half — then Effective **Item 103** (504) |
| **While writing the I/O** | Fluent **Ch 4** (131–134) + Effective **Items 80 / 82** (399, 408) |
| **Before packaging** | Effective **Items 117, 118, 119** (576, 582, 588) + the Packaging User Guide tutorial |
| **Before the defense** | your own README, out loud, against §16 |

### 19.3 From these notes

| Doc | Why, for this project |
| --- | --- |
| [M2_Python_4_concepts.md](M2_Python_4_concepts.md) | file I/O, `with`, streams, stderr — §9 and §10 rest entirely on it |
| [M2_Python_3_concepts.md](M2_Python_3_concepts.md) | lists / tuples / sets / dicts and their trade-offs — the grid and the BFS structures |
| [M2_Python_6_concepts.md](M2_Python_6_concepts.md) | modules vs packages, `__init__.py`, `__all__` — the vocabulary of §12–§13 |
| [M2_Python_7_concepts.md](M2_Python_7_concepts.md) | Strategy: the clean way to make the algorithm selectable (bonus) |
| [M2_Python_5_concepts.md](M2_Python_5_concepts.md) | ABC / Protocol, if you formalize an "algorithm" interface |
| [python_custom_exceptions.md](../02_Python/04_errors/python_custom_exceptions.md) | the `MazeError` hierarchy |
| [python_try_except_raise.md](../02_Python/04_errors/python_try_except_raise.md) | chaining, `else`/`finally`, what to catch and where |
| [python_collections.md](../02_Python/03_data_types/python_collections.md) | `deque`, and picking the right container |
| [python_main_guard.md](../02_Python/02_syntax_flow/python_main_guard.md) | a file that is both importable and runnable |
| [python_naming.md](../02_Python/05_style/python_naming.md) | naming a public API you are asking other people to reuse |
| [Git.md](../05_Others/Git.md) | branches and review flow — this is the first project with a teammate |

### 19.4 Mazes specifically (the best sources)

- **Jamis Buck — "Maze Generation" series**, <https://weblog.jamisbuck.org/2011/2/7/maze-generation-algorithm-recap> — one article per algorithm, each with an animated demo. The reference everyone in this project ends up reading; skim the recap, then the two or three you are considering.
- **Jamis Buck — *Mazes for Programmers*** (Pragmatic Bookshelf, 2015). The book version: generation, braiding, solving, texture comparison, rendering. Ruby, but the algorithms transfer verbatim. The single best source for "why this algorithm".
- **Walter Pullen — Think Labyrinth**, <https://www.astrolog.org/labyrnth.htm> — the classification and vocabulary reference (perfect, braid, unicursal, bias…). Useful for saying the right word at the defense.
- **Red Blob Games — *Introduction to A\**,** <https://www.redblobgames.com/pathfinding/a-star/introduction.html> — interactive BFS → Dijkstra → A\* on grids. Thirty minutes here answers "why BFS?" permanently.
- Wikipedia, [Maze generation algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm) and [Spanning tree](https://en.wikipedia.org/wiki/Spanning_tree) — enough graph theory for §2, correctly worded.

### 19.5 Official docs

- [`random`](https://docs.python.org/3/library/random.html) — read the note on reproducibility and the "not for security" warning.
- [`collections.deque`](https://docs.python.org/3/library/collections.html#collections.deque) and [`enum.IntFlag`](https://docs.python.org/3/library/enum.html#enum.IntFlag).
- [Curses Programming HOWTO](https://docs.python.org/3/howto/curses.html) — if you go for real keypresses.
- [Python Packaging User Guide — *Packaging Python Projects*](https://packaging.python.org/en/latest/tutorials/packaging-projects/) — the tutorial that produces exactly the two files this subject asks for.
- [PEP 621](https://peps.python.org/pep-0621/) (the `[project]` table), [PEP 517](https://peps.python.org/pep-0517/)/[518](https://peps.python.org/pep-0518/) (build backends), [PEP 440](https://peps.python.org/pep-0440/) (versions), [PEP 427](https://peps.python.org/pep-0427/) (the wheel format).
- [PEP 257](https://peps.python.org/pep-0257/) — docstring conventions, since they are graded.
- [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) — the colour table you will copy from once and keep.
- <https://choosealicense.com/> — and its [appendix](https://choosealicense.com/appendix/) comparing every clause side by side.
