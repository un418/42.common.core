/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:59:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/04 19:57:22 by adaferna         ###   ########.fr       */
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
			fail += ft_check(ft_printf("test char : %c", c) == 13, itest++, err_msg);
			// int ret = printf("test char : %c", c);
			// printf ("%d\n",ret);

			// TEST char = '\0'
			c = '\0';
			strcpy(err_msg, "TEST char = \'\0\'");
			fail += ft_check(ft_printf("%c\n", c) == 2, itest++, err_msg);
			// int ret = printf("%c\n", c);
			// printf ("%d\n",ret);

			// TEST empty string
			strcpy(err_msg, "test input with empty string");
			fail += ft_check(ft_printf("") == 0, itest++, err_msg);
			printf("");
	}
}
