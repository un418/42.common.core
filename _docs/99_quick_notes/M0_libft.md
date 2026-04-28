```bash
# avoid running nominette on test.c
 norminette $(ls *.c | grep -v test)
 # alias to update note
 ga $(git rev-parse --show-toplevel)/_docs && gcmsg "update notes" && gp

```

## ToDo List
- [x] Where to use malloc vs calloc ?
	- [x] calloc will do useless memory operation to set bytes to zero if the memory is fill right after provisionning, like for string creation
	- [x] calloc is good when we provision memory and fill it later like for list of string, or any list of list (cf. ft_split)
- [x] calloc : rewrite malloc error mgmt
- [ ] verifying unsigned char casting for char  (improve casting for mem and str func)
- [x] verify syntax for malloc null pointer check condition exit check
- [x] Check atoi behavior in int overflow
	- [x] As the doc say for strtol :"If the value cannot be represented, the behavior is undefined."
	- [x] compare result between ft_atoi and atoi
- [x] rename helper function on ft_islower


## Important Instruction
- **Submitting unused files is not allowed.**
- **All files must be placed at the root of your repository.**
- **Every .c file must compile with the following flags: -Wall -Wextra -Werror.**

- **You must use the ar command to create your library. The use of libtool is strictly forbidden.**
-  **Your libft.a must be created at the root of your repository.**

- To begin, you must reimplement a set of functions from the libc. 
  Your version will have the same **prototypes** and behaviors as the originals, adhering **strictly to their definitions in the man page**. 
  The **only difference will be their names**, which must start with the ’ft_’ prefix. For example, strlen becomes ft_strlen.
## 1. Configure Makefile

- [x] makefile compile file as librairy
- https://www.geeksforgeeks.org/c/how-do-i-create-a-library-in-c/

### Create Library  archive
- https://www.geeksforgeeks.org/linux-unix/ar-command-in-linux-with-examples/

> The '****ar'**** command in Linux is a versatile tool used for creating, modifying, and extracting files from archives

```bash
ar rcs libmylib.a mylib.o
```

- **`r` (replace)** : Insère les fichiers objets (`.o`) dans l'archive. Si l'archive contient déjà un fichier portant le même nom, il est remplacé. C'est l'opération de base pour mettre à jour ou créer ta bibliothèque.
- **`c` (create)** : Crée l'archive si elle n'existe pas déjà. Sans cette option, `ar` pourrait afficher un message d'avertissement sur la sortie d'erreur s'il doit créer un nouveau fichier.
- **`s` (write index)** : Crée un index des symboles (fonctions, variables globales) dans l'archive ou met à jour un index existant. Cet index permet au lieur (`ld`, appelé via `gcc`) d'accélérer la recherche de symboles sans avoir à parcourir tout le contenu de l'archive. Utiliser `s` équivaut à lancer la commande `ranlib` sur ton fichier `.a`.
- https://www.geeksforgeeks.org/c/header-files-in-c-cpp-and-its-uses/



## 2. Be able to test code
Find a way to test the code via a main function that call the library
- https://github.com/un418/42.common.core/commit/5581fd65a7693c45c6d228e9a83cc22ba587d449
- https://github.com/un418/42.common.core/commit/8d4a48f7d20b09c4a4fec19eaa6bc9c2ab5dc66e

## Others

#### ? Is TAB (ASCII = 9) a printable caracter ? 
- This website say no : https://www.ascii-code.com/
- But test with printf works ???
  

## ft_isalnum

* Why the official isalnum return 8 instead of one when there is match ? 

> [!NOTE] `isalnum` & Lookup Table (Optimization)
> 
> The `ctype.h` functions use a **lookup table** (a pre-calculated 256-entry array) for maximum performance. Each ASCII character is assigned a **bitmask** representing its properties:
> - The return value is the result of a bitwise `&` operation: `return (table[c] & _IS_ALNUM_BIT);`.
> - You often get values like `8`, `1024`, or `2048` because it returns the specific bit assigned to that category.
> 
> **Golden Rule:** In C, "true" is any non-zero value. Never check `if (isalnum(c) == 1)`; always use `if (isalnum(c))`.

## ft_strlen

> [!INFO] 📏 The `size_t` Type
> `size_t` is an **unsigned integer type** defined in `<stddef.h>` (and inherited by `<stdlib.h>` or `<stdio.h>`). It is the dedicated type for representing the size of any object in memory.
> 
> ---
> ### 🚀 Key Features
> - **Portability**: Its actual size is architecture-dependent. It is **32-bit** on 32-bit systems and **64-bit** on 64-bit systems. This ensures it can always address the maximum theoretical limit of your RAM.
> - **Safety**: Being **unsigned**, it inherently prevents negative lengths. It is the perfect fit for array indexing and loop counters.
> - **Standard Usage**: It is the mandatory type for core functions like `malloc()`, `strlen()`, `memcpy()`, and `memset()`.
> 
> ---
> ### ⚠️ Risks & Gotchas
> - **Underflow**: Since it cannot be negative, executing `0 - 1` on a `size_t` will cause it to "wrap around" to its maximum possible value (a massive number), often leading to infinite loops.
> - **Comparison**: Avoid comparing `int` and `size_t` directly. You will trigger **signed/unsigned comparison warnings** because the compiler struggles to decide how to handle the sign bit.
> 
> > [!TIP] Best Practice
> > Always use `size_t` for any variable that stores a **count**, a **length**, or an **index**. It makes your code future-proof and 64-bit compatible.

