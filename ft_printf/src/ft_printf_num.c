/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaferna <adaferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:34:05 by adaferna          #+#    #+#             */
/*   Updated: 2026/05/20 16:20:43 by adaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"

ssize_t	ft_writeunbr_fd_recurse(unsigned long ul, int fd)
{
	ssize_t	counter;
	ssize_t	ret;

	counter = 0;
	if (ul > 9)
	{
		ret = ft_writeunbr_fd_recurse(ul / 10, fd);
		if (ret == -1)
			return (-1);
		counter += ret;
	}
	ret = write(fd, &"0123456789"[ul % 10], 1);
	if (ret == -1)
		return (-1);
	counter += ret;
	return (counter);
}

ssize_t	ft_writesnbr_fd(long n, int fd)
{
	ssize_t	counter;
	ssize_t	ret;

	counter = 0;
	if (n < 0)
	{
		ret = write(fd, "-", 1);
		if (ret == -1)
			return (-1);
		counter += ret;
		n = -n;
	}
	ret = ft_writeunbr_fd_recurse(n, fd);
	if (ret == -1)
		return (-1);
	counter += ret;
	return (counter);
}

ssize_t	ft_writehex_fd_recurse(unsigned long un, int fd, int upper)
{
	ssize_t	counter;
	ssize_t	ret;
	char	*base16;

	counter = 0;
	if (upper)
		base16 = "0123456789ABCDEF";
	else
		base16 = "0123456789abcdef";
	if (un > 15)
	{
		ret = ft_writehex_fd_recurse(un / 16, fd, upper);
		if (ret == -1)
			return (-1);
		counter += ret;
	}
	ret = write(fd, &base16[un % 16], 1);
	if (ret == -1)
		return (-1);
	counter += ret;
	return (counter);
}

ssize_t	ft_write_fd_pointer(void *p, int fd)
{
	ssize_t	counter;
	ssize_t	ret;

	counter = 0;
	if (p == NULL)
		return (write(fd, "(nil)", 5));
	ret = write(fd, "0x", 2);
	if (ret == -1)
		return (-1);
	counter += ret;
	ret = ft_writehex_fd_recurse((unsigned long)p, fd, 0);
	if (ret == -1)
		return (-1);
	counter += ret;
	return (counter);
}
