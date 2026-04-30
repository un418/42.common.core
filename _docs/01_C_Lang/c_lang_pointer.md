# Intro

# Terminology

```c
char *ptr_c; // declaration
int *ptr_n;  // declaration of a pointer of named ptr_n of type int

char c;
c = 'A';
int n;
n = 10;

ptr_c = &c; // referencing 
ptr_n = &n; // store the address of var n of type int in var pointer of type int named ptr_n

*ptr_c = 'b'; // dereferencing
*ptr_n = 1; //  store the value 1 of type int at the memory adress stored in ptr_n of type int that have already referenced with the memory address of var n of type int
// In short - store the value 1 in the variable n

```



> [!NOTE] 
> Memo 
```c
int *ptr; //We use * at declaration to indicate that this is a pointer


ptr // After the declaration - without * - A pointer is var that contains an adress memory -> ptr=0x7ffe5367e044
&a // & is the referencing operator -> means: get adress of a var -> &a=0x7ffe67c67554
*ptr = a // * is the dereferencing operator -> means go get the value at the memory adress store at this memory address -> a=10 , *ptr=10


```

# Why do we need pointer ? 

Usually to manipulate data stored in variable from another function.
Because if  a variable is defined in the `main` , it not exist in the `subfonction`.

If we want to manipulate the data of a variable from `main` in a `subfunction`.
A good option is to send the pointer of this variable as an argument (input) of a `subfunction`, then in the `subfunction` we can access the data via `referencing` and store new value by `dereferencing` to pointer passed as argument.

# String


In C Lang, Sting is defined as an array of char.


> [!WARNING] No string() datatypes in C. They are managed by pointers.

```c
// Set string
char *str_ro = "ReadOnly"; // Warning: It's a read-only declaration
char str_rw[10] = "ReadWrite" // Can be modified , usefull in test but Norminette don't authorize this pattern.

str_ro = "LOL"; // ??? Really put the string "LOL" in an array ?
// need to dig into

// end of a string = '\0'


```