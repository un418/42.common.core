## PDB - Python Debugger

> [!TIP]
> `python -m pdb script.py args` → stops **before the first line**, prompt `(Pdb)`
> In a_maze_ing: `make debug` (= `poetry run python3 -m pdb a_maze_ing.py config.txt`)
> Alternative: put `breakpoint()` in the code, then `make run` → stops right there.

## Move through the code

| Command      | Effect                                                 |
| ------------ | ------------------------------------------------------ |
| `n` next     | Run the current line, **without** entering functions  |
| `s` step     | Run the current line, **entering** the called function |
| `c` continue | Run until the next breakpoint (or the end)             |
| `r` return   | Run until the current function returns                 |
| `unt N`      | Run until line N (handy to get out of a loop)          |
| `Enter`      | Repeat the last command                                |

## Breakpoints

| Command           | Effect                                     |
| ----------------- | ------------------------------------------ |
| `b 42`            | Breakpoint at line 42 of the current file  |
| `b file.py:42`    | Breakpoint in another file                 |
| `b my_function`   | Breakpoint at the function's entry         |
| `b 42, x > 10`    | Conditional breakpoint                     |
| `b`               | List breakpoints                           |
| `cl 1` / `cl`     | Delete breakpoint #1 / all of them         |

## Inspect

| Command         | Effect                                                  |
| --------------- | ------------------------------------------------------- |
| `p expr`        | Print a value                                           |
| `pp expr`       | Pretty-print (dicts, lists)                             |
| `l` / `ll`      | Code around the current line / whole current function   |
| `w` where       | Call stack: how did I get here                          |
| `u` / `d`       | Go up / down the stack (see the caller's variables)     |
| `a`             | Arguments of the current function                       |
| `display expr`  | Re-print `expr` at each stop when it changes            |
| `interact`      | Python REPL with local variables (`Ctrl+D` to go back)  |

## Quit / restart

| Command   | Effect                                     |
| --------- | ------------------------------------------ |
| `restart` | Restart the program, keeping breakpoints   |
| `q`       | Quit                                       |
| `h cmd`   | Help on a command                          |

## Example session

```
make debug
(Pdb) b mazegen/generator.py:25   # breakpoint where I want to look
(Pdb) c                           # go to the breakpoint
(Pdb) p width, height             # inspect
(Pdb) n                           # line by line
(Pdb) s                           # step into a suspicious call
(Pdb) w                           # where am I?
(Pdb) q
```

> [!WARNING]
> - Variable named like a command (`n`, `c`, `l`…) → prefix with `!` (`!n`) or use `p n`
> - Crash under pdb → automatic **post-mortem** on the faulty line: use `p`, `w`, `u` to understand it

Related: [[c_lang_debug]] (GDB equivalent)
