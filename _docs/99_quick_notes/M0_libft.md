

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
Find a way to test the code via a main function that call the librairy

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





• **Submitting unused files is not allowed.**
• **All files must be placed at the root of your repository.**
• **Every .c file must compile with the following flags: -Wall -Wextra -Werror.**
• **You must use the ar command to create your library. The use of libtool is strictly forbidden.**
• **Your libft.a must be created at the root of your repository.