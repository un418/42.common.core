- https://choosealicense.com/
- https://www.youtube.com/watch?v=WRZINg_KPWA
- https://www.youtube.com/watch?v=TnMn02CwirY
  * https://www.geeksforgeeks.org/python/python-dsa-libraries/
	  * Lib for graph
- https://en.wikipedia.org/wiki/Maze_generation_algorithm
- https://en.wikipedia.org/wiki/Maze-solving_algorithm
- https://medium.com/@nacerkroudir/randomized-depth-first-search-algorithm-for-maze-generation-fb2d83702742
- https://github.com/NacerKROUDIR/MazeGeneration/blob/main/Maze_Generator.py
- https://professor-l.github.io/mazes/

* https://python-poetry.org/docs/managing-dependencies/#group-include-pep735

# ToDo

- [x] Class Reorganization
	- [x] Module split
		- [x] One module per concept (maze, cell, logo, render) only when the boundaries are settled
		- [x] Clean up the drafts (`_maze_gen copy.py`, `wip.py`) once the reorganization is done
		- [x] Set up import logic to be able to test from root folder
- [x] PerfectMazeGenerator via DFS
- [x] Animate Genration Rendering
	- [x] Add Cursor to see backtracking
- [x] Add Logo and make DFSGenerator works with it
	- [ ]  ( Bonus ) Add Logo Scaling Logic
- [x] Resolution Algorithm
	- [x] Dead end
