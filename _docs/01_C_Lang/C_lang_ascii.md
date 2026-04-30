# Playground

```c
#include <unistd.h>

void ft_putnbr(int nb)
{
	// char c = '0' + nb; 
	char c = 48 + nb; // Same
	write(1 , &c, 1);
}


#include <stdio.h>
int main(void)
{
	int number = -1;
	ft_putnbr(number);
	return 0;
}

```


