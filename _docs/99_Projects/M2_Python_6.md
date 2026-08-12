
# Python Module

- https://www.geeksforgeeks.org/python/create-and-import-modules-in-python/
- https://www.geeksforgeeks.org/python/import-module-python/
# Python Package

- https://www.geeksforgeeks.org/python/python-packages/
- https://www.geeksforgeeks.org/python/what-is-__init__-py-file-in-python/
- https://packaging.python.org/en/latest/tutorials/packaging-projects/
# Relative imports

- https://google.github.io/styleguide/pyguide.html#22-imports
	- Anti Pattern to use relative import

- https://www.geeksforgeeks.org/python/relative-import-in-python/
		- Need to be bind to a package firslty to be resolved.

- https://gist.github.com/justinchuby/9085242a53158f2fd7ae7aa650e55ee3
	- import best practice
	
- https://www.geeksforgeeks.org/python/absolute-and-relative-imports-in-python/
- https://realpython.com/ref/best-practices/imports/
## Q&A from subject:

> When should an alchemist use absolute pathways vs relative pathways?

### Best practice :
> Do not use relative names in imports. Even if the module is in the same package, use the full package name. 
> This helps prevent unintentionally importing a package twice.

-- _from Google style guide_
### In practice: They can be use within package

In Python, ****relative imports**** allow us to import modules in **relation to the current module's location within a package structure**. 
This means instead of using full paths, we can import modules using `.` (current directory) or `..` (parent directory), making the code more concise and easier to maintain. 
Relative imports are especially useful in large projects with complex directory structures, where we want to keep module imports flexible and avoid hard-coding long paths. 
They help ensure that the code remains portable, as the module paths **are relative to the package**, not absolute locations on the filesystem.

Relative imports use dots (`.`) to indicate the current and parent directories:
- **`**.**`** refers to the current directory.
- **`**. .**`** refers to the parent directory.
- **`**. . .**`** refers to the grandparent directory, and so on.

## python -m

> `python -m pkg.mod` = **find the module through the import system (`sys.path`), then run it as `__main__`** — whereas `python path/file.py` just opens a file at that path.

- https://www.reddit.com/r/learnpython/comments/138brzp/a_package_import_works_when_running_script/

## The two modes

| | `python alchemy/potions.py` | `python -m alchemy.potions` |
|---|---|---|
| Argument | a **file path** | a **module name** (dotted, no `.py`) |
| Resolution | opens the file as-is | looks it up in `sys.path`, like an `import` |
| `sys.path[0]` | the **script's** folder (`alchemy/`) | the **cwd** (where you launch from) |
| `__name__` | `"__main__"` | `"__main__"` |
| `__package__` | `""` (no package) | `"alchemy"` |
| `alchemy/__init__.py` | **not executed** | **executed** (parent imported first) |

Relative imports resolve against `__package__` → `""` means `.` has no starting point.

Two conditions are needed, not one:
- the **dotted name** gives the package context — `-m potions` from inside `alchemy/` still fails, no parent;
- the **cwd** must contain the package, since it becomes `sys.path[0]` — `-m alchemy.potions` from `/tmp` → `ModuleNotFoundError`.

`python -m pkg` (a package, not a module) runs `pkg/__main__.py` — that's how `python -m venv`, `python -m http.server` and `python -m pip` work. 
Using `-m` also guarantees *this* interpreter acts, not the first one in `$PATH`.

# Circular import

- https://www.geeksforgeeks.org/python/python-circular-imports/
- 