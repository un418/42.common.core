
# Python dev environment

Tooling setup for the 42 Python modules. 
The subject enforces **flake8** and **mypy**, so most of this revolves around running those two before every commit.

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

