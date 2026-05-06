/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:34:05 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/06 16:38:19 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd)
{
	size_t	counter;

	counter = 0;
	if (ul > 9)
		counter += ft_writeunbr_fd_recurse(ul / 10, fd);
	counter += write(fd, &"0123456789"[ul % 10], fd);
	return (counter);
}

size_t	ft_writesnbr_fd(long n, int fd)
{
	size_t	counter;

	counter = 0;
	if (n < 0)
	{
		counter += write(fd, "-", 1);
		n = -n;
	}
	counter += ft_writeunbr_fd_recurse(n, fd);
	return (counter);
}

size_t	ft_writehex_fd_recurse(unsigned long un, int fd, int upper)
{
	size_t	counter;
	char	*base16;

	counter = 0;
	if (upper)
		base16 = "0123456789ABCDEF";
	else
		base16 = "0123456789abcdef";
	if (un > 15)
		counter += ft_writehex_fd_recurse(un / 16, fd, upper);
	counter += write(fd, &base16[un % 16], fd);
	return (counter);
}

size_t	ft_write_fd_pointer(void *p, int fd)
{
	size_t	counter;

	counter = 0;
	if (p == NULL)
		return (write(fd, "(nil)", 5));
	counter += write(fd, "0x", 2);
	counter += ft_writehex_fd_recurse((unsigned long)p, fd, 0);
	return (counter);
}
