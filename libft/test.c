/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/14 13:05:11 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int main(void)
{
	int test_all = 0;

	if (0 || test_all)
	{
		// ft_isalpha()
		printf("--- TEST for ft_isalpha() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalpha(*str));
			str++;
		}
		printf("---------\n");
	}

	if (0 || test_all)
	{
		// ft_isdigit()
		printf("--- TEST for ft_isdigit() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isdigit(*str));
			str++;
		}
		printf("---------\n");
	}

	if (1 || test_all)
	{
		// ft_isalnum()
		printf("--- TEST for ft_isalnum() ---\n");
		char *str = "ajQT09 #/=@-\\~";
		while (*str)
		{
			printf("%c : %d\n",*str,ft_isalnum(*str));
			str++;
		}
		printf("---------\n");
	}
}

