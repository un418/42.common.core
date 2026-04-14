/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 17:47:23 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int main(void)
{
	int test_all = 0;

	// ft_isalpha()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isalpha() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalpha(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isdigit()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isdigit() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isdigit(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isalnum()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isalnum() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalnum(*str));
			str++;
		}
		printf("---------\n");
	}

	// ft_isascii()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isascii() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isascii(*str));
			str++;
		}
		printf("%d : %d\n",-8,ft_isascii(-8));
		printf("---------\n");
	}

	// ft_isprint()
	if (0 || test_all)
	{
		printf("--- TEST for ft_isprint() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isprint(*str));
			str++;
		}
		printf("%d : %d\n",-8,ft_isprint(-8));
		printf("TAB : %d\n",ft_isprint('	'));
		printf("NULL : %d\n",ft_isprint(0));
		printf("---------\n");
	}

	// ft_strlen()
	if (0 || test_all)
	{
		printf("--- TEST for ft_strlen() ---\n");
		char *str[] = {"ajQT09 #/=@-\\~", "", "	 ", "test", NULL };
		int i = 0;
		while (str[i])
		{
			printf("%s : len =%zu\n",str[i],ft_strlen(str[i]));
			i++;
		}
		printf("---------\n");
		printf("TEST PRINT TAB via printf: %c ; %d\n",9,'	');
		printf("---------\n");

	}

	// ft_memset()
	if (1 || test_all)
	{
		printf("--- TEST for ft_memset() ---\n");
		char str[] = "coucou";
		printf("before:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		ft_memset(str,45,ft_strlen(str));
		printf("after:%s \n",str);
		printf("sizeof str[i]=%zu\n",ft_strlen(str));
		printf("---------\n");
	}
}
