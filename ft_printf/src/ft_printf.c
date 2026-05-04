/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:56:29 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/04 18:37:28 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Need to check if it is a printable char ? 
static size_t ft_printf_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}

static size_t ft_printf_switch(va_list args, const char *str)
{
	size_t	counter;

	counter = 0;
	
	if (*str == 'c')
		return(ft_printf_char(args));
	else
		return (counter);
}


int	ft_printf(const char *str, ...)
{

	size_t count;

	count = 0;
	va_list args;
	va_start(args, str);

	// read until %
	while (*str)
	{
		if (*str == '%')
		{
			count += ft_printf_switch(args, str);
			str++;
			continue;
		}
		ft_putchar_fd(*str, 1);
		count++;
		str++;
	}
	ft_putchar_fd('\n', 1);
	va_end(args);
	return (count);
}
