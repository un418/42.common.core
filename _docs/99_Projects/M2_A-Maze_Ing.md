- https://choosealicense.com/
- https://www.youtube.com/watch?v=WRZINg_KPWA
- https://www.youtube.com/watch?v=TnMn02CwirY
  * https://www.geeksforgeeks.org/python/python-dsa-libraries/
	  * Lib for graph
- https://en.wikipedia.org/wiki/Maze_generation_algorithm

# ToDo

## Class reorganization

### 1. State ownership (do this first, everything else depends on it)

- [ ] `Logo`: define what it owns in its own `__init__` (it currently reads `self.row_max` / `self.col_max`, which it never declares)
- [ ] `MazeRender`: same check (it reads `self.matrix`, `self.row_max`), then decide whether it holds a maze or receives one per call
- [ ] Rule to apply everywhere: if a method needs an attribute the class never declares, it is not a class yet, just orphan functions

### 2. Dependency direction between Maze and Logo

- [ ] Decide whether `Maze` should know the concept of "logo", or only the concept of "constrained cells"
- [ ] Trade-off to weigh: keeping `Maze` generic allows adding other constraint shapes later without touching it
- [ ] Keep `Logo` as a top-level class, not an inner class (a nested class in Python gets no privileged access to the outer instance, only a longer name and a harder import)

### 3. Question the existing types

- [ ] `MazeCell`: empty base class used to mean "not a cell yet", check whether that placeholder is needed at all, and whether inheritance is the right tool to express an absent value
- [ ] `Wallset`: constants only, no behaviour, look for a place closer to the concept those values describe

### 4. Naming consistency

- [ ] One single name for the grid holder (`Matrix` in `__main__`, `Maze` in the class definition)
- [ ] One convention for dimensions (`width` / `height` vs `row_max` / `col_max`)
- [ ] One convention for coordinate order (`(x, y)` vs `(row, col)`, currently mixed between `Cell`, `pregen_maze` and the logo coords)

### 5. Module split (last step, once responsibilities stop moving)

- [ ] One module per concept (maze, cell, logo, render) only when the boundaries are settled
- [ ] Clean up the drafts (`_maze_gen copy.py`, `wip.py`) once the reorganization is done
