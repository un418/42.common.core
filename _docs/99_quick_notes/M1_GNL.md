
## First reading

### Buffer Managememnt
`-D BUFFER_SIZE=n` : Refers to Macro Definition to set the buffer 

```bash
#example
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
```

Using Macro allows to change the size of the buffer at compilation time, and avoid using variable sized array that are not allowed by the 42Norm

```c
#define BUFFER_SIZE 100

// Buffer size declaration
char buffer[BUFFER_SIZE];

```

https://www.geeksforgeeks.org/c/macros-and-its-types-in-c-cpp/
### Static Variable

https://en.wikipedia.org/wiki/Static_variable

##### What is a Static Variable ?

##### What are the **GOOD** use case of static Variable ? 

##### What are the **BAD** use case of static Variable ? 

# Subject 

> [!TIPS] Tips from the Subject
> When writing your tests, remember that: 
> 1) Both the buffer size and the line size can be of very different values. 
> 2) A file descriptor does not only point to regular files. Be thorough and cross-check your work with your peers. 
> Prepare a comprehensive set of diverse tests for the defense.


- Repeated calls (e.g., using a loop) to your get_next_line() function should let you read the text file pointed to by the file descriptor, one line at a time.
	- Means we should keep in memory whats have been read between function calls. (Static Variable)
- Your function should return the line that was read. If there is nothing left to read or if an error occurs, it should return NULL.
	-  Remember that it can have still things in the buffer when read functions have finish to read the file
- Make sure that your function works as expected both when reading a file and when **reading from the standard input.**
	- How it works ? How to test ? 


> [!WARNING] 
> Does your function still work if the BUFFER_SIZE value is 9999? If it is 1? 10000000? Do you know why?


> [!TIPS] 
> Try to read as little as possible each time get_next_line() is called. 
> If you encounter a new line, you have to return the current line. 
> Don’t read the whole file and then process each line.

### Edge case

- File with wrong permisssion
- File not exist
- Empty file
- Malformated or Binary Files

