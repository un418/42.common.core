/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:56:29 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/05 19:49:43 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t ft_printf_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}


static size_t ft_printf_str(va_list args)
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

static size_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd)
{
	size_t counter;

	counter = 0;
	if (ul > 9)
		counter += ft_writeunbr_fd_recurse(ul / 10, fd);
	counter += write(fd, &"0123456789"[ul % 10] , fd);
	return(counter);

}

static size_t	ft_writenbr_fd(long n, int fd)
{
	size_t counter;

	counter = 0;
	if (n < 0)
	{
		counter += write(fd, "-", 1);
		n = -n;
	}
	counter += ft_writeunbr_fd_recurse(n, fd);
	return (counter);
}

static size_t ft_printf_int(va_list args)
{
	int	n;
	size_t	counter;

	counter = 0;
	n = va_arg(args, int);
	counter += ft_writenbr_fd(n,1);
	return (counter);
}

static size_t	ft_writehex_fd_recurse(unsigned int un, int fd, int upper)
{
	size_t counter;
	char *base16;

	counter = 0;
	if (upper)
		base16 = "0123456789ABCDEF";
	else
		base16 = "0123456789abcdef";
	if (un > 15)
		counter += ft_writehex_fd_recurse(un / 16, fd, upper);
	counter += write(fd, &base16[un % 16] , fd);
	return(counter);
}

static size_t ft_printf_switch(va_list args, const char *str)
{
	size_t	counter;

	counter = 0;
	if (*str == 'c')
		return(ft_printf_char(args));
	else if (*str == '%')
		return (write(1, "%", 1));
	else if ( *str == 's')
		return(ft_printf_str(args));
	else if ( *str == 'd' || *str == 'i')
		return(ft_printf_int(args));
	else if ( *str == 'u')
		return(ft_writeunbr_fd_recurse(va_arg(args, unsigned int), 1));
	else if (*str == 'x')
		return(ft_writehex_fd_recurse(va_arg(args,unsigned int), 1, 0));
	else if (*str == 'X')
		return(ft_writehex_fd_recurse(va_arg(args,unsigned int), 1, 1));
	else
		return (counter);
}


int	ft_printf(const char *str, ...)
{
	size_t count;

	count = 0;
	va_list args;
	va_start(args, str);

	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_printf_switch(args, str);
			str++;
			continue;
		}
		ft_putchar_fd(*str, 1);
		count++;
		str++;
	}
	va_end(args);
	return (count);
}
