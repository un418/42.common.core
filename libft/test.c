/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:53:21 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/13 14:25:45 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int main(void)
{

	// ft_isalpha()
	printf("--- TEST for ft_isalpha() ---\n");
	char *str = "ajQT09,.1-]\\~";
	while (*str)
	{
		printf("%c : %d\n",*str,ft_isalpha(*str));
		str++;
	}
	printf("---------\n");
}

