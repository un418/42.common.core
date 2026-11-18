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
- [ ] Makefile
	- [x] build - create package
	- [x] clean - remove build atrifacts
	- [ ] install - create venv
	- [ ] run - inside the venv
	- [ ] fclean - remove venv ?? 
	- [ ] lint - inside the venv
	    
	- [ ] `mazegen` package
		- [ ] Package scope: 
		      - the subject requires "access at least a solution", but the solver lives in `maze_solver/`. 
		        - Need to see how to deal with that... Intergrate `maze_solver` in the package or intergrate the solving algorithm in the `maze_generator` ?
			    - Same for core package -> Maybe put everything inside `maze_generator` package to do it simple
- [ ] Fix `config_importer` ImportError: `__init__.py` + `test_apinho-a.py` still use the old names renamed in `390573c`


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
| **Execution**       | `poetry run <cmd>`                                         | Runs a command inside the venv without activating it                        |
| **Venv management** | `poetry env info` / `poetry env use` / `poetry env remove` | Shows where the venv is, picks the Python version, deletes it               |
| **Build**           | `poetry build`                                             | Produces the `.whl` and the `.tar.gz`                                       |
| **Publishing**      | `poetry publish`                                           | Uploads the package to PyPI                                                 |

- **Venv location**: global cache by default (`~/Library/Caches/pypoetry/virtualenvs/`), check with `poetry env info --path`. `virtualenvs.in-project` → `.venv/` at the root
- **Build output**: `poetry build -o .` writes the artifacts at the root instead of `dist/`. 
	  ⚠️ never combine with `--clean` (it would empty the root)
- **No clean command**: delete the artifacts manually (Makefile `clean` rule)
- **`poetry.lock`** is committed: same versions for both of us
- **Dependency groups**: `mypy` / `flake8` are dev tools, not runtime deps
