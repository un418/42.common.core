/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ub_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:58:06 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/29 11:26:28 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Test printf with undefinied behavior */

/* The test must be complile without -Werror  */

#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

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



	int ret = printf("test %z");
	printf("ret = %d", ret);


	//test error management
	if (1 || test_all)
	{
		printf("----- ft_printf: WRITE ERROR -------\n\n\n");
		{
			printf("-------------\n");
			ft_printf("test\n");
			int ret = ft_printf(" % ");
			ft_printf("ret = %d\n", ret);
			ft_printf("test\n");
		}
		{
			printf("------here-------\n");
			printf("test\n");
			int ret = printf("toto %   \n");
			printf("ret = %d\n", ret);
			printf("test\n");
		}
		{
			printf("-------------\n");
			printf("test\n");
			int ret = printf("%");
			printf("ret = %d\n", ret);
			printf("test\n");
		}
		{
			printf("--------here-----\n");
			printf("test\n");
			int ret = printf("printf    : %%%% : % ");
			printf("ret = %d\n", ret);
			printf("test\n");
		}
		{
			printf("-------------\n");
			int ret;
			ret = ft_printf("%denis\n",1);
			ft_printf("ret = %d\n", ret);
			ret = ft_printf("%denis\n");
			ft_printf("ret = %d\n", ret);
			ret = printf("%denis\n");
			printf("ret = %d\n", ret);
		}
		{
			// /!\ Edge Case Alert 
			// test % alone
			// If the carac after % is not managed it is just not printed 
			// Should I output an error ? 

			// From the man of printf:
			//	"If a conversion specification is invalid, the behavior is undefined."

			strcpy(err_msg, "test error : % alone");
			fail += ft_check(ft_printf("ft_printf : %%%% :%A E\n\n") == -1, itest++, err_msg);
			// official printf make compilation error in this case (only with flag -Werror)
			fail += ft_check(ft_printf("ft_printf : %%%% :%") == printf("printf    : %%%% :%"), itest++, err_msg);

			// test/test.c:92:35: error: invalid conversion specifier ' ' [-Werror,-Wformat-invalid-specifier]
            //            printf("ft_printf    : %%%% :%z %y  E\n", "");
            //                                        ~~^

			// printf("ft_printf    : %%%% :%z %y  E\n", "");
		}
		
		{
			// backup fd
			printf("------toto-------\n");
			int fd_backup = dup(1);
			strcpy(err_msg, "test ft_printf returns -1 when stdout is invalid");
			close(1);
			fail += ft_check(ft_printf("ft_printf : error % alone : %d\n", 42) == -1, itest++, err_msg);
			printf("\n");
			dprintf(2,"ret = %d\n",ft_printf ("test"));
			dprintf(2,"ret should eqal -1\n\n");
			dprintf(2,"ret = %d\n",printf ("test"));
			dprintf(2,"ret should eqal -1\n\n");
			// restore fd
			dup2(fd_backup, 1);
			close(fd_backup);
		}


}

/* 
RESULT

If we use an undefinied paramater:
	1 - There is warning at compilation time
	2 - Printf write nothing and returns -1
*/