- [ ] Animate Braider ([PR #20](https://github.com/un418/a_maze_ing/pull/20))
	- [ ] `gen_braiding` as a generator, same pattern as `MazeGenDFS.gen()`
	- [ ] Decide what to show: dead ends checked / every attempt / kept openings only
	- [ ] Hook it into the render loop of the `PERFECT=False` branch
	- Test: `poetry run python3 test_apinho-a.py testcfg.txt` (`PERFECT=False`)
- [x] Makefile ([PR #19](https://github.com/un418/a_maze_ing/pull/19), in review)
	- [x] build - create package
	- [x] install
	- [x] run / debug - `config.txt` by default, `CONFIG=<file>` to override
	- [x] clean - caches + generated mazes (`*maze.txt`)
	- [x] fclean - clean + wheel
	- [x] lint / lint-strict
	- [ ] test - fix display issues
- [ ] `mazegen` package ([#17](https://github.com/un418/a_maze_ing/issues/17) · [PR #34](https://github.com/un418/a_maze_ing/pull/34))
	- [ ] PR #34 ready for review, merge after [PR #37](https://github.com/un418/a_maze_ing/pull/37) (base → `master`)
	- [ ] School + teammate machines: `poetry --version` (≥ 2.3), `pipx --version`, `python3 -m pip --version`, `python3 -m venv /tmp/t && echo venv ok`
	- [ ] [#41](https://github.com/un418/a_maze_ing/issues/41) (last step), not written in the ticket: after the wheel commit, `make build` again → `git status` shows no change on it
	- Later idea: improve the tests (every check visible inside the test function?)
	- `MazeGenerator` = Facade: [Refactoring.guru – Facade](https://refactoring.guru/design-patterns/facade/python/example) · [TutorialsPoint – Facade](https://tutorialspoint.com/python_design_patterns/python_design_patterns_facade.htm)
	- [x] Empty commit `06a2ac1` ([PR #34](https://github.com/un418/a_maze_ing/pull/34)): squash at merge, or drop with a rebase + `push --force-with-lease`
	- [x] Package scope: `mazegen/` = `core` + `generator` + `solver` (solver shipped for "access at least a solution"), app stays outside

- [ ] Domain input guards in `mazegen` (separate PR, after [PR #34](https://github.com/un418/a_maze_ing/pull/34)): today only pydantic checks them
	- [ ] Move the domain rules (entry ≠ exit, inside the grid, size > 0) from `config_parser/_validator.py` into `mazegen`, raise `ValueError`
	- [ ] Pydantic and `MazeGenerator` both call them (one source of truth)
	- [ ] Check: same app error on a bad config, facade fails loudly on bad input

- [ ] Logo (separate PR, after [PR #34](https://github.com/un418/a_maze_ing/pull/34))
	- [ ] ⚠️ [#28](https://github.com/un418/a_maze_ing/issues/28) Maze too small for "42": subject allows omitting the pattern + asks for a console error message. From reading the code, the app exits instead → test with a 5x5 config
	- [ ] Simplify the sequence `MazeGenDFS` → `import_logoset` → `gen()` (see `TODO` in `_maze_generator.py`)

- [ ] `make test`: analyzer exits 0 on a bad verdict (never fails) + solution path not checked [#12](https://github.com/un418/a_maze_ing/issues/12)
- [ ] `make lint` fails on the code (flake8 + 16 mypy errors): clean it before the defense
- [x] Decide whether `flake8` and `mypy` go in the `dev` dependency group
- [ ] Docstrings: do another full pass (`Args` vs signatures, `Attributes`, `Returns`)

- [x] Fix `config_importer` ImportError: `__init__.py` + `test_apinho-a.py` still use the old names renamed in `390573c` → fixed in [PR #18](https://github.com/un418/a_maze_ing/pull/18)
- [ ] Error handling ([PR #21](https://github.com/un418/a_maze_ing/pull/21))
	- [ ] Output file block: `OSError` not caught + exit code
	- [ ] `NotSolvedError` never raised (unsolved → `[]` → wrong error)
	- [ ] Replace `except Exception` placeholders
	- [ ] Docstrings: `config_parser` Raises (`FileNotFoundError`, `UnicodeDecodeError` is a `ValueError`), `OutputFile` Args

- [ ] README: explain the package split (domain packages vs `maze_app` orchestration), ref: [Fowler, PresentationDomainDataLayering](https://martinfowler.com/bliki/PresentationDomainDataLayering.html)
	- `maze_app` = Service Layer: [Architect Handbook – Service Layer](https://herrera-ignacio.github.io/architect-handbook/legacy/design-patterns/domain-logic/service-layer)

## Optional improvements (later)

- [ ] BFS: bounds check happens after the `grid[ny][nx]` access
- [ ] BFS: `list.pop(0)` is O(n) → look for a proper queue structure
- [ ] BFS: `_was_seen` also adds to `seen`, the name hides it
- [ ] `a_maze_ing.py`: `ValidationError` redundant next to `ValueError` (pydantic's one subclasses `ValueError`)
- [ ] Docstrings style: summary on the same line as `"""` (Google / rest of repo), André's new ones in `maze_app`, `OutputFile` start on the next line
- [ ] Braider: `_3x3_scan` fail fast (stop at the first closed wall), Andre agreed on [PR #20](https://github.com/un418/a_maze_ing/pull/20)
- [ ] (Very optional) Braider: sides always tried N→E→S→W, so ~3/4 of openings are N/S → pick at random, from the same seeded `Random` as the DFS so `SEED` stays reproducible

## Logo

```
4     y 2 2 2
4     y - - 2
4 4 4 x 2 2 2
    4 x 2 - -
    4 x 2 2 2
```

## Poetry

| Role                | Command                                                    | What it does                                                                |
| ------------------- | ---------------------------------------------------------- | --------------------------------------------------------------------------- |
| **Dependencies**    | `poetry add` / `poetry lock`                               | Adds deps to `pyproject.toml`, pins exact versions in `poetry.lock`         |
| **Venv**            | `poetry install`                                           | **Creates the venv automatically** if missing, then installs the deps in it |
| **Venv (deps only)** | `poetry install --no-root`                                | Same, but without installing the project itself                             |
| **Execution**       | `poetry run <cmd>`                                         | Runs a command inside the venv without activating it                        |
| **Activation**      | `eval $(poetry env activate)`                              | Activates the venv in the shell (`poetry shell` is gone in Poetry 2.x)      |
| **Venv management** | `poetry env info` / `poetry env use` / `poetry env remove` | Shows where the venv is, picks the Python version, deletes it               |
| **Dev deps**        | `poetry add --group dev <pkg>`                             | Dev-only dependency, not shipped with the package                           |
| **Inspect**         | `poetry remove <pkg>` / `poetry show --tree` / `poetry check` | Removes a dep / shows the dependency tree / validates `pyproject.toml`   |
| **Version**         | `poetry version patch\|minor\|major`                       | Bumps the version, so the `mazegen-X.Y.Z-...` filename                      |
| **Build**           | `poetry build`                                             | Produces the `.whl` and the `.tar.gz`                                       |
| **Build (wheel)**   | `poetry build -f wheel -o .`                               | Only the `.whl`, at the root (Makefile `build` rule)                        |
| **Publishing**      | `poetry publish`                                           | Uploads the package to PyPI                                                 |

- **`pyproject.toml` blocks**: `[project]` = package info + runtime deps · `[build-system]` = who builds it (`poetry-core`) · `[tool.poetry] packages` = folders shipped in the package (`mazegen`)
- **Defense**: rebuild in a fresh venv, maybe without Poetry → `pip install build` then `python -m build` works thanks to `[build-system]`, test it once before

- **Venv location**: global cache by default (`~/Library/Caches/pypoetry/virtualenvs/`), check with `poetry env info --path`. `virtualenvs.in-project` → `.venv/` at the root
- **Build output**: `poetry build -o .` writes the artifacts at the root instead of `dist/`. 
	  ⚠️ never combine with `--clean` (it would empty the root)
- **No clean command**: delete the artifacts manually (Makefile `clean` rule)
- **`poetry.lock`** is committed: same versions for both of us
- **Dependency groups**: `mypy` / `flake8` are dev tools, not runtime deps

## Dependency versions
- Latest version of a package for Python 3.10:
  `pip index versions <package> --python-version 3.10 | head -1`
- It gives the **newest** one, not the minimum you need
- Full method: [[python_dependency_versions]]

**Why these versions?** (eval answer)
- Each bound is the **oldest version that works**, and we tested it: Python 3.10 (Ubuntu 22.04 on 42 computers), `poetry-core` 2.0 (first one to read our `pyproject.toml`)
- Poetry 2.3+: first one to handle our `dev` / `app` groups. Older ones fail at `poetry install`, and the project says so clearly. `<3.0.0` protects from the next major version
- `mypy`, `pydantic`, etc.: pinned in `poetry.lock`, everyone installs the same ones

## Test the wheel by hand
Copy-paste from the repo root:
```bash
# Build the wheel
make build
# Create a temp folder outside the repo, and bring the wheel into it
TMP=$(mktemp -d)
cp mazegen-*.whl "$TMP"
# Create an empty venv and activate it
cd "$TMP"
python3 -m venv venv
source venv/bin/activate
# Should be empty
pip list
# Install the wheel
pip install mazegen-*.whl
# Should have mazegen now
pip list
# Check "Location" must be in venv/
pip show mazegen
# Use it: a solution (list of cells) must be printed
python -c 'from mazegen import MazeGenerator; print(MazeGenerator(20, 15, entry=(0, 0), exit=(19, 14), perfect=True, seed=42).solution)'
# Leave the venv and go back to the repo
deactivate
cd -
```
