## GDB - Debugger


> [!WARNING] 
> Don't forget to compile on debug mode
>  `cc -g ...` or `gcc -g ...` it allows to get the source code and the compiled code in the same file.
>  Without it gdb will not be able to open the file.


`gdb -tui` :  open gdb in terminal ui mode

# printf

## Basic Usage

```c
#include <stdio.h>
int main() {
	int a = 1245;
    printf("debug: a=%d",a);
    return 0;
}
```
## The Ultimate `printf` Format Specifier Table

| Category               | C Type               | Specifier            | Description / Usage                                 |
| ---------------------- | -------------------- | -------------------- | --------------------------------------------------- |
| **Character**          | `char`               | **`%c`**             | Single character                                    |
|                        | `char *`             | **`%s`**             | String of characters                                |
| **Integer (Signed)**   | `short`              | **`%hd`**            | Short integer                                       |
|                        | `int`                | **`%d`** or **`%i`** | Standard integer (most common)                      |
|                        | `long`               | **`%ld`**            | Long integer                                        |
|                        | `long long`          | **`%lld`**           | Very long integer (64-bit)                          |
| **Integer (Unsigned)** | `unsigned short`     | **`%hu`**            | Unsigned short integer (positive only)              |
|                        | `unsigned int`       | **`%u`**             | Unsigned standard integer                           |
|                        | `unsigned long`      | **`%lu`**            | Unsigned long integer                               |
|                        | `unsigned long long` | **`%llu`**           | Unsigned very long integer                          |
| **Floating Point**     | `float`              | **`%f`**             | Floating point number                               |
|                        | `double`             | **`%lf`**            | Double precision (Note: `%f` also works for printf) |
|                        | `long double`        | **`%Lf`**            | Extended precision (Must use capital **L**)         |
| **Number Bases**       | `int` (Hex)          | **`%x`** / **`%X`**  | Hexadecimal (e.g., `1a` / `1A`)                     |
|                        | `int` (Octal)        | **`%o`**             | Octal base                                          |
| **Miscellaneous**      | `void *`             | **`%p`**             | Pointer address                                     |
|                        | (Symbol)             | **`%%`**             | Prints a literal `%` character                      |

