/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:26:16 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 13:28:16 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_write_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}

size_t	ft_write_str(va_list args)
{
	char	*str;
	size_t	counter;

	counter = 0;
	str = va_arg(args, char *);
	while (*str)
	{
		write(1, &*str++, 1);
		counter++;
	}
	return (counter);
}
