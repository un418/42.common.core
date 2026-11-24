
# Debug 

* To understand what do the make file use :`make -n`


# Basics

https://www.gnu.org/software/make/manual/make.html#How-Make-Works

# 42 Norm for Makefile


From : https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf

```
III.11 Makefile
Makefiles aren’t checked by the norminette, and must be checked during evaluation by
the student when asked by the evaluation guidelines. Unless specific instructions, the
following rules apply to the Makefiles:
• The $(NAME), clean, fclean, re and all rules are mandatory. The all rule must be
the default one and executed when typing just make.
• If the makefile relinks when not necessary, the project will be considered non-
functional.
• In the case of a multibinary project, in addition to the above rules, you must have
a rule for each binary (eg: $(NAME_1), $(NAME_2), ...). The “all” rule will
compile all the binaries, using each binary rule.
• In the case of a project that calls a function from a non-system library (e.g.: libft)
that exists along your source code, your makefile must compile this library auto-
matically.
• All source files needed to compile your project must be explicitly named in your
Makefile. Eg: no “*.c”, no “*.o” , etc ...
```


> [!CAUTION]
> Watchout this quote or your Rush is done for nothing

> • If the makefile relinks when not necessary, the project will be considered non-
functional.


## Objects definition via substitution


```
OBJS = $(SRCS:.c=.o)
```

`:.c=.o` -> Means replace every .c by .o

## Q&A

What means relinks ?
https://stackoverflow.com/questions/52502399/what-does-it-mean-for-a-makefile-to-relink



# Variables

## Assignment operators

| Operator | Expanded | Effect |
| --- | --- | --- |
| `:=` | once, when the line is read | value frozen at that point |
| `=` | at every `$(VAR)` | re-evaluated each time, sees later definitions |
| `?=` | at every `$(VAR)` | set only if not already defined (env or command line) |
| `+=` | same as the original variable | appends to the current value |

```make
A  = $(B)
C := $(B)
B  = hello
# $(A) → "hello" : B is read when A is used
# $(C) → ""      : B didn't exist yet when C was set
```

- **Trap with `=`** : `X = $(X) foo` loops forever (error), `$(shell ...)` runs at every use
- **Trap with `?=` in C** : `CC ?= gcc` does nothing, make already defines `CC=cc` → use `CC := gcc`

## Priority

1. **Command line** (`make run CONFIG=x`) : always wins, even over `:=` (unless `override`)
2. **Makefile**
3. **Environment** : only wins with `?=`, since the variable already exists

## Good practices

- `:=` by default, predictable
- `?=` for user knobs : config file, install prefix, port
- `=` only when lazy evaluation is really needed
- UPPERCASE names, grouped at the top of the file

# Rules

- **`.PHONY`** : every rule that doesn't create a file, otherwise a file named `clean` blocks `make clean`
	- top, bottom or above each rule: all work, make reads the whole file first
- **`$(MAKE)`** instead of `make` in a recipe : passes flags like `-k`, `-j`, `-n`
- **`@`** : hides the command, mostly for `echo`, keep it off while debugging
- **Default goal** : the first rule, or `.DEFAULT_GOAL := <rule>`

# Links
- https://www.gnu.org/software/make/manual/make.html#Flavors : `=` vs `:=`
- https://www.gnu.org/software/make/manual/make.html#Conditional-Assignment : `?=`
- https://www.gnu.org/software/make/manual/make.html#Overriding : command line priority
- [[shell_find]]
