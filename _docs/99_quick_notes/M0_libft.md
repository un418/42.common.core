## Important Instruction

- **Submitting unused files is not allowed.**
- **All files must be placed at the root of your repository.**
- **Every .c file must compile with the following flags: -Wall -Wextra -Werror.**

- **You must use the ar command to create your library. The use of libtool is strictly forbidden.**
-  **Your libft.a must be created at the root of your repository.**

- To begin, you must reimplement a set of functions from the libc. Your version will have the same **prototypes** and behaviors as the originals, adhering s**trictly to their definitions in the man page**. The **only difference will be their names**, which must start with the ’ft_’ prefix. For example, strlen becomes ft_strlen.
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
- 
- https://www.geeksforgeeks.org/c/header-files-in-c-cpp-and-its-uses/



## 2. Be able to test code
Find a way to test the code via a main function that call the library
- https://github.com/un418/42.common.core/commit/5581fd65a7693c45c6d228e9a83cc22ba587d449
- https://github.com/un418/42.common.core/commit/8d4a48f7d20b09c4a4fec19eaa6bc9c2ab5dc66e

## Others

#### ? Is TAB (ASCII = 9) a printable caracter ? 
- This website say no : https://www.ascii-code.com/
- But test with printf works ???
  
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
> > Always use `const` for any function parameter that only needs to **read** data. It makes your code more robust and prevents accidental bugs where a value is unintentionally overwritten.

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

* `size_t` type and `const char *s1` constant definition in function prototype : Check to add in libftTester