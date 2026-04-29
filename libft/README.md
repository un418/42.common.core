_This project has been created as part of the 42 curriculum by adaferna_

# Libft
My very own C library.

## Description
The **Libft** project is about creating a custom C library.

The goal of the project is to **build and package** a library into a `libft.a` file, which is meant to be reused in future projects.

It includes reimplementations of standard C library (`libc`) functions, as well as additional useful functions to manipulate strings and linked lists.


## Instructions
### Build
```bash
make            # same as `make all`
make all        # build the library
make clean      # delete temporary object files `*.o`
make fclean     # delete `*.o` and the final `libft.a` files
make re         # delete `*.o` and `libft.a` files, then rebuild the library
```
### Using the Library in Another Project

To use **Libft** in your own project, follow these steps.

For this example, we assume your project is located in `/home/user/project1` and you have copied the `libft` folder into `/home/user/project1/libft`.

#### 1. Include the Header
Add the library header to any source files that call Libft functions:

```c
#include "libft.h"
```
#### 2. Compile and Link
You must tell the compiler where to find both the header files and the compiled library.

```bash 
cd /home/user/project1
# Build the library by triggering its Makefile
make -C libft
# Compile your project and link the library
cc main.c -Ilibft -Llibft -lft -o my_program
```
#### Flag explanation
- `-Ilibft` : Tells the compiler to look for header files (.h) inside the libft directory.  
- `-Llibft` : Tells the compiler where to search for the compiled library file (libft.a).  
- `-lft` : Tells the compiler which library to link.The prefix lib and the extension .a are added automatically (e.g., -lft searches for libft.a).

## Technical choices

### Don't protect NULL pointer deferencing
According to the C Standard, dereferencing a NULL pointer is Undefined Behavior, which typically results in a segmentation fault.  
I have deliberately chosen not to implement NULL-checks within these functions, leaving the responsibility of pointer validation to the caller.

Commit related :
* https://github.com/un418/42.common.core/commit/a3e4d4cd26df6cfe2ebeb269d30a77a4fd90970c

> [!IMPORTANT]  
> **Linked List functions are an exception**  
> They are designed to handle NULL pointers by default to ensure safe operations on empty or uninitialized lists.

## Resources

* **Manual Pages (`man`):** The primary reference for understanding standard libc functions and system calls.
* **[GeeksforGeeks](https://www.geeksforgeeks.org):** Used to simplify complex concepts; their diagrams were especially helpful for building mental models of memory and data structures.

**[All my notes and related links for this project can be found here](https://github.com/un418/42.common.core/tree/master/_docs)**

### AI Disclosure
I used Large Language Models (LLMs) (mostly Gemini) as learning assistants throughout this project.

My usage focused on the following areas:
* **Concept Clarification:** Bridging gaps in my understanding of low-level C concepts (e.g., memory alignment, pointer arithmetic, and Undefined Behavior).
* **Best Practices:** Gathering information on industry-standard coding patterns and identifying common anti-patterns to write cleaner, more efficient code.
* **Documentation:** Refining the English descriptions and structure of this README to ensure clarity for other developers.

**[You can find the definition of my Gemini Gem here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md)**

> [!NOTE]  
> All code logic was implemented manually.  
> AI was used as a pedagogical tool to deepen my understanding, not as a replacement for problem-solving.

---

## Libft Functions List

A quick reference to help you find the functions you need.

| Function | Description |
| :--- | :--- |
| **Memory** | |
| `ft_memset` | Fill a block of memory with a specific byte |
| `ft_bzero` | Set a block of memory to zero |
| `ft_memcpy` | Copy a memory area from source to destination |
| `ft_memmove` | Safely copy a memory area (handles overlapping) |
| `ft_memchr` | Scan memory for the first occurrence of a specific byte |
| `ft_memcmp` | Compare two memory areas |
| `ft_calloc` | Allocate memory and set it to zero (safe malloc + bzero) |
| **ASCII / Char checks** | |
| `ft_isalpha` | Check if character is alphabetic |
| `ft_isdigit` | Check if character is a digit (0-9) |
| `ft_isalnum` | Check if character is alphanumeric (number or letter) |
| `ft_isascii` | Check if character fits into the ASCII character set |
| `ft_isprint` | Check if character is printable |
| `ft_toupper` | Convert lowercase letter to uppercase |
| `ft_tolower` | Convert uppercase letter to lowercase |
| **String Manipulation** | |
| `ft_strlen` | Calculate the length of a string |
| `ft_strlcpy` | Size-bounded string copying |
| `ft_strlcat` | Size-bounded string concatenation |
| `ft_strchr` | Locate the first occurrence of a character in a string |
| `ft_strrchr` | Locate the last occurrence of a character in a string |
| `ft_strncmp` | Compare two strings up to `n` characters |
| `ft_strnstr` | Locate a substring in a string with a size limit |
| `ft_strdup` | Duplicate a string (allocates memory) |
| `ft_substr` | Extract a substring from a string |
| `ft_strjoin` | Concatenate two strings into a newly allocated string |
| `ft_strtrim` | Trim specified characters from the beginning and end of a string |
| `ft_split` | Split a string into an array of strings using a delimiter |
| `ft_strmapi` | Apply a function to each character of a string (creates new string) |
| `ft_striteri` | Apply a function to each character of a string (modifies in place) |
| **Conversion** | |
| `ft_atoi` | Convert an ASCII string to an integer (`int`) |
| `ft_itoa` | Convert an integer (`int`) to an ASCII string |
| **File Descriptor (Print)** | |
| `ft_putchar_fd` | Output a character to a given file descriptor |
| `ft_putstr_fd` | Output a string to a given file descriptor |
| `ft_putendl_fd` | Output a string followed by a newline to a given file descriptor |
| `ft_putnbr_fd` | Output an integer to a given file descriptor |
| **Linked Lists** | |
| `ft_lstnew` | Create a new list node |
| `ft_lstadd_front`| Add a new node to the beginning of a list |
| `ft_lstsize` | Count the number of nodes in a list |
| `ft_lstlast` | Get the last node of a list |
| `ft_lstadd_back` | Add a new node to the end of a list |
| `ft_lstdelone` | Delete and free a single list node |
| `ft_lstclear` | Delete and free a sequence of list nodes |
| `ft_lstiter` | Apply a function to the content of all list nodes |
| `ft_lstmap` | Apply a function to a list to create a new list |