> [!ABSTRACT] 🛡️ The `const` Qualifier in Pointers
> In function prototypes like `strcmp(const char *s1, ...)`, the `const` keyword before the pointer type defines **Pointer to Constant Data**.
> 
> ---
> ### 🔑 Key Implications
> - **Immutability**: The function treats the memory pointed to by `s1` as **read-only**. Any attempt to modify the characters (e.g., `s1[i] = 'x'`) will trigger a **compiler error**.
> - **Contract of Trust**: It informs the developer that the function is safe to use with data that *must not* change (like string literals stored in the read-only data segment).
> - **Compatibility**: You can pass a non-const variable to a `const char *` parameter, but you **cannot** pass a `const char *` to a function expecting a regular `char *` without a warning/error.
> 
> ---
> ### ⚙️ Memory Layout
> | Syntax | Meaning | Can change data? | Can change pointer address? |
> | :--- | :--- | :--- | :--- |
> | `const char *s` | Pointer to constant | **No** | Yes |
> | `char * const s` | Constant pointer | Yes | **No** |
> 
> > [!TIP] Best Practice
> > Always use `const` for any function parameter that only needs to **read** data. 
> > It makes your code more robust and prevents accidental bugs where a value is unintentionally overwritten.


## memove

#### Memory Overlapping Mental Model
https://cs50.stackexchange.com/questions/14615/memory-overlap-in-c
Memory overlap happens when you try to copy data between two regions that share the same physical memory space. This typically occurs when you are shifting data within the same array or buffer. 
##### The Visual Example
Imagine an array of 5 characters: `[ 'A', 'B', 'C', 'D', 'E' ]`.  
You want to move the first 3 characters (`ABC`) one position to the right.
- **Source (`src`)**: Starts at index 0 (`ABC`)
- **Destination (`dst`)**: Starts at index 1 (`BCD`)
##### Why `memcpy` Fails
A standard `memcpy` often copies from left to right. If it copies one byte at a time:
1. Copy `src[0]` ('A') to `dst[0]` (index 1). Array is now `[A, A, C, D, E]`.
2. Copy `src[1]` to `dst[1]`. **Problem**: `src[1]` was originally 'B', but it was just overwritten by 'A'!
3. The result becomes `[A, A, A, A, E]` instead of `[A, A, B, C, E]`.


## memcmp

> [!WARNING] 
> **Pointer Arithmetic vs. Dereferencing (`char *ptr` vs `unsigned char *ptr`)**
> 
> ### 1. Pointer Arithmetic: Identical Behavior
> Operations like `ptr + 1` or `ptr++` behave exactly the same for both types. 
> Both pointers advance the memory address by **1 byte** because `sizeof(char) == sizeof(unsigned char) == 1`. 
> The compiler strictly looks at the size of the data type, not its sign.
> 
> ### 2. Dereferencing (`*ptr`): The Danger Zone
> The critical difference emerges when you read the value at the address (`*ptr`), especially during **integer promotion** (which happens automatically in C when doing math, comparisons, or returning values).
> 
> * **`*p_s1` (Signed) $\rightarrow$ Sign Extension:** >     If the 8th bit is `1` (negative value), the compiler fills the newly added bits with `1`s when promoting to an `int`. 
>     *Example:* `0xFF` (1 byte) becomes `0xFFFFFFFF` (4 bytes, still `-1`).
> 
> * **`*p_s2` (Unsigned) $\rightarrow$ Zero Extension:** >     The value is strictly treated as a magnitude (0-255). The compiler fills the new bits with `0`s.
>     *Example:* `0xFF` (1 byte) becomes `0x000000FF` (4 bytes, `255`).
> 
> **Core Takeaway:** 
> Arithmetic moves the pointer; dereferencing interprets the memory. 
> **Always use `unsigned char *`** when reading raw memory (like parsing `void *` buffers) to **prevent destructive bugs caused by unintended sign extensions **during byte evaluation.

> [!NOTE] Why `int` instead of `unsigned char` in `mem... functions?
> 
> 1. **Historical Legacy**: In K&R C (pre-ANSI), arguments of type `char` were automatically promoted to `int` during function calls.
> 2. **API Consistency**: Many standard functions (like `fgetc`) return `int` to include the `EOF` constant (-1), which doesn't fit in an `unsigned char`.
> 3. **CPU Efficiency**: Processors handle data in their native word size (usually `int`) more efficiently than masking a single byte in a register.
> 4. **Internal Logic**: Although passed as an `int`, the value is explicitly cast to `unsigned char` inside the function to ensure 8-bit processing.

#TODO  - Reread code to see if I not mistaken on that point

## calloc

#### type limits and bit operation

```c
// https://cplayground.com/
#include <stdio.h>
#include <limits.h>

