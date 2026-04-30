/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:59:58 by adaferna          #+#    #+#             */
/*   Updated: 2026/04/30 20:14:45 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int test_all = 0;
	int debug = 1;

	//test char
	if (1 || test_all)
	{
		char c = 'A';
		ft_prinft("test char : %c", c);
		prinft("test char : %c\n", c);
		// ft_prinft("test char : %c\n", &c);
		prinft("test char : %c\n", &c);
	}
}
