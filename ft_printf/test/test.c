/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:59:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/05 19:43:16 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

int ft_check(int check, int i, char *err_msg)
{
	if (check)
	{
		printf("TEST #%d PASS\n", i);
		return (0);
	}
	else
	{
		printf("TEST #%d FAILED: %s\n", i, err_msg);
		return (1);
	}
}


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // disable printf buffer
	int test_all = 0;
	int itest = 1;
	int fail = 0;
	char err_msg[100]; 
	// int debug = 1;

	//test char
	if (1 || test_all)
	{
			printf("----- ft_printf: TESTING CHAR -------\n");
			char c = 'A';
			// test char at EOL
			strcpy(err_msg, "test char at EOL");
			fail += ft_check(ft_printf("01 - test char : %c\n", c) == 19, itest++, err_msg);
			// int ret = printf("test char : %c", c);
			// printf ("%d\n",ret);

			// TEST char = '\0'
			c = '\0';
			strcpy(err_msg, "TEST char = \'\\0\'");
			fail += ft_check(ft_printf("02 -%c\n", c) == 6, itest++, err_msg);

			// TEST empty string
			strcpy(err_msg, "test input with empty string");
			fail += ft_check(ft_printf("") == 0, itest++, err_msg);
			printf("");

			// TEST %%
			strcpy(err_msg, "test \%%");
			fail += ft_check(ft_printf("04 - test %%\n") == 12, itest++, err_msg);
	}


	//test str
	// itest = 0; // reset counter
	if (1 || test_all)
	{
		printf("----- ft_printf: TESTING STRING -------\n");
		{
			char *str = "05 - test string alone";
			// test string alone
			strcpy(err_msg, "test string alone");
			fail += ft_check(ft_printf("%s\n", str) == 23, itest++, err_msg);
		}
		{
			char *str = "";
			// test empty string
			strcpy(err_msg, "test empty string");
			fail += ft_check(ft_printf("06 - %s\n", str) == 6, itest++, err_msg);
		}
		{
			char *str = "";
			// test empty string in middle of input
			strcpy(err_msg, "test empty string in middle of input");
			fail += ft_check(ft_printf("07 - A %s A\n", str) == 10, itest++, err_msg);
		}
		{
			char *str = "begin";
			// test empty string in middle of input
			strcpy(err_msg, "test empty string in middle of input");
			fail += ft_check(ft_printf("%s 08 - end\n", str) == 15, itest++, err_msg);
		}
	}

	//test decimal
	// itest = 0; // reset counter
	if (1 || test_all)
	{
		printf("----- ft_printf: TESTING DECIMAL/INTEGER -------\n");
		{
			int n = 1234567890;
			// test print n = 1234567890
			strcpy(err_msg, "test print regulal decimal n = 1234567890");
			fail += ft_check(ft_printf("09 - %d\n", n) == 16, itest++, err_msg);
		}
		{
			int n = 10;
			// test print n = 10 - base limit
			strcpy(err_msg, "test print regulal decimal n = 10");
			fail += ft_check(ft_printf("09 - %d\n", n) == 12, itest++, err_msg);
		}
		{
			int n = INT_MAX;
			// test print INT_MAX
			strcpy(err_msg, "test print INT_MAX");
			fail += ft_check(ft_printf("10 - %d\n", n) == 8, itest++, err_msg);
		}
		{
			int n = INT_MIN;
			// test print INT_MIN
			strcpy(err_msg, "test print INT_MIN");
			fail += ft_check(ft_printf("11 - %d\n", n) == 17, itest++, err_msg);
		}
		{
			int n = INT_MAX;
			// test print INT_MAX overflow
			strcpy(err_msg, "test print INT_MAX overflow");
			fail += ft_check(ft_printf("12 - %d\n", n + 2) == 17, itest++, err_msg);
			// printf("printf: %d", (int)n + 2);
		}
	}

	//test hexa
	// itest = 0; // reset counter
	if (1 || test_all)
	{
		printf("----- ft_printf: TESTING HEXA-------\n");
		{
			int n = 10;
			// test print n = 10
			strcpy(err_msg, "10hex=%x\n");
			fail += ft_check(ft_printf("ft_printf :10hex=%x\n", n) == printf("printf    :10hex=%x\n",n), itest++, err_msg);
		}
		{
			int n = 16;
			// test print n = 16 - base limit
			strcpy(err_msg, "16hex=%x\n");
			fail += ft_check(ft_printf("ft_printf :16hex=%x\n", n) == printf("printf    :16hex=%x\n",n), itest++, err_msg);
		}
		{
			int n = 100;
			// test print n = 100
			strcpy(err_msg, "100hex=%x\n");
			fail += ft_check(ft_printf("ft_printf :100hex=%x\n", n) == printf("printf    :100hex=%x\n",n), itest++, err_msg);
		}
		{
			int n = 1000;
			// test print n = 1000
			strcpy(err_msg, "1000hex=%x\n");
			fail += ft_check(ft_printf("ft_printf :1000hex=%x\n", n) == printf("printf    :1000hex=%x\n",n), itest++, err_msg);
		}
		{
			int n = INT_MAX - 1;
			// test print n = INT_MAX
			strcpy(err_msg, "INT_MAXhex=%x\n");
			fail += ft_check(ft_printf("ft_printf :INT_MAXhex=%x\n", n) == printf("printf    :INT_MAXhex=%x\n",n), itest++, err_msg);
		}
		{
			int n = INT_MIN;
			// test print n = INT_MIN
			strcpy(err_msg, "INT_MINhex=%x\n");
			fail += ft_check(ft_printf("ft_printf :INT_MINhex=%x\n", n) == printf("printf    :INT_MINhex=%x\n",n), itest++, err_msg);
		}
		{
			int n = -10;
			// test print negative decimal n = -10
			strcpy(err_msg, "-10hex=%x\n");
			fail += ft_check(ft_printf("ft_printf :-10hex=%x\n", n) == printf("printf    :-10hex=%x\n",n), itest++, err_msg);
		}
		{
			int n = -10;
			// test upper n = -10
			strcpy(err_msg, "-10hex=%X\n");
			fail += ft_check(ft_printf("ft_printf :-10hex=%X\n", n) == printf("printf    :-10hex=%X\n",n), itest++, err_msg);
		}
		
		/* 
		{
			// Playground understand hex negative;
			int n = -10;
			printf("%u\n", n);
			printf("%x\n", n);
			printf("%x\n", INT_MIN);
			printf("%x\n", INT_MAX);

			// ffffffff = 4294967295
			printf("LONG_MAX=%ld\n", LONG_MAX);
			printf("UINT_MAX=%u\n", UINT_MAX);
			// need to use unsigned int
		}
		 */
	}

	//test pointer
	// itest = 0; // reset counter
	if (0 || test_all)
	{
			printf("----- ft_printf: TESTING POINTER -------\n");
			if(0)
			{
				// playground to understand pointer behavior
				void *p;
				char c;
				unsigned long n;

				p = &c;
				n = (unsigned long)p;
				printf("%ld\n",n);
				printf("%lu\n",n);
				printf("%lx\n",n);
				printf("%p\n",p);
				printf("sizeof(void*)=%lu\n",sizeof(void*));
				printf("sizeof(long)=%lu\n",sizeof(long));
				// Conclusion:
				// - Memory adress is store as unsigned long
				// - Need to implement numbers and hexadecimal formating before printing pointer adress
			}
	}
}
