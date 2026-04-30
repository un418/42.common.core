
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


