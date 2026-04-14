

## 1. Configure Makefile

- [ ] create a makefile that compile the files
- [ ] makefile compile file as librairy
- [ ] 

- https://www.geeksforgeeks.org/c/how-do-i-create-a-library-in-c/

Create Library  archive
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
• Declaring global variables is strictly forbidden.
- What is a global variables ? 
- 
• If you need helper functions to break down a more complex function, define them as static 
functions to restrict their scope to the appropriate file. 
- What
- 
• All files must be placed at the root of your repository. 

• Submitting unused files is not allowed. 

• Every .c file must compile with the following flags: -Wall -Wextra -Werror. 

• You must use the ar command to create your library. The use of libtool is strictly forbidden. 

• Your libft.a must be created at the root of your repository.