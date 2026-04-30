## ex00

* set perm
* set date (after all action - chmod not impact ls timestamp)
* test 5 is a hardlink
* test 6 is a symlink

` echo  -n `    : do not output the trailing newline
`touch -ht ...` : -h allow to take action on symlink and not the file pointed

## ex02

find : using 'OR' statement and '( .. )' style logic expression
* https://stackoverflow.com/questions/71562728/find-with-shell-with-different-and-or-conditions


vim : use command line inside vim
* `:!./myscript.sh` : **!** is the operateur to launch command
* https://stackoverflow.com/questions/23097842/how-to-execute-command-inside-vim

## ex03

`man basename`

```
...
DESCRIPTION
       Print NAME with any leading directory components removed.  If specified, also remove a trailing SUFFIX.
...
```

## ex04

## ex05

/!\ Spoiler Alert : Contain the answer
* Painpoint is escaping the  `'` and write inside the file without the newline terminator

```bash
echo -n 42 > '"\?$*'\'MaRViN\''*$?\"'
```

## ex06

To compile with ft_putchar.c (need to use my alias for that's work)
```bash
cc42 ../ft_putchar.c  
```


---
# Other helpful

### man

* Get limits for variable type:  `man limits.h` or `man stdint.h  `

---
## ToDo

* Find a single line command to print git log without going in a pager
* 
