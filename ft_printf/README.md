_This project has been created as part of the 42 curriculum by adaferna._

# ft_printf

Table of Contents
* [Description](#description)
* [Supported Specifiers](#supported-specifiers)
* [Instructions](#instructions)
  * [Build](#build)
  * [Integration](#integration)
* [Implementation](#implementation)
  * [Algorithm](#algorithm)
  * [Data Structures](#data-structures)
  * [File descriptor support](#file-descriptor-support)
  * [Error propagation](#error-propagation)
  * [Internal functions](#internal-functions)
* [Resources](#resources)
  * [AI Usage](#ai-usage)

## Description

The goal of this project is to recode a light implementation of the famous `printf()` function from *libc*.

`ft_printf` reimplements the standard `printf` interface for the `cspdiuxX%` specifiers. Output is unbuffered: every character is written directly through the `write` syscall.

See [Supported Specifiers](#supported-specifiers) for the full list of supported conversions.

## Supported Specifiers

| Specifier | Description |
| --- | --- |
| `%c` | Prints a single character |
| `%s` | Prints a string (`NULL` → `"(null)"`) |
| `%d` | Prints a signed decimal integer |
| `%i` | Prints a signed integer |
| `%u` | Prints an unsigned decimal integer |
| `%x` | Prints an unsigned integer in lowercase hexadecimal |
| `%X` | Prints an unsigned integer in uppercase hexadecimal |
| `%p` | Prints a pointer address in hex with `0x` prefix (`NULL` → `"(nil)"`) |
| `%%` | Prints a literal `%` character |

## Instructions

### Build

```bash
make        # build
make re     # rebuild
make clean  # remove objects
make fclean # remove objects + libftprintf.a
```

### Integration

#### 1 - Clone or copy ft_printf into your project as a subfolder
```bash
make -C ft_printf
cc main.c -Ift_printf/inc -Lft_printf -lftprintf -o my_program
```

#### 2 - Add header file to every source file that calls ft_printf
```c
#include "ft_printf.h"
```

#### 3 - Call the function (see [Supported Specifiers](#supported-specifiers))
```c
ft_printf("Hello %s, answer is %d\n", "world", 42);
```

## Implementation

### Algorithm

`ft_printf` is built around a simple **dispatcher**:

1. The format string is iterated character by character.
2. On a `%`, the next character is read and used as a key in a dispatch chain (`if / else if` on the specifier).
3. The matching handler consumes one argument from the `va_list` and writes its formatted output directly through `write`.
4. The running count of bytes successfully written is returned, matching the behavior of the real `printf`.

### Data Structures

No dynamic memory is allocated.  
The `va_list` is the only data structure needed, it is the standard C mechanism for accessing variadic arguments.

### File descriptor support

Although not required by the subject, output is routed through an internal file descriptor parameter rather than hard-coding `stdout`.  
This makes the same helpers reusable to write to `stderr` or any log file in future 42 projects.  
This decision to be able to write on files required consistent error handling across all write operations ; see [Error propagation](#error-propagation) below.

### Error propagation

All internal helpers return `ssize_t` and propagate `-1` on a `write` failure.  
The main loop checks every return value and short-circuits immediately, mirroring the behaviour of the real `printf` on write errors.

### Internal functions

Only `ft_printf` is meant to be called from user code.  
The helpers below are declared in `ft_printf.h` so they can be reused when integrating the library in larger projects (e.g. writing to a custom file descriptor).

| Name | Prototype | Description |
| --- | --- | --- |
| `ft_printf` | `int ft_printf(const char *str, ...)` | Public entry point — parses the format string and dispatches to handlers |
| `ft_write_fd_char` | `ssize_t ft_write_fd_char(int c, int fd)` | Writes a single character to a file descriptor |
| `ft_write_fd_str` | `ssize_t ft_write_fd_str(char *s, int fd)` | Writes a string to a file descriptor (`NULL` prints `"(null)"`) |
| `ft_writesnbr_fd` | `ssize_t ft_writesnbr_fd(long n, int fd)` | Writes a signed decimal integer to a file descriptor |
| `ft_writeunbr_fd_recurse` | `ssize_t ft_writeunbr_fd_recurse(unsigned long ul, int fd)` | Writes an unsigned decimal integer recursively to a file descriptor |
| `ft_writehex_fd_recurse` | `ssize_t ft_writehex_fd_recurse(unsigned long un, int fd, int upper)` | Writes an unsigned integer in hexadecimal recursively (`upper` selects case) |
| `ft_write_fd_pointer` | `ssize_t ft_write_fd_pointer(void *p, int fd)` | Writes a pointer address with `0x` prefix (`NULL` prints `"(nil)"`) |

## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book : [C Programming. A Modern Approach. by K. N. King(Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagram to building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take note when working on this project you can find them [here]().
* Took inspiration on [Tribouille printfTester](https://github.com/Tripouille/printfTester) to write my first own little tester.
  * try `make tester` and `make test`

### AI Usage

* Clarifying concepts
* Advices on coding best practices
* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.
