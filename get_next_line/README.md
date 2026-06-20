_This project has been created as part of the 42 curriculum by adaferna._

# Get Next Line

Table of Contents
* [Description](#description)
* [Constraints](#constraints)
* [Instructions](#instructions)
  * [Usage](#usage)
* [Implementation](#implementation)
  * [Algorithm](#algorithm)
  * [Function reference](#function-reference)
* [Bonus](#bonus)
* [Testing](#testing)
* [Resources](#resources)
  * [AI Usage](#ai-usage)

## Description

This project is about programming a function that returns a line read from a file descriptor (files, stdin, or any valid `fd`).  
Each call returns the next line, including its trailing `\n`, until end-of-file or an error, at which point it returns `NULL`.

It also introduces the concept of static variables in C: the function must remember, between calls, what was already read but not yet returned.

## Constraints

The tricky part is the limitation around the number of files and from that the number of functions we can use in this project:
> - _Add all the helper functions you need in the get_next_line_utils.c file._
> - _You are not allowed to use your libft in this project._

These two instructions in the subject mean that we are limited to 6 functions maximum according to the _42 Norm_.
- 1 in `get_next_line.c`
- 5 helpers in `get_next_line_utils.c`


## Instructions

### Usage

#### 1 - Add get_next_line to your project
Clone or copy `get_next_line.c`, `get_next_line_utils.c` and `get_next_line.h`
into your project (e.g. as a `get_next_line/` subfolder).

#### 2 - Include the header in every source file that calls get_next_line
```c
#include "get_next_line.h"
```

#### 3 - Compile
```bash
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c -I. -o my_program
```

You can tune two compile-time options with `-D` (both have defaults, so this is optional):

| Macro | Default | Effect |
| --- | --- | --- |
| `BUFFER_SIZE` | `1` | Number of bytes read per `read()` call |
| `DELIMITER` | `'\n'` | Character that ends a line |

```bash
cc ... -D BUFFER_SIZE=4096 -D "DELIMITER='\n'"
```

#### 4 - Call the function
Each call returns the next line (delimiter included), or `NULL` at end of file
or on error. You own each returned line and must `free()` it.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Implementation

### Algorithm

Each call to `get_next_line` runs three steps:

| Step | Helper | What it does |
| --- | --- | --- |
| **Fill** | `buf_to_stash` | Reads `BUFFER_SIZE` bytes at a time into a temporary buffer and appends them to `stash`, looping only until a `\n` appears (or EOF). |
| **Extract** | `ft_line_from_stash` | Copies `stash` up to and including the first `\n`: that copy is the returned line. At EOF with no trailing `\n`, the whole remaining `stash` is returned instead. |
| **Clean** | `ft_clean_stash` | Keeps everything after that `\n` in `stash` for the next call. |

Because `stash` is `static`, it survives between calls: if a read overshoots into the next line,
the extra bytes stay in `stash` and are reused on the next call, with no extra `read()`.

### Function reference

`get_next_line` is the only public entry point. The rest are internal helpers living in
`get_next_line_utils.c`.

| Name | Prototype | Description |
| --- | --- | --- |
| `get_next_line` | `char *get_next_line(int fd)` | Returns the next line read from `fd` (delimiter included), or `NULL` on EOF / error |
| `ft_strchr` | `char *ft_strchr(char *s, int c)` | Locates the first occurrence of `c` in `s`, or `NULL` if not found |
| `ft_strjoin` | `char *ft_strjoin(char *s1, char *s2)` | Concatenates `s1` and `s2` into a newly allocated string |
| `ft_line_from_stash` | `char *ft_line_from_stash(char const *s, char delimiter)` | Extracts the line from the stash up to and including `delimiter` |
| `ft_clean_stash` | `char *ft_clean_stash(char *s, char delimiter)` | Returns the remaining part of the stash after `delimiter` |
| `buf_to_stash` | `char *buf_to_stash(int fd, char *stash)` | Reads from `fd` into the stash until `delimiter` is found or EOF |


## Bonus

The bonus adds **multiple file descriptors** support: `get_next_line` can be called in turn on several
`fd`s without ever mixing their reading states.  
Each `fd` keeps its own stash, so an unfinished
line on one file is never lost or appended to another.

This is done by replacing the single `static char *stash` with an array indexed by the file
descriptor:

```c
static char *stash[1048576];
```

The size **1048576** matches the maximum per-process file-descriptor limit (`ulimit -n` hard
limit) on this system, so `stash[fd]` stays a valid index for any `fd` the process can open.  




Compilation is identical, only the file names change:

```bash
cc -Wall -Wextra -Werror main.c get_next_line_bonus.c get_next_line_utils_bonus.c -I. -o my_program
```

## Testing

Building my own tests was honestly one of the fun parts of this project.
All targets live in [`test/`](test/):

- `make test`: runs the suite under AddressSanitizer (`BUFFER_SIZE=10`), piped through `cat -e`. Covers the tricky inputs: empty file, no trailing newline, single line, only `\n`.
- `make tester`: reruns it at `BUFFER_SIZE=1`, `5`, `100`, each under Valgrind, then `diff_test.sh` checks the generated output against the source files byte for byte. The result must be identical whatever the buffer size.
- `make errtest`: the error paths: an invalid fd, a file that doesn't exist, and an unreadable file (`chmod 000`, created on the fly). `get_next_line` must return `NULL` every time, with no leaks.
- `make stdin`: interactive read from stdin (`BUFFER_SIZE=42`, `Ctrl-D` to quit).
- `make memtest`: Valgrind with `--leak-check=full --track-fds=yes` (no memory **or** fd leaks).

#### Recovering the test suite

The `test/` folder is removed in the final submission commit, so the repository ships only the
files the subject requires. It stays one commit back in the history. To get it back:

```bash
git reset --hard HEAD~1
```

## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book: [C Programming. A Modern Approach. by K. N. King (Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagrams for building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take notes while working on this project. You can find them [here](https://github.com/un418/42.common.core/blob/master/_docs/99_Projects/M1_GNL.md).

### AI Usage

* Clarifying concepts
* Advice on coding best practices
* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.
