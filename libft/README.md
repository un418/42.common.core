_This project has been created as part of the 42 curriculum by adaferna_

# Libft

## Description
**Libft** -. My very own C library

The goal of the project is to **build and package** a library into a `libft.a` file, which is meant to be reused in future projects.

It includes **reimplementations of standard C library (`libc`) functions**, as well as additional useful functions to manipulate **strings** and **linked lists**.


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

#### 1. Include the Header
Add the library header to any source files that call Libft functions:

```c
#include "libft.h"
```
#### 2. Compile and Link
For this example, we assume your project is located in `/home/user/project1` and you have copied the `libft` folder into `/home/user/project1/libft`.  

Now you must tell the compiler where to find both the header files and the compiled library.  
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

#### Don't protect NULL pointer deferencement inside lib function
According to the C Standard, dereferencing a NULL pointer is Undefined Behavior, which typically results in a segmentation fault.  
I have deliberately chosen not to implement NULL-checks within these functions, leaving the responsibility of pointer validation to the caller.

_Linked List functions are an exception_  
_They are designed to handle NULL pointers by default to ensure safe operations on empty or uninitialized lists._.

Commit related :
* https://github.com/un418/42.common.core/commit/a3e4d4cd26df6cfe2ebeb269d30a77a4fd90970c


## Resources

* Manual Pages (`man`): The primary reference for understanding standard libc functions.
* Book : [C Programming. A Modern Approach. by K. N. King(Georgia State University)](http://knking.com/books/c2/)
* [GeeksforGeeks](https://www.geeksforgeeks.org): I liked their diagram to building mental models of memory and data structures.
* [Obsidian.md](https://obsidian.md/) to take note when working on this project you can find them [here](https://github.com/un418/42.common.core/blob/master/_docs/99_quick_notes/M0_libft.md)
* [libfTester by Tripouille](https://github.com/Tripouille/libftTester) ; Doesn't mean I didn't test by myself, find mine [here](https://github.com/un418/42.common.core/blob/master/libft/test/test.c) (~1500 lines)
### AI Usage

I used Large Language Models (LLMs) as learning assistants throughout this project.  
My usage focused on the following areas:
* Demystifying  & clarify concepts
* Coding Best Practices: _How to to write clean, efficient and safe code._
* Documentation:
	* Writing short note to integate in [my Obsidian](https://github.com/un418/42.common.core/tree/master/_docs)
	* Refining the English descriptions and structure of this README to ensure clarity for other developers.

You can find the definition of my Gemini Gem [here](https://github.com/un418/42.common.core/blob/master/_docs/42/AI%20-%20LLM.md), it will give you a clear vision of how I use AI to learn.