int main() {
    // Retrieve min/ max value of a type via bit operation
    printf("Max of unsigned int = %u\n", (unsigned int)-1);
    // overflow of a unsigned int to have all bit at 1, 
    // then bytes operation to move all bytes to the right and release the sign bit at 0.
    // casting the result to an int give INT_MAX
    printf("inline = %d\n", (int)((unsigned int)-1 >> 1 ));
    // Size of because we use bit operation and not bytes operation
    // This operation set value at one on binary then we move the bit to the place of the sign bit
    // casting to an int give INT_MIN
    printf("inline = %d\n", (int)((unsigned int)1 << (sizeof(int) * 8 - 1)));
    return 0;
}

```

> [!danger] Integer Overflow
> Occurs when an arithmetic operation yields a value exceeding the maximum capacity of a **signed** data type. In C, this results in **Undefined Behavior (UB)**.
> ```c
> int max = (int)(((unsigned int)-1) >> 1);
> int overflow = max + 1; // Undefined Behavior
> ```

> [!warning] Integer Underflow
> Occurs when a calculation drops below the minimum representable value. 
> For unsigned types, subtracting from `0` wraps around to the absolute maximum value.
> ```c
> size_t zero = 0;
> size_t underflow = zero - 1; // underflow == (size_t)-1
> ```


> [!warning] Unsigned Wrap-around
> Occurs when a calculation exceeds the maximum value of an **unsigned** type (like `size_t`). 
> This is strictly defined by the C standard: the value wraps around to `0` using modulo arithmetic. 
> ```c
> size_t max = (size_t)-1;
> size_t wrap = max + 1; // wrap == 0
> ```

> [!bug] Heap-based Buffer Overflow
> A memory corruption vulnerability on the heap. 
> Often the direct consequence of passing a wrapped-around/overflowed size to `malloc()`, leading to an undersized allocation and subsequent out-of-bounds memory writes.
> ```c
> char *ptr = malloc(10);
> if (ptr)
>     ptr[10] = 'A'; // Heap corruption (valid indices: 0 to 9)
> ```
## Q & A
- **Declaring global variables is strictly forbidden.**

> [!NOTE] 🌐 Global Variables
>
> A **global variable** is a variable declared outside of any function, typically at the top of a `.c` file. Unlike local variables, it is stored in the **Data Segment** or **BSS** of the program's memory.
>
> * **Scope**: It is accessible from any function within the same file. If not declared `static`, it can also be accessed from other files using the `extern` keyword.
> * **Lifetime**: It exists for the entire duration of the program's execution, from start to finish.
> * **Initialization**: If not explicitly initialized, global variables are automatically set to `0` by the compiler.
> * **42 Norm**: Be careful! Global variables are **strictly forbidden** in most 42 projects unless explicitly allowed (like in *minishell* or *philosophers*).
>
> ---
>
> #### **⚠️ Risks & Debugging**
>
> * **Side Effects**: Since any function can modify a global variable, it creates hidden dependencies. A change in one part of your code might silently break a completely unrelated function.
> * **Thread Safety**: Global variables are dangerous in multi-threaded programs (like *philosophers*) because they can lead to **data races** if multiple threads try to write to them simultaneously.
> * **GDB Debugging**: To track a global variable in GDB, use the `watch` command: `watch my_global_var`. This will pause execution every time the value changes, which is essential for finding where a variable is being unexpectedly modified.

-  **If you need helper functions to break down a more complex function, define them as static functions to restrict their scope to the appropriate file.** 

> [!NOTE] What is a helper function ? 
> A **helper function** is a secondary function designed to handle a specific, isolated sub-task for a more complex main function.
>
> * **Norm Compliance**: Crucial for splitting logic to respect the 42 Norm (e.g., the 25-line limit per function).
> * **Readability**: Abstracts complex operations into named steps, making the main algorithm easier to read and audit.
> * **Reusability**: Avoids code duplication if a specific block of logic is needed multiple times.

> [!NOTE] What is a static function ? 
> A **static function** is a function declared with the `static` keyword, which restricts its scope and visibility exclusively to the `.c` file where it is defined.
>
> * **Encapsulation**: Hides internal logic from the rest of the program. If a function is only meant to be a helper within a specific file, it should be `static`.
> * **Conflict Prevention**: Makes the function invisible to the linker. This prevents symbol conflicts if another `.c` file in your project uses a function with the exact same name.
>
> * **Use case **: Good examples of implementation can but the function to count_word in ft_split





## Point of Attention

* `size_t` type and `const char *s1` constant definition in function prototype : 
	*  Check prototype conform to man : to add in libftTester