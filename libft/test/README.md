
# Libft Functions List

A quick reference to help you find the functions you need.

| Function | Description |
| --- | --- |
| **Memory** | |
| `ft_memset` | Fill a block of memory with a specific byte |
| `ft_bzero` | Set a block of memory to zero |
| `ft_memcpy` | Copy a memory area from source to destination |
| `ft_memmove` | Safely copy a memory area (handles overlapping) |
| `ft_memchr` | Scan memory for the first occurrence of a specific byte |
| `ft_memcmp` | Compare two memory areas |
| `ft_calloc` | Allocate memory and set it to zero (safe malloc + bzero) |
| **ASCII / Char checks** | |
| `ft_isalpha` | Check if character is alphabetic |
| `ft_isdigit` | Check if character is a digit (0-9) |
| `ft_isalnum` | Check if character is alphanumeric (number or letter) |
| `ft_isascii` | Check if character fits into the ASCII character set |
| `ft_isprint` | Check if character is printable |
| `ft_toupper` | Convert lowercase letter to uppercase |
| `ft_tolower` | Convert uppercase letter to lowercase |
| **String Manipulation** | |
| `ft_strlen` | Calculate the length of a string |
| `ft_strlcpy` | Size-bounded string copying |
| `ft_strlcat` | Size-bounded string concatenation |
| `ft_strchr` | Locate the first occurrence of a character in a string |
| `ft_strrchr` | Locate the last occurrence of a character in a string |
| `ft_strncmp` | Compare two strings up to `n` characters |
| `ft_strnstr` | Locate a substring in a string with a size limit |
| `ft_strdup` | Duplicate a string (allocates memory) |
| `ft_substr` | Extract a substring from a string |
| `ft_strjoin` | Concatenate two strings into a newly allocated string |
| `ft_strtrim` | Trim specified characters from the beginning and end of a string |
| `ft_split` | Split a string into an array of strings using a delimiter |
| `ft_strmapi` | Apply a function to each character of a string (creates new string) |
| `ft_striteri` | Apply a function to each character of a string (modifies in place) |
| **Conversion** | |
| `ft_atoi` | Convert an ASCII string to an integer (`int`) |
| `ft_itoa` | Convert an integer (`int`) to an ASCII string |
| **File Descriptor (Print)** | |
| `ft_putchar_fd` | Output a character to a given file descriptor |
| `ft_putstr_fd` | Output a string to a given file descriptor |
| `ft_putendl_fd` | Output a string followed by a newline to a given file descriptor |
| `ft_putnbr_fd` | Output an integer to a given file descriptor |
| **Linked Lists** | |
| `ft_lstnew` | Create a new list node |
| `ft_lstadd_front`| Add a new node to the beginning of a list |
| `ft_lstsize` | Count the number of nodes in a list |
| `ft_lstlast` | Get the last node of a list |
| `ft_lstadd_back` | Add a new node to the end of a list |
| `ft_lstdelone` | Delete and free a single list node |
| `ft_lstclear` | Delete and free a sequence of list nodes |
| `ft_lstiter` | Apply a function to the content of all list nodes |
| `ft_lstmap` | Apply a function to a list to create a new list |
