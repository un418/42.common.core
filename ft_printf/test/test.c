/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:59:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 14:52:09 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

int ft_check(int check, int i, char *err_msg)
{
	if (check)
	{
		printf("TEST #%d PASS\n\n\n", i);
		return (0);
	}
	else
	{
		printf("TEST #%d FAILED: %s\n\n\n", i, err_msg);
		return (1);
	}

}


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // disable printf buffer
	int test_all = 1;
	int itest = 1;
	int fail = 0;
	char err_msg[100]; 
	// int debug = 1;

	//test char
	if (0 || test_all)
	{
		ft_printf("----- ft_printf: TESTING CHAR -------\n\n\n");
		{
			// test char at EOL
			char c = 'A';
			strcpy(err_msg, "test char at EOL");
			fail += ft_check((ft_printf("ft_printf : %%c : c=%c", c)+ft_printf("\n")) == (ft_printf("printf    : %%c : c=%c", c)+printf("\n")), itest++, err_msg);
		}
		{
			// test char c = '\0'
			char c = '\0';
			strcpy(err_msg, "TEST char = \'\\0\'");
			fail += ft_check(ft_printf("ft_printf : %%c : c=%c\n", c) == printf("printf    : %%c : c=%c\n", c), itest++, err_msg);
		}
		{
			// test empty input
			strcpy(err_msg, "test input with empty string");
			fail += ft_check(ft_printf("") == printf(""), itest++, err_msg);
			ft_printf("\n");

		}
		{
			// test %%
			strcpy(err_msg, "test \%%");
			fail += ft_check(ft_printf("ft_printf : %%%% : %%%%=%%\n") == printf("printf    : %%%% : %%%%=%%\n"), itest++, err_msg);
		}
	}

	//test str
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING STRING -------\n\n\n");
		{
			char *str = "test string alone";
			// test string alone
			strcpy(err_msg, "test string alone");
			fail += ft_check((ft_printf("%s", str)+ft_printf("\n")) == (printf("%s", str)+ft_printf("\n")), itest++, err_msg);
		}
		{
			char *str = "";
			// test string empty alone
			strcpy(err_msg, "test empty string");
			fail += ft_check(ft_printf("%s", str) == printf("%s", str), itest++, err_msg);
		}
		{
			char *str = "";
			// test empty string in middle of input
			strcpy(err_msg, "test empty string in middle of input");
			fail += ft_check(ft_printf("ft_printf : %%s : ""=%s\n", str) == printf("printf    : %%s : ""=%s\n", str), itest++, err_msg);

		}
		{
			char *str = "begin";
			// test string in the beginning of the input
			strcpy(err_msg, "test string in the beginning of the input");
			fail += ft_check(ft_printf("%s ft_printf : %%s :\n", str) == printf("%s printf    : %%s :\n", str), itest++, err_msg);

		}
	}

	//test decimal
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING DECIMAL/INTEGER -------\n\n\n");
		{
			int n = 1234567890;
			// test decimal n = 1234567890
			strcpy(err_msg, "test decimal n = 1234567890");
			fail += ft_check(ft_printf("ft_printf : %%d : 1234567890=%d\n", n) == printf("printf    : %%d : 1234567890=%d\n", n), itest++, err_msg);
		}
		{
			int n = 10;
			// test decimal base limit - n = 10
			strcpy(err_msg, "test decimal base limit - n = 10");
			fail += ft_check(ft_printf("ft_printf : %%d : 10=%d\n", n) == printf("printf    : %%d : 10=%d\n", n), itest++, err_msg);
		}
		{
			int n = INT_MAX;
			// test decimal INT_MAX
			strcpy(err_msg, "test decimal INT_MAX");
			fail += ft_check(ft_printf("ft_printf : %%d : INT_MAX=%d\n", n) == printf("printf    : %%d : INT_MAX=%d\n", n), itest++, err_msg);
		}
		{
			int n = INT_MIN;
			// test decimal INT_MIN
			strcpy(err_msg, "test decimal INT_MIN");
			fail += ft_check(ft_printf("ft_printf : %%d : INT_MIN=%d\n", n) == printf("printf    : %%d : INT_MIN=%d\n", n), itest++, err_msg);
		}
		{
			int n = INT_MAX;
			// test decimal INT_MAX overflow
			strcpy(err_msg, "test decimal INT_MAX overflow");
			fail += ft_check(ft_printf("ft_printf : %%d : INT_MAX+2=%d\n", n + 2) == printf("printf    : %%d : INT_MAX+2=%d\n", n + 2), itest++, err_msg);
		}
	}

	//test unsigned decimal
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING UNSIGNED DECIMAL -------\n\n\n");
		{
			unsigned int un = 1234567890;
			// test unsigned decimal un = 1234567890
			strcpy(err_msg, "test print unsigned decimal un = 1234567890");
			fail += ft_check(ft_printf("ft_printf : %%u : 1234567890=%u\n", un) == printf("printf    : %%u : 1234567890=%u\n", un), itest++, err_msg);
		}
		{
			unsigned int un = UINT_MAX;
			// test unsigned decimal un = UINT_MAX
			strcpy(err_msg, "test print un = UINT_MAX");
			fail += ft_check(ft_printf("ft_printf : %%u : UINT_MAX=%u\n", un) == printf("printf    : %%u : UINT_MAX=%u\n", un), itest++, err_msg);
		}
		{
			unsigned int un = UINT_MAX+1;
			// test unsigned decimal un = UINT_MAX - Unsigned Wrap Around
			strcpy(err_msg, "test print un = UINT_MAX");
			fail += ft_check(ft_printf("ft_printf : %%u : UINT_MAX+1=%u\n", un) == printf("printf    : %%u : UINT_MAX+1=%u\n", un), itest++, err_msg);
		}
	}

	//test hexa
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING HEXADECIMAL-------\n\n\n");
		{
			int n = 10;
			// test hex n = 10
			strcpy(err_msg, "test hex n = 10\n");
			fail += ft_check(ft_printf("ft_printf : %%x : 10=%x\n", n) == printf("printf    : %%x : 10=%x\n",n), itest++, err_msg);
		}
		{
			int n = 16;
			// test hex base limit - n = 16 
			strcpy(err_msg, "test hex base limit - n = 16 \n");
			fail += ft_check(ft_printf("ft_printf : %%x : 16=%x\n", n) == printf("printf    : %%x : 16=%x\n",n), itest++, err_msg);
		}
		{
			int n = 100;
			// test hex n = 100
			strcpy(err_msg, "test hex n = 100\n");
			fail += ft_check(ft_printf("ft_printf : %%x : 100=%x\n", n) == printf("printf    : %%x : 100=%x\n",n), itest++, err_msg);
		}
		{
			int n = 1000;
			// test hex n = 1000
			strcpy(err_msg, "test hex n = 1000\n");
			fail += ft_check(ft_printf("ft_printf : %%x : 1000=%x\n", n) == printf("printf    : %%x : 1000=%x\n",n), itest++, err_msg);
		}
		{
			int n = INT_MAX - 1;
			// test hex n = INT_MAX
			strcpy(err_msg, "test hex n = INT_MAX\n");
			fail += ft_check(ft_printf("ft_printf : %%x : INT_MAX=%x\n", n) == printf("printf    : %%x : INT_MAX=%x\n",n), itest++, err_msg);
		}
		{
			int n = INT_MIN;
			// test hex print n = INT_MIN
			strcpy(err_msg, "test hex print n = INT_MIN\n");
			fail += ft_check(ft_printf("ft_printf : %%x : INT_MIN=%x\n", n) == printf("printf    : %%x : INT_MIN=%x\n",n), itest++, err_msg);
		}
		{
			int n = -10;
			// test hex negative  n = -10
			strcpy(err_msg, "test hex negative  n = -10\n");
			fail += ft_check(ft_printf("ft_printf : %%x : -10=%x\n", n) == printf("printf    : %%x : -10=%x\n",n), itest++, err_msg);
		}
		{
			int n = -10;
			// test hex upper n = -10
			strcpy(err_msg, "test hex upper n = -10/n");
			fail += ft_check(ft_printf("ft_printf : %%X : -10=%X\n", n) == printf("printf    : %%X : -10=%X\n",n), itest++, err_msg);
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
	if (1 || test_all)
	{
			printf("----- ft_printf: TESTING POINTER -------\n\n\n");
		{
			int n = 0;
			int *pn = &n ;
			// test regular pointer
			strcpy(err_msg, "test regular pointer\n");
			fail += ft_check(ft_printf("ft_printf : %%p : %p\n", pn) == printf("printf    : %%p : %p\n", pn), itest++, err_msg);
		}
		{
			int *pn = NULL ;
			// test null pointer
			strcpy(err_msg, "test null pointer\n");
			fail += ft_check(ft_printf("ft_printf : %%p : NULL=%p\n", pn) == printf("printf    : %%p : NULL=%p\n", pn), itest++, err_msg);
		}
		/* 
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
		 */
	}
	
	char *final_msg;
	if (fail)
		final_msg = "FAILURE";
	else
		final_msg = "SUCESS";
	ft_printf("#-# %s = %d/%d #-#\n\n", final_msg, (itest - fail), itest);
}
