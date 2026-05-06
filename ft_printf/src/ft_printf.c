/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:56:29 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 15:11:51 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_printf_switch(va_list args, const char *str)
{
	size_t	counter;

	counter = 0;
	if (*str == 'c')
		return (ft_write_fd_char(va_arg(args, int), 1));
	else if (*str == '%')
		return (ft_write_fd_char('%', 1));
	else if (*str == 's')
		return (ft_write_fd_str(va_arg(args, char *), 1));
	else if (*str == 'd' || *str == 'i')
		return (ft_printf_int(args));
	else if (*str == 'u')
		return (ft_writeunbr_fd_recurse(va_arg(args, unsigned int), 1));
	else if (*str == 'x')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), 1, 0));
	else if (*str == 'X')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), 1, 1));
	else if (*str == 'p')
		return (ft_printf_pointer(va_arg(args, void *)));
	else
		return (counter);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_printf_switch(args, str);
			str++;
			continue ;
		}
		count += ft_write_fd_char(*str, 1);
		str++;
	}
	va_end(args);
	return (count);
}
