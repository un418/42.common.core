# `mazegen` package ([#17](https://github.com/un418/a_maze_ing/issues/17) · [PR #34](https://github.com/un418/a_maze_ing/pull/34))

Approach: `mazegen/` package with generator + solver, one `MazeGenerator` facade for external users. The app keeps using the internal bricks (animation unchanged).

## 1. Move folders into `mazegen/` (pure refactor)
- [x] `mazegen/` with `core`, generator and solver inside
- [x] Internal imports work in the repo **and** once installed
- [x] App imports fixed (`a_maze_ing.py`, `maze_app`, `maze_render`, `output_file`)
- [x] Check: `make run`, `make lint`, `make test` same as before
- [x] Commit

## 2. `MazeGenerator` facade
- [x] Own module in `mazegen/`, exposed by `mazegen/__init__.py`
- [x] Takes the parameters (size, seed, entry/exit, perfect or not)
- [x] Gives access to the structure and to a solution
- [x] Same step order as the app
- [x] Check: same config + seed → same maze via the app and via the facade
- [x] Commit

## 3. Tests (pytest)
- [x] pytest in the `dev` dependency group + config in `pyproject.toml`, `.pytest_cache` ignored
- [x] `tests/test_amazing.py`: perfect + imperfect configs
	- [x] App vs facade: same walls and same solution path
	- [x] `check_verdict`: expected `maze_analyzer.py` verdict, docstring says what is (not) tested
- [x] Quiet output: app captured, analyzer reports shown with `poetry run pytest -rP`
- [x] `make test` runs pytest (+ `README.md` line)
- [x] `make test-one` renamed to `make analyzer`
- [x] Commits
	- [x] `build: add pytest as a dev dependency` (`pyproject.toml`, `poetry.lock`, `.gitignore`)
	- [x] `test: check the app against MazeGenerator and the maze analyzer` (`tests/test_amazing.py`)
	- [x] `build: run pytest in make test and rename test-one to analyzer` (`Makefile`, `README.md`)

## 4. Module documentation
- [ ] Facade docstrings (PEP 257)
- [ ] Short doc: basic example, parameters, structure + solution access
	- [ ] Note "no input validation yet" (domain guards come in a later PR)
- [ ] Doc shipped **inside** the package
- [ ] Same doc in the main `README.md` + "what part of your code is reusable, and how"

## 5. `pyproject.toml`
- [x] `packages` → `mazegen` only
- [ ] Runtime deps: only what the shipped code imports
- [ ] `description` filled in
- [ ] Check: no dev tools in the wheel `METADATA`

## 6. Build and test like the evaluator
- [ ] `make build`
- [ ] Fresh venv, **outside the repo**: install build tools, rebuild from sources, install the wheel, run the doc example
- [ ] Check: no import error

## 7. Ship the wheel
- [ ] `mazegen-*.whl` at the repo root, committed (`.gitignore` excludes it today)
- [x] Missing newline at the end of `.gitignore`

Related: [#13](https://github.com/un418/a_maze_ing/issues/13) (`LICENSE.md`)
