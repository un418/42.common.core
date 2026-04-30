

# Concept

> [!IMPORTANT]
> **Must read**
> https://www.geeksforgeeks.org/c/c-recursion/
> 

## Applications of Recursion

Recursion is widely used to solve different kinds of problems from simple ones like printing linked lists to being extensively used in AI. 
Some of the common uses of recursion are:

- Tree-Graph Algorithms
- Mathematical Problems
- Divide and Conquer
- Dynamic Programming
- In Postfix to Infix Conversion
- **Searching and Sorting Algorithms**

## Advantages of Recursion

- Recursion can effectively reduce the length of the code.
- Some problems are easily solved by using recursion like the tower of Hanoi and tree traversals.
- **Data structures like linked lists, trees, etc. are recursive by nature so recursive methods are easier to implement for these data structures.**

## Disadvantages of Recursion

- Recursive functions make our program a bit slower due to function call overhead.
- Recursion functions always take extra space in the function call stack due to separate stack frames.
- **Recursion methods are difficult to understand and implement.**

# Playground

## Understand Call Stack Order

### Simple

```c
// https://cplayground.com

#include <stdio.h>

void f(int n)
{
    printf("F(%d)'s Stack Frame Pushed\n", n);
    if (n > 1)
    {
        f(n - 1);
    }
    printf("F(%d)'s Stack Frame Removed\n", n);
}

int main()
{
    f(3);
    return 0;
}
```
### Nested

```c
//https://cplayground.com

#include <stdio.h>

void f(int n)
{
    printf("F(%d)'s Stack Frame Pushed\n", n);
    if (n > 1)
    {
        f(n - 1);
        f(n - 1);
    }
    printf("F(%d)'s Stack Frame Removed\n", n);
}

int main()
{
    f(3);
    return 0;
}
```
