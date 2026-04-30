## Execute Shell command inside Vim

`!` is the operator to launch command

* ```vim
  :!./myscript.sh
  ```
 
 https://stackoverflow.com/questions/23097842/how-to-execute-command-inside-vim

## To Sort
- https://devhints.io/vim
- https://github.com/LexouDuck/42/blob/master/.vimrc


```bash
:syntax on
:set number
:set autointdent
:set tabstop=4 :set ts=4
set shiftwidth=4
```

`yy`- yank (copy) a line
`2yy` - yank (copy) 2 lines
`yw` - yank (copy) the characters of the word from the cursor position to the start of the next word

`p` - put (paste) the clipboard after cursor
`P`- put (paste) before cursor


`dd` - delete (cut) a line
`2dd` - delete (cut) 2 lines

`:g/{pattern}/d` - delete all lines containing pattern
`:g!/{pattern}/d` - delete all lines not containing pattern

`d$` or `D `- delete (cut) to the end of the line
`x` - delete (cut) character


`:wq` or `:x` or `ZZ` - write (save) and quit

### Still to sort
`:syntax on`
`:help`
`:help syntax`

To check : https://stackoverflow.com/questions/10274146/vim-line-numbers-how-to-have-them-on-by-default
```
set nu
set ai
set tabstop=4
set ls=2
set shiftwidth=4
```