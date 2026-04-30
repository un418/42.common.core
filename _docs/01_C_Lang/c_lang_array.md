# Basics
![image info](/zzz_notes/~assets/c-array-declaration.webp)

> [!Waning] 
> Array Size = 5
> Max index = 4 because index begin at 0


# Pointer and array

* https://www.w3schools.com/c/c_pointers_arrays.php

> [!TIP] 
> In C, the **name of an array**, is actually a **pointer** to the **first element** of the array.
```c
#include <stdio.h>
int main() {
  int myNumbers[4] = {25, 50, 75, 100};

  // Get the memory address of the myNumbers array
  printf("%p\n", myNumbers);
  // Return: 0x7fffc5517c70

  // Get the memory address of the first array element
  printf("%p\n", &myNumbers[0]);
  // Return: 0x7fffc5517c70

  return 0;
}
```

# Strings (Array of Char)

> [!CAUTION] 
> Be careful when declaring array
> You must remind to assign one bit more for the `\0` character that symbolize the end of the string
> `char str[9]="123456789";` will not be null terminated
> So the pattern `while (str[i] = '\0')` or `while (str[i])` will never find the end of the string and the program will crash #segfault
> Must be :
> - `char str[10]="123456789";`
> - `char str[]="123456789";`  --> Let the compiler detect the size of the array needed

* String vs array subtility : https://www.sanfoundry.com/c-tutorials-difference-between-character-array-string-literal/
* https://www.geeksforgeeks.org/c/how-to-convert-a-string-to-a-char-array-in-c/
### Octal representation of Char
* https://www.geeksforgeeks.org/c/octal-numbers-c/

# Code Patterns
## Iteration over an array

### For Humans
```c
// usage of index incrementation
char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i]) // eq. while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
```

### Optimized

```c
// directly increment pointer
void ft_putstr(char *str)
{
	/* 
	// Can be usefull to store the starting adress of the array
	char *ptr_start;
	ptr_start = str;
	*/
	while (*str) // eq. while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}
```

### Modifying an array from memory address (aka. pointer)

```c
char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}
```