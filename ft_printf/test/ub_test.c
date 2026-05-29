/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ub_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:58:06 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/29 15:22:42 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Test ft_printf against undefined behavior  */
/* /!\ Must be compiled WITHOUT -Werror (use `make test_ub`) */

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ft_printf.h"

/* Standard Colors */
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define RESET   "\033[0m"

int ft_check(int check, int i, char *err_msg)
{
	if (check)
	{
		printf(GREEN); printf("\nTEST #%d PASS", i); printf(RESET);
		printf("\n\n\n");
		return (0);
	}
	else
	{
		printf(RED);printf("\nTEST #%d FAILED: ", i);printf(RESET);
		printf("%s\n\n\n", err_msg);
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

	//test invalid conversion specifier
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING INVALID SPECIFIER -------\n\n\n");
		{	
			//   - ft_printf stops at the unknown specifier and returns -1
			//   - on macOS prints the character literally and keeps going, to test on linux glibc
			int ret;
			int ref;
			strcpy(err_msg, "test unknown specifier %k returns -1");
			ret = ft_printf("ft_printf : unknown %k spec"); ft_printf("\n");
			ref = printf("printf    : unknown %k spec"); printf("\n");
			printf("ret: ft_printf = %d | printf = %d\n", ret, ref);
			fail += ft_check(ret == -1, itest++, err_msg);
		}
		{
			// lone % at the end of the string is undefined: ft_printf returns -1
			// to test with official printf
			int ret;
			int ref;
			strcpy(err_msg, "test lone %% at end returns -1");
			ret = ft_printf("ft_printf : %%%% :%"); ft_printf("\n");
			ref = printf("printf    : %%%% :%"); printf("\n");
			printf("ret: ft_printf = %d | printf = %d\n", ret, ref);
			fail += ft_check(ret == -1, itest++, err_msg);
		}
		{
			// percent-space "% " is an incomplete specifier: ft_printf returns -1
			// to test with official printf
			int ret;
			int ref;
			strcpy(err_msg, "test percent-space returns -1");
			ret = ft_printf("ft_printf : %%%% : % "); ft_printf("\n");
			ref = printf("printf    : %%%% : % "); printf("\n");
			printf("ret: ft_printf = %d | printf = %d\n", ret, ref);
			fail += ft_check(ret == -1, itest++, err_msg);
		}
		{
			// valid specifier glued to text: %d keeps printing "enis"
			int n = 1;
			int ret;
			int ref;
			strcpy(err_msg, "test %d glued to text");
			ret = ft_printf("ft_printf : %denis\n", n);
			ref = printf("printf    : %denis\n", n);
			printf("ret: ft_printf = %d | printf = %d\n", ret, ref);
			fail += ft_check(ret == ref, itest++, err_msg);
		}
	}

	//test write error
	if (0 || test_all)
	{
		printf("----- ft_printf: TESTING WRITE ERROR -------\n\n\n");
		{
			// when stdout is closed the write() fails: 
			// both ft_printf and the system printf return -1
			int fd_backup = dup(FT_STDOUT);
			int ret;
			int ref;

			close(FT_STDOUT);
			ret = ft_printf("ft_printf : write error : %d\n", 42);
			ref = printf("printf    : write error : %d\n", 42);
			dup2(fd_backup, FT_STDOUT);
			close(fd_backup);
			clearerr(stdout); // reset stdio error flag set by the failed printf
			printf("ret: ft_printf = %d | printf = %d\n", ret, ref);
			strcpy(err_msg, "test ft_printf returns -1 when stdout is invalid");
			fail += ft_check(ret == -1, itest++, err_msg);
		}
	}

	printf("########## ft_printf: RESULT ##########\n\n");
	char *final_msg;
	if (fail)
		final_msg = "FAILURE";
	else
		final_msg = "SUCESS";
	ft_printf("#-# %s = %d/%d #-#\n\n", final_msg, (itest - fail), itest);
}
