
# Python dev environment

Tooling setup for the 42 Python modules. 
The subject enforces **flake8** and **mypy**, so most of this revolves around running those two before every commit.

# Tool family & real-world equivalents

Both are **static analysis** tools: they inspect code without running it.

| Role                | At 42  | In industry                              |
| ------------------- | ------ | ---------------------------------------- |
| Linter (style/bugs) | flake8 | **Ruff** (also replaces Black as formatter) |
| Static type checker | mypy   | **mypy** or **Pyright** (Pylance's engine)  |

In a real team these run automatically via **pre-commit** hooks and in **CI**
on every PR. Same concepts as here, faster tools.

# Shell aliases (zsh)

```zsh
# Base
alias py='python3'

# Lint flake8 (required by the subject). Default max-line-length is 79
alias flk='flake8'

# Type checking (mandatory for ex7, recommended everywhere)
alias mpy='mypy --strict'

# Run the test helper shipped with the subject
alias runtest='python3 main.py'
```

Combined check on a single file (flake8 + mypy in one shot), the main
time saver before committing:

```zsh
# pycheck ft_plot_area.py  ->  flake8 + mypy at once
pycheck() {
  echo "── flake8 ──"; flake8 "$@";
  echo "── mypy ──";   mypy --strict "$@";
}
```

Virtual environment (isolates flake8/mypy instead of polluting the system):

```zsh
alias venv='python3 -m venv .venv && source .venv/bin/activate'
alias act='source .venv/bin/activate'
```

# Shell completion (flake8 / mypy)

flake8 and mypy ship **no argument completion**: no `completion` subcommand, no
`PYTHON_ARGCOMPLETE_OK` marker in their `~/.local/bin` scripts. `argcomplete` only
works on tools that opt in, so even a global activation gives nothing for these two.
`pip completion --zsh` completes `pip` itself only, never the packages it installs.

Options, lightest first:

1. **Do nothing** (recommended): both are used with few flags, TAB just falls back to
   file completion.
2. **Hand-written completion**: a `_mypy` / `_flake8` file in `$fpath`. Works, but the
   option list is maintained by hand; nothing official exists for these two.
3. **Global argcomplete**: only useful for other tools that carry the marker, useless
   for mypy/flake8.

# VS Code

## Extensions

| Extension         | ID                            | Purpose                                 |
| ----------------- | ----------------------------- | --------------------------------------- |
| Python            | `ms-python.python`            | Base: debug, run, interpreter selection |
| Pylance           | `ms-python.vscode-pylance`    | IntelliSense / autocompletion           |
| Flake8            | `ms-python.flake8`            | Inline lint, matches the subject        |
| Mypy Type Checker | `ms-python.mypy-type-checker` | Typing errors underlined in the editor  |

## Settings (`settings.json`)

```jsonc
{
  "editor.rulers": [79],               // visible flake8 limit
  "files.trimTrailingWhitespace": true,
  "files.insertFinalNewline": true,    // avoids flake8 W292 / W391
  "editor.renderWhitespace": "trailing",
  "flake8.args": ["--max-line-length=79"],
  "mypy-type-checker.args": ["--strict"]
}
```

The ruler at 79 plus trim/final-newline alone remove the most common flake8
errors.

## Keyboard shortcuts

Native ones are enough to start with:

- `Ctrl+Shift+P` -> command palette ("Python: Select Interpreter")
- `Ctrl+`` ` -> integrated terminal
- `F8` / `Shift+F8` -> navigate between reported problems (lint/typing)

