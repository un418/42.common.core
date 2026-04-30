# COO

## H2

```
Moulinette compiles with the following flags: -Wall -Wextra -Werror, using
cc.

```

- Main fuction always return an integer
    - https://www.reddit.com/r/C_Programming/comments/rwrti5/why_is_the_function_main_called_as_an_int_instead/
     

## Q&A
- https://www.reddit.com/r/C_Programming/comments/rwrti5/why_is_the_function_main_called_as_an_int_instead/
- https://medium.com/@sylvialee_91721/useful-shortcuts-alias-i-use-for-42-d4c752ba872a

### Where is the Norminette ?
`norminette` -> Lien symblique dans le /bin
**Rules**:
    - include : New line after include
    - tab 2 : Apriori la taille du tab n'as pas d'importance -> A check

### How to create file header ?
- vim -> Stdheader
- extension vscode42
- https://github.com/42paris/42header
- https://github.com/kube/vscode-42header
### Compilation 
```bash
gcc -o exe ft_print_numbers.c  && ./exe
```

## Others
```bash
# Cool tools pour savoir ou situe le fichier de la commande
which norminette
whereis norminette
```

## VScode Flatpak Escape

```
    "terminal.integrated.profiles.linux": {
        "BASH": {
          "path": "/usr/bin/flatpak-spawn",
          "args": ["--host", "--env=TERM=xterm-256color", "bash"]
        },
        "ZSHELL": {
          "path": "/usr/bin/flatpak-spawn",
          "args": ["--host", "--env=TERM=xterm-256color", "zsh"]
        },
        "Flatpak": {
          "path": "/bin/bash"
        }
    },
```



# Backup

```bash
cp -r piscine_42 piscine_42_bak_$(date +"%m%d%y%H%M") 
```