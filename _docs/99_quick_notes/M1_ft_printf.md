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
	