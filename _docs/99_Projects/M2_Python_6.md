
# Relative imports

- https://google.github.io/styleguide/pyguide.html#22-imports

Relative import:
- https://www.geeksforgeeks.org/python/relative-import-in-python/
		- Need to be bind to a package firslty to be resolved.

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

