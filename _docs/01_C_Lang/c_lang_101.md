# Terminology


![image info](/zzz_notes/~assets/c_lang_101_terminology.png)

# Variables
## C Data Types: The Master Reference

| Category           | Type             | Size (Bytes) | Size (Bits) | **Power of 2 Calculation** | Exact Range (Signed or Unsigned) |
| ------------------ | ---------------- | ------------ | ----------- | -------------------------- | -------------------------------- |
| **Character**      | `char`           | 1            | 8           | 28                         | −128 to 127                      |
|                    | `unsigned char`  | 1            | 8           | 28                         | 0 to 255                         |
| **Integer**        | `short`          | 2            | 16          | 216                        | −32,768 to 32,767                |
|                    | `unsigned short` | 2            | 16          | 216                        | 0 to 65,535                      |
|                    | `int`            | 4            | 32          | 232                        | −2,147,483,648 to 2,147,483,647  |
|                    | `unsigned int`   | 4            | 32          | 232                        | 0 to 4,294,967,295               |
|                    | `long`           | 8            | 64          | 264                        | −263 to 263−1                    |
|                    | `unsigned long`  | 8            | 64          | 264                        | 0 to 264−1                       |
| **Floating Point** | `float`          | 4            | 32          | 232 (encoded)              | ≈±3.4×1038                       |
|                    | `double`         | 8            | 64          | 264 (encoded)              | ≈±1.7×10308                      |
## Char
* https://www.geeksforgeeks.org/c/c-ascii-value/#why-are-ascii-values-needed-in-c
* ASCII Table : https://www.ascii-code.com/


## Variables TypeCasting

Char is a good example for that.
* https://www.cprogramming.com/tutorial/c/lesson11.html
>   The (char) is a typecast, telling the computer to interpret the 65 as a
 >   character, not as a number.  It is going to give the character output of 
 >   the equivalent of the number 65 (It should be the letter A for ASCII).
>   Note that the %c below is the format code for printing a single character

* https://www.geeksforgeeks.org/c/c-typecasting/

## int
### Convert an `int` in `char`

* https://stackoverflow.com/questions/2279379/how-to-convert-integer-to-char-in-c
* https://www.geeksforgeeks.org/c/c-program-for-int-to-char-conversion/

```c
	int c = 3;
	c = i +'0';  
	// We assign at the ascii value of '0' (that is 48) and add 3 to it
	// So c = 51 taht in ascii is '3'
	printf("debug:%c",c); // %c means print as char (convert via ascii table)
	// output '3'
	printf("%d"`,c); // %d means print as int
	// output 51 // The ascii representation of '3'
	
```

### Print an int

```c
void ft_nbrtochar(unsigned int nb)
{
	char c = '0' + nb;
	char c = 48 + nb; // 48 is ascci value for '0'
	
	write(1 , &c, 1);
	
	write(1, &"0123456789"[number], 1);
	// via Lookup Table
	// String Literal as Array: The string "0123456789" is treated as a constant array of characters.
	// Indexing: The `[number]` part accesses a specific character in that array (e.g., if `number` is 5, it selects '5').
	// Address-of Operator The & symbol retrieves the **memory address** of that specific character.
}
```


# Conditions

### Logic operator
`&&` : AND
`||` : OR
`()` : Grouping result of condition to compare to another

```c



```

### Yoda Condition
Can be simpler to understand a condition.
