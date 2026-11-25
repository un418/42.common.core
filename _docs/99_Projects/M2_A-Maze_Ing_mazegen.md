# `mazegen` package ([#17](https://github.com/un418/a_maze_ing/issues/17) · [PR #34](https://github.com/un418/a_maze_ing/pull/34))

Approach: `mazegen/` package with generator + solver, one `MazeGenerator` facade for external users. The app keeps using the internal bricks (animation unchanged).

## 1. Move folders into `mazegen/` (pure refactor)
- [x] `mazegen/` with `core`, generator and solver inside
- [x] Internal imports work in the repo **and** once installed
- [x] App imports fixed (`a_maze_ing.py`, `maze_app`, `maze_render`, `output_file`)
- [x] Check: `make run`, `make lint`, `make test` same as before
- [x] Commit

## 2. `MazeGenerator` facade
- [ ] Own module in `mazegen/`, exposed by `mazegen/__init__.py`
- [ ] Takes the parameters (size, seed, entry/exit, perfect or not)
- [ ] Gives access to the structure and to a solution
- [ ] Same step order as the app
- [ ] Check: same config + seed → same maze via the app and via the facade
- [ ] Commit

## 3. Module documentation
- [ ] Facade docstrings (PEP 257)
- [ ] Short doc: basic example, parameters, structure + solution access
- [ ] Doc shipped **inside** the package
- [ ] Same doc in the main `README.md` + "what part of your code is reusable, and how"

## 4. `pyproject.toml`
- [x] `packages` → `mazegen` only
- [ ] Runtime deps: only what the shipped code imports
- [ ] `description` filled in
- [ ] Check: no dev tools in the wheel `METADATA`

## 5. Build and test like the evaluator
- [ ] `make build`
- [ ] Fresh venv, **outside the repo**: install build tools, rebuild from sources, install the wheel, run the doc example
- [ ] Check: no import error

## 6. Ship the wheel
- [ ] `mazegen-*.whl` at the repo root, committed (`.gitignore` excludes it today)
- [ ] Missing newline at the end of `.gitignore`

Related: [#13](https://github.com/un418/a_maze_ing/issues/13) (`LICENSE.md`)
