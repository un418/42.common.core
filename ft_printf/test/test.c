/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:59:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/05 16:08:42 by adaferna         ###   ########.fr       */
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
			int n = 123456;
			// test print regulal decimal n = 123456
			strcpy(err_msg, "test print regulal decimal n = 123456");
			fail += ft_check(ft_printf("09 - %d\n", n) == 12, itest++, err_msg);
			printf("test dec=%d\n",ft_printf("%d\n", 123456));
		}
		{
			int n = INT_MAX;
			// test print INT_MAX
			strcpy(err_msg, "test print INT_MAX");
			fail += ft_check(ft_printf("10 - %d\n", n) == 16, itest++, err_msg);
		}
		{
			int n = INT_MIN;
			// test print INT_MIN
			strcpy(err_msg, "test print INT_MIN");
			fail += ft_check(ft_printf("11 - %d\n", n) == 17, itest++, err_msg);
		}
		{
			long n = INT_MAX;
			// test print INT_MAX overflow
			strcpy(err_msg, "test print INT_MAX overflow");
			fail += ft_check(ft_printf("12 - %d\n", n + 2) == 17, itest++, err_msg);
			// printf("printf: %d", (int)n + 2);
		}
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
