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
- [ ] `mazegen` package → [[M2_A-Maze_Ing_mazegen]]
	- `MazeGenerator` = Facade: [Refactoring.guru – Facade](https://refactoring.guru/design-patterns/facade/python/example) · [TutorialsPoint – Facade](https://tutorialspoint.com/python_design_patterns/python_design_patterns_facade.htm)
	- [ ] Empty commit `06a2ac1` ([PR #34](https://github.com/un418/a_maze_ing/pull/34)): squash at merge, or drop with a rebase + `push --force-with-lease`
	- [x] Package scope: `mazegen/` = `core` + `generator` + `solver` (solver shipped for "access at least a solution"), app stays outside

- [ ] Domain input guards in `mazegen` (separate PR, after [PR #34](https://github.com/un418/a_maze_ing/pull/34)): today only pydantic checks them
	- [ ] Move the domain rules (entry ≠ exit, inside the grid, size > 0) from `config_parser/_validator.py` into `mazegen`, raise `ValueError`
	- [ ] Pydantic and `MazeGenerator` both call them (one source of truth)
	- [ ] Check: same app error on a bad config, facade fails loudly on bad input

- [ ] `make test`: analyzer exits 0 on a bad verdict (never fails) + solution path not checked [#12](https://github.com/un418/a_maze_ing/issues/12)
- [ ] `make lint` fails on the code (flake8 + 16 mypy errors): clean it before the defense

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

- **`pyproject.toml` blocks**: `[project]` = package info + runtime deps · `[build-system]` = who builds it (`poetry-core`) · `[tool.poetry] packages` = folders shipped in the package (`core`, `maze_generator`)
- **Defense**: rebuild in a fresh venv, maybe without Poetry → `pip install build` then `python -m build` works thanks to `[build-system]`, test it once before

- **Venv location**: global cache by default (`~/Library/Caches/pypoetry/virtualenvs/`), check with `poetry env info --path`. `virtualenvs.in-project` → `.venv/` at the root
- **Build output**: `poetry build -o .` writes the artifacts at the root instead of `dist/`. 
	  ⚠️ never combine with `--clean` (it would empty the root)
- **No clean command**: delete the artifacts manually (Makefile `clean` rule)
- **`poetry.lock`** is committed: same versions for both of us
- **Dependency groups**: `mypy` / `flake8` are dev tools, not runtime deps
