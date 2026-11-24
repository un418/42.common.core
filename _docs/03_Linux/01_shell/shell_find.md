# find
## -exec : `\;` vs `+`

Both end the `-exec` action. The difference is how many times the command runs.

```bash
find . -name __pycache__ -exec rm -rf {} \;   # one rm per result
find . -name __pycache__ -exec rm -rf {} +    # one rm for all results
```

- **`\;`** : runs the command once per result
	- `rm -rf ./core/__pycache__`, then `rm -rf ./maze_solver/__pycache__`, ...
	- `;` is escaped, otherwise the shell eats it as its own command separator
	- `{}` can go anywhere in the command
- **`+`** : groups all results into a single call
	- `rm -rf ./core/__pycache__ ./maze_solver/__pycache__ ...`
	- faster: one process instead of one per result
	- `{}` must be last, right before `+`
- **Which one** : `+` when the command accepts several files (`rm`, `cat`...), `\;` when it takes one file at a time

## OR and `( .. )`

```bash
find . -type d \( -name __pycache__ -o -name .mypy_cache \) -print
```

- **AND** : implicit between two tests (`-type d -name x` = both must match)
- **OR** : `-o`
- **NOT** : `!` or `-not`
- **Precedence** : AND binds tighter than OR, like `*` before `+`
- **Parentheses** : group the tests, escaped as `\(` `\)` so the shell leaves them to `find`
	- spaces around them are required
- **Trap without parentheses** : the action sticks to the last test only
	- `find . -name a -o -name b -print` prints only `b`
	- read as `-name a -o (-name b -print)`

## Links
- https://askubuntu.com/questions/339015/what-does-mean-in-the-find-command
- https://stackoverflow.com/questions/71562728/find-with-shell-with-different-and-or-conditions
- https://stackoverflow.com/questions/10437012/find-command-and-inverse-regex : inverse regex
- https://man7.org/linux/man-pages/man1/find.1.html : man page, search `printf` for custom output
- [[shell_101]]
