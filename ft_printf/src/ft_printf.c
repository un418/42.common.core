/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:56:29 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/14 17:20:09 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_dprintf_switch(int fd, va_list args, const char *str)
{
	size_t	counter;

	counter = 0;
	if (*str == 'c')
		return (ft_write_fd_char(va_arg(args, int), fd));
	else if (*str == '%')
		return (ft_write_fd_char('%', fd));
	else if (*str == 's')
		return (ft_write_fd_str(va_arg(args, char *), fd));
	else if (*str == 'd' || *str == 'i')
		return (ft_writesnbr_fd(va_arg(args, int), fd));
	else if (*str == 'u')
		return (ft_writeunbr_fd_recurse(va_arg(args, unsigned int), fd));
	else if (*str == 'x')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), fd, 0));
	else if (*str == 'X')
		return (ft_writehex_fd_recurse(va_arg(args, unsigned int), fd, 1));
	else if (*str == 'p')
		return (ft_write_fd_pointer(va_arg(args, void *), fd));
	else
		return (counter);
}

static int	ft_dprintf(int fd, const char *str, va_list args)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_dprintf_switch(fd, args, str);
			str++;
			continue ;
		}
		count += ft_write_fd_char(*str, fd);
		str++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	va_list	args;

	count = 0;
	va_start(args, str);
	count = ft_dprintf(1, str, args);
	va_end(args);
	return (count);
}
