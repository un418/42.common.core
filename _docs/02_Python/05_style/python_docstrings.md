# Docstrings — memo

> Style chosen: **Google**. 42 Python subjects ask for docstrings on functions and classes, following PEP 257 (Google or NumPy style). See also [python_idioms.md](python_idioms.md).

## What needs a docstring

- **Modules**: every file starts with a docstring (contents + usage) → [PEP 257 · What is a Docstring?](https://peps.python.org/pep-0257/#what-is-a-docstring) · [Google 3.8.2 Modules](https://google.github.io/styleguide/pyguide.html#s3.8.2-comments-in-modules)
- **Functions**: mandatory if public API, nontrivial size or non-obvious logic → [Google 3.8.3 Functions and Methods](https://google.github.io/styleguide/pyguide.html#s3.8.3-functions-and-methods)
- **Classes**: describe the class + list public `Attributes:` → [Google 3.8.4 Classes](https://google.github.io/styleguide/pyguide.html#s3.8.4-comments-in-classes)
- **Test modules**: module docstring optional → [Google 3.8.2.1](https://google.github.io/styleguide/pyguide.html#s3.8.2.1-test-modules)

## Format (Google)

- Sections `Args:`, `Returns:` (or `Yields:`), `Raises:` → [Google 3.8.3](https://google.github.io/styleguide/pyguide.html#s3.8.3-functions-and-methods)
- One summary line, blank line, then details → [PEP 257 · Multi-line Docstrings](https://peps.python.org/pep-0257/#multi-line-docstrings)
- Keep docstrings in sync when a signature changes

## Main script

- Logic in a `main()` function, called behind `if __name__ == '__main__'` (importable by pydoc and tests) → [Google 3.17 Main](https://google.github.io/styleguide/pyguide.html#s3.17-main)
- `main()` is a function → it needs a docstring like any other
- The script's module docstring should work as its **usage message** → [PEP 257 · Multi-line Docstrings](https://peps.python.org/pep-0257/#multi-line-docstrings)
