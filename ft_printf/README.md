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
  * [Hexadecimal case handling](#hexadecimal-case-handling)
  * [Headers](#headers)
  * [Function reference](#function-reference)
* [Testing](#testing)
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
The `va_list` is the only data structure needed; it is the standard C mechanism for accessing variadic arguments.

### File descriptor support

Although not required by the subject, output is routed through an internal file descriptor parameter rather than hard-coding `stdout`.  
This makes the same helpers reusable to write to `stderr` or any log file in future 42 projects.  
Supporting writes to an arbitrary file descriptor required consistent error handling across all write operations; see [Error propagation](#error-propagation) below.

### Error propagation

All internal helpers return `ssize_t` and propagate `-1` on a `write` failure.  
The main loop checks every return value and short-circuits immediately, mirroring the behavior of the real `printf` on write errors.

### Hexadecimal case handling

`%x` and `%X` differ only by digit case (`a-f` vs `A-F`).  
Instead of writing a dedicated function for each, `ft_writehex_fd_recurse` takes an `upper` flag that selects the digit alphabet (lowercase when `0`, uppercase when `1`).  
See [`ft_writehex_fd_recurse`](https://github.com/un418/42.common.core/blob/master/ft_printf/src/ft_printf_num.c#L63-L66).

### Headers

Following common industry practice, the interface is split in two: 
- `ft_printf.h` exposes the public API meant to be called from user code.
- `ft_printf_private.h` holds the internal conversion helpers needed to build the library archive.

### Function reference

#### **Public API** - `ft_printf.h`
- `ft_printf` covers the subject
- `dprintf` / `vprintf` are not required for the subject, but I chose to implement them for use in my future projects (e.g. the push_swap bonus)

| Name | Prototype | Description |
| --- | --- | --- |
| `ft_printf` | `int ft_printf(const char *str, ...)` | Subject entry point — formats to `stdout` |
| `ft_dprintf` | `int ft_dprintf(int fd, const char *str, ...)` | Same as `ft_printf` but writes to an arbitrary file descriptor |
| `ft_vprintf` | `int ft_vprintf(const char *str, va_list args)` | `ft_printf` variant taking an already-started `va_list` |
| `ft_vdprintf` | `int ft_vdprintf(int fd, const char *str, va_list args)` | `ft_dprintf` variant taking an already-started `va_list` |

#### **Internal helpers** - `ft_printf_private.h`
Implementation details, not meant to be called directly.

| Name | Prototype | Description |
| --- | --- | --- |
| `ft_write_fd_char` | `ssize_t ft_write_fd_char(int c, int fd)` | Writes a single character to a file descriptor |
| `ft_write_fd_str` | `ssize_t ft_write_fd_str(char *s, int fd)` | Writes a string to a file descriptor (`NULL` prints `"(null)"`) |
| `ft_writesnbr_fd` | `ssize_t ft_writesnbr_fd(long n, int fd)` | Writes a signed decimal integer to a file descriptor |
| `ft_writeunbr_fd_recurse` | `ssize_t ft_writeunbr_fd_recurse(unsigned long ul, int fd)` | Writes an unsigned decimal integer recursively to a file descriptor |
| `ft_writehex_fd_recurse` | `ssize_t ft_writehex_fd_recurse(unsigned long un, int fd, int upper)` | Writes an unsigned integer in hexadecimal recursively (`upper` selects case — see [Hexadecimal case handling](#hexadecimal-case-handling)) |
| `ft_write_fd_pointer` | `ssize_t ft_write_fd_pointer(void *p, int fd)` | Writes a pointer address with `0x` prefix (`NULL` prints `"(nil)"`) |

## Testing

Building my own tests was honestly one of the fun parts of this project — it was my first time writing a tester, even a very basic one, and it taught me as much about `printf` as coding `ft_printf` itself.

The approach is simple: run the same format strings through `ft_printf` and the real `printf`, then compare both the **output** and the **return value**.  

Three complementary tools:
- **Functional suite** ([`test/test.c`](https://github.com/un418/42.common.core/blob/master/ft_printf/test/test.c)) — `make test`  
Built with AddressSanitizer (`-fsanitize=address`), it checks every specifier against the system `printf`.
- **Undefined-behavior suite** ([`test/ub_test.c`](https://github.com/un418/42.common.core/blob/master/ft_printf/test/ub_test.c)) — `make test_ub` (compiled without `-Werror`)  
Covers the messy edge cases: unknown specifiers, a lone `%`, a `NULL` format, and write errors on a closed `stdout`. It lets me reproduce the behavior of `printf` as closely as possible in these edge cases.
- **Stdout comparison** ([`test/tester.sh`](https://github.com/un418/42.common.core/blob/master/ft_printf/test/tester.sh)) — `make tester`  
A small bash script that `diff`s `ft_printf` output against `printf` line by line.

A `make memtest` target also runs the suite under Valgrind to confirm there are no leaks.

## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book: [C Programming. A Modern Approach. by K. N. King (Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagrams for building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take notes while working on this project — you can find them [here](https://github.com/un418/42.common.core/blob/master/_docs/99_quick_notes/M1_ft_printf.md).
* Took inspiration from [Tripouille's printfTester](https://github.com/Tripouille/printfTester) to write my own first little tester.
  * try `make tester` and `make test`
* Took inspiration from [aleksify](https://github.com/aleksify)'s [ft_printf implementation](https://github.com/42lx/ft_printf/blob/main/include/ft_printf.h) for:
  * Going beyond the subject's requirements and implementing [File descriptor support](#file-descriptor-support)
  * Splitting the headers between public and private — see [Headers](#headers)

### AI Usage

* Clarifying concepts
* Advice on coding best practices
* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.
