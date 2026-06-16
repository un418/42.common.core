## TODO



- [ ] Init Readme
- [ ] From eval sheet , to add to my test

> [!WARNING]
> Carry out AT LEAST the following tests to try to stress the error management.  
> - Pass an arbitrary, invalid file descriptor (e.g., 42) to get_next_line. The function must return NULL.
> - Check the error returns for read and malloc. If there is an error, the evaluation stops here. You can keep going and discuss the implementation of the code, but the assignment will not be graded.

- [ ] Add diff tester
	- Compare .txt with .output manage specific case for no exists files
	- Try to reproduce the tests where there is a func call with bad fd and next call with good fd
- [ ] Do Bonus
	Only a fixed size array of pointer to store FD `stash[4096]` 
		justification:
			- fd number are provides by process , it is unlikely that the moulinette or any other programs need to deal with 4096 files in the same run
			- what is the max number of fd by process ?
			  - How to find this number via a linux command ?
	
- [ ] Test with stdin (fd 0)
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
## Static Variable

https://en.wikipedia.org/wiki/Static_variable

##### What is a Static Variable ?
- Static variable are stored in the Data Segment (not in stack)  and **persist between different function call in the same program runs.**

| Local Variable                             | Static Variable                         |
| ------------------------------------------ | --------------------------------------- |
| Local to the function or block             | Local to the function or block          |
| Exists only during function execution      | Exists throughout the program execution |
| Reinitialized each time function is called | Initialized only once                   |
| Stored in the stack                        | Stored in the data segment              |

##### What are the **GOOD** use case of static Variable ? 
* Counter to protect from infinite loop (recursion ...)
* Keep track of bytes previously read in a file, etc

##### What are the **BAD** use case of static Variable ? 
* Have more space to store data because of limitation of the stack -> Use malloc

## Subject 

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

## Testing

## How to open a file

```c
char *file="test0.txt";
int fd = open(file, O_RDONLY);
ft_gnl(fd);
close(fd);
```

## Read file

- The `read` function **keep in memory natively** the last reading position to start from this point at the next run

## Memory Limits 

* Stack is limited to 8MB usually.
	If the Buffer is stored in stack and is too large we reach the famous STACK OVERFLOW 

* Static Variable are in the Data Segment *