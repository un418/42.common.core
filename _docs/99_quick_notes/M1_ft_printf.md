
# Todo

- [x]  NOT DONE Improve counter by using one function to write a char and a static variable
- [x] Improve logic when writing number by using a base wrinting function ( avoid code repetion for hexa upper and lower )
- [x] Add color to test
- [x] automate test by comparing the output from my function and the official one
- [x] add file descriptor management for my printf
- [x] add test prefix in diff output file and move them to test folder
- [x] Go Deeper inside the EDGE CASE //return -1 like printf
- [x] Verify the check error compliance
	- [x] https://42-cursus.gitbook.io/guide/1-rank-01/ft_printf
	- [x] How to test it ? 
- [x] Check about printf(NULL)
	- https://42born2code.slack.com/archives/C033QK0NPQA/p1779456719311929
	- It is undefined behavior to dereference a NULL pointer , basic undefined behavior
	
- [x] Finish readme
- [x] Clean MakeFile
- [x]  Refactor headers : split `ft_printf.h` (public, only `ft_printf`) and `ft_printf_private.h` (internal helpers)
- [x] finir implem vprintf + dprintf
- [x] Do deeper final tests 
- [x] Last subject Reading
- [ ] isolated test from evaluated part
- [ ] improve header isolation logic
# Q&A
### What is a variadic function ?

* a function that can take a variable name of argument ( usefull when the number of argument is unknow)
	* it need a least one fixed argument, and then any number of variable argument
* https://www.geeksforgeeks.org/c/variadic-functions-in-c/


### What happen if we send wrong data type to printf ? 

```c
int main(void){
	char c = 'A';
	//printf("test char : %c\n", c);
	printf("test char : %c\n", &c); 
}
```

The compiler return a `type error` 

```bash
test.c:28:30: error: format specifies type 'int' but the argument has type 'char *' [-Werror,-Wformat]
   28 |                 printf("test char : %c\n", &c);
      |                                     ~~     ^~
      |                                     %s
1 error generated.
```

Result : 
* We **don't need** to manage this kind of error in the project
* Just try to cast and let the compiler return error when casing wrong type

## Variadic Function

#todo

## Static Variable

Variable that retain value across function call
- can be used in recursion to manage recursion depth and avoid infinite recursion loop
- can be used for printf to mange the counter of character written.

https://www.geeksforgeeks.org/c/static-variables-in-c/

## Lookup table

- https://stackoverflow.com/questions/3408504/whats-the-best-way-to-do-a-lookup-table-in-c

```c
// Usefull when we need to translate data
char *displayDigitInletter[] = {
  "zero", "one", "two", "three", "four", "five", "..."
};
printf("%s",displayDigitInletter[4]);
```

Trick used for base print and translation
```c
// Here we use also a lookup table
write(fd, &"0123456789abcdef"[un % 16] , fd);
// Let's understand the tricks via this example
char base16[] = "0123456789abcdef";
"0123456789abcdef"[un % 16] == base16[un % 16];
// It allow to avoid the need of array declaration
```

