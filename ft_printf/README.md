_This project has been created as part of the 42 curriculum by adaferna._

# ft_printf

Table of Contents
* [Description](#description)
* [Instructions](#instructions)
  * [Build](#build)
  * [Using the Library in Another Project](#using-the-library-in-another-project)
    * [1. Include the Header](#1-include-the-header)
    * [2. Compile and Link](#2-compile-and-link)
* [Technical choices](#technical-choices)
* [Resources](#resources)
  * [AI Usage](#ai-usage)
* [Libft Functions List](#libft-functions-list)

## Description

## Instructions

```bash
make            # same as `make all`
make all        # build the library
make clean      # delete temporary object files `*.o`
make fclean     # delete `*.o` and the final `libft.a` files
make re         # delete `*.o` and `libft.a` files, then rebuild the library
```

### Using the Library in Another Project

To use **Libft** in your own project, follow these steps.

#### 1. Include the Header
Add the library header to any source files that call Libft functions:

```c
#include "ft_printf.h"
```
#### 2. Compile and Link
For this example, we assume your project is located in `/home/user/project1` and you have copied the `ft_printf` folder into `/home/user/project1/ft_printf`.  

Now you must tell the compiler where to find both the header files and the compiled library.  
```bash 
cd /home/user/project1
# Build the library by triggering its Makefile
make -C libft
# Compile your project and link the library
cc main.c -Ift_printf-Lft_printf -lftprintf -o my_program
```

**Flag explanation**
- `-ft_printf` : Tells the compiler to look for header files (.h) **inside the libft directory**.  
- `-Lft_printf` : Tells the compiler to search for the compiled library file (libft.a) **inside the libft directory**.  
- `-lftprintf` : Tells the compiler which library to **link**. The prefix lib and the extension .a are added automatically (e.g., -lft searches for libftprintf.a).

## Technical choices


## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book : [C Programming. A Modern Approach. by K. N. King(Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagram to building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take note when working on this project you can find them [here]()
* _TESTING_

### AI Usage

I used LLMs as learning assistants throughout this project, my usage focused on the following areas:
* Clarifying concepts
* Advices on coding best practices: _How to to write clean, efficient and safe code._
* Documentation:
	* Writing short note to integate in [my Obsidian](https://github.com/un418/42.common.core/tree/master/_docs)
	* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.


## Libftprintf Functions List

A quick reference to help you find the functions you need.

| Function | Description |
| --- | --- |