_This project has been created as part of the 42 curriculum by adaferna._

# Get Next Line

Table of Contents
* [Description](#description)
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

This project is about programming a function that returns a line
read from a file descriptor.





## Instructions

### Build

```bash
make        # build
make re     # rebuild
make clean  # remove objects
make fclean # remove objects + libftprintf.a
```

### Usage

#### 1 - Clone or copy get_next_line into your project as a subfolder
```bash
cc main.c  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c -Iget_next_line -o my_program
```

#### 2 - Add header file to every source file that calls ft_printf
```c
#include "get_next_line.h"
```

#### 3 - Call the function
```c
//todo
```

## Implementation

### Algorithm
### Error management

### Function reference

| Name | Prototype | Description |
| --- | --- | --- |


## Testing

Building my own tests was honestly one of the fun parts of this project.

A `make memtest` target also runs the suite under Valgrind to confirm there are no leaks.

## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book: [C Programming. A Modern Approach. by K. N. King (Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagrams for building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take notes while working on this project — you can find them [here](https://github.com/un418/42.common.core/blob/master/_docs/99_quick_notes/M1_ft_printf.md).

### AI Usage

* Clarifying concepts
* Advice on coding best practices
* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.
